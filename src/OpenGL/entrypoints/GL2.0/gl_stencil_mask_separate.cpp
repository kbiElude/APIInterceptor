/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_stencil_mask_separate.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiStencilMaskSeparate(GLenum face,
                                               GLuint mask)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glStencilMaskSeparate(face=[%s] mask=[%u])",
             OpenGL::Utils::get_raw_string_for_gl_enum(face),
             mask);

    reinterpret_cast<PFNGLSTENCILMASKSEPARATEPROC>(g_cached_gl_stencil_mask_separate)(face,
                                                                                      mask);
}