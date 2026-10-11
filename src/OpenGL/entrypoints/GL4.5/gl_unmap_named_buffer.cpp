/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_unmap_named_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiUnmapNamedBuffer(GLuint buffer)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    GLboolean                               result                 = GL_FALSE;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    /* Retrieve mapping state before the driver call invalidates the pointer. */
    void*                       mapped_ptr     = nullptr;
    OpenGL::BufferMappingAccess mapping_access = OpenGL::BufferMappingAccess::READ_ONLY;
    uint32_t                    unmap_chunk_id = 0;
    uint32_t                    size_bytes     = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glUnmapNamedBuffer(buffer=[%u])",
                 buffer);

        APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNMAPNAMEDBUFFER,
                                                      &pre_callback_func_ptr,
                                                      &pre_callback_func_arg);

        APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNMAPNAMEDBUFFER,
                                                       &post_callback_func_ptr,
                                                       &post_callback_func_arg);

        auto& context = OpenGL::get_context_state();

        {
            const auto buffer_props_iterator = context.buffer_object_id_to_buffer_props_ptr_map.find(buffer);

            AI_ASSERT(buffer_props_iterator                               != context.buffer_object_id_to_buffer_props_ptr_map.end() );
            AI_ASSERT(buffer_props_iterator->second                       != nullptr);
            AI_ASSERT(buffer_props_iterator->second->mapping_state.access != OpenGL::BufferMappingAccess::UNKNOWN);

            mapped_ptr     = buffer_props_iterator->second->mapping_state.mapped_ptr;
            mapping_access = buffer_props_iterator->second->mapping_state.access;
            size_bytes     = buffer_props_iterator->second->size_bytes;
        }
    }

    if (pre_callback_func_ptr != nullptr)
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(buffer),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNMAPNAMEDBUFFER,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    AI_ASSERT(should_pass_through);

    /* Snapshot the contents before the driver call: the mapped pointer is invalid once the buffer is unmapped.
     * Anything the application could have written to (WRITE_ONLY included) needs to be captured. */
    if (tracker.is_top_level_api_call() && post_callback_func_ptr != nullptr)
    {
        const bool is_writable = (mapping_access != OpenGL::BufferMappingAccess::READ_ONLY);

        unmap_chunk_id = APIInterceptor::register_data_chunk((is_writable)                          ? mapped_ptr
                                                                                                    : nullptr,
                                                             (is_writable && mapped_ptr != nullptr) ? size_bytes
                                                                                                    : 0u);
    }

    result = reinterpret_cast<PFNGLUNMAPNAMEDBUFFERPROC>(OpenGL::g_cached_gl_unmap_named_buffer)(buffer);

    if (tracker.is_top_level_api_call() )
    {
        auto& context = OpenGL::get_context_state();

        {
            const auto buffer_props_iterator = context.buffer_object_id_to_buffer_props_ptr_map.find(buffer);

            AI_ASSERT(buffer_props_iterator != context.buffer_object_id_to_buffer_props_ptr_map.end() );

            buffer_props_iterator->second->mapping_state = OpenGL::BufferMappingState();
        }

        if (post_callback_func_ptr != nullptr)
        {
            APIInterceptor::APIFunctionArgument result_arg;

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (buffer),
                APIInterceptor::APIFunctionArgument::create_u8           (result),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(unmap_chunk_id),
            };

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNMAPNAMEDBUFFER,
                                   post_callback_func_arg,
                                   static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                   args,
                                  &result_arg);
        }
    }

    return result;
}
