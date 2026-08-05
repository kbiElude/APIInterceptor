/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_invalidate_tex_sub_image.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiInvalidateTexSubImage(GLuint  texture,
                                                 GLint   level,
                                                 GLint   xoffset,
                                                 GLint   yoffset,
                                                 GLint   zoffset,
                                                 GLsizei width,
                                                 GLsizei height,
                                                 GLsizei depth)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glInvalidateTexSubImage(texture=[%u] level=[%d] xoffset=[%d] yoffset=[%d] zoffset=[%d] width=[%d] height=[%d] depth=[%d])",
                 texture,
                 level,
                 xoffset,
                 yoffset,
                 zoffset,
                 static_cast<int32_t>(width),
                 static_cast<int32_t>(height),
                 static_cast<int32_t>(depth));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLINVALIDATETEXSUBIMAGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(texture),
                APIInterceptor::APIFunctionArgument::create_i32(level),
                APIInterceptor::APIFunctionArgument::create_i32(xoffset),
                APIInterceptor::APIFunctionArgument::create_i32(yoffset),
                APIInterceptor::APIFunctionArgument::create_i32(zoffset),
                APIInterceptor::APIFunctionArgument::create_i32(width),
                APIInterceptor::APIFunctionArgument::create_i32(height),
                APIInterceptor::APIFunctionArgument::create_i32(depth),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLINVALIDATETEXSUBIMAGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLINVALIDATETEXSUBIMAGEPROC>(OpenGL::g_cached_gl_invalidate_tex_sub_image)(texture,
                                                                                                        level,
                                                                                                        xoffset,
                                                                                                        yoffset,
                                                                                                        zoffset,
                                                                                                        width,
                                                                                                        height,
                                                                                                        depth);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLINVALIDATETEXSUBIMAGE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(texture),
            APIInterceptor::APIFunctionArgument::create_i32(level),
            APIInterceptor::APIFunctionArgument::create_i32(xoffset),
            APIInterceptor::APIFunctionArgument::create_i32(yoffset),
            APIInterceptor::APIFunctionArgument::create_i32(zoffset),
            APIInterceptor::APIFunctionArgument::create_i32(width),
            APIInterceptor::APIFunctionArgument::create_i32(height),
            APIInterceptor::APIFunctionArgument::create_i32(depth),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLINVALIDATETEXSUBIMAGE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
