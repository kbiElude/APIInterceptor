/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_clamp_color.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClampColor(GLenum target,
                                      GLenum clamp)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glClampColor(target=[%s] clamp=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(clamp) );

    reinterpret_cast<PFNGLCLAMPCOLORPROC>(OpenGL::g_cached_gl_clamp_color)(target,
                                                                           clamp);
}