/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_begin_transform_feedback.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBeginTransformFeedback(GLenum primitiveMode)
{
    AI_TRACE("glBeginTransformFeedback(primitiveMode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(primitiveMode) );

    if (OpenGL::g_cached_gl_begin_transform_feedback == nullptr)
    {
        OpenGL::g_cached_gl_begin_transform_feedback = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glBeginTransformFeedback");
    }

    reinterpret_cast<PFNGLBEGINTRANSFORMFEEDBACKPROC>(OpenGL::g_cached_gl_begin_transform_feedback)(primitiveMode);
}