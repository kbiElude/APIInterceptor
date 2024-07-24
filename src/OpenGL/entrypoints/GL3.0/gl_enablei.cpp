/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_enablei.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEnablei(GLenum target,
                                   GLuint index)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glEnablei(target=[%s] index=[%u])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             index);

    if (OpenGL::g_cached_gl_delete_framebuffers == nullptr)
    {
        OpenGL::g_cached_gl_delete_framebuffers = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDeleteFramebuffers");
    }

    reinterpret_cast<PFNGLENABLEIPROC>(OpenGL::g_cached_gl_enablei)(target,
                                                                    index);
}