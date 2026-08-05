/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.2/gl_draw_elements_instanced_base_vertex_base_instance.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawElementsInstancedBaseVertexBaseInstance(GLenum      mode,
                                                                       GLsizei     count,
                                                                       GLenum      type,
                                                                       const void* indices,
                                                                       GLsizei     instancecount,
                                                                       GLint       basevertex,
                                                                       GLuint      baseinstance)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawElementsInstancedBaseVertexBaseInstance(mode=[%s] count=[%d] type=[%s] indices=[%p] instancecount=[%d] basevertex=[%d] baseinstance=[%u])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 static_cast<int32_t>(count),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 indices,
                 static_cast<int32_t>(instancecount),
                 basevertex,
                 baseinstance);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
                APIInterceptor::APIFunctionArgument::create_i32       (count),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (indices),
                APIInterceptor::APIFunctionArgument::create_i32       (instancecount),
                APIInterceptor::APIFunctionArgument::create_i32       (basevertex),
                APIInterceptor::APIFunctionArgument::create_u32       (baseinstance),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCEPROC>(OpenGL::g_cached_gl_draw_elements_instanced_base_vertex_base_instance)(mode,
                                                                                                                                                      count,
                                                                                                                                                      type,
                                                                                                                                                      indices,
                                                                                                                                                      instancecount,
                                                                                                                                                      basevertex,
                                                                                                                                                      baseinstance);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
            APIInterceptor::APIFunctionArgument::create_i32       (count),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (indices),
            APIInterceptor::APIFunctionArgument::create_i32       (instancecount),
            APIInterceptor::APIFunctionArgument::create_i32       (basevertex),
            APIInterceptor::APIFunctionArgument::create_u32       (baseinstance),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
