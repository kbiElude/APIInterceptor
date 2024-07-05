/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4i(GLint s,
                                      GLint t,
                                      GLint r,
                                      GLint q)
{
    AI_TRACE("glTexCoord4i(s=[%d], t=[%d], r=[%d], q=[%d])",
             s,
             t,
             r,
             q);

    reinterpret_cast<PFNGLTEXCOORD4IPROC>(OpenGL::g_cached_gl_tex_coord_4i)(s,
                                                                            t,
                                                                            r,
                                                                            q);
}