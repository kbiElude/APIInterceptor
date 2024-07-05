/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_2f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalCoord2f(GLfloat u,
                                       GLfloat v)
{
    AI_TRACE("glEvalCoord2f(u=[%.4f], v=[%.4f])",
             u,
             v);

    reinterpret_cast<PFNGLEVALCOORD2FPROC>(OpenGL::g_cached_gl_eval_coord_2f)(u,
                                                                              v);
}