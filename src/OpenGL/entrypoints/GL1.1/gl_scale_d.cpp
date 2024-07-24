/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_scale_d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiScaled(GLdouble x,
                                  GLdouble y,
                                  GLdouble z)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glScaled(x=[%.4lf], y=[%.4lf], z=[%.4lf])",
             x,
             y,
             z);

    reinterpret_cast<PFNGLSCALEDPROC>(OpenGL::g_cached_gl_scale_d)(x,
                                                                   y,
                                                                   z);
}