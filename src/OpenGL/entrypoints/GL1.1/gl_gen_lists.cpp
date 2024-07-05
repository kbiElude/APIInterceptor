/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_gen_lists.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiGenLists(GLsizei range)
{
    AI_TRACE("glGenLists(range=[%d])",
             range);

    return reinterpret_cast<PFNGLGENLISTSPROC>(OpenGL::g_cached_gl_gen_lists)(range);
}