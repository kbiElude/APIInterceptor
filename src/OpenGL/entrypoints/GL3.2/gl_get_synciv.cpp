/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_get_synciv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetSynciv(GLsync   sync,
                                     GLenum   pname,
                                     GLsizei  bufSize,
                                     GLsizei* length,
                                     GLint*   values)
{
    AI_TRACE("glGetSynciv(sync=[%p] pname=[%s] bufSize=[%d] length=[%p] values=[%p])",
             sync,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             static_cast<int32_t>(bufSize),
             length,
             values);

    if (OpenGL::g_cached_gl_end_transform_feedback == nullptr)
    {
        OpenGL::g_cached_gl_end_transform_feedback = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndTransformFeedback");
    }

    reinterpret_cast<PFNGLGETSYNCIVPROC>(OpenGL::g_cached_gl_get_synciv)(sync,
                                                                         pname,
                                                                         bufSize,
                                                                         length,
                                                                         values);
}