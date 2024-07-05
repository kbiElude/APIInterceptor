/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord3i(GLint s,
                                      GLint t,
                                      GLint r)
{
    AI_TRACE("glTexCoord3i(s=[%d], t=[%d], r=[%d])",
             s,
             t,
             r);

    reinterpret_cast<PFNGLTEXCOORD3IPROC>(OpenGL::g_cached_gl_tex_coord_3i)(s,
                                                                            t,
                                                                            r);
}