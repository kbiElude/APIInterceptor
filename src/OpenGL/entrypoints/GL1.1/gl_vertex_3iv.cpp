/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3iv.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiVertex3iv(const GLint* v)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glVertex3iv(v=[%p])",
                 v);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLVERTEX3IV,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const auto data_chunk_id = APIInterceptor::register_data_chunk(v,
                                                                           sizeof(GLint) * 3);

            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(data_chunk_id),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLVERTEX3IV,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLVERTEX3IVPROC>(OpenGL::g_cached_gl_vertex_3iv)(v);
    }
}