/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.2/gl_tex_image_2d_multisample.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexImage2DMultisample(GLenum    target,
                                                 GLsizei   samples,
                                                 GLenum    internalformat,
                                                 GLsizei   width,
                                                 GLsizei   height,
                                                 GLboolean fixedsamplelocations)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glTexImage2DMultisample(target=[%s] samples=[%d] internalformat=[%s] width=[%d] height=[%d] fixedsamplelocations=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             static_cast<int32_t>(samples),
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             (fixedsamplelocations == GL_TRUE) ? 1 : 0);

    reinterpret_cast<PFNGLTEXIMAGE2DMULTISAMPLEPROC>(OpenGL::g_cached_gl_tex_image_2DMultisample)(target,
                                                                                                  samples,
                                                                                                  internalformat,
                                                                                                  width,
                                                                                                  height,
                                                                                                  fixedsamplelocations);
}