/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_polygon_offset.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPolygonOffset(GLfloat factor,
                                         GLfloat units)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glPolygonOffset(factor=[%.4f] units=[%.4f])",
             factor,
             units);


    if (OpenGL::g_cached_gl_polygon_offset == nullptr)
    {
        OpenGL::g_cached_gl_polygon_offset = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glPolygonOffset");
    }

    reinterpret_cast<PFNGLPOLYGONOFFSETPROC>(g_cached_gl_polygon_offset)(factor,
                                                                         units);
}