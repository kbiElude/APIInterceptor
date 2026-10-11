/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include <string>
#include "Detours/src/detours.h"
#include "launcher.h"

bool APIDumperLauncher::get_target_arch(const char*  in_filename_ptr,
                                        TargetArch*  out_arch_ptr,
                                        std::string* out_error_ptr)
{
    IMAGE_DOS_HEADER  dos_header      = {};
    IMAGE_FILE_HEADER file_header     = {};
    FILE*             file_handle     = ::fopen(in_filename_ptr,
                                                "rb");
    uint32_t          pe_signature    = 0;
    bool              result          = false;

    *out_arch_ptr = TargetArch::Unknown;

    if (file_handle == nullptr)
    {
        *out_error_ptr = "Could not open the file for reading.";

        goto end;
    }

    if (::fread(&dos_header,
                sizeof(dos_header),
                1,
                file_handle) != 1                   ||
        dos_header.e_magic   != IMAGE_DOS_SIGNATURE)
    {
        *out_error_ptr = "Not a valid PE executable (no MZ header).";

        goto end;
    }

    if (::fseek(file_handle,
                dos_header.e_lfanew,
                SEEK_SET)    != 0                   ||
        ::fread(&pe_signature,
                sizeof(pe_signature),
                1,
                file_handle) != 1                   ||
        ::fread(&file_header,
                sizeof(file_header),
                1,
                file_handle) != 1                   ||
        pe_signature         != IMAGE_NT_SIGNATURE)
    {
        *out_error_ptr = "Not a valid PE executable (no PE header).";

        goto end;
    }

    switch (file_header.Machine)
    {
        case IMAGE_FILE_MACHINE_I386:
        {
            *out_arch_ptr = TargetArch::X86;
             result       = true;

             break;
        }

        case IMAGE_FILE_MACHINE_AMD64:
        {
            *out_arch_ptr = TargetArch::X64;
             result       = true;

             break;
        }

        default:
        {
            char error_buffer[128];

            snprintf(error_buffer,
                     sizeof(error_buffer),
                     "Unsupported target architecture (PE machine type 0x%04X). Only x86 and x64 are supported.",
                     static_cast<uint32_t>(file_header.Machine) );

            *out_error_ptr = error_buffer;
            break;
        }
    }

end:
    if (file_handle != nullptr)
    {
        ::fclose(file_handle);
    }

    return result;
}

int main(int   in_argc,
         char* in_argv[])
{
    std::string apidumper_dll_file_name;
    std::string dll_dir;
    uint32_t    dump_swapchain_on_present = 0;
    uint32_t    n_file_path_cmd_line_arg  = 1;
    uint32_t    n_frames_to_dump          = UINT32_MAX;
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
                "APIDumper.exe (--dump-n-frames VALUE) (--dump-swapchain-on-present) c:\\path\\to\\file\\file.exe (app args)\n"
                "\n"
                "The --dump-n-frames VALUE is optional; if specified, VALUE should be an uint\n"
                "telling the number of presented frames to include in the dump. By default,\n"
                "it's UINT32_MAX.\n"
                "\n"
                "The --dump-swapchain-on-present is optional; if specified, swapchain contents (color / depth) will\n"
                "be taken right before present and stored in the dump. Use --dump-n-frames to limit the number of\n"
                "frames to be dumped.\n"
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
        char                          dll_dir_raw    [MAX_PATH] = {};
        std::string                   target_arch_error;
        APIDumperLauncher::TargetArch target_arch               = APIDumperLauncher::TargetArch::Unknown;
        char                          working_dir_raw[MAX_PATH] = {};

        if (!APIDumperLauncher::get_target_arch(filename_ptr,
                                               &target_arch,
                                               &target_arch_error) )
        {
            fprintf(stderr,
                    "[!] Could not determine architecture of [%s]: %s\n",
                    filename_ptr,
                    target_arch_error.c_str() );

            goto end;
        }

        #if defined(_WIN64)
            constexpr APIDumperLauncher::TargetArch launcher_arch = APIDumperLauncher::TargetArch::X64;
        #else
            constexpr APIDumperLauncher::TargetArch launcher_arch = APIDumperLauncher::TargetArch::X86;
        #endif

        /* Detours cannot inject across architectures when launching a process this way. */
        if (target_arch != launcher_arch)
        {
            const char* target_arch_str   = (target_arch   == APIDumperLauncher::TargetArch::X86) ? "x86"
                                                                                                  : "x64";
            const char* launcher_arch_str = (launcher_arch == APIDumperLauncher::TargetArch::X86) ? "x86"
                                                                                                  : "x64";

            fprintf(stderr,
                    "[!] [%s] is an %s executable but this is the %s APIDumper. Use APIDumper_%s.exe instead.\n",
                    filename_ptr,
                    target_arch_str,
                    launcher_arch_str,
                    target_arch_str);

            goto end;
        }

        apidumper_dll_file_name = (target_arch == APIDumperLauncher::TargetArch::X86) ? "APIDumperDLL_x86.dll"
                                                                                      : "APIDumperDLL_x64.dll";

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
            fprintf(stderr,
                    "[!] [%s] is an %s executable but [%s] was not found.\n",
                    filename_ptr,
                    (target_arch == APIDumperLauncher::TargetArch::X86) ? "x86"
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

        uint8_t settings_data_u8vec8[8] = {};

        static_assert(sizeof(n_frames_to_dump)          == sizeof(uint32_t), "Size mismatch");
        static_assert(sizeof(dump_swapchain_on_present) == sizeof(uint32_t), "Size mismatch");

        memcpy(settings_data_u8vec8,
              &n_frames_to_dump,
               sizeof(uint32_t) );
        memcpy(settings_data_u8vec8 + sizeof(uint32_t),
              &dump_swapchain_on_present,
               sizeof(uint32_t) );

        if (settings_file_handle == nullptr)
        {
            fprintf(stderr,
                    "[!] Could not open [%s] for writing!\n",
                    settings_filename.c_str() );

            goto end;
        }

        if (::fwrite(settings_data_u8vec8,
                     sizeof(settings_data_u8vec8),
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
            const DWORD last_error = ::GetLastError();

            fprintf(stderr,
                    "[!] Could not launch [%s] with [%s] attached (error %lu).\n",
                    filename_ptr,
                    apidumper_dll_file_name.c_str(),
                    last_error);

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
