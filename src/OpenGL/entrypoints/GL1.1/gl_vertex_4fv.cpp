/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4fv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex4fv(const GLfloat* v)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertex4fv(v.x=[%.4f], v.y=[%.4f], v.z=[%.4f], v.w=[%.4f])",
                 v[0],
                 v[1],
                 v[2],
                 v[3]);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEX4FV,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const auto data_chunk_id = APIInterceptor::register_data_chunk(v,
                                                                           sizeof(GLfloat) * 4);

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk_id)
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEX4FV,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEX4FVPROC>(OpenGL::g_cached_gl_vertex_4fv)(v);
    }
}