/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_object_ptr_label.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiObjectPtrLabel(const void*   ptr,
                                          GLsizei       length,
                                          const GLchar* label)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glObjectPtrLabel(ptr=[%p] length=[%d] label=[%s])",
                 ptr,
                 static_cast<int32_t>(length),
                 label);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLOBJECTPTRLABEL,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(ptr),
                APIInterceptor::APIFunctionArgument::create_i32     (length),
                APIInterceptor::APIFunctionArgument::create_i8_ptr  (label),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLOBJECTPTRLABEL,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLOBJECTPTRLABELPROC>(OpenGL::g_cached_gl_object_ptr_label)(ptr,
                                                                                         length,
                                                                                         label);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLOBJECTPTRLABEL,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_void_ptr(ptr),
            APIInterceptor::APIFunctionArgument::create_i32     (length),
            APIInterceptor::APIFunctionArgument::create_i8_ptr  (label),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLOBJECTPTRLABEL,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
