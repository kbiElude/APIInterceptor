/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_validate_program.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiValidateProgram(GLuint program)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glValidateProgram(program=[%u])",
             program);

    reinterpret_cast<PFNGLVALIDATEPROGRAMPROC>(OpenGL::g_cached_gl_validate_program)(program);
}