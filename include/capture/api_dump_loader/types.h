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

        /* What the next frame of the file came to. */
        enum class FrameFetch
        {
            CLEAN_END,
            DAMAGED_END, /* a frame which cannot be told to be one: nothing more can be read */
            SEGMENT
        };
    }
}

#endif /* APIDUMPLOADER_TYPES_H */
