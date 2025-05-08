/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_transform_feedback_varyings.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTransformFeedbackVaryings(GLuint               program,
                                                     GLsizei              count,
                                                     const GLchar* const* varyings,
                                                     GLenum               bufferMode)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    /* TODO: Make me more useful */
    AI_TRACE("glTransformFeedbackVaryings(program=[%u] count=[%d] varyings=[%p] bufferMode=[%s])",
             program,
             static_cast<int32_t>(count),
             varyings,
             OpenGL::Utils::get_raw_string_for_gl_enum(bufferMode) );

    reinterpret_cast<PFNGLTRANSFORMFEEDBACKVARYINGSPROC>(OpenGL::g_cached_gl_transform_feedback_varyings)(program,
                                                                                                          count,
                                                                                                          varyings,
                                                                                                          bufferMode);
}