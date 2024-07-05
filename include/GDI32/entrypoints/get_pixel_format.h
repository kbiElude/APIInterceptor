/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GET_PIXEL_FORMAT_H
#define AI_GET_PIXEL_FORMAT_H

#include <Windows.h>

namespace GDI32
{
    int WINAPI get_pixel_format(HDC in_hdc);
}

#endif /* AI_GET_PIXEL_FORMAT_H */