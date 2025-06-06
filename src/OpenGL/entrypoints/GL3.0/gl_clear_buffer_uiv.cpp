/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearBufferuiv(GLenum        buffer,
                                          GLint         drawbuffer,
                                          const GLuint* value)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glClearBufferuiv(buffer=[%s] drawbuffer=[%d] *value=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(buffer),
             drawbuffer,
            *value);

    reinterpret_cast<PFNGLCLEARBUFFERUIVPROC>(OpenGL::g_cached_gl_clear_buffer_uiv)(buffer,
                                                                                    drawbuffer,
                                                                                    value);
}