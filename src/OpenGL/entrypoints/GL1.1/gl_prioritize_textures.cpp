/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_prioritize_textures.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPrioritizeTextures(GLsizei n,
                                              const GLuint* textures,
                                              const GLclampf* priorities)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glPrioritizeTexturesEXT(n=[%d] textures=[%p] priorities=[%p])",
             n,
             textures,
             priorities);

    if (OpenGL::g_cached_prioritize_textures_ext == nullptr)
    {
        OpenGL::g_cached_prioritize_textures_ext = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glPrioritizeTexturesEXT");
    }

    reinterpret_cast<PFNGLPRIORITIZETEXTURESEXTPROC>(OpenGL::g_cached_prioritize_textures_ext)(n,
                                                                                               textures,
                                                                                               priorities);
}