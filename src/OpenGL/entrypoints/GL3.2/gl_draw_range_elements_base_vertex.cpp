/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL3.2/gl_draw_range_elements_base_vertex.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawRangeElementsBaseVertex(GLenum      mode,
                                                       GLuint      start,
                                                       GLuint      end,
                                                       GLsizei     count,
                                                       GLenum      type,
                                                       const void* indices,
                                                       GLint       basevertex)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glDrawRangeElementsBaseVertex(mode=[%s] start=[%u] end=[%u] count=[%d] type=[%s] indices=[%p] basevertex=[%d])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(mode),
                 start,
                 end,
                 static_cast<int32_t>(count),
                 OpenGL::Utils::get_raw_string_for_gl_enum(type),
                 indices,
                 basevertex);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWRANGEELEMENTSBASEVERTEX,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
                APIInterceptor::APIFunctionArgument::create_u32       (start),
                APIInterceptor::APIFunctionArgument::create_u32       (end),
                APIInterceptor::APIFunctionArgument::create_i32       (count),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
                APIInterceptor::APIFunctionArgument::create_void_ptr  (indices),
                APIInterceptor::APIFunctionArgument::create_i32       (basevertex),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWRANGEELEMENTSBASEVERTEX,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLDRAWRANGEELEMENTSBASEVERTEXPROC>(OpenGL::g_cached_gl_draw_range_elements_base_vertex)(mode,
                                                                                                                    start,
                                                                                                                    end,
                                                                                                                    count,
                                                                                                                    type,
                                                                                                                    indices,
                                                                                                                    basevertex);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLDRAWRANGEELEMENTSBASEVERTEX,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(mode),
            APIInterceptor::APIFunctionArgument::create_u32       (start),
            APIInterceptor::APIFunctionArgument::create_u32       (end),
            APIInterceptor::APIFunctionArgument::create_i32       (count),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(type),
            APIInterceptor::APIFunctionArgument::create_void_ptr  (indices),
            APIInterceptor::APIFunctionArgument::create_i32       (basevertex),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLDRAWRANGEELEMENTSBASEVERTEX,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
