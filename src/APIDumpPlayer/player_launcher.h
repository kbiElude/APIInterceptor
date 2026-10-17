/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPPLAYER_PLAYER_LAUNCHER_H
#define APIDUMPPLAYER_PLAYER_LAUNCHER_H

#include <string>

namespace APIDumpPlayer
{
    /* D3D8 is a 32-bit API, so only the 32-bit player can replay a workload which holds D3D8 calls. This lets the
     * 64-bit player notice such a workload, and hand it over to the 32-bit player which sits next to it.
     */
    class PlayerLauncher
    {
    public:
        /* True if this is the 64-bit player, and the workload holds D3D8 calls. A file which cannot be read gives
         * false: the replay reports what is wrong with it.
         */
        static bool is_handover_needed(const char* in_workload_path_ptr);

        /* Runs the 32-bit player on the workload, and waits until it ends. The child ends with this process. Returns
         * false, with the reason, if it cannot be started.
         */
        static bool run_x86_player(const std::string& in_workload_path,
                                   const bool&        in_is_console,
                                   int*               out_exit_code_ptr,
                                   std::string*       out_error_ptr);

    private:
        /* The text in the ANSI code page, as the command line gives it. */
        static std::wstring get_wide_string(const std::string& in_text);
    };
}

#endif /* APIDUMPPLAYER_PLAYER_LAUNCHER_H */
