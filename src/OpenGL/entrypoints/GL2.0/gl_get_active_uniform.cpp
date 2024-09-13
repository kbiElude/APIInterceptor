/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_active_uniform.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetActiveUniform(GLuint   program,
                                            GLuint   index,
                                            GLsizei  bufSize,
                                            GLsizei* length,
                                            GLint*   size,
                                            GLenum*  type,
                                            GLchar*  name)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetActiveUniform(program=[%u] index=[%u] bufSize=[%d] length=[%p] size=[%p] type=[%p] name=[%p])",
             program,
             index,
             static_cast<int32_t>(bufSize),
             length,
             size,
             type,
             name);

    reinterpret_cast<PFNGLGETACTIVEUNIFORMPROC>(OpenGL::g_cached_gl_get_active_uniform)(program,
                                                                                        index,
                                                                                        bufSize,
                                                                                        length,
                                                                                        size,
                                                                                        type,
                                                                                        name);
}