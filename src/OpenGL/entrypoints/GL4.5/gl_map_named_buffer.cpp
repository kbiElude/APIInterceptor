/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_map_named_buffer.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void* AI_APIENTRY OpenGL::aiMapNamedBuffer(GLuint buffer,
                                           GLenum access)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    void*                                   result                 = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMapNamedBuffer(buffer=[%u] access=[%s])",
                 buffer,
                 OpenGL::Utils::get_raw_string_for_gl_enum(access) );

        APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFER,
                                                      &pre_callback_func_ptr,
                                                      &pre_callback_func_arg);

        APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFER,
                                                       &post_callback_func_ptr,
                                                       &post_callback_func_arg);
    }

    if (pre_callback_func_ptr != nullptr)
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (buffer),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(access),
        };

        pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFER,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
    }

    AI_ASSERT(should_pass_through);

    result = reinterpret_cast<PFNGLMAPNAMEDBUFFERPROC>(OpenGL::g_cached_gl_map_named_buffer)(buffer,
                                                                                              access);

    if (tracker.is_top_level_api_call() )
    {
        uint32_t                    buffer_size_bytes = 0;
        auto&                       context           = OpenGL::get_context_state();
        OpenGL::BufferMappingAccess mapping_access;
        const bool                  is_known_access   = OpenGL::Utils::get_buffer_mapping_access_for_gl_enum(access,
                                                                                                             &mapping_access);
        AI_ASSERT(is_known_access);

        if (result != nullptr)
        {
            auto& buffer_props_ptr = context.buffer_object_id_to_buffer_props_ptr_map[buffer];

            if (buffer_props_ptr == nullptr)
            {
                buffer_props_ptr.reset(new OpenGL::BufferProps() );
            }

            buffer_props_ptr->mapping_state.mapped_ptr = result;
            buffer_props_ptr->mapping_state.access     = mapping_access;

            buffer_size_bytes = buffer_props_ptr->size_bytes;
        }

        if (post_callback_func_ptr != nullptr)
        {
            const bool is_readable  = (mapping_access == OpenGL::BufferMappingAccess::READ_ONLY ||
                                       mapping_access == OpenGL::BufferMappingAccess::READ_WRITE);
            const auto map_chunk_id = APIInterceptor::register_data_chunk((is_readable)                       ? result
                                                                                                               : nullptr,
                                                                          (is_readable && result != nullptr)  ? buffer_size_bytes
                                                                                                               : 0u);

            APIInterceptor::APIFunctionArgument result_arg;

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (buffer),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (access),
                APIInterceptor::APIFunctionArgument::create_void_ptr     (result),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(map_chunk_id),
            };

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFER,
                                   post_callback_func_arg,
                                   static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                   args,
                                  &result_arg);
        }
    }

    return result;
}
