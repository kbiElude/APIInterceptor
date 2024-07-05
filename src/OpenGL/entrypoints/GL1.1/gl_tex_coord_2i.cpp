/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord2i(GLint s,
                                      GLint t)
{
    AI_TRACE("glTexCoord2i(s=[%d], t=[%d])",
             s,
             t);

    reinterpret_cast<PFNGLTEXCOORD2IPROC>(OpenGL::g_cached_gl_tex_coord_2i)(s,
                                                                            t);
}