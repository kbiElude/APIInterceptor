/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "api_info.h"
#include "Interception/Core/D3D8Utils/methods.h"

const char* Capture::APIDumpPrinter::get_function_name(const APIInterceptor::APIFunction& in_function)
{
    const char* result_ptr = nullptr;

    switch (Capture::APIDumpLoader::get_api_group(in_function) )
    {
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

        default:
        {
            break;
        }
    }

    return (result_ptr != nullptr) ? result_ptr
                                   : "?!";
}
