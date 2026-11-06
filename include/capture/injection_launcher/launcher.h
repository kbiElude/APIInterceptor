/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef INJECTIONLAUNCHER_LAUNCHER_H
#define INJECTIONLAUNCHER_LAUNCHER_H

#include "capture/injection_launcher/types.h"
#include <string>
#include <Windows.h>

namespace Capture
{
    namespace InjectionLauncher
    {
        /* Starts an application with a DLL in it. Detours cannot inject across architectures when it starts a process, so the program
         * which calls this has to be of the architecture of the application (see get_target_architecture()).
         */
        class Launcher
        {
        public:
            /* The command line of the application: the path is quoted, since it can have spaces. */
            static std::string get_command_line(const LaunchRequest& in_request);

            /* The architecture of this program. */
            static TargetArchitecture get_own_architecture();

            /* Reads the PE headers of the executable. Returns false, and says why, if it is not one of x86 or x64. */
            static bool get_target_architecture(const std::string&  in_filename,
                                                TargetArchitecture* out_architecture_ptr,
                                                std::string*        out_error_ptr);

            /* The application is suspended while the DLL is put in, and runs when this returns. Detours is used; for an executable
             * which it rejects (a packed one), the DLL is loaded through an APC instead. The process information is the caller's to
             * close.
             */
            static bool launch(const LaunchRequest& in_request,
                               PROCESS_INFORMATION* out_process_info_ptr,
                               std::string*         out_error_ptr);

        private:
            static bool launch_with_apc_injection(const LaunchRequest& in_request,
                                                  PROCESS_INFORMATION* out_process_info_ptr);
        };
    }
}

#endif /* INJECTIONLAUNCHER_LAUNCHER_H */
