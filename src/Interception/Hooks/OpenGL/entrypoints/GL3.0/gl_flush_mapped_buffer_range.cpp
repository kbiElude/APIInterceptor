/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/memory_chunk.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/buffer_mapping_manager.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL3.0/gl_flush_mapped_buffer_range.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/OpenGL/utils.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY OpenGL::aiFlushMappedBufferRange(GLenum     target,
                                                  GLintptr   offset,
                                                  GLsizeiptr length)
{
    GLuint                                  buffer_id              = 0;
    APIInterceptor::MemoryChunk             flush_chunk(nullptr,
                                                        0,
                                                        sizeof(uint8_t) );
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glFlushMappedBufferRange(target=[%s] offset=[%lld] length=[%lld])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 static_cast<long long>(offset),
                 static_cast<long long>(length));

        auto& context = OpenGL::get_context_state();

        {
            OpenGL::BufferBindingTarget binding_target;
            const bool                  is_known_target = OpenGL::Utils::get_buffer_binding_target_for_gl_enum(target,
                                                                                                               &binding_target);

            AI_ASSERT(is_known_target);

            buffer_id = context.buffer_manager.get_bound_buffer(binding_target);
        }

        const OpenGL::BufferMappingManager::Region flush_region = context.buffer_mapping_manager.get_flush_region(buffer_id,
                                                                                                                  offset,
                                                                                                                  length);

        flush_chunk = APIInterceptor::MemoryChunk(flush_region.data_ptr,
                                                  static_cast<int64_t>(flush_region.n_bytes),
                                                  sizeof(uint8_t) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFLUSHMAPPEDBUFFERRANGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_i64          (static_cast<int64_t>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i64          (static_cast<int64_t>(length) ),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(flush_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFLUSHMAPPEDBUFFERRANGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLFLUSHMAPPEDBUFFERRANGEPROC>(OpenGL::g_cached_gl_flush_mapped_buffer_range)(target,
                                                                                                         offset,
                                                                                                         length);
    }

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLFLUSHMAPPEDBUFFERRANGE,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            APIInterceptor::APIFunctionArgument result_arg;

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_i64          (static_cast<int64_t>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i64          (static_cast<int64_t>(length) ),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(flush_chunk.get_id() ),
            };

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLFLUSHMAPPEDBUFFERRANGE,
                                   post_callback_func_arg,
                                   static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                   args,
                                  &result_arg);
        }
    }
}
