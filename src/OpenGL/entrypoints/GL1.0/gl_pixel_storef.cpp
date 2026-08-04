/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL1.0/gl_pixel_storef.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void APIENTRY OpenGL::aiPixelStoref(GLenum  pname,
                                    GLfloat param)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glPixelStoref(pname=[%s] param=[%.4f])",
                 OpenGL::Utils::get_raw_string_for_gl_enum(pname),
                 param);

        switch (pname)
        {
            case GL_PACK_ALIGNMENT:
            case GL_UNPACK_ALIGNMENT:
            {
                AI_ASSERT(param == 4.0f);

                break;
            }

            case GL_PACK_IMAGE_HEIGHT:
            case GL_PACK_ROW_LENGTH:
            case GL_PACK_SKIP_IMAGES:
            case GL_PACK_SKIP_PIXELS:
            case GL_PACK_SKIP_ROWS:
            case GL_PACK_SWAP_BYTES:
            case GL_PACK_LSB_FIRST:
            case GL_UNPACK_IMAGE_HEIGHT:
            case GL_UNPACK_ROW_LENGTH:
            case GL_UNPACK_SKIP_IMAGES:
            case GL_UNPACK_SKIP_PIXELS:
            case GL_UNPACK_SKIP_ROWS:
            case GL_UNPACK_SWAP_BYTES:
            case GL_UNPACK_LSB_FIRST:
            {
                AI_ASSERT(param == 0.0f);

                break;
            }

            default:
            {
                break;
            }
        }

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPIXELSTOREF,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum(pname),
                APIInterceptor::APIFunctionArgument::create_fp32      (param),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPIXELSTOREF,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPIXELSTOREFPROC>(g_cached_gl_pixel_storef)(pname,
                                                                         param);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPIXELSTOREF,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum(pname),
            APIInterceptor::APIFunctionArgument::create_fp32      (param),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPIXELSTOREF,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
