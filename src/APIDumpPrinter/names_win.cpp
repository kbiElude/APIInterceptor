/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "api_info.h"

const char* APIDumpPrinter::get_win_function_name(const APIInterceptor::APIFunction& in_func)
{
    static const FunctionNameEntry name_entry_array[] =
    {
        { APIInterceptor::APIFunction::APIFUNCTION_GDI32_CHOOSEPIXELFORMAT, "ChoosePixelFormat" },
        { APIInterceptor::APIFunction::APIFUNCTION_GDI32_DESCRIBEPIXELFORMAT, "DescribePixelFormat" },
        { APIInterceptor::APIFunction::APIFUNCTION_GDI32_GETPIXELFORMAT, "GetPixelFormat" },
        { APIInterceptor::APIFunction::APIFUNCTION_GDI32_SETPIXELFORMAT, "SetPixelFormat" },
        { APIInterceptor::APIFunction::APIFUNCTION_GDI32_SWAPBUFFERS, "SwapBuffers" },
        { APIInterceptor::APIFunction::APIFUNCTION_USER32_ADJUSTWINDOWRECTEX, "AdjustWindowRectEx" },
        { APIInterceptor::APIFunction::APIFUNCTION_USER32_CREATEDCA, "CreateDCA" },
        { APIInterceptor::APIFunction::APIFUNCTION_USER32_CREATEDCW, "CreateDCW" },
        { APIInterceptor::APIFunction::APIFUNCTION_USER32_CREATEWINDOWEXA, "CreateWindowExA" },
        { APIInterceptor::APIFunction::APIFUNCTION_USER32_CREATEWINDOWEXW, "CreateWindowExW" },
        { APIInterceptor::APIFunction::APIFUNCTION_USER32_GETDC, "GetDC" },
        { APIInterceptor::APIFunction::APIFUNCTION_USER32_RELEASEDC, "ReleaseDC" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLCOPYCONTEXT, "wglCopyContext" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLCREATECONTEXT, "wglCreateContext" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLCREATECONTEXTATTRIBSARB, "wglCreateContextAttribsARB" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLCREATELAYERCONTEXT, "wglCreateLayerContext" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLDELETECONTEXT, "wglDeleteContext" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLGETCURRENTCONTEXT, "wglGetCurrentContext" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLGETCURRENTDC, "wglGetCurrentDC" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLGETEXTENSIONSSTRINGARB, "wglGetExtensionsStringARB" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLGETSWAPINTERVALEXT, "wglGetSwapIntervalEXT" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLMAKECURRENT, "wglMakeCurrent" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLSHARELISTS, "wglShareLists" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLSWAPINTERVALEXT, "wglSwapIntervalEXT" },
        { APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLSWAPLAYERBUFFERS, "wglSwapLayerBuffers" },
    };
    static const FunctionNameTable name_table(name_entry_array,
                                              sizeof(name_entry_array) / sizeof(name_entry_array[0]) );

    return name_table.get_name(in_func);
}
