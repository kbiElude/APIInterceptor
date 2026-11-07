/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include "Detours/src/detours.h"
#include "capture/injection_launcher/launcher.h"
#include <stdint.h>
#include <stdio.h>

std::string Capture::InjectionLauncher::Launcher::get_command_line(const LaunchRequest& in_request)
{
    return "\"" + in_request.executable_path + "\"" + ((in_request.arguments.empty() ) ? std::string()
                                                                                       : " " + in_request.arguments);
}

Capture::InjectionLauncher::TargetArchitecture Capture::InjectionLauncher::Launcher::get_own_architecture()
{
    #if defined(_WIN64)
        return TargetArchitecture::X64;
    #else
        return TargetArchitecture::X86;
    #endif
}

bool Capture::InjectionLauncher::Launcher::get_target_architecture(const std::string&  in_filename,
                                                                   TargetArchitecture* out_architecture_ptr,
                                                                   std::string*        out_error_ptr)
{
    IMAGE_DOS_HEADER  dos_header   = {};
    IMAGE_FILE_HEADER file_header  = {};
    FILE*             file_handle  = ::fopen(in_filename.c_str(),
                                             "rb");
    uint32_t          pe_signature = 0;
    bool              result       = false;

    *out_architecture_ptr = TargetArchitecture::UNKNOWN;

    if (file_handle == nullptr)
    {
        *out_error_ptr = "Could not open the file for reading.";

        goto end;
    }

    {
        const size_t n_dos_header_read = ::fread(&dos_header,
                                                 sizeof(dos_header),
                                                 1,
                                                 file_handle);

        if (n_dos_header_read   != 1 ||
            dos_header.e_magic  != IMAGE_DOS_SIGNATURE)
        {
            *out_error_ptr = "Not a valid PE executable (no MZ header).";

            goto end;
        }
    }

    {
        bool      is_pe_header_valid = false;
        const int seek_result        = ::fseek(file_handle,
                                               dos_header.e_lfanew,
                                               SEEK_SET);

        if (seek_result == 0)
        {
            const size_t n_signature_read = ::fread(&pe_signature,
                                                    sizeof(pe_signature),
                                                    1,
                                                    file_handle);

            if (n_signature_read == 1)
            {
                const size_t n_file_header_read = ::fread(&file_header,
                                                          sizeof(file_header),
                                                          1,
                                                          file_handle);

                is_pe_header_valid = (n_file_header_read == 1 &&
                                      pe_signature       == IMAGE_NT_SIGNATURE);
            }
        }

        if (is_pe_header_valid == false)
        {
            *out_error_ptr = "Not a valid PE executable (no PE header).";

            goto end;
        }
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

            ::snprintf(error_buffer_i8vec128,
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

bool Capture::InjectionLauncher::Launcher::launch(const LaunchRequest& in_request,
                                                  PROCESS_INFORMATION* out_process_info_ptr,
                                                  std::string*         out_error_ptr)
{
    std::string  command_line = get_command_line(in_request);
    DWORD        last_error   = ERROR_SUCCESS;
    bool         result       = false;
    STARTUPINFOA startup_info = {};

    startup_info.cb       = sizeof(startup_info);
    *out_process_info_ptr = {};

    if (::DetourCreateProcessWithDllA(nullptr,
                                      &command_line[0],
                                      nullptr,                                   /* lpProcessAttributes */
                                      nullptr,                                   /* lpThreadAttributes  */
                                      FALSE,                                     /* bInheritHandles     */
                                      CREATE_DEFAULT_ERROR_MODE,
                                      nullptr,                                   /* lpEnvironment       */
                                      (in_request.working_directory.empty() ) ? nullptr
                                                                              : in_request.working_directory.c_str(),
                                     &startup_info,
                                      out_process_info_ptr,
                                      in_request.dll_path.c_str(),
                                      nullptr) == TRUE)                          /* pfCreateProcessA    */
    {
        result = true;

        goto end;
    }

    last_error = ::GetLastError();

    /* Detours rejects PEs with non-standard headers (e.g. packed ones). */
    if (last_error == ERROR_INVALID_OPERATION)
    {
        result = launch_with_apc_injection(in_request,
                                           out_process_info_ptr);

        last_error = ::GetLastError();
    }

    if (result == false)
    {
        char error_buffer_i8vec64[64];

        ::snprintf(error_buffer_i8vec64,
                   sizeof(error_buffer_i8vec64),
                   " (error %lu).",
                   last_error);

        *out_error_ptr = "Could not start [" + in_request.executable_path + "] with [" + in_request.dll_path + "] in it" + error_buffer_i8vec64;
    }

end:
    return result;
}

bool Capture::InjectionLauncher::Launcher::launch_with_apc_injection(const LaunchRequest& in_request,
                                                                     PROCESS_INFORMATION* out_process_info_ptr)
{
    std::string  command_line       = get_command_line(in_request);
    DWORD        last_error         = ERROR_SUCCESS;
    bool         is_process_created = false;
    const size_t n_path_bytes       = in_request.dll_path.size() + 1;
    void*        remote_path_ptr    = nullptr;
    bool         result             = false;
    STARTUPINFOA startup_info       = {};

    startup_info.cb       = sizeof(startup_info);
    *out_process_info_ptr = {};

    if (::CreateProcessA(nullptr,
                         &command_line[0],
                         nullptr,                                   /* lpProcessAttributes */
                         nullptr,                                   /* lpThreadAttributes  */
                         FALSE,                                     /* bInheritHandles     */
                         CREATE_SUSPENDED | CREATE_DEFAULT_ERROR_MODE,
                         nullptr,                                   /* lpEnvironment       */
                         (in_request.working_directory.empty() ) ? nullptr
                                                                 : in_request.working_directory.c_str(),
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
                             in_request.dll_path.c_str(),
                             n_path_bytes,
                             nullptr) == FALSE)
    {
        goto end;
    }

    /* kernel32 is mapped at the same address in every process of the same bitness. */
    {
        const HMODULE kernel32_module  = ::GetModuleHandleA("kernel32.dll");
        const FARPROC load_library_ptr = ::GetProcAddress  (kernel32_module,
                                                            "LoadLibraryA");

        if (::QueueUserAPC(reinterpret_cast<PAPCFUNC>(load_library_ptr),
                           out_process_info_ptr->hThread,
                           reinterpret_cast<ULONG_PTR>(remote_path_ptr) ) == 0)
        {
            goto end;
        }
    }

    if (::ResumeThread(out_process_info_ptr->hThread) == static_cast<DWORD>(-1) )
    {
        goto end;
    }

    result = true;

end:
    if (result             == false &&
        is_process_created)
    {
        last_error = ::GetLastError();

        ::TerminateProcess(out_process_info_ptr->hProcess,
                           EXIT_FAILURE);
        ::SetLastError    (last_error);
    }

    return result;
}
