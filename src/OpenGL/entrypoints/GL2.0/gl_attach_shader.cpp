/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_attach_shader.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiAttachShader(GLuint program,
                                        GLuint shader)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glAttachShader(program=[%d] shader=[%d])",
             program,
             shader);

    reinterpret_cast<PFNGLATTACHSHADERPROC>(OpenGL::g_cached_gl_attach_shader)(program,
                                                                               shader);
}