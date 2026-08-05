/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/tracker.h"
#include "OpenGL/entrypoints/GL4.3/gl_texture_view.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiTextureView(GLuint texture,
                                       GLenum target,
                                       GLuint origtexture,
                                       GLenum internalformat,
                                       GLuint minlevel,
                                       GLuint numlevels,
                                       GLuint minlayer,
                                       GLuint numlayers)
{
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glTextureView(texture=[%u] target=[%s] origtexture=[%u] internalformat=[%s] minlevel=[%u] numlevels=[%u] minlayer=[%u] numlayers=[%u])",
                 texture,
                 OpenGL::Utils::get_raw_string_for_gl_enum(target),
                 origtexture,
                 OpenGL::Utils::get_raw_string_for_gl_enum(internalformat),
                 minlevel,
                 numlevels,
                 minlayer,
                 numlayers);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTUREVIEW,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32       (texture),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
                APIInterceptor::APIFunctionArgument::create_u32       (origtexture),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
                APIInterceptor::APIFunctionArgument::create_u32       (minlevel),
                APIInterceptor::APIFunctionArgument::create_u32       (numlevels),
                APIInterceptor::APIFunctionArgument::create_u32       (minlayer),
                APIInterceptor::APIFunctionArgument::create_u32       (numlayers),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTUREVIEW,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLTEXTUREVIEWPROC>(OpenGL::g_cached_gl_texture_view)(texture,
                                                                                  target,
                                                                                  origtexture,
                                                                                  internalformat,
                                                                                  minlevel,
                                                                                  numlevels,
                                                                                  minlayer,
                                                                                  numlayers);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLTEXTUREVIEW,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32       (texture),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(target),
            APIInterceptor::APIFunctionArgument::create_u32       (origtexture),
            APIInterceptor::APIFunctionArgument::create_u32_glenum(internalformat),
            APIInterceptor::APIFunctionArgument::create_u32       (minlevel),
            APIInterceptor::APIFunctionArgument::create_u32       (numlevels),
            APIInterceptor::APIFunctionArgument::create_u32       (minlayer),
            APIInterceptor::APIFunctionArgument::create_u32       (numlayers),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLTEXTUREVIEW,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}
