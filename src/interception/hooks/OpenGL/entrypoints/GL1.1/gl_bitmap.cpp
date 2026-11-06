/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_bitmap.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/hooks/OpenGL/pixel_data_chunk.h"
#include "interception/core/OpenGLUtils/utils_enum.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiBitmap(GLsizei        width,
                                                       GLsizei        height,
                                                       GLfloat        xorig,
                                                       GLfloat        yorig,
                                                       GLfloat        xmove,
                                                       GLfloat        ymove,
                                                       const GLubyte* bitmapef)
{
    Interception::Hooks::OpenGL::PixelDataChunk pixels_chunk;
    void*                                       post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC     post_callback_func_ptr = nullptr;
    void*                                       pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC      pre_callback_func_ptr  = nullptr;
    bool                                        should_pass_through    = true;
    APIInterceptor::Tracker                     tracker;

    if (tracker.is_top_level_api_call() )
    {
        pixels_chunk = Interception::Hooks::OpenGL::PixelDataChunk::create_for_unpack_bitmap(bitmapef,
                                                                                             width,
                                                                                             height);
    }

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBitmap(width=[%d] width=[%d] xorig=[%.4f] yorig=[%.4f] xmove=[%.4f] ymove=[%.4f] bitmapef=[%p])",
                 width,
                 height,
                 xorig,
                 yorig,
                 xmove,
                 ymove,
                 bitmapef);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBITMAP,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32 (width),
                APIInterceptor::APIFunctionArgument::create_i32 (height),
                APIInterceptor::APIFunctionArgument::create_fp32(xorig),
                APIInterceptor::APIFunctionArgument::create_fp32(yorig),
                APIInterceptor::APIFunctionArgument::create_fp32(xmove),
                APIInterceptor::APIFunctionArgument::create_fp32(ymove),
                pixels_chunk.get_arg(),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBITMAP,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBITMAPPROC>(Interception::Hooks::OpenGL::g_cached_gl_bitmap)(width,
                                                                                           height,
                                                                                           xorig,
                                                                                           yorig,
                                                                                           xmove,
                                                                                           ymove,
                                                                                           bitmapef);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBITMAP,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32 (width),
            APIInterceptor::APIFunctionArgument::create_i32 (height),
            APIInterceptor::APIFunctionArgument::create_fp32(xorig),
            APIInterceptor::APIFunctionArgument::create_fp32(yorig),
            APIInterceptor::APIFunctionArgument::create_fp32(xmove),
            APIInterceptor::APIFunctionArgument::create_fp32(ymove),
            pixels_chunk.get_arg(),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBITMAP,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}