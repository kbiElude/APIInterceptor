/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_point1.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalPoint1(GLint i)
{
    AI_TRACE("glEvalPoint1(i=[%d])",
             i);

    reinterpret_cast<PFNGLEVALPOINT1PROC>(OpenGL::g_cached_gl_eval_point1)(i);
}