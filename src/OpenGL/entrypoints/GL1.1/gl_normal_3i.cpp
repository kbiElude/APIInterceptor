/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_normal_3i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormal3i(GLint nx,
                                    GLint ny,
                                    GLint nz)
{
    AI_TRACE("glNormal3i(nx=[%d], ny=[%d], ny=[%d])",
             nx,
             ny,
             nz);

    reinterpret_cast<PFNGLNORMAL3IPROC>(OpenGL::g_cached_gl_normal_3i)(nx,
                                                                       ny,
                                                                       nz);
}