/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "capture/api_dump_loader/api_info.h"
#include "capture/api_dump_names/function_names.h"
#include "common/macros.h"
#include "function_names_by_group.h"
#include "interception/core/D3D7Utils/methods.h"
#include "interception/core/D3D8Utils/methods.h"

const char* Capture::APIDumpNames::get_function_name(const APIInterceptor::APIFunction& in_function)
{
    const char* result_ptr = nullptr;

    switch (Capture::APIDumpLoader::get_api_group(in_function) )
    {
        case Capture::APIDumpLoader::APIGroup::D3D7:
        {
            result_ptr = Interception::Core::D3D7Utils::get_function_name_ptr(in_function);

            break;
        }

        case Capture::APIDumpLoader::APIGroup::D3D8:
        {
            result_ptr = Interception::Core::D3D8Utils::get_function_name_ptr(in_function);

            break;
        }

        case Capture::APIDumpLoader::APIGroup::GL:
        {
            result_ptr = get_gl_function_name(in_function);

            break;
        }

        case Capture::APIDumpLoader::APIGroup::GDI32:
        case Capture::APIDumpLoader::APIGroup::WGL:
        case Capture::APIDumpLoader::APIGroup::USER32:
        {
            result_ptr = get_win_function_name(in_function);

            break;
        }

        case Capture::APIDumpLoader::APIGroup::UNKNOWN:
        {
            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(Capture::APIDumpLoader::get_api_group(in_function) );

            break;
        }
    }

    return (result_ptr != nullptr) ? result_ptr
                                   : "?!";
}
