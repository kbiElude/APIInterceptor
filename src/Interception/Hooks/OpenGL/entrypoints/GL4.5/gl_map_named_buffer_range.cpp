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
#include "Interception/Hooks/OpenGL/entrypoints/GL4.5/gl_map_named_buffer_range.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/OpenGL/utils.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void* AI_APIENTRY Interception::Hooks::OpenGL::aiMapNamedBufferRange(GLuint     buffer,
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
        AI_TRACE("glMapNamedBufferRange(buffer=[%u] offset=[%lld] length=[%lld] access=[0x%x])",
                 buffer,
                 static_cast<long long>(offset),
                 static_cast<long long>(length),
                 access);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFERRANGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32(buffer),
                APIInterceptor::APIFunctionArgument::create_i64(static_cast<int64_t>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i64(static_cast<int64_t>(length) ),
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

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLMAPNAMEDBUFFERRANGEPROC>(Interception::Hooks::OpenGL::g_cached_gl_map_named_buffer_range)(buffer,
                                                                                                                                 offset,
                                                                                                                                 length,
                                                                                                                                 access);
    }

    if (tracker.is_top_level_api_call() )
    {
        auto& context = Interception::Hooks::OpenGL::get_context_state();

        context.buffer_mapping_manager.on_buffer_mapped(buffer,
                                                        result,
                                                        offset,
                                                        length,
                                                        access);

        if (context.buffer_mapping_manager.is_persistent(buffer) )
        {
            AI_WARN("[!] Buffer [%u] is mapped persistently: writes between flushes or unmapping are not captured.",
                    buffer);
        }

        const Interception::Hooks::OpenGL::BufferMappingManager::Region initial_region = context.buffer_mapping_manager.get_initial_region(buffer);

        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPNAMEDBUFFERRANGE,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            APIInterceptor::MemoryChunk initial_chunk(initial_region.data_ptr,
                                             static_cast<int64_t>(initial_region.n_bytes),
                                             sizeof(uint8_t) );

            APIInterceptor::APIFunctionArgument result_arg;

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32          (buffer),
                APIInterceptor::APIFunctionArgument::create_i64          (static_cast<int64_t>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i64          (static_cast<int64_t>(length) ),
                APIInterceptor::APIFunctionArgument::create_u32          (access),
                APIInterceptor::APIFunctionArgument::create_void_ptr     (result),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(initial_chunk.get_id() ),
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
