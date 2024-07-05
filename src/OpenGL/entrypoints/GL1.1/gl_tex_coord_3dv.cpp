/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord3dv(const GLdouble* v)
{
    AI_TRACE("glTexCoord3dv(v=[%p])",
             v);

    reinterpret_cast<PFNGLTEXCOORD3DVPROC>(OpenGL::g_cached_gl_tex_coord_3dv)(v);
}