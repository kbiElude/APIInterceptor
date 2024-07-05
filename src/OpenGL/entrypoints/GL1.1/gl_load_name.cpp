/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_load_name.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLoadName(GLuint name)
{
    AI_TRACE("glLoadName(name=[%d])",
             name);

    reinterpret_cast<PFNGLLOADNAMEPROC>(OpenGL::g_cached_gl_load_name)(name);
}