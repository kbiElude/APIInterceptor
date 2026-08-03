/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_clip_plane.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClipPlane(GLenum          plane,
                                     const GLdouble* equation)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                equation_chunk_id             = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glClipPlane(plane=[%s], equation=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(plane),
                 equation);

        equation_chunk_id = APIInterceptor::register_data_chunk(equation,
                                                         (equation != nullptr) ? 4 * static_cast<uint32_t>(sizeof(GLdouble)) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLIPPLANE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(plane),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(equation_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLIPPLANE,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCLIPPLANEPROC>(OpenGL::g_cached_gl_clip_plane)(plane,
                                                                             equation);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLIPPLANE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(plane),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(equation_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLIPPLANE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}