/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_gen_textures.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenTextures(GLsizei n,
                                       GLuint* textures)
{
    AI_TRACE("glGenTextures(n=[%d] textures=[%p])",
             static_cast<int32_t>(n),
             textures);

    if (OpenGL::g_cached_gl_gen_textures == nullptr)
    {
        OpenGL::g_cached_gl_gen_textures = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGenTextures");
    }

    reinterpret_cast<PFNGLGENTEXTURESPROC>(OpenGL::g_cached_gl_gen_textures)(n,
                                                                             textures);
}