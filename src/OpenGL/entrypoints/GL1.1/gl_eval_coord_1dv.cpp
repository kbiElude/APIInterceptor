/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_1dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalCoord1dv(const GLdouble* u)
{
    AI_TRACE("glEvalCoord1dv(u=[%p])",
             u);

    reinterpret_cast<PFNGLEVALCOORD1DVPROC>(OpenGL::g_cached_gl_eval_coord_1dv)(u);
}