/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord1iv(const GLint* v)
{
    AI_TRACE("glTexCoord1iv(v=[%p])",
             v);

    reinterpret_cast<PFNGLTEXCOORD1IVPROC>(OpenGL::g_cached_gl_tex_coord_1iv)(v);
}