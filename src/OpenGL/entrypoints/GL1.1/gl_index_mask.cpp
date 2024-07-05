/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_index_mask.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiIndexMask(GLuint mask)
{
    AI_TRACE("glIndexMask(mask=[%d])",
             mask);

    reinterpret_cast<PFNGLINDEXMASKPROC>(OpenGL::g_cached_gl_index_mask)(mask);
}