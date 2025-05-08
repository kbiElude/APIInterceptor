/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_uniformfv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetUniformfv(GLuint   program,
                                        GLint    location,
                                        GLfloat* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetUniformfv(program=[%u] location=[%d] params=[%p])",
             program,
             location,
             params);

    reinterpret_cast<PFNGLGETUNIFORMFVPROC>(OpenGL::g_cached_gl_get_uniformfv)(program,
                                                                               location,
                                                                               params);
}