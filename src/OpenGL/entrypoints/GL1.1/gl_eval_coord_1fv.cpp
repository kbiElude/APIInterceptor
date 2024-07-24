/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_1fv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEvalCoord1fv(const GLfloat* u)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glEvalCoord1fv(u=[%p])",
             u);

    reinterpret_cast<PFNGLEVALCOORD1FVPROC>(OpenGL::g_cached_gl_eval_coord_1fv)(u);
}