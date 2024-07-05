/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_push_name.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPushName(GLuint name)
{
    AI_TRACE("glPushName(name=[%d])",
             name);

    reinterpret_cast<PFNGLPUSHNAMEPROC>(OpenGL::g_cached_gl_push_name)(name);
}