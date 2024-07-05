/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3s.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTexCoord3s(GLshort s,
                                      GLshort t,
                                      GLshort r)
 {
    AI_TRACE("glTexCoord3i(s=[%d], t=[%d], r=[%d])",
             static_cast<int32_t>(s),
             static_cast<int32_t>(t),
             static_cast<int32_t>(r) );

    reinterpret_cast<PFNGLTEXCOORD3SPROC>(OpenGL::g_cached_gl_tex_coord_3s)(s,
                                                                            t,
                                                                            r);
}