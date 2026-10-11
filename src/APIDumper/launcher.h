/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Declarations of helpers used by the API Dumper launcher, defined in main.cpp.
 */
#ifndef APIDUMPER_LAUNCHER_H
#define APIDUMPER_LAUNCHER_H

#include <string>

namespace APIDumperLauncher
{
    enum class TargetArch
    {
        X86,
        X64,

        Unknown
    };

    /* Reads the PE headers of the specified file and tells which architecture the executable was built for.
     *
     * On failure, returns false and fills out_error_ptr with a human-readable description.
     */
    bool get_target_arch(const char*  in_filename_ptr,
                         TargetArch*  out_arch_ptr,
                         std::string* out_error_ptr);
}

#endif /* APIDUMPER_LAUNCHER_H */
