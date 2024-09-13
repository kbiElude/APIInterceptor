/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_attached_shaders.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetAttachedShaders(GLuint   program,
                                              GLsizei  maxCount,
                                              GLsizei* count,
                                              GLuint*  shaders)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetAttachedShaders(program=[%u] maxCount=[%d] count=[%p] shaders=[%p])",
             program,
             static_cast<int32_t>(maxCount),
             count,
             shaders);

    reinterpret_cast<PFNGLGETATTACHEDSHADERSPROC>(OpenGL::g_cached_gl_get_attached_shaders)(program,
                                                                                            maxCount,
                                                                                            count,
                                                                                            shaders);
}