/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_is_query.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsQuery(GLuint id)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glIsQuery(id=[%u])",
             id);

    return reinterpret_cast<PFNGLISQUERYPROC>(OpenGL::g_cached_gl_is_query)(id);
}