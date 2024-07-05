/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_end_list.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEndList()
{
    AI_TRACE("glEndList()");

    reinterpret_cast<PFNGLENDLISTPROC>(OpenGL::g_cached_gl_end_list)();
}