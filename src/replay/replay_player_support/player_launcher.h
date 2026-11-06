/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYPLAYERSUPPORT_PLAYER_LAUNCHER_H
#define REPLAYPLAYERSUPPORT_PLAYER_LAUNCHER_H

#include <string>
#include <vector>

namespace Replay
{
    namespace ReplayPlayerSupport
    {
        /* Direct3D 7 and 8 are 32-bit only: a workload with their calls is handed from the 64-bit player to the 32-bit one next to it. */
        class PlayerLauncher
        {
        public:
            /* True if this is the 64-bit player and the workload holds D3D7 or D3D8 calls. False if the file cannot be read: the replay
             * reports it.
             */
            static bool is_handover_needed(const char* in_workload_path_ptr);

            /* Runs the 32-bit player, which is in the folder of this one under the file name, with the arguments (the workload last), and waits.
             * It is killed with this process. False, with the reason, if it cannot be started.
             */
            static bool run_x86_player(const std::string&              in_x86_player_file_name,
                                       const std::vector<std::string>& in_argument_vec,
                                       int*                            out_exit_code_ptr,
                                       std::string*                    out_error_ptr);

        private:
            /* The text in the ANSI code page, as the command line gives it. */
            static std::wstring get_wide_string(const std::string& in_text);
        };
    }
}

#endif /* REPLAYPLAYERSUPPORT_PLAYER_LAUNCHER_H */
