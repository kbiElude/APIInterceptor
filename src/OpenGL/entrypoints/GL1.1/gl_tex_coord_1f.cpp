/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord1f(GLfloat s)
{
    AI_TRACE("glTexCoord1f(s=[%.4f])",
             s);

    reinterpret_cast<PFNGLTEXCOORD1FPROC>(OpenGL::g_cached_gl_tex_coord_1f)(s);
}