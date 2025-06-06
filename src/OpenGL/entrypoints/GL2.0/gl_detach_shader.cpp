/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_detach_shader.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDetachShader(GLuint program,
                                        GLuint shader)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDetachShader(program=[%d] shader=[%d])",
             program,
             shader);

    reinterpret_cast<PFNGLDETACHSHADERPROC>(OpenGL::g_cached_gl_detach_shader)(program,
                                                                               shader);
}