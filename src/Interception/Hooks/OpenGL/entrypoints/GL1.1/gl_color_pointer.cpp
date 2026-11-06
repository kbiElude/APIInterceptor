/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL1.1/gl_color_pointer.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Hooks/OpenGL/state_tracker.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiColorPointer(GLint         size,
                                                             GLenum        type,
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
        AI_TRACE("glColorPointer(size=[%d] type=[%s] stride=[%d] pointer=[%p])",
                 size,
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(type),
                 stride,
                 pointer);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLORPOINTER,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32       (size),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_i32       (stride),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (pointer),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLORPOINTER,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOLORPOINTERPROC>(Interception::Hooks::OpenGL::g_cached_gl_color_pointer)(size,
                                                                                                        type,
                                                                                                        stride,
                                                                                                        pointer);
    }

    if (tracker.is_top_level_api_call() )
    {
        auto&          context      = Interception::Hooks::OpenGL::get_context_state();
        const uint32_t bound_buffer = context.buffer_manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ARRAY_BUFFER);

        context.client_array_manager.set_pointer(Interception::Hooks::OpenGL::ClientArrayKind::COLOR,
                                               0,
                                               size,
                                               type,
                                               stride,
                                               pointer,
                                               bound_buffer,
                                               false,  /* in_is_integer    */
                                               false,  /* in_is_long       */
                                               false); /* in_is_normalized */
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOLORPOINTER,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32       (size),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_i32       (stride),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (pointer),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOLORPOINTER,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}