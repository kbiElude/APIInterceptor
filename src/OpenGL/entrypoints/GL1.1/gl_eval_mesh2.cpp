/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_mesh2.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalMesh2(GLenum mode,
                                     GLint  i1,
                                     GLint  i2,
                                     GLint  j1,
                                     GLint  j2)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glEvalMesh2(mode=[%s], i1=[%d], i2=[%d], j1=[%d], j2=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             i1,
             i2,
             j1,
             j2);

    reinterpret_cast<PFNGLEVALMESH2PROC>(OpenGL::g_cached_gl_eval_mesh2)(mode,
                                                                         i1,
                                                                         i2,
                                                                         j1,
                                                                         j2);
}