/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "D3D8Utils/methods.h"
#include <assert.h>

APIInterceptor::APIFunction D3D8::Utils::get_api_function(const Interface& in_interface,
                                                          const uint32_t&  in_vtable_index)
{
    uint32_t                    n_methods   = 0;
    const MethodInfo*           methods_ptr = get_method_info_array_ptr(&n_methods);
    APIInterceptor::APIFunction result      = APIInterceptor::APIFUNCTION_UNKNOWN;

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

const char* D3D8::Utils::get_function_name_ptr(const APIInterceptor::APIFunction& in_function)
{
    const MethodInfo* method_info_ptr = get_method_info_ptr(in_function);
    const char*       result_ptr      = nullptr;

    if (in_function == APIInterceptor::APIFUNCTION_D3D8_DIRECT3DCREATE8)
    {
        result_ptr = "Direct3DCreate8";
    }
    else
    if (method_info_ptr != nullptr)
    {
        result_ptr = method_info_ptr->full_name_ptr;
    }

    return result_ptr;
}

const char* D3D8::Utils::get_interface_name_ptr(const Interface& in_interface)
{
    const char* result_ptr = "?";

    switch (in_interface)
    {
        #define D3D8_INTERFACE(INTERFACE_TAG, interface_name) \
            case Interface::INTERFACE_TAG:                    \
            {                                                 \
                result_ptr = #interface_name;                 \
                                                              \
                break;                                        \
            }

        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters)

        #include "D3D8/d3d8_methods.inl"

        #undef D3D8_METHOD
        #undef D3D8_INTERFACE

        default:
        {
            break;
        }
    }

    return result_ptr;
}

const D3D8::MethodInfo* D3D8::Utils::get_method_info_ptr(const APIInterceptor::APIFunction& in_function)
{
    uint32_t          n_methods   = 0;
    const MethodInfo* methods_ptr = get_method_info_array_ptr(&n_methods);
    const MethodInfo* result_ptr  = nullptr;

    if (in_function >= APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_D3D8_METHODS_LAST)
    {
        result_ptr = methods_ptr + (in_function - APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST);

        assert(result_ptr->function == in_function);
    }

    return result_ptr;
}

const D3D8::MethodInfo* D3D8::Utils::get_method_info_array_ptr(uint32_t* out_n_methods_ptr)
{
    /* Same order as the APIFUNCTION_D3D8_* enum: position = function - APIFUNCTION_D3D8_METHODS_FIRST. */
    static const MethodInfo method_info_array[] =
    {
        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
            {                                                                                                              \
                #interface_name "::" #method_name,                                                                         \
                APIInterceptor::APIFUNCTION_D3D8_##INTERFACE_TAG##_##METHOD_TAG,                                           \
                #interface_name,                                                                                           \
                Interface::INTERFACE_TAG,                                                                                  \
                #method_name,                                                                                              \
                vtable_index                                                                                               \
            },

        #include "D3D8/d3d8_methods.inl"

        #undef D3D8_METHOD
    };

    *out_n_methods_ptr = static_cast<uint32_t>(sizeof(method_info_array) / sizeof(method_info_array[0]) );

    return method_info_array;
}

uint32_t D3D8::Utils::get_n_methods(const Interface& in_interface)
{
    uint32_t          n_methods   = 0;
    const MethodInfo* methods_ptr = get_method_info_array_ptr(&n_methods);
    uint32_t          result      = 0;

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

const char* D3D8::Utils::get_object_type_name_ptr(const ObjectType& in_object_type)
{
    const char* result_ptr = nullptr;

    switch (in_object_type)
    {
        case ObjectType::BaseTexture:
        {
            result_ptr = "BaseTexture";

            break;
        }

        case ObjectType::CubeTexture:
        {
            result_ptr = "CubeTexture";

            break;
        }

        case ObjectType::Device:
        {
            result_ptr = "Device";

            break;
        }

        case ObjectType::Direct3D8:
        {
            result_ptr = "Direct3D8";

            break;
        }

        case ObjectType::IndexBuffer:
        {
            result_ptr = "IndexBuffer";

            break;
        }

        case ObjectType::Surface:
        {
            result_ptr = "Surface";

            break;
        }

        case ObjectType::SwapChain:
        {
            result_ptr = "SwapChain";

            break;
        }

        case ObjectType::Texture:
        {
            result_ptr = "Texture";

            break;
        }

        case ObjectType::VertexBuffer:
        {
            result_ptr = "VertexBuffer";

            break;
        }

        case ObjectType::Volume:
        {
            result_ptr = "Volume";

            break;
        }

        case ObjectType::VolumeTexture:
        {
            result_ptr = "VolumeTexture";

            break;
        }

        default:
        {
            break;
        }
    }

    return result_ptr;
}
