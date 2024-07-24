/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_index_s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiIndexs(GLshort c)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIndexs(c=[%d])",
             static_cast<int32_t>(c) );

    reinterpret_cast<PFNGLINDEXSPROC>(OpenGL::g_cached_gl_index_s)(c);
}