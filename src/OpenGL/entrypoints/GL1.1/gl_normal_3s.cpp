/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3s.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNormal3s(GLshort nx,
                                    GLshort ny,
                                    GLshort nz)
{
    AI_TRACE("glNormal3s(nx=[%d], ny=[%d], ny=[%d])",
             static_cast<int32_t>(nx),
             static_cast<int32_t>(ny),
             static_cast<int32_t>(nz) );

    reinterpret_cast<PFNGLNORMAL3SPROC>(OpenGL::g_cached_gl_normal_3s)(nx,
                                                                       ny,
                                                                       nz);
}