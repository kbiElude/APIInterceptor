/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL2.0/gl_create_program.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiCreateProgram()
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    GLuint                                  result                 = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glCreateProgram()");

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCREATEPROGRAM,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCREATEPROGRAM,
                                  0,
                                  nullptr,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(OpenGL::g_cached_gl_create_program)();
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCREATEPROGRAM,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg = APIInterceptor::APIFunctionArgument::create_u32(result);

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCREATEPROGRAM,
                               post_callback_func_arg,
                               0,
                               nullptr,
                              &result_arg);
    }

    return result;
}
