/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_primitive_restart_index.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPrimitiveRestartIndex(GLuint index)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glPrimitiveRestartIndex(index=[%u])",
             index);

    reinterpret_cast<PFNGLPRIMITIVERESTARTINDEXPROC>(g_cached_gl_primitive_restart_index)(index);
}