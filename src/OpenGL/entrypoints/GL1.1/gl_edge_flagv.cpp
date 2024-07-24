/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_edge_flagv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEdgeFlagv(const GLboolean *flag)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glEdgeFlagv(flag=[%p])",
             flag);

    reinterpret_cast<PFNGLEDGEFLAGVPROC>(OpenGL::g_cached_gl_edge_flagv)(flag);
}