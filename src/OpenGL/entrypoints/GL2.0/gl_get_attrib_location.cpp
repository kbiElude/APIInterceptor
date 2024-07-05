/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_attrib_location.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLint AI_APIENTRY OpenGL::aiGetAttribLocation(GLuint        program,
                                              const GLchar* name)
{
    AI_TRACE("glGetAttribLocation(program=[%u] name=[%s])",
             program,
             name);

    if (OpenGL::g_cached_gl_end_transform_feedback == nullptr)
    {
        OpenGL::g_cached_gl_end_transform_feedback = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndTransformFeedback");
    }

    return reinterpret_cast<PFNGLGETATTRIBLOCATIONPROC>(OpenGL::g_cached_gl_get_attrib_location)(program,
                                                                                                 name);
}