/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.5/gl_map_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void* AI_APIENTRY OpenGL::aiMapBuffer(GLenum target,
                                      GLenum access)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMapBuffer(target=[%s] access=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 OpenGL::Utils::get_raw_string_for_gl_enum(access) );

        APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFER,
                                                      &pre_callback_func_ptr,
                                                      &pre_callback_func_arg);

        APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFER,
                                                       &post_callback_func_ptr,
                                                       &post_callback_func_arg);
    }

    if (pre_callback_func_ptr != nullptr)
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(access),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFER,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    AI_ASSERT(should_pass_through);

    void* const mapped_ptr = reinterpret_cast<PFNGLMAPBUFFERPROC>(OpenGL::g_cached_gl_map_buffer)(target,
                                                                                                   access);

    if (tracker.is_top_level_api_call() )
    {
        OpenGL::BufferBindingTarget binding_target;
        uint32_t                    buffer_size_bytes = 0;
        auto&                       context           = OpenGL::get_context_state();
        OpenGL::BufferMappingAccess mapping_access;
        const bool                  is_known_access   = OpenGL::Utils::get_buffer_mapping_access_for_gl_enum(access,
                                                                                                             &mapping_access);

        AI_ASSERT(is_known_access);

        {
            const bool is_known_target = OpenGL::Utils::get_buffer_binding_target_for_gl_enum(target,
                                                                                              &binding_target);

            AI_ASSERT(is_known_target);
        }

        const GLuint bound_buffer_id = context.bound_buffers[static_cast<size_t>(binding_target)];

        AI_ASSERT(bound_buffer_id != 0);

        if (mapped_ptr != nullptr)
        {
            auto& buffer_props_ptr = context.buffer_object_id_to_buffer_props_ptr_map[bound_buffer_id];

            if (buffer_props_ptr == nullptr)
            {
                buffer_props_ptr.reset(new OpenGL::BufferProps() );
            }

            buffer_props_ptr->mapping_state.mapped_ptr = mapped_ptr;
            buffer_props_ptr->mapping_state.access     = mapping_access;

            buffer_size_bytes = buffer_props_ptr->size_bytes;
        }

        if (post_callback_func_ptr != nullptr)
        {
            const bool     is_readable   = (mapping_access == OpenGL::BufferMappingAccess::READ_ONLY ||
                                            mapping_access == OpenGL::BufferMappingAccess::READ_WRITE);
            const auto     map_chunk_id  = APIInterceptor::register_data_chunk((is_readable)                          ? mapped_ptr
                                                                                                                      : nullptr,
                                                                               (is_readable && mapped_ptr != nullptr) ? buffer_size_bytes
                                                                                                                      : 0);

            {
                APIInterceptor::APIFunctionArgument result_arg;

                const APIInterceptor::APIFunctionArgument args[] =
                {
                    APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                    APIInterceptor::APIFunctionArgument::create_u32_glenum   (access),
                    APIInterceptor::APIFunctionArgument::create_void_ptr     (mapped_ptr),
                    APIInterceptor::APIFunctionArgument::create_data_chunk_id(map_chunk_id),
                };

                post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFER,
                                       post_callback_func_arg,
                                       static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                       args,
                                      &result_arg);
            }
        }
    }

    return mapped_ptr;
}
