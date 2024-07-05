/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_feedback_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFeedbackBuffer(GLsizei  size,
                                          GLenum   type,
                                          GLfloat* buffer)
{
    AI_TRACE("glFeedbackBuffer(size={%d], type=[%s], buffer=[%p])",
             size,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             buffer);

    reinterpret_cast<PFNGLFEEDBACKBUFFERPROC>(OpenGL::g_cached_gl_feedback_buffer)(size,
                                                                                   type,
                                                                                   buffer);
}