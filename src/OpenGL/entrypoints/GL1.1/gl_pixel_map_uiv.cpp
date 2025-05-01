/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.1/gl_pixel_map_uiv.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPixelMapuiv(GLenum        map,
                                       GLsizei       mapsize,
                                       const GLuint* values)
{
    void*                                  callback_func_arg   = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC callback_func_ptr   = nullptr;
    bool                                   should_pass_through = true;

    AI_TRACE("glPixelMapuiv(map=[%s], mapsize=[%d], values=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(map),
             mapsize,
             values);

    if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLPIXELMAPUIV,
                                                     &callback_func_ptr,
                                                     &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32    (map),
            APIInterceptor::APIFunctionArgument::create_i32    (mapsize),
            APIInterceptor::APIFunctionArgument::create_u32_ptr(values),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLPIXELMAPUIV,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg,
                         &should_pass_through);
    }


    if (should_pass_through)
    {
        reinterpret_cast<PFNGLPIXELMAPUIVPROC>(OpenGL::g_cached_gl_pixel_map_uiv)(map,
                                                                                  mapsize,
                                                                                  values);
    }
}