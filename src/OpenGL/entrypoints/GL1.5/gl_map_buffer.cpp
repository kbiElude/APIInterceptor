/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_map_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void *APIENTRY OpenGL::aiMapBuffer(GLenum target,
                                   GLenum access)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glMapBuffer(target=[%s] access=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(access) );


    return reinterpret_cast<PFNGLMAPBUFFERPROC>(OpenGL::g_cached_gl_map_buffer)(target,
                                                                                access);
}
