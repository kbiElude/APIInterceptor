/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_begin_conditional_render.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBeginConditionalRender(GLuint id,
                                                  GLenum mode)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBeginConditionalRender(id=[%d] mode=[%s])",
             id,
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    if (OpenGL::g_cached_gl_begin_conditional_render == nullptr)
    {
        OpenGL::g_cached_gl_begin_conditional_render = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBeginConditionalRender");
    }

    reinterpret_cast<PFNGLBEGINCONDITIONALRENDERPROC>(OpenGL::g_cached_gl_begin_conditional_render)(id,
                                                                                                    mode);
}