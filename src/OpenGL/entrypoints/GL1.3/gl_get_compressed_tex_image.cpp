/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.3/gl_get_compressed_tex_image.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
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

    if (OpenGL::g_cached_gl_end_transform_feedback == nullptr)
    {
        OpenGL::g_cached_gl_end_transform_feedback = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glEndTransformFeedback");
    }

    reinterpret_cast<PFNGLGETCOMPRESSEDTEXIMAGEPROC>(OpenGL::g_cached_gl_get_compressed_tex_image)(target,
                                                                                                   level,
                                                                                                   img);
}