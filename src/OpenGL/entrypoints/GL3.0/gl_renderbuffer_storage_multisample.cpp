/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_renderbuffer_storage_multisample.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRenderbufferStorageMultisample(GLenum  target,
                                                          GLsizei samples,
                                                          GLenum  internalformat,
                                                          GLsizei width,
                                                          GLsizei height)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glRenderbufferStorageMultisample(target=[%s] samples=[%d] internalformat=[%s] width=[%d] height=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             static_cast<int32_t>(samples),
             OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
             static_cast<int32_t>(width),
             static_cast<int32_t>(height) );

    reinterpret_cast<PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC>(g_cached_gl_renderbuffer_storage_multisample)(target,
                                                                                                            samples,
                                                                                                            internalformat,
                                                                                                            width,
                                                                                                            height);
}