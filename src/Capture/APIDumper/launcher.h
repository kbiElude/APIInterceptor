/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Launcher helpers (defined in main.cpp).
 */
#ifndef APIDUMPER_LAUNCHER_H
#define APIDUMPER_LAUNCHER_H

#include "types.h"
#include <string>
#include <Windows.h>

namespace APIDumperLauncher
{
    /* Reads the executable's PE headers. On failure, returns false and describes the error in *out_error_ptr. */
    bool get_target_architecture(const char*         in_filename_ptr,
                                 TargetArchitecture* out_architecture_ptr,
                                 std::string*        out_error_ptr);

    /* Creates the process suspended and loads the DLL into it via an APC, before the exe's entry point. Works with PEs
     * which Detours rejects. On failure, terminates the process and returns false (see GetLastError()).
     */
    bool launch_with_apc_injection(const char*          in_command_line_ptr,
                                   const char*          in_working_directory_ptr,
                                   const char*          in_dll_path_ptr,
                                   PROCESS_INFORMATION* out_process_info_ptr);
}

#endif /* APIDUMPER_LAUNCHER_H */
