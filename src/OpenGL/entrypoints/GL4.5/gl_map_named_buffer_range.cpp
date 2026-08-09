/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.5/gl_map_named_buffer_range.h"
#include "OpenGL/globals.h"
#include "OpenGL/state_tracker.h"
#include "OpenGL/utils.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void* AI_APIENTRY OpenGL::aiMapNamedBufferRange(GLuint     buffer,
                                                GLintptr   offset,
                                                GLsizeiptr length,
                                                GLbitfield access)
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
        AI_TRACE("glMapNamedBufferRange(buffer=[%u] offset=[%d] length=[%d] access=[%u])",
                 buffer,
                 static_cast<int32_t>(offset),
                 static_cast<int32_t>(length),
                 access);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFERRANGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(buffer),
                APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i32(static_cast<GLint>(length) ),
                APIInterceptor::APIFunctionArgument::create_u32(access),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFERRANGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    result = reinterpret_cast<PFNGLMAPNAMEDBUFFERRANGEPROC>(OpenGL::g_cached_gl_map_named_buffer_range)(buffer,
                                                                                                         offset,
                                                                                                         length,
                                                                                                         access);

    if (tracker.is_top_level_api_call() )
    {
        if (result != nullptr)
        {
            const OpenGL::BufferMappingAccess mapping_access = (access & GL_MAP_READ_BIT)
                                                                   ? ((access & GL_MAP_WRITE_BIT) ? OpenGL::BufferMappingAccess::READ_WRITE
                                                                                                  : OpenGL::BufferMappingAccess::READ_ONLY)
                                                                   : OpenGL::BufferMappingAccess::WRITE_ONLY;
            auto& context          = OpenGL::get_context_state();
            auto& buffer_props_ptr = context.buffer_object_id_to_buffer_props_ptr_map[buffer];

            if (buffer_props_ptr == nullptr)
            {
                buffer_props_ptr.reset(new OpenGL::BufferProps() );
            }

            buffer_props_ptr->mapping_state.mapped_ptr = result;
            buffer_props_ptr->mapping_state.access     = mapping_access;
        }

        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFERRANGE,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const bool is_readable  = (access & GL_MAP_READ_BIT) != 0;
            const auto map_chunk_id = APIInterceptor::register_data_chunk((is_readable)                      ? result
                                                                                                              : nullptr,
                                                                          (is_readable && result != nullptr) ? static_cast<uint32_t>(length)
                                                                                                              : 0u);

            APIInterceptor::APIFunctionArgument result_arg;

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (buffer),
                APIInterceptor::APIFunctionArgument::create_i32          (static_cast<GLint>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i32          (static_cast<GLint>(length) ),
                APIInterceptor::APIFunctionArgument::create_u32          (access),
                APIInterceptor::APIFunctionArgument::create_void_ptr     (result),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(map_chunk_id),
            };

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFERRANGE,
                                   post_callback_func_arg,
                                   static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                   args,
                                  &result_arg);
        }
    }

    return result;
}
