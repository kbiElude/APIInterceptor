/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_is_buffer.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsBuffer(GLuint buffer)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIsBuffer(buffer=[%u])",
             buffer);

    return reinterpret_cast<PFNGLISBUFFERPROC>(OpenGL::g_cached_gl_is_buffer)(buffer);
}