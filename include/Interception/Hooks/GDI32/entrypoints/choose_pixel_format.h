/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_CHOOSE_PIXEL_FORMAT_H
#define AI_CHOOSE_PIXEL_FORMAT_H

#include <windows.h>

namespace GDI32
{
    int WINAPI choose_pixel_format(HDC                          in_hdc,
                                   CONST PIXELFORMATDESCRIPTOR* in_pixel_format_descriptor_ptr);
}

#endif /* AI_CHOOSE_PIXEL_FORMAT_H */