/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_load_identity.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiLoadIdentity()
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glLoadIdentity()");

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLLOADIDENTITY,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLLOADIDENTITY,
                          0,
                          nullptr,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLLOADIDENTITYPROC>(OpenGL::g_cached_gl_load_identity)();
    }
}