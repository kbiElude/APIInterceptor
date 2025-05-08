/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_vertex_attrib_i_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetVertexAttribIuiv(GLuint  index,
                                               GLenum  pname,
                                               GLuint* params)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetVertexAttribIuiv(index=[%u] pname=[%s] params=[%p])",
             index,
             OpenGL::Utils::get_raw_string_for_gl_enum(pname),
             params);

    reinterpret_cast<PFNGLGETVERTEXATTRIBIUIVPROC>(OpenGL::g_cached_gl_get_vertex_attrib_i_uiv)(index,
                                                                                                pname,
                                                                                                params);
}