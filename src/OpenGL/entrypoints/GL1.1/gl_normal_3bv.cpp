/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_normal_3bv.h"
#include "OpenGL/globals.h"
#include "Common/logger.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormal3bv(const GLbyte* v)
{
    AI_TRACE("glNormal3bv(v=[%p])",
             v);

    reinterpret_cast<PFNGLNORMAL3BVPROC>(OpenGL::g_cached_gl_normal_3bv)(v);
}