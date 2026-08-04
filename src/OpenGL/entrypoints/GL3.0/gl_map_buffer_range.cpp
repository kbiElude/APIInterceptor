/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_map_buffer_range.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void* APIENTRY OpenGL::aiMapBufferRange(GLenum     target,
                                        GLintptr   offset,
                                        GLsizeiptr length,
                                        GLbitfield access)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMapBufferRange(target=[%s] offset=[%d] length=[%d] access=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 static_cast<int32_t>(offset),
                 static_cast<int32_t>(length),
                 OpenGL::Utils::get_raw_string_for_gl_bitfield(OpenGL::BitfieldType::Buffer_Access_Mask, access) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFERRANGE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_i32       (static_cast<int32_t>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i32       (static_cast<int32_t>(length) ),
                APIInterceptor::APIFunctionArgument::create_u32       (access),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFERRANGE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    void* const mapped_ptr = reinterpret_cast<PFNGLMAPBUFFERRANGEPROC>(g_cached_gl_map_buffer_range)(target,
                                                                                                     offset,
                                                                                                     length,
                                                                                                     access);

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFERRANGE,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const bool is_readable     = (access & GL_MAP_READ_BIT) != 0;
            const auto map_chunk_id    = APIInterceptor::register_data_chunk((is_readable)                          ? mapped_ptr
                                                                                                                    : nullptr,
                                                                             (is_readable && mapped_ptr != nullptr) ? static_cast<uint32_t>(length)
                                                                                                                    : 0u);

            APIInterceptor::APIFunctionArgument result_arg;

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_i32          (static_cast<int32_t>(offset) ),
                APIInterceptor::APIFunctionArgument::create_i32          (static_cast<int32_t>(length) ),
                APIInterceptor::APIFunctionArgument::create_u32          (access),
                APIInterceptor::APIFunctionArgument::create_void_ptr     (mapped_ptr),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(map_chunk_id),
            };

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAPBUFFERRANGE,
                                   post_callback_func_arg,
                                   static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                                   args,
                                  &result_arg);
        }
    }

    return mapped_ptr;
}
