/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4dv(const GLdouble* v)
{
    AI_TRACE("glTexCoord4dv(v=[%p])",
             v);

    reinterpret_cast<PFNGLTEXCOORD4DVPROC>(OpenGL::g_cached_gl_tex_coord_4dv)(v);
}