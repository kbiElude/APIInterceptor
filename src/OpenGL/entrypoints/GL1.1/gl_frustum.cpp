/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_frustum.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiFrustum(GLdouble left,
                                   GLdouble right,
                                   GLdouble bottom,
                                   GLdouble top,
                                   GLdouble zNear,
                                   GLdouble zFar)
{
    AI_TRACE("glFrustum(left=[%.4lf], right=[%.4lf] bottom=[%.4lf] top=[%.4lf] zNear=[%.4lf] zFar=[%.4lf])",
             left,
             right,
             bottom,
             top,
             zNear,
             zFar);

    reinterpret_cast<PFNGLFRUSTUMPROC>(OpenGL::g_cached_gl_frustum)(left,
                                                                    right,
                                                                    bottom,
                                                                    top,
                                                                    zNear,
                                                                    zFar);
}