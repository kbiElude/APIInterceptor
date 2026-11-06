/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_disable_client_state.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/hooks/OpenGL/state_tracker.h"
#include "interception/core/OpenGLUtils/utils_enum.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiDisableClientState(GLenum array)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDisableClientState(array=[%s])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(array) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDISABLECLIENTSTATE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(array),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDISABLECLIENTSTATE,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDISABLECLIENTSTATEPROC>(Interception::Hooks::OpenGL::g_cached_gl_disable_client_state)(array);
    }

    if (tracker.is_top_level_api_call() )
    {
        Interception::Hooks::OpenGL::ClientArrayKind kind;
        auto&                                        context = Interception::Hooks::OpenGL::get_context_state();

        if (Interception::Hooks::OpenGL::ClientArrayManager::get_kind_for_array_enum(array,
                                                             &kind) )
        {
            const uint32_t index = (kind == Interception::Hooks::OpenGL::ClientArrayKind::TEX_COORD) ? context.client_array_manager.get_client_active_texture()
                                                                                : 0;

            context.client_array_manager.set_enabled(kind,
                                                   index,
                                                   false);  /* in_is_enabled */
        }
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDISABLECLIENTSTATE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(array),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDISABLECLIENTSTATE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}