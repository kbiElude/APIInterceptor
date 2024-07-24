/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_level_parameterfv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexLevelParameterfv(GLenum   target,
                                                  GLint    level,
                                                  GLenum   pname,
                                                  GLfloat* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetTexLevelParameterfv(target=[%s] level=[%d] pname=[%s] params=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    if (OpenGL::g_cached_gl_end_transform_feedback == nullptr)
    {
        OpenGL::g_cached_gl_end_transform_feedback = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndTransformFeedback");
    }

    reinterpret_cast<PFNGLGETTEXLEVELPARAMETERFVPROC>(OpenGL::g_cached_gl_get_tex_level_parameterfv)(target,
                                                                                                     level,
                                                                                                     pname,
                                                                                                     params);
}