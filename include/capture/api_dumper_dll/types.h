/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The enums of the dumper.
 */
#ifndef APIDUMPERDLL_TYPES_H
#define APIDUMPERDLL_TYPES_H

namespace Capture
{
    namespace APIDumperDLL
    {
        /* The formats a back buffer is read in. A reader maps the formats of its API to these, and fails for any other. */
        enum class PixelSourceFormat
        {
            A1R5G5B5,
            A8R8G8B8,
            R5G6B5,
            X1R5G5B5,
            X8R8G8B8
        };
    }
}

#endif /* APIDUMPERDLL_TYPES_H */
