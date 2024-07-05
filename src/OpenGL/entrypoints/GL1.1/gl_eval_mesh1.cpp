/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_mesh1.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalMesh1(GLenum mode,
                                     GLint  i1,
                                     GLint  i2)
{
    AI_TRACE("glEvalMesh1(mode=[%s], i1=[%d], i2=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             i1,
             i2);

    reinterpret_cast<PFNGLEVALMESH1PROC>(OpenGL::g_cached_gl_eval_mesh1)(mode,
                                                                         i1,
                                                                         i2);
}