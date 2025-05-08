/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_end_conditional_render.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEndConditionalRender(void)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glEndConditionalRender()");

    reinterpret_cast<PFNGLENDCONDITIONALRENDERPROC>(OpenGL::g_cached_gl_end_conditional_render)();
}