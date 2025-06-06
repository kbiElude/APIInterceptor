/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.1/gl_bitmap.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBitmap(GLsizei        width,
                                  GLsizei        height,
                                  GLfloat        xorig,
                                  GLfloat        yorig,
                                  GLfloat        xmove,
                                  GLfloat        ymove,
                                  const GLubyte* bitmapef)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;
    APIInterceptor::Tracker                tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBitmap(width=[%d] width=[%d] xorig=[%.4f] yorig=[%.4f] xmove=[%.4f] ymove=[%.4f] bitmapef=[%p])",
                 width,
                 height,
                 xorig,
                 yorig,
                 xmove,
                 ymove,
                 bitmapef);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBITMAP,
                                                         &callback_func_ptr,
                                                         &callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_i32     (width),
                APIInterceptor::APIFunctionArgument::create_i32     (height),
                APIInterceptor::APIFunctionArgument::create_fp32    (xorig),
                APIInterceptor::APIFunctionArgument::create_fp32    (yorig),
                APIInterceptor::APIFunctionArgument::create_fp32    (xmove),
                APIInterceptor::APIFunctionArgument::create_fp32    (ymove),
                APIInterceptor::APIFunctionArgument::create_void_ptr(bitmapef),
            };

            callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBITMAP,
                              sizeof(args) / sizeof(args[0]),
                              args,
                              callback_func_arg,
                             &should_pass_through);
        }
    }

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBITMAPPROC>(OpenGL::g_cached_gl_bitmap)(width,
                                                                      height,
                                                                      xorig,
                                                                      yorig,
                                                                      xmove,
                                                                      ymove,
                                                                      bitmapef);
    }
}