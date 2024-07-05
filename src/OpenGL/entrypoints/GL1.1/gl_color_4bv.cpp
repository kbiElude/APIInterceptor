/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_color_4bv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiColor4bv(const GLbyte *v)
{
    AI_TRACE("glColor4bv(v=[%p])",
             v);

    reinterpret_cast<PFNGLCOLOR4BVPROC>(OpenGL::g_cached_gl_color_4bv)(v);
}