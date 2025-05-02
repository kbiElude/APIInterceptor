/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include <string>
#include "Detours/src/detours.h"

int main(int   in_argc,
         char* in_argv[])
{
    std::string apidumper_dll_file_name = "APIDumperDLL.dll";
    std::string dll_dir;
    int         result                  = EXIT_FAILURE;
    std::string working_dir;

    if (in_argc < 2)
    {
        fprintf(stderr,
                "To dump API calls used by the app, launch it with the following cmd line args:\n"
                "\n"
                "APIDumper.exe c:\\path\\to\\file\\file.exe (optional app args)\n");

        goto end;
    }

    /* Verify the specified file can be found. */
    const char* filename_ptr = in_argv[1];

    if (::GetFileAttributes(filename_ptr) == INVALID_FILE_ATTRIBUTES)
    {
        fprintf(stderr,
                "[!] Specified file (%s) couldn't be found.\n",
                filename_ptr);

        goto end;
    }

    /* Now look for the dumper dll .. */
    {
        char dll_dir_raw    [MAX_PATH] = {};
        char working_dir_raw[MAX_PATH] = {};

        if (::GetCurrentDirectory(sizeof(working_dir_raw),
                                  working_dir_raw) == 0)
        {
            ::MessageBox(HWND_DESKTOP,
                         "Failed to identify working directory.",
                         "Error",
                         MB_OK | MB_ICONERROR);

            goto end;
        }

        if (::GetModuleFileName(nullptr,
                                dll_dir_raw,
                                sizeof(dll_dir_raw) ) == 0)
        {
            ::MessageBox(HWND_DESKTOP,
                         "Failed to identify process' module file name.",
                         "Error",
                         MB_OK | MB_ICONERROR);

            goto end;
        }

        dll_dir                 = std::string(dll_dir_raw,
                                              0,
                                              std::string(dll_dir_raw).find_last_of('\\') );
        working_dir             = working_dir_raw;
        apidumper_dll_file_name = dll_dir + "\\" + apidumper_dll_file_name;

        if (::GetFileAttributes(apidumper_dll_file_name.c_str() ) == INVALID_FILE_ATTRIBUTES)
        {
            ::MessageBox(HWND_DESKTOP,
                         "APIDumper.dll not found in the working directory.",
                         "Error",
                         MB_OK | MB_ICONERROR);

            goto end;
        }
    }

    // Launch the process with APIDumper attached.
    {
        std::string         filename_with_args = std::string(filename_ptr);
        PROCESS_INFORMATION process_info;
        STARTUPINFO         startup_info;

        memset(&process_info,
               0,
               sizeof(process_info) );
        memset(&startup_info,
               0,
               sizeof(startup_info) );

        startup_info.cb = sizeof(startup_info);

        {
            uint32_t n_current_arg = 2;

            while (n_current_arg < in_argc)
            {
                filename_with_args += std::string(" ") + in_argv[n_current_arg];

                n_current_arg++;
            }
        }

        if (::DetourCreateProcessWithDll(nullptr,
                                         const_cast<LPSTR>(filename_with_args.c_str() ),
                                         nullptr,                          /* lpProcessAttributes */
                                         nullptr,                          /* lpThreadAttributes  */
                                         FALSE,                            /* bInheritHandles     */
                                         CREATE_DEFAULT_ERROR_MODE,
                                         nullptr,                          /* lpEnvironment       */
                                         working_dir.c_str(),              /* lpCurrentDirectory  */
                                        &startup_info,
                                        &process_info,
                                         apidumper_dll_file_name.c_str(),
                                         nullptr) != TRUE)                 /* pfCreateProcessA    */
        {
            std::string error = "Could not launch the specified process with APIDumper attached.";

            ::MessageBox(HWND_DESKTOP,
                         error.c_str(),
                         "Error",
                         MB_OK | MB_ICONERROR);
        }

        #if defined(_DEBUG)
        {
            ::WaitForSingleObject(process_info.hProcess,
                                  INFINITE);
        }
        #endif
    }

    result = EXIT_SUCCESS;
end:
    return result;
}