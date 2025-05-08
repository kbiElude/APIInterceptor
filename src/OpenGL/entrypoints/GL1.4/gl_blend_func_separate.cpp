/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.4/gl_blend_func_separate.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBlendFuncSeparate(GLenum sfactorRGB,
                                             GLenum dfactorRGB,
                                             GLenum sfactorAlpha,
                                             GLenum dfactorAlpha)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBlendFuncSeparate(sfactorRGB=[%s] dfactorRGB=[%s] sfactorAlpha=[%s] dfactorAlpha=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(sfactorRGB),
             OpenGL::Utils::get_raw_string_for_gl_enum(dfactorRGB),
             OpenGL::Utils::get_raw_string_for_gl_enum(sfactorAlpha),
             OpenGL::Utils::get_raw_string_for_gl_enum(dfactorAlpha) );

    reinterpret_cast<PFNGLBLENDFUNCSEPARATEPROC>(OpenGL::g_cached_gl_blend_func_separate)(sfactorRGB,
                                                                                          dfactorRGB,
                                                                                          sfactorAlpha,
                                                                                          dfactorAlpha);
}