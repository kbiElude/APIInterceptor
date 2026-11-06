/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/memory_chunk.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_bind_buffers_range.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/core/OpenGLUtils/utils_enum.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiBindBuffersRange(GLenum            target,
                                                                 GLuint            first,
                                                                 GLsizei           count,
                                                                 const GLuint*     buffers,
                                                                 const GLintptr*   offsets,
                                                                 const GLsizeiptr* sizes)
{
    APIInterceptor::MemoryChunk             buffers_chunk(buffers,
                                                          count,
                                                          sizeof(GLuint));
    APIInterceptor::MemoryChunk             offsets_chunk(offsets,
                                                          count,
                                                          sizeof(GLintptr));
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::MemoryChunk             sizes_chunk(sizes,
                                                        count,
                                                        sizeof(GLsizeiptr));
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBindBuffersRange(target=[%s] first=[%u] count=[%d] buffers=[%p] offsets=[%p] sizes=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(target),
                 first,
                 static_cast<int32_t>(count),
                 buffers,
                 offsets,
                 sizes);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDBUFFERSRANGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_u32          (first),
                APIInterceptor::APIFunctionArgument::create_i32          (count),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(buffers_chunk.get_id() ),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(offsets_chunk.get_id() ),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(sizes_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDBUFFERSRANGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBINDBUFFERSRANGEPROC>(Interception::Hooks::OpenGL::g_cached_gl_bind_buffers_range)(target,
                                                                                                                  first,
                                                                                                                  count,
                                                                                                                  buffers,
                                                                                                                  offsets,
                                                                                                                  sizes);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDBUFFERSRANGE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
            APIInterceptor::APIFunctionArgument::create_u32          (first),
            APIInterceptor::APIFunctionArgument::create_i32          (count),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(buffers_chunk.get_id() ),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(offsets_chunk.get_id() ),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(sizes_chunk.get_id() ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDBUFFERSRANGE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
