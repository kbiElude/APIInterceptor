/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_delete_shader.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteShader(GLuint shader)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDeleteShader(shader=[%d])",
             shader);

    reinterpret_cast<PFNGLDELETESHADERPROC>(OpenGL::g_cached_gl_delete_shader)(shader);
}