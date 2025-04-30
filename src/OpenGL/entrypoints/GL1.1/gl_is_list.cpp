/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_is_list.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

GLboolean AI_APIENTRY OpenGL::aiIsList(GLuint list)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    GLboolean                           result              = GL_FALSE;
    bool                                should_pass_through = true;

    AI_TRACE("glIsList(list=[%d])",
             list);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLISLIST,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(list),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLISLIST,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        result = reinterpret_cast<PFNGLISLISTPROC>(OpenGL::g_cached_gl_is_list)(list);
    }

    return result;
}