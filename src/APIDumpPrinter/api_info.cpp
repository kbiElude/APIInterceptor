/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "api_info.h"
#include "D3D8Utils/methods.h"
#include <string.h>

APIDumpPrinter::APIGroup APIDumpPrinter::get_api_group(const APIInterceptor::APIFunction& in_function)
{
    APIGroup result = APIGroup::Unknown;

    if (in_function >= APIInterceptor::APIFUNCTION_GDI32_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_GDI32_LAST)
    {
        result = APIGroup::GDI32;
    }
    else
    if (in_function >= APIInterceptor::APIFUNCTION_GL_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_GL_LAST)
    {
        result = APIGroup::GL;
    }
    else
    if (in_function >= APIInterceptor::APIFUNCTION_WGL_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_WGL_LAST)
    {
        result = APIGroup::WGL;
    }
    else
    if (in_function >= APIInterceptor::APIFUNCTION_USER32_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_USER32_LAST)
    {
        result = APIGroup::USER32;
    }
    else
    if (in_function >= APIInterceptor::APIFUNCTION_D3D8_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_D3D8_LAST)
    {
        result = APIGroup::D3D8;
    }

    return result;
}

const char* APIDumpPrinter::get_api_group_name(const APIGroup& in_group)
{
    const char* result_ptr = "unknown";

    switch (in_group)
    {
        case APIGroup::GDI32:
        {
            result_ptr = "gdi32";

            break;
        }

        case APIGroup::GL:
        {
            result_ptr = "gl";

            break;
        }

        case APIGroup::WGL:
        {
            result_ptr = "wgl";

            break;
        }

        case APIGroup::USER32:
        {
            result_ptr = "user32";

            break;
        }

        case APIGroup::D3D8:
        {
            result_ptr = "d3d8";

            break;
        }

        default:
        {
            break;
        }
    }

    return result_ptr;
}

const char* APIDumpPrinter::get_function_name(const APIInterceptor::APIFunction& in_function)
{
    const char* result_ptr = nullptr;

    switch (get_api_group(in_function) )
    {
        case APIGroup::D3D8:
        {
            result_ptr = D3D8::Utils::get_function_name_ptr(in_function);

            break;
        }

        case APIGroup::GL:
        {
            result_ptr = get_gl_function_name(in_function);

            break;
        }

        case APIGroup::GDI32:
        case APIGroup::WGL:
        case APIGroup::USER32:
        {
            result_ptr = get_win_function_name(in_function);

            break;
        }

        default:
        {
            break;
        }
    }

    return (result_ptr != nullptr) ? result_ptr
                                   : "?!";
}

bool APIDumpPrinter::is_frame_boundary(const APIInterceptor::APIFunction& in_function)
{
    bool result = false;

    /* IDirect3DSwapChain8::Present is not a boundary: it presents additional swap chains. */
    if (in_function == APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS ||
        in_function == APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT)
    {
        result = true;
    }

    return result;
}

bool APIDumpPrinter::parse_api_group_name(const char* in_name_ptr,
                                          APIGroup*   out_group_ptr)
{
    bool result = false;

    for (APIGroup group  = APIGroup::GDI32;
                  group != APIGroup::Unknown;
                  group  = static_cast<APIGroup>(static_cast<int>(group) + 1) )
    {
        if (_stricmp(in_name_ptr,
                     get_api_group_name(group) ) == 0)
        {
            *out_group_ptr = group;
            result         = true;

            break;
        }
    }

    return result;
}
