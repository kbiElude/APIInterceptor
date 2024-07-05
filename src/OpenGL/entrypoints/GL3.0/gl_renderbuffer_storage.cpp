/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_renderbuffer_storage.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRenderbufferStorage(GLenum  target,
                                               GLenum  internalformat,
                                               GLsizei width,
                                               GLsizei height)
{
    AI_TRACE("glRenderbufferStorage(target=[%s] internalformat=[%s] width=[%d] height=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             static_cast<int32_t>(height) );

    if (OpenGL::g_cached_gl_renderbuffer_storage == nullptr)
    {
        OpenGL::g_cached_gl_renderbuffer_storage = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glRenderbufferStorage");
    }

    reinterpret_cast<PFNGLRENDERBUFFERSTORAGEPROC>(g_cached_gl_renderbuffer_storage)(target,
                                                                                     internalformat,
                                                                                     width,
                                                                                     height);
}