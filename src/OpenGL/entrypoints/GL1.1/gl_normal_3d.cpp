/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_normal_3d.h"
#include "OpenGL/globals.h"
#include "Common/logger.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormal3d(GLdouble nx,
                                    GLdouble ny,
                                    GLdouble nz)
{
    AI_TRACE("glNormal3d(nx=[%.4lf], ny=[%.4lf], ny=[%.4lf])",
             nx,
             ny,
             nz);

    reinterpret_cast<PFNGLNORMAL3DPROC>(OpenGL::g_cached_gl_normal_3d)(nx,
                                                                       ny,
                                                                       nz);
}