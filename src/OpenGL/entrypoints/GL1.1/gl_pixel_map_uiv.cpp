/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_pixel_map_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPixelMapuiv(GLenum        map,
                                       GLsizei       mapsize,
                                       const GLuint* values)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;
    uint32_t                                values_chunk_id             = 0;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glPixelMapuiv(map=[%s], mapsize=[%d], values=[%p])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(map),
                 mapsize,
                 values);

        values_chunk_id = APIInterceptor::register_data_chunk(values,
                                                          (values != nullptr) ? static_cast<uint32_t>(mapsize) * sizeof(GLuint) : 0u);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPIXELMAPUIV,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(map),
                APIInterceptor::APIFunctionArgument::create_i32       (mapsize),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(values_chunk_id),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPIXELMAPUIV,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              pre_callback_func_arg,
                             &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPIXELMAPUIVPROC>(OpenGL::g_cached_gl_pixel_map_uiv)(map,
                                                                                  mapsize,
                                                                                  values);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPIXELMAPUIV,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(map),
            APIInterceptor::APIFunctionArgument::create_i32       (mapsize),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(values_chunk_id),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPIXELMAPUIV,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}