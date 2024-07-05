/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_disable_client_state.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDisableClientState(GLenum array)
{
    AI_TRACE("glDisableClientState(array=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(array) );

    reinterpret_cast<PFNGLDISABLECLIENTSTATEPROC>(OpenGL::g_cached_gl_disable_client_state)(array);
}