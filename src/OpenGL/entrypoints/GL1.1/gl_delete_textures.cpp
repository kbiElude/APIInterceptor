/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_delete_textures.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteTextures(GLsizei       n,
                                          const GLuint* textures)
{
    AI_TRACE("glDeleteTextures(n=[%d] texture=[%p])",
             static_cast<int32_t>(n),
             textures);

    if (OpenGL::g_cached_gl_delete_textures == nullptr)
    {
        OpenGL::g_cached_gl_delete_textures = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glDeleteTextures");
    }

    reinterpret_cast<PFNGLDELETETEXTURESPROC>(OpenGL::g_cached_gl_delete_textures)(n,
                                                                                   textures);
}