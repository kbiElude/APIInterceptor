/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_init_names.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiInitNames()
{
    AI_TRACE("glInitNames()");

    reinterpret_cast<PFNGLINITNAMESPROC>(OpenGL::g_cached_gl_init_names)();
}