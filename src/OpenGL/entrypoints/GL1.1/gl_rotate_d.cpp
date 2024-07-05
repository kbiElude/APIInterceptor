/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_rotate_d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRotated(GLdouble angle,
                                   GLdouble x,
                                   GLdouble y,
                                   GLdouble z)
{
    AI_TRACE("glRotated(angle=[%.4lf], x=[%.4lf], y=[%.4lf], z=[%.4lf])",
             angle,
             x,
             y,
             z);

    reinterpret_cast<PFNGLROTATEDPROC>(OpenGL::g_cached_gl_rotate_d)(angle,
                                                                     x,
                                                                     y,
                                                                     z);
}