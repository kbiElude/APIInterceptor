/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
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
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawElements(mode=[%s] count=[%d] type=[%s] indices=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 static_cast<int32_t>(count),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 indices);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTS,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const auto&                         context   = OpenGL::get_context_state();
            const auto                          bound_ebo = context.bound_buffers    [static_cast<size_t>(OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER)];
            APIInterceptor::APIFunctionArgument indices_arg;

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
                                                                                       (indices != nullptr) ? n_bytes_per_index * static_cast<uint32_t>(count) : 0);

                indices_arg = APIInterceptor::APIFunctionArgument::create_data_chunk_id(indices_chunk_id);
            }

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
                APIInterceptor::APIFunctionArgument::create_i32       (count),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                indices_arg,
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTS,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWELEMENTSPROC>(OpenGL::g_cached_gl_draw_elements)(mode,
                                                                                   count,
                                                                                   type,
                                                                                   indices);
    }
}