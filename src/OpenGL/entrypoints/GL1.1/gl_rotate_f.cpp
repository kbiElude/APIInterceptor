/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_rotate_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiRotatef(GLfloat angle,
                                   GLfloat x,
                                   GLfloat y,
                                   GLfloat z)
{
    AI_TRACE("glRotatef(angle=[%.4f], x=[%.4f], y=[%.4f], z=[%.4f])",
             angle,
             x,
             y,
             z);

    reinterpret_cast<PFNGLROTATEFPROC>(OpenGL::g_cached_gl_rotate_f)(angle,
                                                                     x,
                                                                     y,
                                                                     z);
}