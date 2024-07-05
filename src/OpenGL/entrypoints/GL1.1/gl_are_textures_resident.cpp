/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_are_textures_resident.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"


GLboolean AI_APIENTRY OpenGL::aiAreTexturesResident(GLsizei       n,
                                                    const GLuint* textures,
                                                    GLboolean*    residences)
{
    AI_TRACE("glAreTexturesResident(n=[%d] textures=[%p] residences=[%p])",
             n,
             textures,
             residences);

    if (OpenGL::g_cached_are_textures_resident_ext == nullptr)
    {
        OpenGL::g_cached_are_textures_resident_ext = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glAreTexturesResidentEXT");
    }

    return reinterpret_cast<PFNGLARETEXTURESRESIDENTEXTPROC>(OpenGL::g_cached_are_textures_resident_ext)(n,
                                                                                                         textures,
                                                                                                         residences);
}