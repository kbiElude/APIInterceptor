/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_clear_accum.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClearAccum(GLfloat red,
                                      GLfloat green,
                                      GLfloat blue,
                                      GLfloat alpha)
{
    AI_TRACE("glClearAccum(red=[%.4f] green=[%.4f] blue=[%.4f] alpha=[%.4f])",
             red,
             green,
             blue,
             alpha);

    reinterpret_cast<PFNGLCLEARACCUMPROC>(OpenGL::g_cached_gl_clear_accum)(red,
                                                                           green,
                                                                           blue,
                                                                           alpha);
}