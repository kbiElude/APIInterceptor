/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_stencil_func.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilFunc(GLenum func,
                                       GLint  ref,
                                       GLuint mask)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glStencilFunc(func=[%s] ref=[%d] mask=[%u])",
             OpenGL::Utils::get_raw_string_for_gl_enum(func),
             ref,
             mask);

    reinterpret_cast<PFNGLSTENCILFUNCPROC>(g_cached_gl_stencil_func)(func,
                                                                     ref,
                                                                     mask);
}