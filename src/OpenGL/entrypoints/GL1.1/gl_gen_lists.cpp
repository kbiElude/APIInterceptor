/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_gen_lists.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLuint AI_APIENTRY OpenGL::aiGenLists(GLsizei range)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    GLuint                              result              = 0;
    bool                                should_pass_through = true;

    AI_TRACE("glGenLists(range=[%d])",
             range);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLGENLISTS,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_i32(range),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLGENLISTS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLGENLISTSPROC>(OpenGL::g_cached_gl_gen_lists)(range);
    }

    return result;
}