/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_are_textures_resident.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"


GLboolean AI_APIENTRY OpenGL::aiAreTexturesResident(GLsizei       n,
                                                    const GLuint* textures,
                                                    GLboolean*    residences)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    GLboolean                           result              = FALSE;
    bool                                should_pass_through = true;

    AI_TRACE("glAreTexturesResident(n=[%d] textures=[%p] residences=[%p])",
             n,
             textures,
             residences);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLARETEXTURESRESIDENT,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32    (n),
            APIInterceptor::APIFunctionArgument::create_u32_ptr(textures),
            APIInterceptor::APIFunctionArgument::create_u8_ptr (residences),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLARETEXTURESRESIDENT,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLARETEXTURESRESIDENTEXTPROC>(OpenGL::g_cached_are_textures_resident_ext)(n,
                                                                                                               textures,
                                                                                                               residences);
    }

    return result;
}