/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_MOVE_WINDOW_H
#define AI_MOVE_WINDOW_H

#include <windows.h>

namespace Interception
{
    namespace Hooks
    {
        namespace User32
        {
            BOOL WINAPI move_window(HWND,
                                    int,
                                    int,
                                    int,
                                    int,
                                    BOOL);
        }
    }
}

#endif /* AI_MOVE_WINDOW_H */
