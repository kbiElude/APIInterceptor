@echo off

rem ============================================================
rem  build.bat
rem
rem  Builds APIInterceptor for both x86 and x64, then installs both
rem  into build_final\ (cmake\Install.cmake says what goes where).
rem
rem  Usage:
rem    build.bat [mode] [--debug] [--source-dir <dir>]
rem
rem  Modes (at most one; default is incremental):
rem    --from-scratch  Wipe build directory contents, configure,
rem                    then build.
rem    --clean         Wipe build directory contents only;
rem                    do not build.
rem
rem  Options:
rem    --debug         Build Debug configuration (default: Release).
rem    --source-dir    Build the CMake project in <dir> instead of this one
rem                    (a project which has this one as a submodule uses
rem                    this script as its own); the build trees and
rem                    build_final\ are made in <dir>.
rem ============================================================

setlocal

set SCRIPT_DIR=%~dp0
rem %~dp0 always carries a trailing backslash. Strip it so that quoting
rem "%SCRIPT_DIR%" later does not produce a \" sequence that the C runtime
rem misreads as an escaped quote, which causes CMake to warn about an
rem extra source-directory argument.
if "%SCRIPT_DIR:~-1%"=="\" set SCRIPT_DIR=%SCRIPT_DIR:~0,-1%

set SOURCE_DIR=%SCRIPT_DIR%
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
if /i "%~1"=="--source-dir" (
    if "%~2"=="" (
        echo [!] --source-dir needs a directory.
        exit /b 1
    )
    set SOURCE_DIR=%~f2
    shift
    shift
    goto parse_next_arg
)

echo [!] Unrecognised argument: %~1
echo     Valid arguments: --from-scratch, --clean, --debug, --source-dir ^<dir^>
exit /b 1

:args_done

if "%SOURCE_DIR:~-1%"=="\" set SOURCE_DIR=%SOURCE_DIR:~0,-1%

set BUILD_X86_DIR=%SOURCE_DIR%\build_x86
set BUILD_X64_DIR=%SOURCE_DIR%\build_x64
set BUILD_FINAL_DIR=%SOURCE_DIR%\build_final

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
      "%SOURCE_DIR%"
exit /b %errorlevel%

rem --- :configure_x64 ------------------------------------------
rem  Runs CMake configure for the x64 build tree.

:configure_x64
cmake -B "%BUILD_X64_DIR%" ^
      -G "%CMAKE_GENERATOR%" ^
      -A x64                 ^
      "%SOURCE_DIR%"
exit /b %errorlevel%

rem --- :collect_binaries ----------------------------------------
rem  Empties build_final\, then installs both build trees into it, so that the
rem  directory can be zipped as it is. What goes where, and under which name, is
rem  said by cmake\Install.cmake (the layout is described there): no libraries,
rem  no debug information, and nothing that is not a target any more.

:collect_binaries
echo [*] Collecting binaries into build_final\...

call :empty_directory "%BUILD_FINAL_DIR%"
if %errorlevel% neq 0 exit /b 1

call :install_tree "%BUILD_X86_DIR%" x86
if %errorlevel% neq 0 exit /b 1

call :install_tree "%BUILD_X64_DIR%" x64
if %errorlevel% neq 0 exit /b 1

echo [*] Binaries are ready in: %BUILD_FINAL_DIR%
exit /b 0

rem --- :install_tree --------------------------------------------
rem  Installs the build tree %~1 (named %~2 in the messages) into build_final\.
rem  What CMake says is shown only if it fails.

:install_tree
set INSTALL_LOG=%TEMP%\apiinterceptor_install_%~2.log
cmake --install "%~1" --config %BUILD_CONFIG% --prefix "%BUILD_FINAL_DIR%" > "%INSTALL_LOG%" 2>&1
if %errorlevel% neq 0 (
    type "%INSTALL_LOG%"
    echo [!] Installing the %~2 build failed.
    exit /b 1
)
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
