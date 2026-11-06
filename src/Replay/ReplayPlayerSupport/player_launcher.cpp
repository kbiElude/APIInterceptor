/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "player_launcher.h"
#include "Capture/APIDumpLoader/WorkloadReader.h"
#include <stdlib.h>
#include <vector>
#include <Windows.h>

std::wstring Replay::ReplayPlayerSupport::PlayerLauncher::get_wide_string(const std::string& in_text)
{
    const int n_characters = ::MultiByteToWideChar(CP_ACP,
                                                   0, /* flags */
                                                   in_text.c_str(),
                                                   static_cast<int>(in_text.size() ),
                                                   nullptr,
                                                   0);

    std::wstring result(static_cast<size_t>(n_characters),
                        L'\0');

    if (n_characters > 0)
    {
        ::MultiByteToWideChar(CP_ACP,
                              0, /* flags */
                              in_text.c_str   (),
                              static_cast<int>(in_text.size() ),
                              &result.front   (),
                              n_characters);
    }

    return result;
}

bool Replay::ReplayPlayerSupport::PlayerLauncher::is_handover_needed(const char* in_workload_path_ptr)
{
    constexpr uint32_t N_BYTES_PER_POINTER_X86 = 4;

    /* Only a 64-bit player hands over, and only a dump with 32-bit pointers can hold D3D7 or D3D8. */
    bool result = false;

    if (sizeof(void*) != N_BYTES_PER_POINTER_X86)
    {
        const auto reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(in_workload_path_ptr);

        if (reader_ptr != nullptr)
        {
            if (reader_ptr->get_pointer_n_bytes() == N_BYTES_PER_POINTER_X86)
            {
                Capture::APIDumpLoader::Workload workload;

                /* One pass for both APIs: a reader only goes forward, so what the first look has read is gone for the second. */
                while (result == false                                &&
                       reader_ptr->read_next_segment(&workload) )
                {
                    for (const auto& call : *workload.dumped_api_call_vec_ptr)
                    {
                        const auto group = Capture::APIDumpLoader::get_api_group(call.func);

                        if (group == Capture::APIDumpLoader::APIGroup::D3D7 ||
                            group == Capture::APIDumpLoader::APIGroup::D3D8)
                        {
                            result = true;

                            break;
                        }
                    }
                }
            }
        }
    }

    return result;
}

bool Replay::ReplayPlayerSupport::PlayerLauncher::run_x86_player(const std::string&              in_x86_player_file_name,
                                                                 const std::vector<std::string>& in_argument_vec,
                                                                 int*                            out_exit_code_ptr,
                                                                 std::string*                    out_error_ptr)
{
    std::wstring                         command_line;
    DWORD                                exit_code           = EXIT_FAILURE;
    HANDLE                               job_handle          = nullptr;
    JOBOBJECT_EXTENDED_LIMIT_INFORMATION job_limits          = {};
    PROCESS_INFORMATION                  process_information = {};
    bool                                 result              = false;
    STARTUPINFOW                         startup_information = {};
    std::wstring                         x86_player_path;

    std::vector<wchar_t> module_path_vec(MAX_PATH);

    startup_information.cb = sizeof(startup_information);

    if (::GetModuleFileNameW(nullptr,
                             module_path_vec.data(),
                             static_cast<DWORD>(module_path_vec.size() ) ) == 0)
    {
        *out_error_ptr = "The location of this player is unknown.";

        goto end;
    }

    /* The 32-bit player is in the folder of this one. */
    x86_player_path = module_path_vec.data  ();

    {
        const size_t       n_directory_chars = x86_player_path.find_last_of(L'\\') + 1;
        const std::wstring player_file_name  = get_wide_string(in_x86_player_file_name);

        x86_player_path = x86_player_path.substr(0,
                                                 n_directory_chars) + player_file_name;
    }

    if (::GetFileAttributesW(x86_player_path.c_str() ) == INVALID_FILE_ATTRIBUTES)
    {
        *out_error_ptr = "This workload holds Direct3D 7 or 8 calls, which only the 32-bit player can replay, but " + in_x86_player_file_name + " is not next to this player.";

        goto end;
    }

    /* The child must not outlive this process, as it would go on using the console. */
    job_handle                                  = ::CreateJobObjectW(nullptr,
                                                                     nullptr);
    job_limits.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;

    if (job_handle != nullptr)
    {
        ::SetInformationJobObject(job_handle,
                                  JobObjectExtendedLimitInformation,
                                 &job_limits,
                                  sizeof(job_limits) );
    }

    command_line = L"\""           +
                   x86_player_path +
                   L"\"";

    for (const auto& argument : in_argument_vec)
    {
        command_line += L" \""                    +
                        get_wide_string(argument) +
                        L"\"";
    }

    if (::CreateProcessW(x86_player_path.c_str(),
                         &command_line.front  (),
                         nullptr, /* process attributes */
                         nullptr, /* thread attributes  */
                         TRUE,    /* inherit handles    */
                         CREATE_SUSPENDED,
                         nullptr, /* environment        */
                         nullptr, /* current directory  */
                        &startup_information,
                        &process_information) == FALSE)
    {
        *out_error_ptr = "The 32-bit player cannot be started.";

        goto end;
    }

    if (job_handle != nullptr)
    {
        ::AssignProcessToJobObject(job_handle,
                                   process_information.hProcess);
    }

    ::ResumeThread       (process_information.hThread);
    ::WaitForSingleObject(process_information.hProcess,
                          INFINITE);
    ::GetExitCodeProcess (process_information.hProcess,
                         &exit_code);

    *out_exit_code_ptr = static_cast<int>(exit_code);
    result             = true;

end:
    if (process_information.hThread != nullptr)
    {
        ::CloseHandle(process_information.hThread);
    }

    if (process_information.hProcess != nullptr)
    {
        ::CloseHandle(process_information.hProcess);
    }

    if (job_handle != nullptr)
    {
        ::CloseHandle(job_handle);
    }

    return result;
}
