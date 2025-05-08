/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_are_textures_resident.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"


GLboolean AI_APIENTRY OpenGL::aiAreTexturesResident(GLsizei       n,
                                                    const GLuint* textures,
                                                    GLboolean*    residences)
{
    void*                                   post_callback_func_arg  = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr  = nullptr;
    void*                                   pre_callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr   = nullptr;
    GLboolean                               result                  = FALSE;
    bool                                    should_pass_through     = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glAreTexturesResident(n=[%d] textures=[%p] residences=[%p])",
                 n,
                 textures,
                 residences);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLARETEXTURESRESIDENT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32    (n),
                APIInterceptor::APIFunctionArgument::create_u32_ptr(textures),
                APIInterceptor::APIFunctionArgument::create_u8_ptr (residences),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLARETEXTURESRESIDENT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLARETEXTURESRESIDENTEXTPROC>(OpenGL::g_cached_are_textures_resident_ext)(n,
                                                                                                               textures,
                                                                                                               residences);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLARETEXTURESRESIDENT,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_u8(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLARETEXTURESRESIDENT,
                                   post_callback_func_arg,
                                  &result_arg);
        }
    }

    return result;
}