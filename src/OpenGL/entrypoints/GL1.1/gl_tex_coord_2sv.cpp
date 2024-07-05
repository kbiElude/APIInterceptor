/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2sv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord2sv(const GLshort* v)
{
    AI_TRACE("glTexCoord2sv(v=[%p])",
             v);

    reinterpret_cast<PFNGLTEXCOORD2SVPROC>(OpenGL::g_cached_gl_tex_coord_2sv)(v);
}