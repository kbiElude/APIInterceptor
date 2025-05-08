/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_compile_shader.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCompileShader(GLuint shader)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glCompileShader(shader=[%d])",
             shader);

    reinterpret_cast<PFNGLCOMPILESHADERPROC>(OpenGL::g_cached_gl_compile_shader)(shader);
}