/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_alpha_func.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiAlphaFunc(GLenum   func,
                                     GLclampf ref)
{
    AI_TRACE("glAlphaFunc(func=[%s], ref=[%.4f])",
             OpenGL::Utils::get_raw_string_for_gl_enum(func),
             ref);

    reinterpret_cast<PFNGLACCUMPROC>(OpenGL::g_cached_gl_alpha_func)(func,
                                                                     ref);
}