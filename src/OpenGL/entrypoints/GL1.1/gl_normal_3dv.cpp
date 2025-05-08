/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_normal_3dv.h"
#include "OpenGL/globals.h"
#include "Common/logger.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormal3dv(const GLdouble* v)
{
    AI_TRACE("glNormal3dv(v=[%p])",
             v);

    reinterpret_cast<PFNGLNORMAL3DVPROC>(OpenGL::g_cached_gl_normal_3dv)(v);
}