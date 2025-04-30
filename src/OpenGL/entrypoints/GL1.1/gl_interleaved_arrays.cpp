/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_interleaved_arrays.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiInterleavedArrays(GLenum        format,
                                             GLsizei       stride,
                                             const GLvoid* pointer)
{
    void*                               callback_func_arg   = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                should_pass_through = true;

    AI_TRACE("glInterleavedArrays(format=[%s], stride=[%d], pointer=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             stride,
             pointer);

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLINTERLEAVEDARRRAYS,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32     (format),
            APIInterceptor::APIFunctionArgument::create_i32     (stride),
            APIInterceptor::APIFunctionArgument::create_void_ptr(pointer),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLINTERLEAVEDARRRAYS,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLINTERLEAVEDARRAYSPROC>(OpenGL::g_cached_gl_interleaved_arrays)(format,
                                                                                             stride,
                                                                                             pointer);
    }
}