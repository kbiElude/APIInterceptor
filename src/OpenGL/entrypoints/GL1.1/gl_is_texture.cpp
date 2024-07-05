/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_is_texture.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsTexture(GLuint texture)
{
    AI_TRACE("glIsTexture(texture=[%u])",
               texture);

    if (OpenGL::g_cached_gl_is_texture == nullptr)
    {
        OpenGL::g_cached_gl_is_texture = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glIsTexture");
    }

    return reinterpret_cast<PFNGLISTEXTUREPROC>(OpenGL::g_cached_gl_is_texture)(texture);
}