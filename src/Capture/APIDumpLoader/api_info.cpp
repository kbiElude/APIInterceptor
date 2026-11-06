/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Capture/APIDumpLoader/api_info.h"
#include "Capture/APIDumpLoader/api_dump_loader.h"
#include "Common/frame_boundary.h"
#include "Common/macros.h"
#include <string.h>

Capture::APIDumpLoader::APIGroup Capture::APIDumpLoader::get_api_group(const APIInterceptor::APIFunction& in_function)
{
    APIGroup result = APIGroup::UNKNOWN;

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
    else
    if (in_function >= APIInterceptor::APIFUNCTION_D3D7_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_D3D7_LAST)
    {
        result = APIGroup::D3D7;
    }

    return result;
}

const char* Capture::APIDumpLoader::get_api_group_name(const APIGroup& in_group)
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

        case APIGroup::D3D7:
        {
            result_ptr = "d3d7";

            break;
        }

        case APIGroup::D3D8:
        {
            result_ptr = "d3d8";

            break;
        }

        case APIGroup::UNKNOWN:
        {
            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_group);

            break;
        }
    }

    return result_ptr;
}

const std::vector<Capture::APIDumpLoader::APIGroup>& Capture::APIDumpLoader::get_api_groups()
{
    static const std::vector<APIGroup> result_vec =
    {
        APIGroup::GDI32,
        APIGroup::GL,
        APIGroup::WGL,
        APIGroup::USER32,
        APIGroup::D3D8,
        APIGroup::D3D7
    };

    return result_vec;
}

bool Capture::APIDumpLoader::is_frame_boundary(const DumpedAPICall& in_call)
{
    return APIInterceptor::is_frame_boundary(in_call.func,
                                             static_cast<uint32_t>(in_call.arg_in_vec.size() ),
                                             in_call.arg_in_vec.data() );
}

bool Capture::APIDumpLoader::parse_api_group_name(const char* in_name_ptr,
                                                  APIGroup*   out_group_ptr)
{
    bool result = false;

    for (const auto& group : get_api_groups() )
    {
        const char* group_name_ptr = get_api_group_name(group);

        if (_stricmp(in_name_ptr,
                     group_name_ptr) == 0)
        {
            *out_group_ptr = group;
            result         = true;

            break;
        }
    }

    return result;
}
