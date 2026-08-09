/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_texture_storage2d_multisample.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTextureStorage2DMultisample(GLuint    texture,
                                                       GLsizei   samples,
                                                       GLenum    internalformat,
                                                       GLsizei   width,
                                                       GLsizei   height,
                                                       GLboolean fixedsamplelocations)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTextureStorage2DMultisample(texture=[%u] samples=[%d] internalformat=[%s] width=[%d] height=[%d] fixedsamplelocations=[%u])",
                 texture,
                 static_cast<int32_t>(samples),
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height),
                 static_cast<uint32_t>(fixedsamplelocations) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTURESTORAGE2DMULTISAMPLE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (texture),
                APIInterceptor::APIFunctionArgument::create_i32       (samples),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_i32       (width),
                APIInterceptor::APIFunctionArgument::create_i32       (height),
                APIInterceptor::APIFunctionArgument::create_u8        (fixedsamplelocations),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTURESTORAGE2DMULTISAMPLE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXTURESTORAGE2DMULTISAMPLEPROC>(OpenGL::g_cached_gl_texture_storage2d_multisample)(texture,
                                                                                                                  samples,
                                                                                                                  internalformat,
                                                                                                                  width,
                                                                                                                  height,
                                                                                                                  fixedsamplelocations);

        if (tracker.is_top_level_api_call() )
        {
            auto& context = OpenGL::get_context_state();

            context.set_texture_level_props(texture,
                                            0, /* multisample textures have a single implicit level */
                                            static_cast<uint32_t>(width),
                                            static_cast<uint32_t>(height),
                                            1);
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTURESTORAGE2DMULTISAMPLE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (texture),
            APIInterceptor::APIFunctionArgument::create_i32       (samples),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
            APIInterceptor::APIFunctionArgument::create_i32       (width),
            APIInterceptor::APIFunctionArgument::create_i32       (height),
            APIInterceptor::APIFunctionArgument::create_u8        (fixedsamplelocations),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTURESTORAGE2DMULTISAMPLE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
