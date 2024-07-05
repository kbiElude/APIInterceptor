/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_delete_lists.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDeleteLists(GLuint  list,
                                       GLsizei range)
{
    AI_TRACE("glDeleteLists(list=[%d] range=[%d])",
             list,
             range);

    reinterpret_cast<PFNGLDELETELISTSPROC>(OpenGL::g_cached_gl_delete_lists)(list,
                                                                             range);
}