/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_is_list.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsList(GLuint list)
{
    AI_TRACE("glIsList(list=[%d])",
             list);

    return reinterpret_cast<PFNGLISLISTPROC>(OpenGL::g_cached_gl_is_list)(list);
}