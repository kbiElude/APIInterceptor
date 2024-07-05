/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_index_ub.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiIndexub(GLubyte c)
{
    AI_TRACE("glIndexub(c=[%d])",
             static_cast<int32_t>(c) );

    reinterpret_cast<PFNGLINDEXUBPROC>(OpenGL::g_cached_gl_index_ub)(c);
}