/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_get_map_iv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetMapiv(GLenum target,
                                    GLenum query,
                                    GLint* v)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetMapiv(target=[%s], query=[%s], v=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             OpenGL::Utils::get_raw_string_for_gl_enum(query),
             v);

    reinterpret_cast<PFNGLGETMAPIVPROC>(OpenGL::g_cached_gl_get_map_iv)(target,
                                                                        query,
                                                                        v);
}