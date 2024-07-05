/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord3d(GLdouble s,
                                      GLdouble t,
                                      GLdouble r)
{
    AI_TRACE("glTexCoord3d(s=[%.4lf], t=[%.4lf], r=[%.4lf])",
             s,
             t,
             r);

    reinterpret_cast<PFNGLTEXCOORD3DPROC>(OpenGL::g_cached_gl_tex_coord_3d)(s,
                                                                            t,
                                                                            r);
}