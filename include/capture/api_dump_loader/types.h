/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The enums of the loader of workloads.
 */
#ifndef APIDUMPLOADER_TYPES_H
#define APIDUMPLOADER_TYPES_H

namespace Capture
{
    namespace APIDumpLoader
    {
        enum class APIGroup
        {
            D3D7,
            D3D8,
            GDI32,
            GL,
            USER32,
            WGL,

            UNKNOWN
        };
    }
}

#endif /* APIDUMPLOADER_TYPES_H */
