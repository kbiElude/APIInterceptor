/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_draw_elements.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawElements(GLenum      mode,
                                        GLsizei     count,
                                        GLenum      type,
                                        const void* indices)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    APIInterceptor::APIFunctionArgument     indices_arg;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawElements(mode=[%s] count=[%d] type=[%s] indices=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 static_cast<int32_t>(count),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 indices);

        {
            const auto& context   = OpenGL::get_context_state();
            const auto  bound_ebo = context.bound_buffers[static_cast<size_t>(OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER)];

            if (bound_ebo != 0)
            {
                indices_arg = APIInterceptor::APIFunctionArgument::create_void_ptr(indices);
            }
            else
            {
                AI_ASSERT(type == GL_UNSIGNED_BYTE  ||
                          type == GL_UNSIGNED_SHORT ||
                          type == GL_UNSIGNED_INT);

                const uint32_t n_bytes_per_index = (type == GL_UNSIGNED_BYTE)  ? 1u :
                                                   (type == GL_UNSIGNED_SHORT) ? 2u : 4u;
                const auto     indices_chunk_id  = APIInterceptor::register_data_chunk(indices,
                                                                                       (indices != nullptr) ? n_bytes_per_index * static_cast<uint32_t>(count) : 0u);

                indices_arg = APIInterceptor::APIFunctionArgument::create_data_chunk_id(indices_chunk_id);
            }
        }

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
                APIInterceptor::APIFunctionArgument::create_i32       (count),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                indices_arg,
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWELEMENTSPROC>(OpenGL::g_cached_gl_draw_elements)(mode,
                                                                                   count,
                                                                                   type,
                                                                                   indices);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
            APIInterceptor::APIFunctionArgument::create_i32       (count),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            indices_arg,
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}