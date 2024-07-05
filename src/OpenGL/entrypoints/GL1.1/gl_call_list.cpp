/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_call_list.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCallList(GLuint list)
{
    AI_TRACE("glCallList(list=[%d])",
             list);

    reinterpret_cast<PFNGLCALLLISTPROC>(OpenGL::g_cached_gl_call_list)(list);
}