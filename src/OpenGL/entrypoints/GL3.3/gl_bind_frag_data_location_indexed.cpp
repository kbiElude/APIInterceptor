/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.3/gl_bind_frag_data_location_indexed.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBindFragDataLocationIndexed(GLuint        program,
                                                       GLuint        colorNumber,
                                                       GLuint        index,
                                                       const GLchar* name)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBindFragDataLocationIndexed(program=[%u] colorNumber=[%u] index=[%u] name=[%s])",
                 program,
                 colorNumber,
                 index,
                 name);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDFRAGDATALOCATIONINDEXED,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32  (program),
                APIInterceptor::APIFunctionArgument::create_u32  (colorNumber),
                APIInterceptor::APIFunctionArgument::create_u32  (index),
                APIInterceptor::APIFunctionArgument::create_i8_ptr(name),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDFRAGDATALOCATIONINDEXED,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBINDFRAGDATALOCATIONINDEXEDPROC>(OpenGL::g_cached_gl_bind_frag_data_location_indexed)(program,
                                                                                                                    colorNumber,
                                                                                                                    index,
                                                                                                                    name);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDFRAGDATALOCATIONINDEXED,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32  (program),
            APIInterceptor::APIFunctionArgument::create_u32  (colorNumber),
            APIInterceptor::APIFunctionArgument::create_u32  (index),
            APIInterceptor::APIFunctionArgument::create_i8_ptr(name),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDFRAGDATALOCATIONINDEXED,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
