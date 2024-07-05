/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_clear_depth.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"


void AI_APIENTRY OpenGL::aiClearDepth(GLdouble depth)
{
    AI_TRACE("glClearDepth(depth=[%.4f])",
             static_cast<float>(depth) );

    if (OpenGL::g_cached_gl_clear_depth == nullptr)
    {
        OpenGL::g_cached_gl_clear_depth = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glClearDepth");
    }

    reinterpret_cast<PFNGLCLEARDEPTHPROC>(OpenGL::g_cached_gl_clear_depth)(depth);
}