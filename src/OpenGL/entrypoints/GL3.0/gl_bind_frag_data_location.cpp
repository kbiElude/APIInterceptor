/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_frag_data_location.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindFragDataLocation(GLuint        program,
                                                GLuint        color,
                                                const GLchar* name)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBindFragDataLocation(program=[%d] color=[%d] name=[%s])",
             program,
             color,
             name);

    reinterpret_cast<PFNGLBINDFRAGDATALOCATIONPROC>(OpenGL::g_cached_gl_bind_frag_data_location)(program,
                                                                                                 color,
                                                                                                 name);
}