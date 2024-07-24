/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_passthrough.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPassthrough(GLfloat token)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glPassThrough(token=[%.4f])",
             token);

    reinterpret_cast<PFNGLPASSTHROUGHPROC>(OpenGL::g_cached_gl_passthrough)(token);
}