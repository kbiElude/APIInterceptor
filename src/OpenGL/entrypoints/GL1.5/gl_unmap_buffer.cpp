/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.5/gl_unmap_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiUnmapBuffer(GLenum target)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    /* Retrieve mapping state before the driver call invalidates the pointer. */
    GLuint                      bound_buffer_id  = 0;
    void*                       mapped_ptr       = nullptr;
    OpenGL::BufferMappingAccess mapping_access   = OpenGL::BufferMappingAccess::READ_ONLY;
    uint32_t                    size_bytes       = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glUnmapBuffer(target=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target) );

        APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNMAPBUFFER,
                                                      &pre_callback_func_ptr,
                                                      &pre_callback_func_arg);

        APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNMAPBUFFER,
                                                       &post_callback_func_ptr,
                                                       &post_callback_func_arg);

        OpenGL::BufferBindingTarget binding_target;
        auto&                       context         = OpenGL::get_context_state                           ();
        const bool                  is_known_target = OpenGL::Utils::get_buffer_binding_target_for_gl_enum(target,
                                                                                                           &binding_target);
        AI_ASSERT(is_known_target);

        bound_buffer_id = context.bound_buffers[static_cast<size_t>(binding_target)];
        AI_ASSERT(bound_buffer_id != 0);

        {
            const auto buffer_props_iterator = context.buffer_object_id_to_buffer_props_ptr_map.find(bound_buffer_id);

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
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNMAPBUFFER,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    AI_ASSERT(should_pass_through);

    const GLboolean result = reinterpret_cast<PFNGLUNMAPBUFFERPROC>(OpenGL::g_cached_gl_unmap_buffer)(target);

    if (tracker.is_top_level_api_call() )
    {
        auto& context = OpenGL::get_context_state();

        {
            const auto buffer_props_iterator = context.buffer_object_id_to_buffer_props_ptr_map.find(bound_buffer_id);

            AI_ASSERT(buffer_props_iterator != context.buffer_object_id_to_buffer_props_ptr_map.end() );

            buffer_props_iterator->second->mapping_state = OpenGL::BufferMappingState();
        }

        if (post_callback_func_ptr != nullptr)
        {   
            const bool is_readable    = (mapping_access == OpenGL::BufferMappingAccess::READ_WRITE);
            const auto unmap_chunk_id = APIInterceptor::register_data_chunk((is_readable)                          ? mapped_ptr
                                                                                                                   : nullptr,
                                                                            (is_readable && mapped_ptr != nullptr) ? size_bytes
                                                                                                                   : 0);

            {
                APIInterceptor::APIFunctionArgument result_arg;

                const APIInterceptor::APIFunctionArgument args[] =
                {
                    APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                    APIInterceptor::APIFunctionArgument::create_u8           (result),
                    APIInterceptor::APIFunctionArgument::create_data_chunk_id(unmap_chunk_id),
                };

                post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNMAPBUFFER,
                                       post_callback_func_arg,
                                       static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                       args,
                                      &result_arg);
            }
        }
    }

    return result;
}
