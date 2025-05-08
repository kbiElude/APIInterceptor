/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_buffer_data.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBufferData(GLenum      target,
                                      GLsizeiptr  size,
                                      const void* data,
                                      GLenum      usage)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBufferData(target=[%s] size=[%d] data=[%p] usage=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             static_cast<uint32_t>(size),
             data,
             OpenGL::Utils::get_raw_string_for_gl_enum(usage) );

    reinterpret_cast<PFNGLBUFFERDATAPROC>(OpenGL::g_cached_gl_buffer_data)(target,
                                                                           size,
                                                                           data,
                                                                           usage);
}