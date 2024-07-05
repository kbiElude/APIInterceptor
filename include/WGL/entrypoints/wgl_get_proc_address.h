/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef WGL_GET_PROC_ADDRESS_H
#define WGL_GET_PROC_ADDRESS_H

#include <windows.h>

namespace WGL
{
    PROC WINAPI get_proc_address(LPCSTR in_name);
}

#endif /* WGL_GET_PROC_ADDRESS_H */