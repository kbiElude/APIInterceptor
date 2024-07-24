/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_image.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTexImage(GLenum target,
                                       GLint  level,
                                       GLenum format,
                                       GLenum type,
                                       void*  pixels)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetTexImage(target=[%s] level=[%d] format=[%s] type=[%s] pixels=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             pixels);

    if (OpenGL::g_cached_gl_get_tex_image == nullptr)
    {
        OpenGL::g_cached_gl_get_tex_image = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetTexImage");
    }

    reinterpret_cast<PFNGLGETTEXIMAGEPROC>(OpenGL::g_cached_gl_get_tex_image)(target,
                                                                              level,
                                                                              format,
                                                                              type,
                                                                              pixels);
}