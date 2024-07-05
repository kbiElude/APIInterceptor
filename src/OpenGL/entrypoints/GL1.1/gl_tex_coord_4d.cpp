/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4d(GLdouble s,
                                      GLdouble t,
                                      GLdouble r,
                                      GLdouble q)
{
    AI_TRACE("glTexCoord4d(s=[%.4lf], t=[%.4lf], r=[%.4lf], q=[%.4lf])",
             s,
             t,
             r,
             q);

    reinterpret_cast<PFNGLTEXCOORD4DPROC>(OpenGL::g_cached_gl_tex_coord_4d)(s,
                                                                            t,
                                                                            r,
                                                                            q);
}