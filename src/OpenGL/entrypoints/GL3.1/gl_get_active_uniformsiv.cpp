/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniformsiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetActiveUniformsiv(GLuint        program,
                                               GLsizei       uniformCount,
                                               const GLuint* uniformIndices,
                                               GLenum        pname,
                                               GLint*        params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetActiveUniformsiv(program=[%u] uniformCount=[%d] uniformIndices=[%p] pname=[%s] params=[%p])",
             program,
             static_cast<int32_t>(uniformCount),
             uniformIndices,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETACTIVEUNIFORMSIVPROC>(OpenGL::g_cached_gl_get_active_uniformsiv)(program,
                                                                                              uniformCount,
                                                                                              uniformIndices,
                                                                                              pname,
                                                                                              params);
}