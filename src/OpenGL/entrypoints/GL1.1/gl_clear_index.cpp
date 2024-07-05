/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_clear_index.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearIndex(GLfloat c)
{
    AI_TRACE("glClearIndex(c=[%.4f])",
             c);

    reinterpret_cast<PFNGLCLEARINDEXPROC>(OpenGL::g_cached_gl_clear_index)(c);
}