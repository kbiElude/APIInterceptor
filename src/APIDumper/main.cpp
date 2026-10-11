/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include <string>
#include "Detours/src/detours.h"
#include "launcher.h"

bool APIDumperLauncher::get_target_architecture(const char*         in_filename_ptr,
                                                TargetArchitecture* out_architecture_ptr,
                                                std::string*        out_error_ptr)
{
    IMAGE_DOS_HEADER  dos_header   = {};
    IMAGE_FILE_HEADER file_header  = {};
    FILE*             file_handle  = ::fopen(in_filename_ptr,
                                             "rb");
    uint32_t          pe_signature = 0;
    bool              result       = false;

    *out_architecture_ptr = TargetArchitecture::Unknown;

    if (file_handle == nullptr)
    {
        *out_error_ptr = "Could not open the file for reading.";

        goto end;
    }

    if (::fread(&dos_header,
                sizeof(dos_header),
                1,
                file_handle) != 1)
    {
        *out_error_ptr = "Not a valid PE executable (no MZ header).";

        goto end;
    }

    if (dos_header.e_magic != IMAGE_DOS_SIGNATURE)
    {
        *out_error_ptr = "Not a valid PE executable (no MZ header).";

        goto end;
    }

    if (::fseek(file_handle,
                dos_header.e_lfanew,
                SEEK_SET) != 0)
    {
        *out_error_ptr = "Not a valid PE executable (no PE header).";

        goto end;
    }

    if (::fread(&pe_signature,
                sizeof(pe_signature),
                1,
                file_handle) != 1)
    {
        *out_error_ptr = "Not a valid PE executable (no PE header).";

        goto end;
    }

    if (::fread(&file_header,
                sizeof(file_header),
                1,
                file_handle) != 1)
    {
        *out_error_ptr = "Not a valid PE executable (no PE header).";

        goto end;
    }

    if (pe_signature != IMAGE_NT_SIGNATURE)
    {
        *out_error_ptr = "Not a valid PE executable (no PE header).";

        goto end;
    }

    switch (file_header.Machine)
    {
        case IMAGE_FILE_MACHINE_I386:
        {
            *out_architecture_ptr = TargetArchitecture::X86;
             result               = true;

             break;
        }

        case IMAGE_FILE_MACHINE_AMD64:
        {
            *out_architecture_ptr = TargetArchitecture::X64;
             result               = true;

             break;
        }

        default:
        {
            char error_buffer_i8vec128[128];

            snprintf(error_buffer_i8vec128,
                     sizeof(error_buffer_i8vec128),
                     "Unsupported target architecture (PE machine type 0x%04X). Only x86 and x64 are supported.",
                     static_cast<uint32_t>(file_header.Machine) );

            *out_error_ptr = error_buffer_i8vec128;
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

bool APIDumperLauncher::launch_with_apc_injection(const char*          in_command_line_ptr,
                                                  const char*          in_working_directory_ptr,
                                                  const char*          in_dll_path_ptr,
                                                  PROCESS_INFORMATION* out_process_info_ptr)
{
    std::string command_line       (in_command_line_ptr);
    DWORD       last_error         = ERROR_SUCCESS;
    bool        is_process_created = false;
    size_t      n_path_bytes       = ::strlen(in_dll_path_ptr) + 1;
    void*       remote_path_ptr    = nullptr;
    bool        result             = false;
    STARTUPINFO startup_info       = {};

    startup_info.cb       = sizeof(startup_info);
    *out_process_info_ptr = {};

    if (::CreateProcessA(nullptr,
                         &command_line[0],
                         nullptr,                                   /* lpProcessAttributes */
                         nullptr,                                   /* lpThreadAttributes  */
                         FALSE,                                     /* bInheritHandles     */
                         CREATE_SUSPENDED | CREATE_DEFAULT_ERROR_MODE,
                         nullptr,                                   /* lpEnvironment       */
                         in_working_directory_ptr,
                        &startup_info,
                         out_process_info_ptr) == FALSE)
    {
        goto end;
    }

    is_process_created = true;

    remote_path_ptr = ::VirtualAllocEx(out_process_info_ptr->hProcess,
                                       nullptr,
                                       n_path_bytes,
                                       MEM_COMMIT | MEM_RESERVE,
                                       PAGE_READWRITE);

    if (remote_path_ptr == nullptr)
    {
        goto end;
    }

    if (::WriteProcessMemory(out_process_info_ptr->hProcess,
                             remote_path_ptr,
                             in_dll_path_ptr,
                             n_path_bytes,
                             nullptr) == FALSE)
    {
        goto end;
    }

    /* kernel32 is mapped at the same address in every process of the same bitness. */
    if (::QueueUserAPC(reinterpret_cast<PAPCFUNC>(::GetProcAddress(::GetModuleHandleA("kernel32.dll"),
                                                                   "LoadLibraryA") ),
                       out_process_info_ptr->hThread,
                       reinterpret_cast<ULONG_PTR>(remote_path_ptr) ) == 0)
    {
        goto end;
    }

    if (::ResumeThread(out_process_info_ptr->hThread) == static_cast<DWORD>(-1) )
    {
        goto end;
    }

    result = true;
end:
    if (result            == false &&
        is_process_created)
    {
        last_error = ::GetLastError();

        ::TerminateProcess(out_process_info_ptr->hProcess,
                           EXIT_FAILURE);
        ::SetLastError    (last_error);
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
                "The --dump-swapchain-on-present is optional; if specified, the color buffer (OpenGL, D3D8) is taken\n"
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
        char                                  dll_dir_raw_i8vec260    [MAX_PATH] = {};
        std::string                           target_architecture_error;
        APIDumperLauncher::TargetArchitecture target_architecture       = APIDumperLauncher::TargetArchitecture::Unknown;
        char                                  working_dir_raw_i8vec260[MAX_PATH] = {};

        if (!APIDumperLauncher::get_target_architecture(filename_ptr,
                                                       &target_architecture,
                                                       &target_architecture_error) )
        {
            fprintf(stderr,
                    "[!] Could not determine architecture of [%s]: %s\n",
                    filename_ptr,
                    target_architecture_error.c_str() );

            goto end;
        }

        #if defined(_WIN64)
            constexpr APIDumperLauncher::TargetArchitecture launcher_architecture = APIDumperLauncher::TargetArchitecture::X64;
        #else
            constexpr APIDumperLauncher::TargetArchitecture launcher_architecture = APIDumperLauncher::TargetArchitecture::X86;
        #endif

        /* Detours cannot inject across architectures when launching a process this way. */
        if (target_architecture != launcher_architecture)
        {
            const char* target_architecture_string   = (target_architecture   == APIDumperLauncher::TargetArchitecture::X86) ? "x86"
                                                                                                                             : "x64";
            const char* launcher_architecture_string = (launcher_architecture == APIDumperLauncher::TargetArchitecture::X86) ? "x86"
                                                                                                                             : "x64";

            fprintf(stderr,
                    "[!] [%s] is an %s executable but this is the %s APIDumper. Use APIDumper_%s.exe instead.\n",
                    filename_ptr,
                    target_architecture_string,
                    launcher_architecture_string,
                    target_architecture_string);

            goto end;
        }

        apidumper_dll_file_name = (target_architecture == APIDumperLauncher::TargetArchitecture::X86) ? "APIDumperDLL_x86.dll"
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

        dll_dir                 = std::string(dll_dir_raw_i8vec260,
                                              0,
                                              std::string(dll_dir_raw_i8vec260).find_last_of('\\') );
        working_dir             = working_dir_raw_i8vec260;
        apidumper_dll_file_name = dll_dir + "\\" + apidumper_dll_file_name;

        if (::GetFileAttributes(apidumper_dll_file_name.c_str() ) == INVALID_FILE_ATTRIBUTES)
        {
            fprintf(stderr,
                    "[!] [%s] is an %s executable but [%s] was not found.\n",
                    filename_ptr,
                    (target_architecture == APIDumperLauncher::TargetArchitecture::X86) ? "x86"
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

            /* Detours rejects PEs with non-standard headers (e.g. packed ones). */
            if (last_error == ERROR_INVALID_OPERATION)
            {
                fprintf(stderr,
                        "[*] Detours cannot patch [%s]; injecting via APC instead.\n",
                        filename_ptr);

                if (APIDumperLauncher::launch_with_apc_injection(filename_with_args.c_str(),
                                                                 working_dir.c_str(),
                                                                 apidumper_dll_file_name.c_str(),
                                                                &process_info) == false)
                {
                    fprintf(stderr,
                            "[!] Could not launch [%s] with [%s] attached (error %lu).\n",
                            filename_ptr,
                            apidumper_dll_file_name.c_str(),
                            ::GetLastError() );

                    goto end;
                }
            }
            else
            {
                fprintf(stderr,
                        "[!] Could not launch [%s] with [%s] attached (error %lu).\n",
                        filename_ptr,
                        apidumper_dll_file_name.c_str(),
                        last_error);

                goto end;
            }
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
