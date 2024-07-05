/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_pop_attrib.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPopAttrib()
{
    AI_TRACE("PopAttrib()");

    reinterpret_cast<PFNGLPOPATTRIBPROC>(OpenGL::g_cached_gl_pop_attrib)();
}