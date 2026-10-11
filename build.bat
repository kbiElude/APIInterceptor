@echo off

rem ============================================================
rem  build.bat
rem
rem  Builds APIInterceptor for both x86 and x64, then collects
rem  all runtime outputs into build_final\.
rem
rem  Usage:
rem    build.bat [mode] [--debug]
rem
rem  Modes (at most one; default is incremental):
rem    --from-scratch  Wipe build directory contents, configure,
rem                    then build.
rem    --clean         Wipe build directory contents only;
rem                    do not build.
rem
rem  Options:
rem    --debug         Build Debug configuration (default: Release).
rem ============================================================

setlocal

set SCRIPT_DIR=%~dp0
rem %~dp0 always carries a trailing backslash. Strip it so that quoting
rem "%SCRIPT_DIR%" later does not produce a \" sequence that the C runtime
rem misreads as an escaped quote, which causes CMake to warn about an
rem extra source-directory argument.
if "%SCRIPT_DIR:~-1%"=="\" set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

set BUILD_X86_DIR=%SCRIPT_DIR%\build_x86
set BUILD_X64_DIR=%SCRIPT_DIR%\build_x64
set BUILD_FINAL_DIR=%SCRIPT_DIR%\build_final
set CMAKE_GENERATOR=Visual Studio 18 2026
set BUILD_CONFIG=Release
set MODE=incremental

rem --- Argument parsing -----------------------------------------

:parse_next_arg
if "%~1"=="" goto args_done

if /i "%~1"=="--from-scratch" (
    set MODE=from-scratch
    shift
    goto parse_next_arg
)
if /i "%~1"=="--clean" (
    set MODE=clean
    shift
    goto parse_next_arg
)
if /i "%~1"=="--debug" (
    set BUILD_CONFIG=Debug
    shift
    goto parse_next_arg
)

echo [!] Unrecognised argument: %~1
echo     Valid arguments: --from-scratch, --clean, --debug
exit /b 1

:args_done

rem --- Mode dispatch --------------------------------------------

if "%MODE%"=="clean"        goto do_clean
if "%MODE%"=="from-scratch" goto do_from_scratch
goto do_incremental

rem ============================================================
rem  CLEAN  --  wipe build directory contents only, no build
rem ============================================================

:do_clean
echo [*] Cleaning build_x86...
call :empty_directory "%BUILD_X86_DIR%"
if %errorlevel% neq 0 exit /b 1

echo [*] Cleaning build_x64...
call :empty_directory "%BUILD_X64_DIR%"
if %errorlevel% neq 0 exit /b 1

echo [*] Clean complete.
goto end

rem ============================================================
rem  FROM SCRATCH  --  wipe, configure, then build
rem ============================================================

:do_from_scratch
echo [*] From-scratch build -- cleaning first...

call :empty_directory "%BUILD_X86_DIR%"
if %errorlevel% neq 0 exit /b 1

call :empty_directory "%BUILD_X64_DIR%"
if %errorlevel% neq 0 exit /b 1

goto configure_both

rem ============================================================
rem  INCREMENTAL  --  configure only when cache is absent, then build
rem ============================================================

:do_incremental
if not exist "%BUILD_X86_DIR%\CMakeCache.txt" (
    echo [*] build_x86: no cache found -- configuring...
    call :configure_x86
    if %errorlevel% neq 0 exit /b 1
) else (
    echo [*] build_x86: cache found -- skipping configure.
)

if not exist "%BUILD_X64_DIR%\CMakeCache.txt" (
    echo [*] build_x64: no cache found -- configuring...
    call :configure_x64
    if %errorlevel% neq 0 exit /b 1
) else (
    echo [*] build_x64: cache found -- skipping configure.
)

goto build_both

rem ============================================================
rem  CONFIGURE BOTH  (reached from --from-scratch path only)
rem ============================================================

:configure_both
echo [*] Configuring x86...
call :configure_x86
if %errorlevel% neq 0 exit /b 1

echo [*] Configuring x64...
call :configure_x64
if %errorlevel% neq 0 exit /b 1

rem ============================================================
rem  BUILD BOTH
rem ============================================================

:build_both
echo [*] Building x86 (%BUILD_CONFIG%)...
cmake --build "%BUILD_X86_DIR%" --config %BUILD_CONFIG%
if %errorlevel% neq 0 (
    echo [!] x86 build failed.
    exit /b 1
)

echo [*] Building x64 (%BUILD_CONFIG%)...
cmake --build "%BUILD_X64_DIR%" --config %BUILD_CONFIG%
if %errorlevel% neq 0 (
    echo [!] x64 build failed.
    exit /b 1
)

call :collect_binaries
if %errorlevel% neq 0 exit /b 1

goto end

rem ============================================================
rem  SUBROUTINES
rem ============================================================

rem --- :configure_x86 ------------------------------------------
rem  Runs CMake configure for the x86 build tree.
rem  Tests are disabled: the test runner is x64-only.

:configure_x86
cmake -B "%BUILD_X86_DIR%"           ^
      -G "%CMAKE_GENERATOR%"         ^
      -A Win32                       ^
      -DAPIINTERCEPTOR_BUILD_TESTS=OFF ^
      "%SCRIPT_DIR%"
exit /b %errorlevel%

rem --- :configure_x64 ------------------------------------------
rem  Runs CMake configure for the x64 build tree.

:configure_x64
cmake -B "%BUILD_X64_DIR%" ^
      -G "%CMAKE_GENERATOR%" ^
      -A x64                 ^
      "%SCRIPT_DIR%"
exit /b %errorlevel%

rem --- :collect_binaries ----------------------------------------
rem  Copies runtime outputs from both build trees into build_final\.
rem  APIDumperDLL.dll and APIDumper.exe are renamed to distinguish architectures:
rem    build_x64\bin\<Config>\APIDumperDLL.dll -> build_final\APIDumperDLL_x64.dll
rem    build_x86\bin\<Config>\APIDumperDLL.dll -> build_final\APIDumperDLL_x86.dll
rem    build_x64\bin\<Config>\APIDumper.exe    -> build_final\APIDumper_x64.exe
rem    build_x86\bin\<Config>\APIDumper.exe    -> build_final\APIDumper_x86.exe
rem  All other x64 outputs (incl. APIDumpPrinter.exe, which reads dumps from
rem  either architecture) are copied as-is.

:collect_binaries
echo [*] Collecting binaries into build_final\...

if not exist "%BUILD_FINAL_DIR%" mkdir "%BUILD_FINAL_DIR%"

rem Copy all x64 runtime outputs.
xcopy /y /q "%BUILD_X64_DIR%\bin\%BUILD_CONFIG%\*" "%BUILD_FINAL_DIR%\" >nul
if %errorlevel% neq 0 (
    echo [!] Failed to copy x64 binaries from build_x64\bin\%BUILD_CONFIG%\.
    exit /b 1
)

rem Rename the x64 interceptor DLL that was just copied.
if exist "%BUILD_FINAL_DIR%\APIDumperDLL.dll" (
    del /q "%BUILD_FINAL_DIR%\APIDumperDLL_x64.dll" >nul 2>&1
    rename "%BUILD_FINAL_DIR%\APIDumperDLL.dll" "APIDumperDLL_x64.dll"
    if %errorlevel% neq 0 (
        echo [!] Failed to rename APIDumperDLL.dll to APIDumperDLL_x64.dll.
        exit /b 1
    )
)

rem Rename the x64 launcher that was just copied.
if exist "%BUILD_FINAL_DIR%\APIDumper.exe" (
    del /q "%BUILD_FINAL_DIR%\APIDumper_x64.exe" >nul 2>&1
    rename "%BUILD_FINAL_DIR%\APIDumper.exe" "APIDumper_x64.exe"
    if %errorlevel% neq 0 (
        echo [!] Failed to rename APIDumper.exe to APIDumper_x64.exe.
        exit /b 1
    )
)

rem Copy the x86 launcher.
if not exist "%BUILD_X86_DIR%\bin\%BUILD_CONFIG%\APIDumper.exe" (
    echo [!] x86 APIDumper.exe not found at build_x86\bin\%BUILD_CONFIG%\APIDumper.exe.
    exit /b 1
)
copy /y "%BUILD_X86_DIR%\bin\%BUILD_CONFIG%\APIDumper.exe" "%BUILD_FINAL_DIR%\APIDumper_x86.exe" >nul
if %errorlevel% neq 0 (
    echo [!] Failed to copy x86 APIDumper.exe to build_final\APIDumper_x86.exe.
    exit /b 1
)

rem Copy the x86 interceptor DLL.
if not exist "%BUILD_X86_DIR%\bin\%BUILD_CONFIG%\APIDumperDLL.dll" (
    echo [!] x86 APIDumperDLL.dll not found at build_x86\bin\%BUILD_CONFIG%\APIDumperDLL.dll.
    exit /b 1
)
copy /y "%BUILD_X86_DIR%\bin\%BUILD_CONFIG%\APIDumperDLL.dll" "%BUILD_FINAL_DIR%\APIDumperDLL_x86.dll" >nul
if %errorlevel% neq 0 (
    echo [!] Failed to copy x86 APIDumperDLL.dll to build_final\APIDumperDLL_x86.dll.
    exit /b 1
)

echo [*] Binaries are ready in: %BUILD_FINAL_DIR%
exit /b 0

rem --- :empty_directory -----------------------------------------
rem  Removes all files and subdirectories inside %~1 without
rem  removing %~1 itself. Creates %~1 if it does not exist.

:empty_directory
if not exist "%~1\" (
    mkdir "%~1"
    exit /b 0
)
del /f /s /q "%~1\*" >nul 2>&1
for /d %%D in ("%~1\*") do rd /s /q "%%D" 2>nul
exit /b 0

rem ============================================================

:end
echo [*] Done.
endlocal
