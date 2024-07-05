/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_accum.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiAccum(GLenum  op,
                                 GLfloat value)
{
    AI_TRACE("glAccum(op=[%s], value=[%.4f])",
             OpenGL::Utils::get_raw_string_for_gl_enum(op),
             value);

    reinterpret_cast<PFNGLACCUMPROC>(OpenGL::g_cached_gl_accum)(op,
                                                                value);
}