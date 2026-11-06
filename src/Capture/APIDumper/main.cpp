/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include <string>
#include "Capture/InjectionLauncher/launcher.h"

int main(int   in_argc,
         char* in_argv[])
{
    std::string apidumper_dll_file_name;
    std::string dll_dir;
    uint32_t    dump_swapchain_on_present = 0;
    uint32_t    n_file_path_cmd_line_arg  = 1;
    uint32_t    n_frames_to_dump          = UINT32_MAX;
    uint32_t    n_spill_threshold_mb      = 128;
    int         result                    = EXIT_FAILURE;
    std::string working_dir;

    /* Parse arguments if specified */
    while (static_cast<uint32_t>(in_argc) > n_file_path_cmd_line_arg)
    {
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
        else
        if (std::string(in_argv[n_file_path_cmd_line_arg]) == "--spill-threshold-mb")
        {
            if (static_cast<uint32_t>(in_argc) <= (n_file_path_cmd_line_arg + 1))
            {
                fprintf(stderr,
                        "[!] --spill-threshold-mb argument must be followed by a positive integer value.\n");

                goto end;
            }

            if (sscanf(in_argv[n_file_path_cmd_line_arg + 1],
                       "%u",
                       &n_spill_threshold_mb) != 1)
            {
                fprintf(stderr,
                        "[!] --spill-threshold-mb argument must be followed by a positive integer value.\n");

                goto end;
            }

            if (n_spill_threshold_mb == 0)
            {
                fprintf(stderr,
                        "[!] --spill-threshold-mb argument must be followed by a positive integer value.\n");

                goto end;
            }

            n_file_path_cmd_line_arg += 2;
        }
        else
        if (std::string(in_argv[n_file_path_cmd_line_arg]) == "--dump-swapchain-on-present")
        {
            dump_swapchain_on_present = 1;
            n_file_path_cmd_line_arg  ++;
        }
        else
        {
            break;
        }
    }

    if (static_cast<uint32_t>(in_argc) <= n_file_path_cmd_line_arg)
    {
        fprintf(stderr,
                "To dump API calls used by an app, launch it with the following cmd line args:\n"
                "\n"
                "APIDumper.exe (--dump-n-frames VALUE) (--dump-swapchain-on-present) (--spill-threshold-mb VALUE) c:\\path\\to\\file\\file.exe (app args)\n"
                "\n"
                "The --dump-n-frames VALUE is optional; if specified, VALUE should be an uint\n"
                "telling the number of presented frames to include in the dump. By default,\n"
                "it's UINT32_MAX. The dump is written as soon as that many frames have been presented; otherwise,\n"
                "it is written when the app exits.\n"
                "\n"
                "The --dump-swapchain-on-present is optional; if specified, the color buffer (OpenGL, D3D7, D3D8) is taken\n"
                "right before present and stored in the dump as RGBA8, bottom row first. Use --dump-n-frames to\n"
                "limit the number of frames to be dumped.\n"
                "\n"
                "The --spill-threshold-mb VALUE is optional (128 by default). Once that many megabytes of dump data\n"
                "are waiting in memory, they are written to the dump file at the next frame boundary and freed, so that\n"
                "long captures do not run a 32-bit app out of memory.\n"
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

    /* Now look for the dumper dll .. The DLL must match the target's architecture, not ours. */
    {
        char                                           dll_dir_raw_i8vec260    [MAX_PATH] = {};
        std::string                                    target_architecture_error;
        Capture::InjectionLauncher::TargetArchitecture target_architecture                = Capture::InjectionLauncher::TargetArchitecture::UNKNOWN;
        char                                           working_dir_raw_i8vec260[MAX_PATH] = {};

        if (Capture::InjectionLauncher::Launcher::get_target_architecture(filename_ptr,
                                                                         &target_architecture,
                                                                         &target_architecture_error) == false)
        {
            fprintf(stderr,
                    "[!] Could not determine architecture of [%s]: %s\n",
                    filename_ptr,
                    target_architecture_error.c_str() );

            goto end;
        }

        const Capture::InjectionLauncher::TargetArchitecture launcher_architecture = Capture::InjectionLauncher::Launcher::get_own_architecture();

        /* Detours cannot inject across architectures when launching a process this way. */
        if (target_architecture != launcher_architecture)
        {
            const char* target_architecture_string   = (target_architecture   == Capture::InjectionLauncher::TargetArchitecture::X86) ? "x86"
                                                                                                                                      : "x64";
            const char* launcher_architecture_string = (launcher_architecture == Capture::InjectionLauncher::TargetArchitecture::X86) ? "x86"
                                                                                                                                      : "x64";

            fprintf(stderr,
                    "[!] [%s] is an %s executable but this is the %s APIDumper. Use APIDumper_%s.exe instead.\n",
                    filename_ptr,
                    target_architecture_string,
                    launcher_architecture_string,
                    target_architecture_string);

            goto end;
        }

        apidumper_dll_file_name = (target_architecture == Capture::InjectionLauncher::TargetArchitecture::X86) ? "APIDumperDLL_x86.dll"
                                                                                                               : "APIDumperDLL_x64.dll";

        if (::GetCurrentDirectory(sizeof(working_dir_raw_i8vec260),
                                  working_dir_raw_i8vec260) == 0)
        {
            ::MessageBox(HWND_DESKTOP,
                         "Failed to identify working directory.",
                         "Error",
                         MB_OK | MB_ICONERROR);

            goto end;
        }

        if (::GetModuleFileName(nullptr,
                                dll_dir_raw_i8vec260,
                                sizeof(dll_dir_raw_i8vec260) ) == 0)
        {
            ::MessageBox(HWND_DESKTOP,
                         "Failed to identify process' module file name.",
                         "Error",
                         MB_OK | MB_ICONERROR);

            goto end;
        }

        {
            const size_t n_last_separator_char = std::string(dll_dir_raw_i8vec260).find_last_of('\\');

            dll_dir = std::string(dll_dir_raw_i8vec260,
                                  0,
                                  n_last_separator_char);
        }

        working_dir             = working_dir_raw_i8vec260;
        apidumper_dll_file_name = dll_dir + "\\" + apidumper_dll_file_name;

        if (::GetFileAttributes(apidumper_dll_file_name.c_str() ) == INVALID_FILE_ATTRIBUTES)
        {
            fprintf(stderr,
                    "[!] [%s] is an %s executable but [%s] was not found.\n",
                    filename_ptr,
                    (target_architecture == Capture::InjectionLauncher::TargetArchitecture::X86) ? "x86"
                                                                                                 : "x64",
                    apidumper_dll_file_name.c_str() );

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

        uint8_t settings_data_u8vec12[12] = {};

        static_assert(sizeof(n_frames_to_dump)          == sizeof(uint32_t), "Size mismatch");
        static_assert(sizeof(dump_swapchain_on_present) == sizeof(uint32_t), "Size mismatch");
        static_assert(sizeof(n_spill_threshold_mb)      == sizeof(uint32_t), "Size mismatch");

        memcpy(settings_data_u8vec12,
              &n_frames_to_dump,
               sizeof(uint32_t) );
        memcpy(settings_data_u8vec12 + sizeof(uint32_t),
              &dump_swapchain_on_present,
               sizeof(uint32_t) );
        memcpy(settings_data_u8vec12 + sizeof(uint32_t) * 2,
              &n_spill_threshold_mb,
               sizeof(uint32_t) );

        if (settings_file_handle == nullptr)
        {
            fprintf(stderr,
                    "[!] Could not open [%s] for writing!\n",
                    settings_filename.c_str() );

            goto end;
        }

        if (::fwrite(settings_data_u8vec12,
                     sizeof(settings_data_u8vec12),
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
        std::string                               launch_error;
        PROCESS_INFORMATION                       process_info;
        Capture::InjectionLauncher::LaunchRequest request;

        request.dll_path          = apidumper_dll_file_name;
        request.executable_path   = filename_ptr;
        request.working_directory = working_dir;

        {
            uint32_t n_current_arg = n_file_path_cmd_line_arg + 1;

            while (n_current_arg < static_cast<uint32_t>(in_argc) )
            {
                request.arguments += (request.arguments.empty() ) ? std::string()
                                                                  : std::string(" ");
                request.arguments += in_argv[n_current_arg];

                n_current_arg++;
            }
        }

        if (Capture::InjectionLauncher::Launcher::launch(request,
                                                        &process_info,
                                                        &launch_error) == false)
        {
            fprintf(stderr,
                    "[!] %s\n",
                    launch_error.c_str() );

            goto end;
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
