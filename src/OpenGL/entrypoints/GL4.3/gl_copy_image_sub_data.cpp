/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_copy_image_sub_data.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiCopyImageSubData(GLuint  srcName,
                                            GLenum  srcTarget,
                                            GLint   srcLevel,
                                            GLint   srcX,
                                            GLint   srcY,
                                            GLint   srcZ,
                                            GLuint  dstName,
                                            GLenum  dstTarget,
                                            GLint   dstLevel,
                                            GLint   dstX,
                                            GLint   dstY,
                                            GLint   dstZ,
                                            GLsizei srcWidth,
                                            GLsizei srcHeight,
                                            GLsizei srcDepth)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glCopyImageSubData(srcName=[%u] srcTarget=[%s] srcLevel=[%d] srcX=[%d] srcY=[%d] srcZ=[%d] dstName=[%u] dstTarget=[%s] dstLevel=[%d] dstX=[%d] dstY=[%d] dstZ=[%d] srcWidth=[%d] srcHeight=[%d] srcDepth=[%d])",
                 srcName,
                 OpenGL::Utils::get_raw_string_for_gl_enum(srcTarget),
                 srcLevel,
                 srcX,
                 srcY,
                 srcZ,
                 dstName,
                 OpenGL::Utils::get_raw_string_for_gl_enum(dstTarget),
                 dstLevel,
                 dstX,
                 dstY,
                 dstZ,
                 static_cast<int32_t>(srcWidth),
                 static_cast<int32_t>(srcHeight),
                 static_cast<int32_t>(srcDepth));

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOPYIMAGESUBDATA,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (srcName),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(srcTarget),
                APIInterceptor::APIFunctionArgument::create_i32       (srcLevel),
                APIInterceptor::APIFunctionArgument::create_i32       (srcX),
                APIInterceptor::APIFunctionArgument::create_i32       (srcY),
                APIInterceptor::APIFunctionArgument::create_i32       (srcZ),
                APIInterceptor::APIFunctionArgument::create_u32       (dstName),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(dstTarget),
                APIInterceptor::APIFunctionArgument::create_i32       (dstLevel),
                APIInterceptor::APIFunctionArgument::create_i32       (dstX),
                APIInterceptor::APIFunctionArgument::create_i32       (dstY),
                APIInterceptor::APIFunctionArgument::create_i32       (dstZ),
                APIInterceptor::APIFunctionArgument::create_i32       (srcWidth),
                APIInterceptor::APIFunctionArgument::create_i32       (srcHeight),
                APIInterceptor::APIFunctionArgument::create_i32       (srcDepth),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOPYIMAGESUBDATA,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLCOPYIMAGESUBDATAPROC>(OpenGL::g_cached_gl_copy_image_sub_data)(srcName,
                                                                                              srcTarget,
                                                                                              srcLevel,
                                                                                              srcX,
                                                                                              srcY,
                                                                                              srcZ,
                                                                                              dstName,
                                                                                              dstTarget,
                                                                                              dstLevel,
                                                                                              dstX,
                                                                                              dstY,
                                                                                              dstZ,
                                                                                              srcWidth,
                                                                                              srcHeight,
                                                                                              srcDepth);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCOPYIMAGESUBDATA,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (srcName),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(srcTarget),
            APIInterceptor::APIFunctionArgument::create_i32       (srcLevel),
            APIInterceptor::APIFunctionArgument::create_i32       (srcX),
            APIInterceptor::APIFunctionArgument::create_i32       (srcY),
            APIInterceptor::APIFunctionArgument::create_i32       (srcZ),
            APIInterceptor::APIFunctionArgument::create_u32       (dstName),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(dstTarget),
            APIInterceptor::APIFunctionArgument::create_i32       (dstLevel),
            APIInterceptor::APIFunctionArgument::create_i32       (dstX),
            APIInterceptor::APIFunctionArgument::create_i32       (dstY),
            APIInterceptor::APIFunctionArgument::create_i32       (dstZ),
            APIInterceptor::APIFunctionArgument::create_i32       (srcWidth),
            APIInterceptor::APIFunctionArgument::create_i32       (srcHeight),
            APIInterceptor::APIFunctionArgument::create_i32       (srcDepth),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCOPYIMAGESUBDATA,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
