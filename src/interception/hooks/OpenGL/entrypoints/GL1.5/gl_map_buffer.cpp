/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/globals.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/memory_chunk.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/buffer_mapping_manager.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_map_buffer.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/hooks/OpenGL/state_tracker.h"
#include "interception/hooks/OpenGL/utils.h"
#include "interception/core/OpenGLUtils/utils_enum.h"
#include "interception/hooks/WGL/globals.h"

void* AI_APIENTRY Interception::Hooks::OpenGL::aiMapBuffer(GLenum target,
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
        AI_TRACE("glMapBuffer(target=[%s] access=[%s])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(target),
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(access));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFER,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
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
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLMAPBUFFERPROC>(Interception::Hooks::OpenGL::g_cached_gl_map_buffer)(target,
                                                                                                           access);
    }

    if (tracker.is_top_level_api_call() )
    {
        auto& context = Interception::Hooks::OpenGL::get_context_state();

        GLuint buffer_id = 0;

        {
            Interception::Hooks::OpenGL::BufferBindingTarget binding_target;
            const bool                                       is_known_target = Interception::Hooks::OpenGL::Utils::get_buffer_binding_target_for_gl_enum(target,
                                                                                                                                    &binding_target);

            AI_ASSERT(is_known_target);

            buffer_id = context.buffer_manager.get_bound_buffer(binding_target);
        }

        const uint32_t flags  = Interception::Hooks::OpenGL::BufferMappingManager::get_flags_for_access(access);
        const int64_t  length = static_cast<int64_t>(context.buffer_manager.get_size(buffer_id) );

        context.buffer_mapping_manager.on_buffer_mapped(buffer_id,
                                                        result,
                                                        0,
                                                        length,
                                                        flags);

        if (context.buffer_mapping_manager.is_persistent(buffer_id) )
        {
            AI_WARN("[!] Buffer [%u] is mapped persistently: writes between flushes or unmapping are not captured.",
                    buffer_id);
        }

        const Interception::Hooks::OpenGL::BufferMappingManager::Region initial_region = context.buffer_mapping_manager.get_initial_region(buffer_id);

        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFER,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            APIInterceptor::MemoryChunk initial_chunk(initial_region.data_ptr,
                                             static_cast<int64_t>(initial_region.n_bytes),
                                             sizeof(uint8_t) );

            APIInterceptor::APIFunctionArgument result_arg;

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (access),
                APIInterceptor::APIFunctionArgument::create_void_ptr     (result),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(initial_chunk.get_id() ),
            };

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFER,
                                   post_callback_func_arg,
                                   static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                   args,
                                  &result_arg);
        }
    }

    return result;
}
