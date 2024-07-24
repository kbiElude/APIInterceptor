/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_sample_coverage.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiSampleCoverage(GLfloat   value,
                                          GLboolean invert)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glSampleCoverage(value=[%.4f] invert=[%d])",
             value,
             (invert == GL_TRUE) ? 1 : 0);

    if (OpenGL::g_cached_gl_sample_coverage == nullptr)
    {
        OpenGL::g_cached_gl_sample_coverage = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glSampleCoverage");
    }

    reinterpret_cast<PFNGLSAMPLECOVERAGEPROC>(g_cached_gl_sample_coverage)(value,
                                                                           invert);
}