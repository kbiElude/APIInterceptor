/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_get_uniformuiv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetUniformuiv(GLuint  program,
                                         GLint   location,
                                         GLuint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetUniformuiv(program=[%u] location=[%d] params=[%p])",
             program,
             location,
             params);

    reinterpret_cast<PFNGLGETUNIFORMUIVPROC>(OpenGL::g_cached_gl_get_uniformuiv)(program,
                                                                                 location,
                                                                                 params);
}