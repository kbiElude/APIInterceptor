/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_normal_3f.h"
#include "OpenGL/globals.h"
#include "Common/logger.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormal3f(GLfloat nx,
                                    GLfloat ny,
                                    GLfloat nz)
{
    AI_TRACE("glNormal3f(nx=[%.4f], ny=[%.4f], ny=[%.4f])",
             nx,
             ny,
             nz);

    reinterpret_cast<PFNGLNORMAL3FPROC>(OpenGL::g_cached_gl_normal_3f)(nx,
                                                                       ny,
                                                                       nz);
}