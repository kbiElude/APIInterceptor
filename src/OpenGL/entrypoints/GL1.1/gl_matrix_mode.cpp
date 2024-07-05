/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_matrix_mode.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMatrixMode(GLenum mode)
{
    AI_TRACE("glMatrixMode(mode=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode) );

    reinterpret_cast<PFNGLMATRIXMODEPROC>(OpenGL::g_cached_gl_matrix_mode)(mode);
}