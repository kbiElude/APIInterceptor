/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.5/gl_begin_query.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBeginQuery(GLenum target,
                                      GLuint id)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBeginQuery(target=[%s] id=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             id);

    reinterpret_cast<PFNGLBEGINQUERYPROC>(OpenGL::g_cached_gl_begin_query)(target,
                                                                           id);
}