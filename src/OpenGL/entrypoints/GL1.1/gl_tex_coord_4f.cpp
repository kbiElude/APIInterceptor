/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4f(GLfloat s,
                                      GLfloat t,
                                      GLfloat r,
                                      GLfloat q)
{
    AI_TRACE("glTexCoord4f(s=[%.4f], t=[%.4f], r=[%.4f], q=[%.4f])",
             s,
             t,
             r,
             q);

    reinterpret_cast<PFNGLTEXCOORD4FPROC>(OpenGL::g_cached_gl_tex_coord_4f)(s,
                                                                            t,
                                                                            r,
                                                                            q);
}