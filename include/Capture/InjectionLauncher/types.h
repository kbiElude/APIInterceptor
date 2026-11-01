/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef INJECTIONLAUNCHER_TYPES_H
#define INJECTIONLAUNCHER_TYPES_H

#include <string>

namespace Capture
{
    namespace InjectionLauncher
    {
        enum class TargetArchitecture
        {
            X86,
            X64,

            UNKNOWN
        };

        /* An application to start with a DLL injected into it, before its own code runs. */
        struct LaunchRequest
        {
            std::string arguments;         /* of the application; as they are put on its command line                 */
            std::string dll_path;          /* of the same architecture as the application                             */
            std::string executable_path;
            std::string working_directory; /* empty: that of the launcher                                             */
        };
    }
}

#endif /* INJECTIONLAUNCHER_TYPES_H */
