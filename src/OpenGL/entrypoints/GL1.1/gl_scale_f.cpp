/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_scale_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiScalef(GLfloat x,
                                  GLfloat y,
                                  GLfloat z)
{
    AI_TRACE("glScalef(x=[%.4f], y=[%.4f], z=[%.4f])",
             x,
             y,
             z);

    reinterpret_cast<PFNGLSCALEFPROC>(OpenGL::g_cached_gl_scale_f)(x,
                                                                   y,
                                                                   z);
}