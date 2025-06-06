/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_query_objectiv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetQueryObjectiv(GLuint id,
                                            GLenum pname,
                                            GLint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetQueryObjectiv(id=[%u] pname=[%s] params=[%p])",
             id,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETQUERYOBJECTIVPROC>(OpenGL::g_cached_gl_get_query_objectiv)(id,
                                                                                        pname,
                                                                                        params);
}