/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_index_ubv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiIndexubv(const GLubyte* c)
{
    AI_TRACE("glIndexubv(c=[%p])",
             c);

    reinterpret_cast<PFNGLINDEXUBVPROC>(OpenGL::g_cached_gl_index_ubv)(c);
}