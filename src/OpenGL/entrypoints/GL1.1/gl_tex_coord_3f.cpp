/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord3f(GLfloat s,
                                      GLfloat t,
                                      GLfloat r)
{
    AI_TRACE("glTexCoord3f(s=[%.4f], t=[%.4f], r=[%.4f])",
             s,
             t,
             r);

    reinterpret_cast<PFNGLTEXCOORD3FPROC>(OpenGL::g_cached_gl_tex_coord_3f)(s,
                                                                            t,
                                                                            r);
}