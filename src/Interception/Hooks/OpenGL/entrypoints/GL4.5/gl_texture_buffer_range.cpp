/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL4.5/gl_texture_buffer_range.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiTextureBufferRange(GLuint     texture,
                                                                   GLenum     internalformat,
                                                                   GLuint     buffer,
                                                                   GLintptr   offset,
                                                                   GLsizeiptr size)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTextureBufferRange(texture=[%u] internalformat=[%s] buffer=[%u] offset=[%d] size=[%d])",
                 texture,
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(internalformat),
                 buffer,
                 static_cast<int32_t>(offset),
                 static_cast<int32_t>(size) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTUREBUFFERRANGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (texture),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_u32       (buffer),
                APIInterceptor::APIFunctionArgument::create_i64       (static_cast<int64_t>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i64       (static_cast<int64_t>(size) ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTUREBUFFERRANGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXTUREBUFFERRANGEPROC>(Interception::Hooks::OpenGL::g_cached_gl_texture_buffer_range)(texture,
                                                                                                                     internalformat,
                                                                                                                     buffer,
                                                                                                                     offset,
                                                                                                                     size);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTUREBUFFERRANGE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (texture),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
            APIInterceptor::APIFunctionArgument::create_u32       (buffer),
            APIInterceptor::APIFunctionArgument::create_i64       (static_cast<int64_t>(offset) ),
            APIInterceptor::APIFunctionArgument::create_i64       (static_cast<int64_t>(size) ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTUREBUFFERRANGE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
