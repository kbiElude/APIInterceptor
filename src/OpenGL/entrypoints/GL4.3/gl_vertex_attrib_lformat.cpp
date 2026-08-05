/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_vertex_attrib_lformat.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribLFormat(GLuint attribindex,
                                               GLint  size,
                                               GLenum type,
                                               GLuint relativeoffset)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertexAttribLFormat(attribindex=[%u] size=[%d] type=[%s] relativeoffset=[%u])",
                 attribindex,
                 size,
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 relativeoffset);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIBLFORMAT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (attribindex),
                APIInterceptor::APIFunctionArgument::create_i32       (size),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_u32       (relativeoffset),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIBLFORMAT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEXATTRIBLFORMATPROC>(OpenGL::g_cached_gl_vertex_attrib_lformat)(attribindex,
                                                                                                   size,
                                                                                                   type,
                                                                                                   relativeoffset);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIBLFORMAT,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (attribindex),
            APIInterceptor::APIFunctionArgument::create_i32       (size),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_u32       (relativeoffset),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIBLFORMAT,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
