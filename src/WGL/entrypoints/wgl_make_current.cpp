/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_make_current.h"


#include "OpenGL/globals.h"

BOOL WINAPI WGL::make_current(HDC   in_hdc,
                              HGLRC in_hglrc)
{
    AI_TRACE("wglMakeCurrent(in_hdc=[%p] in_hglrc=[%p])",
               in_hdc,
               in_hglrc);

    return reinterpret_cast<PFNWGLMAKECURRENTPROC>(WGL::g_cached_make_current_func_ptr)(in_hdc,
                                                                                        in_hglrc);
}
