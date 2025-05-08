/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_map_buffer_range.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void* APIENTRY OpenGL::aiMapBufferRange(GLenum     target,
                                        GLintptr   offset,
                                        GLsizeiptr length,
                                        GLbitfield access)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMapBufferRange(target=[%s] offset=[%d] length=[%d] access=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             static_cast<int32_t>(offset),
             static_cast<int32_t>(length),
             OpenGL::Utils::get_raw_string_for_gl_bitfield(OpenGL::BitfieldType::Buffer_Access_Mask, access) );

    return reinterpret_cast<PFNGLMAPBUFFERRANGEPROC>(g_cached_gl_map_buffer_range)(target,
                                                                                   offset,
                                                                                   length,
                                                                                   access);
}