/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_1f.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalCoord1f(GLfloat u)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glEvalCoord1f(u=[%.4f])",
             u);

    reinterpret_cast<PFNGLEVALCOORD1FPROC>(OpenGL::g_cached_gl_eval_coord_1f)(u);
}