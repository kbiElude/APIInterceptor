/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_vertex_attrib_format.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertexAttribFormat(GLuint    attribindex,
                                              GLint     size,
                                              GLenum    type,
                                              GLboolean normalized,
                                              GLuint    relativeoffset)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertexAttribFormat(attribindex=[%u] size=[%d] type=[%s] normalized=[%u] relativeoffset=[%u])",
                 attribindex,
                 size,
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 static_cast<uint32_t>(normalized),
                 relativeoffset);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIBFORMAT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (attribindex),
                APIInterceptor::APIFunctionArgument::create_i32       (size),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_u8        (normalized),
                APIInterceptor::APIFunctionArgument::create_u32       (relativeoffset),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIBFORMAT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEXATTRIBFORMATPROC>(OpenGL::g_cached_gl_vertex_attrib_format)(attribindex,
                                                                                                 size,
                                                                                                 type,
                                                                                                 normalized,
                                                                                                 relativeoffset);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIBFORMAT,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (attribindex),
            APIInterceptor::APIFunctionArgument::create_i32       (size),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_u8        (normalized),
            APIInterceptor::APIFunctionArgument::create_u32       (relativeoffset),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEXATTRIBFORMAT,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
