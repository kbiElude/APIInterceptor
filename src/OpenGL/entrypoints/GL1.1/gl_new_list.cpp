/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_new_list.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiNewList(GLuint list,
                                   GLenum mode)
{
    AI_TRACE("glNewList(list=[%d], mode=[%s])",
             list,
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    reinterpret_cast<PFNGLNEWLISTPROC>(OpenGL::g_cached_gl_new_list)(list,
                                                                     mode);
}