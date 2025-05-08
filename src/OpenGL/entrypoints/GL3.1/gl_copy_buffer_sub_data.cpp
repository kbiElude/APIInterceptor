/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.1/gl_copy_buffer_sub_data.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyBufferSubData(GLenum     readTarget,
                                             GLenum     writeTarget,
                                             GLintptr   readOffset,
                                             GLintptr   writeOffset,
                                             GLsizeiptr size)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCopyBufferSubData(readTarget=[%s] writeTarget=[%s] readOffset=[%d] writeOffset=[%d] size=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(readTarget),
             OpenGL::Utils::get_raw_string_for_gl_enum(writeTarget),
             static_cast<int32_t>(readOffset),
             static_cast<int32_t>(writeOffset),
             static_cast<int32_t>(size) );

    reinterpret_cast<PFNGLCOPYBUFFERSUBDATAPROC>(OpenGL::g_cached_gl_copy_buffer_sub_data)(readTarget,
                                                                                           writeTarget,
                                                                                           readOffset,
                                                                                           writeOffset,
                                                                                           size);
}