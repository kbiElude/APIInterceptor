/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord2f(GLfloat s,
                                      GLfloat t)
{
    AI_TRACE("glTexCoord2f(s=[%.4f], t=[%.4f])",
             s,
             t);

    reinterpret_cast<PFNGLTEXCOORD2FPROC>(OpenGL::g_cached_gl_tex_coord_2f)(s,
                                                                            t);
}