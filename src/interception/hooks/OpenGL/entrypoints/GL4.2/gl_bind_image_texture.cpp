/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/callbacks.h"
#include "common/logger.h"
#include "common/macros.h"
#include "common/tracker.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_bind_image_texture.h"
#include "interception/hooks/OpenGL/globals.h"
#include "interception/core/OpenGLUtils/utils_enum.h"
#include "interception/hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiBindImageTexture(GLuint    unit,
                                                                 GLuint    texture,
                                                                 GLint     level,
                                                                 GLboolean layered,
                                                                 GLint     layer,
                                                                 GLenum    access,
                                                                 GLenum    format)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glBindImageTexture(unit=[%u] texture=[%u] level=[%d] layered=[%u] layer=[%d] access=[%s] format=[%s])",
                 unit,
                 texture,
                 level,
                 static_cast<uint32_t>(layered),
                 layer,
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(access),
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(format) );

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDIMAGETEXTURE,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (unit),
                APIInterceptor::APIFunctionArgument::create_u32       (texture),
                APIInterceptor::APIFunctionArgument::create_i32       (level),
                APIInterceptor::APIFunctionArgument::create_u8        (layered),
                APIInterceptor::APIFunctionArgument::create_i32       (layer),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(access),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDIMAGETEXTURE,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLBINDIMAGETEXTUREPROC>(Interception::Hooks::OpenGL::g_cached_gl_bind_image_texture)(unit,
                                                                                                                  texture,
                                                                                                                  level,
                                                                                                                  layered,
                                                                                                                  layer,
                                                                                                                  access,
                                                                                                                  format);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLBINDIMAGETEXTURE,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (unit),
            APIInterceptor::APIFunctionArgument::create_u32       (texture),
            APIInterceptor::APIFunctionArgument::create_i32       (level),
            APIInterceptor::APIFunctionArgument::create_u8        (layered),
            APIInterceptor::APIFunctionArgument::create_i32       (layer),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(access),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(format),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLBINDIMAGETEXTURE,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
