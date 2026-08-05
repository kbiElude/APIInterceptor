/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_get_object_ptr_label.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGetObjectPtrLabel(const void* ptr,
                                             GLsizei     bufSize,
                                             GLsizei*    length,
                                             GLchar*     label)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glGetObjectPtrLabel(ptr=[%p] bufSize=[%d] length=[%p] label=[%p])",
                 ptr,
                 static_cast<int32_t>(bufSize),
                 length,
                 label);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETOBJECTPTRLABEL,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(ptr),
                APIInterceptor::APIFunctionArgument::create_i32     (bufSize),
                APIInterceptor::APIFunctionArgument::create_i32_ptr (length),
                APIInterceptor::APIFunctionArgument::create_i8_ptr  (label),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETOBJECTPTRLABEL,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLGETOBJECTPTRLABELPROC>(OpenGL::g_cached_gl_get_object_ptr_label)(ptr,
                                                                                                bufSize,
                                                                                                length,
                                                                                                label);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGETOBJECTPTRLABEL,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;
        const auto                          length_chunk_id = APIInterceptor::register_data_chunk(length,
                                                                                                  (length != nullptr) ? sizeof(GLsizei) : 0);
        const auto                          label_chunk_id  = APIInterceptor::register_data_chunk(label,
                                                                                                  (label != nullptr) ? static_cast<uint32_t>(bufSize) : 0);

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr      (ptr),
            APIInterceptor::APIFunctionArgument::create_i32           (bufSize),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (length_chunk_id),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id (label_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGETOBJECTPTRLABEL,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
