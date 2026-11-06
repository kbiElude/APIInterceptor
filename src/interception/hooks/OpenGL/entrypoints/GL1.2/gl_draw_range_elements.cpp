/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/client_array_chunk.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.2/gl_draw_range_elements.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/core/OpenGLUtils/utils_enum.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiDrawRangeElements(GLenum      mode,
                                                                  GLuint      start,
                                                                  GLuint      end,
                                                                  GLsizei     count,
                                                                  GLenum      type,
                                                                  const void* indices)
{
    Interception::Hooks::OpenGL::ClientArrayChunk client_arrays_chunk;
    void*                                         post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC       post_callback_func_ptr = nullptr;
    void*                                         pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC        pre_callback_func_ptr  = nullptr;
    bool                                          should_pass_through    = true;
    APIInterceptor::Tracker                       tracker;

    client_arrays_chunk.add_elements(count,
                                     type,
                                     indices,
                                     0);

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawRangeElements(mode=[%s] start=[%d] end=[%d] count=[%d] type=[%s] indices=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(mode),
                 static_cast<int32_t>(start),
                 static_cast<int32_t>(end),
                 static_cast<int32_t>(count),
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(type),
                 indices);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWRANGEELEMENTS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (mode),
                APIInterceptor::APIFunctionArgument::create_u32          (start),
                APIInterceptor::APIFunctionArgument::create_u32          (end),
                APIInterceptor::APIFunctionArgument::create_i32          (count),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
                client_arrays_chunk.get_indices_arg(),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(client_arrays_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWRANGEELEMENTS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWRANGEELEMENTSPROC>(Interception::Hooks::OpenGL::g_cached_gl_draw_range_elements)(mode,
                                                                                                                   start,
                                                                                                                   end,
                                                                                                                   count,
                                                                                                                   type,
                                                                                                                   indices);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWRANGEELEMENTS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (mode),
            APIInterceptor::APIFunctionArgument::create_u32          (start),
            APIInterceptor::APIFunctionArgument::create_u32          (end),
            APIInterceptor::APIFunctionArgument::create_i32          (count),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
            client_arrays_chunk.get_indices_arg(),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(client_arrays_chunk.get_id() ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWRANGEELEMENTS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
