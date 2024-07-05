/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_SET_PIXEL_FORMAT_H
#define AI_SET_PIXEL_FORMAT_H

#include <Windows.h>

namespace GDI32
{
    BOOL WINAPI set_pixel_format(HDC                          in_hdc,
                                 int                          in_format,
                                 CONST PIXELFORMATDESCRIPTOR* in_pixel_format_descriptor_ptr);
}

#endif /* AI_SET_PIXEL_FORMAT_H */