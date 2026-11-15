/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Captures the rectangles of a D3D8 Present call.
 */
#ifndef D3D8_PRESENT_CAPTURE_H
#define D3D8_PRESENT_CAPTURE_H

#include "common/api_function_argument.h"
#include "interception/hooks/D3D8/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D8
        {
            class PresentCapture
            {
            public:
                /* Captures the rectangles of a Present call: the source and destination ones, and the dirty ones of the region
                 * (only the rectangles of RGNDATA are of interest). Writes 3 arguments.
                 */
                static void create_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                             const RECT*                          in_source_rect_ptr,
                                             const RECT*                          in_dest_rect_ptr,
                                             const RGNDATA*                       in_dirty_region_ptr);
            };
        }
    }
}

#endif /* D3D8_PRESENT_CAPTURE_H */
