/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "Interception/Core/D3D7Utils/methods.h"
#include <assert.h>

APIInterceptor::APIFunction Interception::Core::D3D7Utils::get_api_function(const Interception::Hooks::D3D7::Interface& in_interface,
                                                                            const uint32_t&                             in_vtable_index)
{
    uint32_t                                     n_methods   = 0;
    const Interception::Hooks::D3D7::MethodInfo* methods_ptr = get_method_info_array_ptr(&n_methods);
    APIInterceptor::APIFunction                  result      = APIInterceptor::APIFUNCTION_UNKNOWN;

    for (uint32_t n_method = 0;
                  n_method < n_methods;
                ++n_method)
    {
        if (methods_ptr[n_method].interface_type == in_interface &&
            methods_ptr[n_method].vtable_index   == in_vtable_index)
        {
            result = methods_ptr[n_method].function;

            break;
        }
    }

    return result;
}

const char* Interception::Core::D3D7Utils::get_function_name_ptr(const APIInterceptor::APIFunction& in_function)
{
    const Interception::Hooks::D3D7::MethodInfo* method_info_ptr = get_method_info_ptr(in_function);
    const char*                                  result_ptr      = nullptr;

    if (in_function == APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX)
    {
        result_ptr = "DirectDrawCreateEx";
    }
    else
    if (method_info_ptr != nullptr)
    {
        result_ptr = method_info_ptr->full_name_ptr;
    }

    return result_ptr;
}

const char* Interception::Core::D3D7Utils::get_interface_name_ptr(const Interception::Hooks::D3D7::Interface& in_interface)
{
    const char* result_ptr = "?";

    switch (in_interface)
    {
        #define D3D7_INTERFACE(INTERFACE_TAG, interface_name) \
            case Interception::Hooks::D3D7::Interface::INTERFACE_TAG: \
            {                                                         \
                result_ptr = #interface_name;                         \
                                                                      \
                break;                                                \
            }

        #define D3D7_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters)

        #include "Interception/Hooks/D3D7/d3d7_methods.inl"

        #undef D3D7_METHOD
        #undef D3D7_INTERFACE

        case Interception::Hooks::D3D7::Interface::UNKNOWN:
        {
            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_interface);

            break;
        }
    }

    return result_ptr;
}

const Interception::Hooks::D3D7::MethodInfo* Interception::Core::D3D7Utils::get_method_info_ptr(const APIInterceptor::APIFunction& in_function)
{
    uint32_t                                     n_methods   = 0;
    const Interception::Hooks::D3D7::MethodInfo* methods_ptr = get_method_info_array_ptr(&n_methods);
    const Interception::Hooks::D3D7::MethodInfo* result_ptr  = nullptr;

    if (in_function >= APIInterceptor::APIFUNCTION_D3D7_METHODS_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_D3D7_METHODS_LAST)
    {
        result_ptr = methods_ptr + (in_function - APIInterceptor::APIFUNCTION_D3D7_METHODS_FIRST);

        assert(result_ptr->function == in_function);
    }

    return result_ptr;
}

const Interception::Hooks::D3D7::MethodInfo* Interception::Core::D3D7Utils::get_method_info_array_ptr(uint32_t* out_n_methods_ptr)
{
    /* Same order as the APIFUNCTION_D3D7_* enum: position = function - APIFUNCTION_D3D7_METHODS_FIRST. */
    static const Interception::Hooks::D3D7::MethodInfo method_info_array[] =
    {
        #define D3D7_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
            {                                                                                                              \
                #interface_name "::" #method_name,                                                                         \
                APIInterceptor::APIFUNCTION_D3D7_##INTERFACE_TAG##_##METHOD_TAG,                                           \
                #interface_name,                                                                                           \
                Interception::Hooks::D3D7::Interface::INTERFACE_TAG,                                                       \
                #method_name,                                                                                              \
                vtable_index                                                                                               \
            },

        #include "Interception/Hooks/D3D7/d3d7_methods.inl"

        #undef D3D7_METHOD
    };

    *out_n_methods_ptr = static_cast<uint32_t>(sizeof(method_info_array) / sizeof(method_info_array[0]) );

    return method_info_array;
}

uint32_t Interception::Core::D3D7Utils::get_n_methods(const Interception::Hooks::D3D7::Interface& in_interface)
{
    uint32_t                                     n_methods   = 0;
    const Interception::Hooks::D3D7::MethodInfo* methods_ptr = get_method_info_array_ptr(&n_methods);
    uint32_t                                     result      = 0;

    for (uint32_t n_method = 0;
                  n_method < n_methods;
                ++n_method)
    {
        if (methods_ptr[n_method].interface_type == in_interface)
        {
            result++;
        }
    }

    return result;
}
