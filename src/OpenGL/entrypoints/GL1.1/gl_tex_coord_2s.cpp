/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord2s(GLshort s,
                                      GLshort t)
{
    AI_TRACE("glTexCoord2s(s=[%d], t=[%d])",
             static_cast<int32_t>(s),
             static_cast<int32_t>(t) );

    reinterpret_cast<PFNGLTEXCOORD2SPROC>(OpenGL::g_cached_gl_tex_coord_2s)(s,
                                                                            t);
}