/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_flush_mapped_buffer_range.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFlushMappedBufferRange(GLenum     target,
                                                  GLintptr   offset,
                                                  GLsizeiptr length)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glFlushMappedBufferRange(target=[%s] offset=[%d] length=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             static_cast<int32_t>(offset),
             static_cast<int32_t>(length) );

    reinterpret_cast<PFNGLFLUSHMAPPEDBUFFERRANGEPROC>(OpenGL::g_cached_gl_flush_mapped_buffer_range)(target,
                                                                                                     offset,
                                                                                                     length);
}