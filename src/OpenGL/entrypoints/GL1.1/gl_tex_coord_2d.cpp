/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord2d(GLdouble s,
                                      GLdouble t)
{
    AI_TRACE("glTexCoord2d(s=[%.4lf], t=[%.4lf])",
             s,
             t);

    reinterpret_cast<PFNGLTEXCOORD2DPROC>(OpenGL::g_cached_gl_tex_coord_2d)(s,
                                                                            t);
}