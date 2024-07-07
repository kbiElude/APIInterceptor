/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "OpenGL/entrypoints/GL1.0/gl_clear.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiClear(GLbitfield mask)
{
    void*                               callback_func_arg = nullptr;
    APIInterceptor::PFNCALLBACKFUNCPROC callback_func_ptr = nullptr;

    AI_TRACE("glClear(mask=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_bitfield(OpenGL::BitfieldType::Clear_Buffer_Mask, mask) );

    if (APIInterceptor::get_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLCLEAR,
                                                  &callback_func_ptr,
                                                  &callback_func_arg) )
    {
        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32(mask),
        };

        callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLCLEAR,
                          sizeof(args) / sizeof(args[0]),
                          args,
                          callback_func_arg);
    }

    if (OpenGL::g_cached_gl_clear == nullptr)
    {
        OpenGL::g_cached_gl_clear = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("glClear");
    }

    reinterpret_cast<PFNGLCLEARPROC>(OpenGL::g_cached_gl_clear)(mask);
}