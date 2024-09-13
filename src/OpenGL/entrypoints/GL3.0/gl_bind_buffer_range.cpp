/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_bind_buffer_range.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindBufferRange(GLenum     target,
                                           GLuint     index,
                                           GLuint     buffer,
                                           GLintptr   offset,
                                           GLsizeiptr size)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBindBufferRange(target=[%s] index=[%d] buffer=[%d] offset=[%d] size=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index,
             buffer,
             static_cast<uint32_t>(offset),
             static_cast<uint32_t>(size) );

    reinterpret_cast<PFNGLBINDBUFFERRANGEPROC>(OpenGL::g_cached_gl_bind_buffer_range)(target,
                                                                                      index,
                                                                                      buffer,
                                                                                      offset,
                                                                                      size);
}