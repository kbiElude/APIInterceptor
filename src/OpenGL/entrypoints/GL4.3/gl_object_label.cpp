/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_object_label.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiObjectLabel(GLenum        identifier,
                                       GLuint        name,
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
        AI_TRACE("glObjectLabel(identifier=[%s] name=[%u] length=[%d] label=[%s])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(identifier),
                 name,
                 static_cast<int32_t>(length),
                 label);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLOBJECTLABEL,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(identifier),
                APIInterceptor::APIFunctionArgument::create_u32       (name),
                APIInterceptor::APIFunctionArgument::create_i32       (length),
                APIInterceptor::APIFunctionArgument::create_i8_ptr    (label),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLOBJECTLABEL,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLOBJECTLABELPROC>(OpenGL::g_cached_gl_object_label)(identifier,
                                                                                  name,
                                                                                  length,
                                                                                  label);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLOBJECTLABEL,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(identifier),
            APIInterceptor::APIFunctionArgument::create_u32       (name),
            APIInterceptor::APIFunctionArgument::create_i32       (length),
            APIInterceptor::APIFunctionArgument::create_i8_ptr    (label),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLOBJECTLABEL,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
