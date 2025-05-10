/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_CREATE_DC_A_H
#define AI_CREATE_DC_A_H

#include <windows.h>

namespace User32
{
    HDC WINAPI create_dc_a(LPCSTR, LPCSTR, LPCSTR, const DEVMODEA* pdm);
}

#endif /* AI_CREATE_DC_A_H */