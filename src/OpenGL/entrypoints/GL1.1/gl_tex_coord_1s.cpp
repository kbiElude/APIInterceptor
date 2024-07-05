/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord1s(GLshort s)
{
    AI_TRACE("glTexCoord1s(s=[%d])",
             static_cast<int32_t>(s) );

    reinterpret_cast<PFNGLTEXCOORD1SPROC>(OpenGL::g_cached_gl_tex_coord_1s)(s);
}