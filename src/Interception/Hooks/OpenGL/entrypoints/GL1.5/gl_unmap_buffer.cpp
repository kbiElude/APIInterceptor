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
#include "Interception/Hooks/OpenGL/entrypoints/GL1.5/gl_unmap_buffer.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Hooks/OpenGL/utils.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

GLboolean AI_APIENTRY Interception::Hooks::OpenGL::aiUnmapBuffer(GLenum target)
{
    GLuint                                  buffer_id              = 0;
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    GLboolean                               result                 = GL_FALSE;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    APIInterceptor::MemoryChunk             unmap_chunk(nullptr,
                                                        0,
                                                        sizeof(uint8_t) );

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glUnmapBuffer(target=[%s])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(target));

        auto& context = Interception::Hooks::OpenGL::get_context_state();

        {
            Interception::Hooks::OpenGL::BufferBindingTarget binding_target;
            const bool                                       is_known_target = Interception::Hooks::OpenGL::Utils::get_buffer_binding_target_for_gl_enum(target,
                                                                                                                                    &binding_target);

            AI_ASSERT(is_known_target);

            buffer_id = context.buffer_manager.get_bound_buffer(binding_target);
        }

        /* The pointer is not valid once the buffer is unmapped, so the copy is made now. */
        const Interception::Hooks::OpenGL::BufferMappingManager::Region unmap_region = context.buffer_mapping_manager.get_unmap_region(buffer_id);

        unmap_chunk = APIInterceptor::MemoryChunk(unmap_region.data_ptr,
                                                  static_cast<int64_t>(unmap_region.n_bytes),
                                                  sizeof(uint8_t) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNMAPBUFFER,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
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

        /* Nobody may ask for the copy later, but then it is not needed at all. */
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNMAPBUFFER,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            unmap_chunk.get_id();
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLUNMAPBUFFERPROC>(Interception::Hooks::OpenGL::g_cached_gl_unmap_buffer)(target);
    }

    if (tracker.is_top_level_api_call() )
    {
        Interception::Hooks::OpenGL::get_context_state().buffer_mapping_manager.on_buffer_unmapped(buffer_id);

        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLUNMAPBUFFER,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            APIInterceptor::APIFunctionArgument result_arg;

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_u8           (result),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(unmap_chunk.get_id() ),
            };

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLUNMAPBUFFER,
                                   post_callback_func_arg,
                                   static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                   args,
                                  &result_arg);
        }
    }

    return result;
}
