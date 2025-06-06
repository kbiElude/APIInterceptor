/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.4/gl_blend_equation.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendEquation(GLenum mode)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBlendEquation(mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    reinterpret_cast<PFNGLBLENDEQUATIONPROC>(OpenGL::g_cached_gl_blend_equation)(mode);
}