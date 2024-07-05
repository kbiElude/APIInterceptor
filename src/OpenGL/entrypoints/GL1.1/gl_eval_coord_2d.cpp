/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_2d.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalCoord2d(GLdouble u,
                                       GLdouble v)
{
    AI_TRACE("glEvalCoord2d(u=[%.4f], v=[%.4f])",
             u,
             v);

    reinterpret_cast<PFNGLEVALCOORD2DPROC>(OpenGL::g_cached_gl_eval_coord_2d)(u,
                                                                              v);
}