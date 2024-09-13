/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_is_texture.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsTexture(GLuint texture)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIsTexture(texture=[%u])",
               texture);

    return reinterpret_cast<PFNGLISTEXTUREPROC>(OpenGL::g_cached_gl_is_texture)(texture);
}