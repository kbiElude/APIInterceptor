/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_pointer.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribIPointer(GLuint      index,
                                                GLint       size,
                                                GLenum      type,
                                                GLsizei     stride,
                                                const void* pointer)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertexAttribIPointer(index=[%u] size=[%d] type=[%s] stride=[%d] pointer=[%p])",
                 index,
                 size,
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 static_cast<int32_t>(stride),
                 pointer);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_IPOINTER,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32      (index),
                APIInterceptor::APIFunctionArgument::create_i32      (size),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_i32      (stride),
                APIInterceptor::APIFunctionArgument::create_void_ptr (pointer),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_IPOINTER,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEXATTRIBIPOINTERPROC>(OpenGL::g_cached_gl_vertex_attrib_i_pointer)(index,
                                                                                                     size,
                                                                                                     type,
                                                                                                     stride,
                                                                                                     pointer);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_IPOINTER,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32      (index),
            APIInterceptor::APIFunctionArgument::create_i32      (size),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_i32      (stride),
            APIInterceptor::APIFunctionArgument::create_void_ptr (pointer),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIB_IPOINTER,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
