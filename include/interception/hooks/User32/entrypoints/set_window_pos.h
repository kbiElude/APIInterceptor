/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_SET_WINDOW_POS_H
#define AI_SET_WINDOW_POS_H

#include <windows.h>

namespace Interception
{
    namespace Hooks
    {
        namespace User32
        {
            BOOL WINAPI set_window_pos(HWND,
                                       HWND,
                                       int,
                                       int,
                                       int,
                                       int,
                                       UINT);
        }
    }
}

#endif /* AI_SET_WINDOW_POS_H */
