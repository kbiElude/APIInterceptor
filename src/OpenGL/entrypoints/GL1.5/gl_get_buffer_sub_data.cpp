/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_sub_data.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetBufferSubData(GLenum     target,
                                            GLintptr   offset,
                                            GLsizeiptr size,
                                            void*      data)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetBufferSubData(target=[%s] offset=[%d] size=[%d] data=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             static_cast<int32_t>(offset),
             static_cast<int32_t>(size),
             data);

    reinterpret_cast<PFNGLGETBUFFERSUBDATAPROC>(OpenGL::g_cached_gl_get_buffer_sub_data)(target,
                                                                                         offset,
                                                                                         size,
                                                                                         data);
}