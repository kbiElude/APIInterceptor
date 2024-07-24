/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL2.0/gl_get_uniformiv.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetUniformiv(GLuint program,
                                        GLint  location,
                                        GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetUniformiv(program=[%u] location=[%d] params=[%p])",
             program,
             location,
             params);

    if (OpenGL::g_cached_gl_get_uniformiv == nullptr)
    {
        OpenGL::g_cached_gl_get_uniformiv = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glGetUniformiv");
    }

    reinterpret_cast<PFNGLGETUNIFORMIVPROC>(OpenGL::g_cached_gl_get_uniformiv)(program,
                                                                               location,
                                                                               params);
}