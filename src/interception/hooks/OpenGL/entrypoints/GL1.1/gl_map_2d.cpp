/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/memory_chunk.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_map_2d.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/hooks/OpenGL/param_counts.h"
#include "interception/core/OpenGLUtils/utils_enum.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiMap2d(GLenum          target,
                                                      GLdouble        u1,
                                                      GLdouble        u2,
                                                      GLint           ustride,
                                                      GLint           uorder,
                                                      GLdouble        v1,
                                                      GLdouble        v2,
                                                      GLint           vstride,
                                                      GLint           vorder,
                                                      const GLdouble* points)
{
    const uint32_t                          n_points = Interception::Hooks::OpenGL::Utils::get_n_map2_values(target,
                                                                                                             ustride,
                                                                                                             uorder,
                                                                                                             vstride,
                                                                                                             vorder);
    APIInterceptor::MemoryChunk             points_chunk(points,
                                                         n_points,
                                                         sizeof(GLdouble) );
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMap2d(target=[%s], u1=[%lf], u2=[%lf], ustride=[%d], uorder=[%d], v1=[%lf], v2=[%lf], vstride=[%d], vorder=[%d], points=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(target),
                 u1,
                 u2,
                 ustride,
                 uorder,
                 v1,
                 v2,
                 vstride,
                 vorder,
                 points);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAP2D,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
                APIInterceptor::APIFunctionArgument::create_fp64         (u1),
                APIInterceptor::APIFunctionArgument::create_fp64         (u2),
                APIInterceptor::APIFunctionArgument::create_i32          (ustride),
                APIInterceptor::APIFunctionArgument::create_i32          (uorder),
                APIInterceptor::APIFunctionArgument::create_fp64         (v1),
                APIInterceptor::APIFunctionArgument::create_fp64         (v2),
                APIInterceptor::APIFunctionArgument::create_i32          (vstride),
                APIInterceptor::APIFunctionArgument::create_i32          (vorder),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(points_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAP2D,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMAP2DPROC>(Interception::Hooks::OpenGL::g_cached_gl_map_2d)(target,
                                                                                          u1,
                                                                                          u2,
                                                                                          ustride,
                                                                                          uorder,
                                                                                          v1,
                                                                                          v2,
                                                                                          vstride,
                                                                                          vorder,
                                                                                          points);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMAP2D,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (target),
            APIInterceptor::APIFunctionArgument::create_fp64         (u1),
            APIInterceptor::APIFunctionArgument::create_fp64         (u2),
            APIInterceptor::APIFunctionArgument::create_i32          (ustride),
            APIInterceptor::APIFunctionArgument::create_i32          (uorder),
            APIInterceptor::APIFunctionArgument::create_fp64         (v1),
            APIInterceptor::APIFunctionArgument::create_fp64         (v2),
            APIInterceptor::APIFunctionArgument::create_i32          (vstride),
            APIInterceptor::APIFunctionArgument::create_i32          (vorder),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(points_chunk.get_id() ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMAP2D,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}