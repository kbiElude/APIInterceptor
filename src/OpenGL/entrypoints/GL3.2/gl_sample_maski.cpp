/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_sample_maski.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiSampleMaski(GLuint     maskNumber,
                                       GLbitfield mask)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glSampleMaski(maskNumber=[%u] mask=[%x])",
             maskNumber,
             mask);

    reinterpret_cast<PFNGLSAMPLEMASKIPROC>(g_cached_gl_sample_maski)(maskNumber,
                                                                     mask);
}