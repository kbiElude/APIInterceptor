/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_active_attrib.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetActiveAttrib(GLuint   program,
                                           GLuint   index,
                                           GLsizei  bufSize,
                                           GLsizei* length,
                                           GLint*   size,
                                           GLenum*  type,
                                           GLchar*  name)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetActiveAttrib(program=[%u] index=[%u] bufSize=[%d] length=[%p] size=[%p] type=[%p] name=[%p])",
             program,
             index,
             static_cast<int32_t>(bufSize),
             length,
             size,
             type,
             name);

    reinterpret_cast<PFNGLGETACTIVEATTRIBPROC>(OpenGL::g_cached_gl_get_active_attrib)(program,
                                                                                      index,
                                                                                      bufSize,
                                                                                      length,
                                                                                      size,
                                                                                      type,
                                                                                      name);
}