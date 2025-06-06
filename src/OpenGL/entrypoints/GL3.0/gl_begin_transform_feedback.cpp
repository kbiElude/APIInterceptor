/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_begin_transform_feedback.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBeginTransformFeedback(GLenum primitiveMode)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBeginTransformFeedback(primitiveMode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(primitiveMode) );

    reinterpret_cast<PFNGLBEGINTRANSFORMFEEDBACKPROC>(OpenGL::g_cached_gl_begin_transform_feedback)(primitiveMode);
}