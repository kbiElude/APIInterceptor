/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_pointerv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetPointerv(GLenum   pname,
                                       GLvoid** params)
{
    AI_TRACE("glGetPointerv(pname=[%s], params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETPOINTERVPROC>(OpenGL::g_cached_gl_get_pointerv)(pname,
                                                                             params);
}