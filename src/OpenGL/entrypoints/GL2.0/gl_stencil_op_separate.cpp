/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_stencil_op_separate.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilOpSeparate(GLenum face,
                                             GLenum sfail,
                                             GLenum dpfail,
                                             GLenum dppass)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glStencilOpSeparate(face=[%s] sfail={%s] dpfail=[%s] dppass=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(face),
             OpenGL::Utils::get_raw_string_for_gl_enum(sfail),
             OpenGL::Utils::get_raw_string_for_gl_enum(dpfail),
             OpenGL::Utils::get_raw_string_for_gl_enum(dppass) );

    reinterpret_cast<PFNGLSTENCILOPSEPARATEPROC>(g_cached_gl_stencil_op_separate)(face,
                                                                                  sfail,
                                                                                  dpfail,
                                                                                  dppass);
}