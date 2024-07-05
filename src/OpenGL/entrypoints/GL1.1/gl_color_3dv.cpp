/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_3dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor3dv(const GLdouble *v)
{
    AI_TRACE("glColor3dv(v=[%p])",
             v);

    reinterpret_cast<PFNGLCOLOR3DVPROC>(OpenGL::g_cached_gl_color_3dv)(v);
}