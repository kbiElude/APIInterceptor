/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_2dv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalCoord2dv(const GLdouble* u)
{
    AI_TRACE("glEvalCoord2dv(u=[%p])",
             u);

    reinterpret_cast<PFNGLEVALCOORD2DVPROC>(OpenGL::g_cached_gl_eval_coord_2dv)(u);
}