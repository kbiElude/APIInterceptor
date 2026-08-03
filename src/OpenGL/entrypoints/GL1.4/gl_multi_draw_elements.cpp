/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_elements.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiMultiDrawElements(GLenum             mode,
                                             const GLsizei*     count,
                                             GLenum             type,
                                             const void* const* indices,
                                             GLsizei            drawcount)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                count_chunk_id         = 0;
    APIInterceptor::DataChunkID             indices_chunk_id;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMultiDrawElements(mode=[%s] count=[%p] type=[%s] indices=[%p] drawcount=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 count,
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 indices,
                 static_cast<int32_t>(drawcount) );

        count_chunk_id = APIInterceptor::register_data_chunk(count,
                                                             (count != nullptr) ? sizeof(GLsizei) * static_cast<uint32_t>(drawcount) : 0);

        const auto& context   = OpenGL::get_context_state();
        const auto  bound_ebo = context.bound_buffers    [static_cast<size_t>(OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER)];

        if (bound_ebo != 0)
        {
            /* Each indices[i] is a byte offset into the bound EBO — capture the pointer array as raw bytes. */
            indices_chunk_id = APIInterceptor::register_data_chunk(indices,
                                                                   (indices != nullptr) ? sizeof(void*) * static_cast<uint32_t>(drawcount) : 0);
        }
        else
        {
            AI_ASSERT(type == GL_UNSIGNED_BYTE  ||
                      type == GL_UNSIGNED_SHORT ||
                      type == GL_UNSIGNED_INT);

            /* Each indices[i] is a CPU pointer to count[i] index values.
             * Register each draw's index data as a separate chunk and store the resulting IDs. */
            const uint32_t n_bytes_per_index = (type == GL_UNSIGNED_BYTE)  ? 1u
                                             : (type == GL_UNSIGNED_SHORT) ? 2u
                                                                           : 4u;

            std::vector<APIInterceptor::DataChunkID> per_draw_chunk_id_vec(static_cast<size_t>(drawcount) );

            for (int32_t n_draw = 0;
                         n_draw < static_cast<int32_t>(drawcount);
                       ++n_draw)
            {
                const void*    draw_indices  = (indices != nullptr) ? indices[n_draw]
                                                                    : nullptr;
                const uint32_t n_index_bytes = (draw_indices != nullptr  &&
                                                count        != nullptr) ? n_bytes_per_index * static_cast<uint32_t>(count[n_draw])
                                                                         : 0;

                per_draw_chunk_id_vec[n_draw] = APIInterceptor::register_data_chunk(draw_indices,
                                                                                    n_index_bytes);
            }

            indices_chunk_id = APIInterceptor::register_data_chunk(per_draw_chunk_id_vec.data(),
                                                                   static_cast<uint32_t>(per_draw_chunk_id_vec.size() ) * sizeof(APIInterceptor::DataChunkID) );
        }

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWELEMENTS,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (mode),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(count_chunk_id),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(indices_chunk_id),
                APIInterceptor::APIFunctionArgument::create_i32          (drawcount),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWELEMENTS,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMULTIDRAWELEMENTSPROC>(g_cached_gl_multi_draw_elements)(mode,
                                                                                      count,
                                                                                      type,
                                                                                      indices,
                                                                                      drawcount);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWELEMENTS,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (mode),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(count_chunk_id),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(indices_chunk_id),
            APIInterceptor::APIFunctionArgument::create_i32          (drawcount),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWELEMENTS,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
