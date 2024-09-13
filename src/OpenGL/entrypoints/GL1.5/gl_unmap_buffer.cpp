/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.5/gl_unmap_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiUnmapBuffer(GLenum target)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glUnmapBuffer(target=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target) );

    return reinterpret_cast<PFNGLUNMAPBUFFERPROC>(OpenGL::g_cached_gl_unmap_buffer)(target);
}