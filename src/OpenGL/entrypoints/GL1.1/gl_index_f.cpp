/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_index_f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiIndexf(GLfloat c)
{
    AI_TRACE("glIndexf(c=[%.4f])",
             c);

    reinterpret_cast<PFNGLINDEXFPROC>(OpenGL::g_cached_gl_index_f)(c);
}