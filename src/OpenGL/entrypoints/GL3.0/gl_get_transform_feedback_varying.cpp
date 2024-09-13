/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.0/gl_get_transform_feedback_varying.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetTransformFeedbackVarying(GLuint   program,
                                                       GLuint   index,
                                                       GLsizei  bufSize,
                                                       GLsizei* length,
                                                       GLsizei* size,
                                                       GLenum*  type,
                                                       GLchar*  name)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetTransformFeedbackVarying(program=[%u] index[%u] bufSize=[%d] length=[%p] size=[%p] type=[%p] name=[%p])",
             program,
             index,
             static_cast<int32_t>(bufSize),
             length,
             size,
             type,
             name);

    reinterpret_cast<PFNGLGETTRANSFORMFEEDBACKVARYINGPROC>(OpenGL::g_cached_gl_get_transform_feedback_varying)(program,
                                                                                                               index,
                                                                                                               bufSize,
                                                                                                               length,
                                                                                                               size,
                                                                                                               type,
                                                                                                               name);
}