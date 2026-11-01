/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL1.1/gl_index_pointer.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiIndexPointer(GLenum        type,
                                                             GLsizei       stride,
                                                             const GLvoid* pointer)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glIndexPointer(type=[%s], stride=[%d], pointer=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(type),
                 stride,
                 pointer);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLINDEXPOINTER,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_i32       (stride),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (pointer),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLINDEXPOINTER,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLINDEXPOINTERPROC>(Interception::Hooks::OpenGL::g_cached_gl_index_pointer)(type,
                                                                                                        stride,
                                                                                                        pointer);
    }

    if (tracker.is_top_level_api_call() )
    {
        auto& context = Interception::Hooks::OpenGL::get_context_state();

        context.client_array_manager.set_pointer(Interception::Hooks::OpenGL::ClientArrayKind::INDEX,
                                               0,
                                               1,
                                               type,
                                               stride,
                                               pointer,
                                               context.buffer_manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ARRAY_BUFFER),
                                               false,  /* in_is_integer    */
                                               false,  /* in_is_long       */
                                               false); /* in_is_normalized */
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLINDEXPOINTER,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_i32       (stride),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (pointer),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLINDEXPOINTER,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}