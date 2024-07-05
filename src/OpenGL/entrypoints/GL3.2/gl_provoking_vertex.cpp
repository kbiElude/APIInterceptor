/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.2/gl_provoking_vertex.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiProvokingVertex(GLenum mode)
{
    AI_TRACE("glProvokingVertex(mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    if (OpenGL::g_cached_gl_provoking_vertex == nullptr)
    {
        OpenGL::g_cached_gl_provoking_vertex = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glProvokingVertex");
    }

    reinterpret_cast<PFNGLPROVOKINGVERTEXPROC>(g_cached_gl_provoking_vertex)(mode);
}