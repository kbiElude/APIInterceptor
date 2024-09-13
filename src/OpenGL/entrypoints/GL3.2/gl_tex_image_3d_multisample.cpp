/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_tex_image_3d_multisample.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexImage3DMultisample(GLenum    target,
                                                 GLsizei   samples,
                                                 GLenum    internalformat,
                                                 GLsizei   width,
                                                 GLsizei   height,
                                                 GLsizei   depth,
                                                 GLboolean fixedsamplelocations)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glTexImage3DMultisample(target=[%s] samples=[%d] internalformat=[%s] width=[%d] height=[%d] depth=[%d] fixedsamplelocations=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             static_cast<int32_t>(samples),
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             static_cast<int32_t>(height),
             static_cast<int32_t>(depth),
             (fixedsamplelocations == GL_TRUE) ? 1 : 0);

    reinterpret_cast<PFNGLTEXIMAGE3DMULTISAMPLEPROC>(OpenGL::g_cached_gl_tex_image_3DMultisample)(target,
                                                                                                  samples,
                                                                                                  internalformat,
                                                                                                  width,
                                                                                                  height,
                                                                                                  depth,
                                                                                                  fixedsamplelocations);
}