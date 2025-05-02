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
    std::string apidumper_dll_file_name  = "APIDumperDLL.dll";
    std::string dll_dir;
    uint32_t    n_file_path_cmd_line_arg = 1;
    uint32_t    n_frames_to_dump         = UINT32_MAX;
    int         result                   = EXIT_FAILURE;
    std::string working_dir;

    /* Parse arguments if specified */
    if (std::string(in_argv[n_file_path_cmd_line_arg]) == "--dump-n-frames")
    {
        if (static_cast<uint32_t>(in_argc) <= (n_file_path_cmd_line_arg + 1))
        {
            fprintf(stderr,
                    "[!] If --dump-n-frames argument is specified, it must be followed by an integer value.\n");

            goto end;
        }

        if (sscanf(in_argv[n_file_path_cmd_line_arg + 1],
                   "%d",
                   &n_frames_to_dump) != 1)
        {
            fprintf(stderr,
                    "[!] --dump-n-frames argument must be followed by an integer value.\n");

            goto end;
        }

        if (n_frames_to_dump == 0)
        {
            fprintf(stderr,
                    "[!] User requested zero frames to dump - exiting.\n");

            goto end;
        }

        n_file_path_cmd_line_arg += 2;
    }

    if (static_cast<uint32_t>(in_argc) < n_file_path_cmd_line_arg)
    {
        fprintf(stderr,
                "To dump API calls used by an app, launch it with the following cmd line args:\n"
                "\n"
                "APIDumper.exe (--dump-n-frames VALUE) c:\\path\\to\\file\\file.exe (app args)\n"
                "\n"
                "The --dump-n-frames VALUE is optional; if specified, VALUE should be an uint\n"
                "telling the number of presented frames to include in the dump. By default,\n"
                "it's UINT32_MAX.\n"
                "\n"
                "If the app takes arguments, specify them by replacing (app args) accordingly.\n"
                "No arguments? Just skip the part.\n"
                "\n");

        goto end;
    }

    if (in_argv[n_file_path_cmd_line_arg][0] == '-')
    {
        fprintf(stderr,
                "[!] File path / name must not start with -.\n");

        goto end;
    }

    /* Verify the specified app can be found. */
    const char* filename_ptr = in_argv[n_file_path_cmd_line_arg];

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

    /* Store user settings in a helper file.
     *
     * We could have used more fancy approaches like named pipes here, but let's keep it simple.
     */
    {
        const std::string settings_filename    = working_dir + "\\apidumper_settings.bin";
        auto              settings_file_handle = ::fopen(settings_filename.c_str(),
                                                         "w+");

        if (settings_file_handle == nullptr)
        {
            fprintf(stderr,
                    "[!] Could not open [%s] for writing!\n",
                    settings_filename.c_str() );

            goto end;
        }

        if (::fwrite(&n_frames_to_dump,
                     sizeof(uint32_t),
                     1,
                     settings_file_handle) != 1)
        {
            fprintf(stderr,
                    "[!] Could not write to [%s].\n",
                    settings_filename.c_str() );

            goto end;
        }

        ::fclose(settings_file_handle);
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
            uint32_t n_current_arg = n_file_path_cmd_line_arg + 1;

            while (n_current_arg < static_cast<uint32_t>(in_argc) )
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