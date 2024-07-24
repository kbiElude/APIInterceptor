/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_point2.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalPoint2(GLint i,
                                      GLint j)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glEvalPoint2(i=[%d], j=[%d])",
             i,
             j);

    reinterpret_cast<PFNGLEVALPOINT2PROC>(OpenGL::g_cached_gl_eval_point2)(i,
                                                                           j);
}