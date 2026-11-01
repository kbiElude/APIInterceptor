/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_SWAP_BUFFERS_H
#define AI_SWAP_BUFFERS_H

#include <Windows.h>

namespace GDI32
{
    BOOL WINAPI swap_buffers(HDC in_hdc);
}

#endif /* AI_SWAP_BUFFERS_H */