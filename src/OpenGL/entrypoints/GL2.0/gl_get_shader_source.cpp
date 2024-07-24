/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_shader_source.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetShaderSource(GLuint   shader,
                                           GLsizei  bufSize,
                                           GLsizei* length,
                                           GLchar*  source)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetShaderSource(shader=[%u] bufSize=[%d] length=[%p] source=[%p])",
             shader,
             static_cast<int32_t>(bufSize),
             length,
             source);

    if (OpenGL::g_cached_gl_end_transform_feedback == nullptr)
    {
        OpenGL::g_cached_gl_end_transform_feedback = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndTransformFeedback");
    }

    reinterpret_cast<PFNGLGETSHADERSOURCEPROC>(OpenGL::g_cached_gl_get_shader_source)(shader,
                                                                                      bufSize,
                                                                                      length,
                                                                                      source);
}