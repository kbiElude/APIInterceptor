/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_call_lists.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCallLists(GLsizei       n,
                                     GLenum        type,
                                     const GLvoid* lists)
{
    AI_TRACE("glCallLists(n=[%d], type=[%s], lists=[%p])",
             n,
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             lists);

    reinterpret_cast<PFNGLCALLLISTSPROC>(OpenGL::g_cached_gl_call_lists)(n,
                                                                         type,
                                                                         lists);
}