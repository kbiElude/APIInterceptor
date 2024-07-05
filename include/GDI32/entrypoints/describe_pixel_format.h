/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_DESCRIBE_PIXEL_FORMAT_H
#define AI_DESCRIBE_PIXEL_FORMAT_H

#include <windows.h>

namespace GDI32
{
    int WINAPI describe_pixel_format(HDC                     in_hdc,
                                     int                     in_n_pixel_format,
                                     UINT                    in_n_bytes,
                                     LPPIXELFORMATDESCRIPTOR out_pixel_format_descriptor_ptr);
}

#endif /* AI_DESCRIBE_PIXEL_FORMAT_H */