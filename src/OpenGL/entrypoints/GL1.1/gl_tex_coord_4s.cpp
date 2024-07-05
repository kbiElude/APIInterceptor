/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord4s(GLshort s,
                                      GLshort t,
                                      GLshort r,
                                      GLshort q)
{
    AI_TRACE("glTexCoord4s(s=[%d], t=[%d], r=[%d], q=[%d])",
             static_cast<int32_t>(s),
             static_cast<int32_t>(t),
             static_cast<int32_t>(r),
             static_cast<int32_t>(q) );

    reinterpret_cast<PFNGLTEXCOORD4SPROC>(OpenGL::g_cached_gl_tex_coord_4s)(s,
                                                                            t,
                                                                            r,
                                                                            q);
}