/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_index_i.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiIndexi(GLint c)
{
    AI_TRACE("glIndexi(c=[%d])",
             c);

    reinterpret_cast<PFNGLINDEXIPROC>(OpenGL::g_cached_gl_index_i)(c);
}