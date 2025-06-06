/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL1.3/gl_get_compressed_tex_image.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetCompressedTexImage(GLenum target,
                                                 GLint  level,
                                                 void*  img)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGetCompressedTexImage(target=[%s] level=[%d] img=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target),
             level,
             img);

    reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEPROC>(OpenGL::g_cached_gl_get_compressed_tex_image)(target,
                                                                                                   level,
                                                                                                   img);
}