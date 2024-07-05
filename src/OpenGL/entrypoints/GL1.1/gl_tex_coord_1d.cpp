/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord1d(GLdouble s)
{
    AI_TRACE("glTexCoord1d(s=[%.4lf])",
             s);

    reinterpret_cast<PFNGLTEXCOORD1DPROC>(OpenGL::g_cached_gl_tex_coord_1d)(s);
}