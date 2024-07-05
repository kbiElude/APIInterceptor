/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_pop_matrix.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPopMatrix()
{
    AI_TRACE("glPopMatrix()");

    reinterpret_cast<PFNGLPOPMATRIXPROC>(OpenGL::g_cached_gl_pop_matrix)();
}