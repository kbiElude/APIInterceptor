/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_fi.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearBufferfi(GLenum  buffer,
                                         GLint   drawbuffer,
                                         GLfloat depth,
                                         GLint   stencil)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glClearBufferfi(buffer=[%s] drawbuffer=[%d] depth=[%.4f] stencil=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(buffer),
             drawbuffer,
             depth,
             stencil);

    reinterpret_cast<PFNGLCLEARBUFFERFIPROC>(OpenGL::g_cached_gl_clear_buffer_fi)(buffer,
                                                                                  drawbuffer,
                                                                                  depth,
                                                                                  stencil);
}