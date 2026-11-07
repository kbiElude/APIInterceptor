/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/macros.h"
#include "interception/core/common/method_table.h"
#include "interception/core/D3D8Utils/methods.h"
#include <assert.h>

namespace
{
    /* What the lookups of the table are made with (see MethodTable). */
    struct MethodTableTraits
    {
        typedef Interception::Hooks::D3D8::Interface  Interface;
        typedef Interception::Hooks::D3D8::MethodInfo MethodInfo;

        static const MethodInfo* get_method_info_array_ptr(uint32_t* out_n_methods_ptr)
        {
            return Interception::Core::D3D8Utils::get_method_info_array_ptr(out_n_methods_ptr);
        }

        static APIInterceptor::APIFunction get_first_function()
        {
            return APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST;
        }

        static APIInterceptor::APIFunction get_last_function()
        {
            return APIInterceptor::APIFUNCTION_D3D8_METHODS_LAST;
        }
    };

    typedef Interception::Core::Common::MethodTable<MethodTableTraits> Table;
}

APIInterceptor::APIFunction Interception::Core::D3D8Utils::get_api_function(const Interception::Hooks::D3D8::Interface& in_interface,
                                                                            const uint32_t&                             in_vtable_index)
{
    return Table::get_api_function(in_interface,
                                   in_vtable_index);
}

const char* Interception::Core::D3D8Utils::get_function_name_ptr(const APIInterceptor::APIFunction& in_function)
{
    const Interception::Hooks::D3D8::MethodInfo* method_info_ptr = get_method_info_ptr(in_function);
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

const char* Interception::Core::D3D8Utils::get_interface_name_ptr(const Interception::Hooks::D3D8::Interface& in_interface)
{
    const char* result_ptr = "?";

    switch (in_interface)
    {
        #define D3D8_INTERFACE(INTERFACE_TAG, interface_name) \
            case Interception::Hooks::D3D8::Interface::INTERFACE_TAG:                    \
            {                                                 \
                result_ptr = #interface_name;                 \
                                                              \
                break;                                        \
            }

        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters)

        #include "interception/hooks/D3D8/d3d8_methods.inl"

        #undef D3D8_METHOD
        #undef D3D8_INTERFACE

        case Interception::Hooks::D3D8::Interface::UNKNOWN:
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

const Interception::Hooks::D3D8::MethodInfo* Interception::Core::D3D8Utils::get_method_info_ptr(const APIInterceptor::APIFunction& in_function)
{
    return Table::get_method_info_ptr(in_function);
}

const Interception::Hooks::D3D8::MethodInfo* Interception::Core::D3D8Utils::get_method_info_array_ptr(uint32_t* out_n_methods_ptr)
{
    /* Same order as the APIFUNCTION_D3D8_* enum: position = function - APIFUNCTION_D3D8_METHODS_FIRST. */
    static const Interception::Hooks::D3D8::MethodInfo method_info_array[] =
    {
        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
            {                                                                                                              \
                #interface_name "::" #method_name,                                                                         \
                APIInterceptor::APIFUNCTION_D3D8_##INTERFACE_TAG##_##METHOD_TAG,                                           \
                #interface_name,                                                                                           \
                Interception::Hooks::D3D8::Interface::INTERFACE_TAG,                                                       \
                #method_name,                                                                                              \
                vtable_index                                                                                               \
            },

        #include "interception/hooks/D3D8/d3d8_methods.inl"

        #undef D3D8_METHOD
    };

    *out_n_methods_ptr = static_cast<uint32_t>(sizeof(method_info_array) / sizeof(method_info_array[0]) );

    return method_info_array;
}

uint32_t Interception::Core::D3D8Utils::get_n_methods(const Interception::Hooks::D3D8::Interface& in_interface)
{
    return Table::get_n_methods(in_interface);
}

const char* Interception::Core::D3D8Utils::get_object_type_name_ptr(const ObjectType& in_object_type)
{
    const char* result_ptr = nullptr;

    switch (in_object_type)
    {
        case ObjectType::BASE_TEXTURE:
        {
            result_ptr = "BaseTexture";

            break;
        }

        case ObjectType::CUBE_TEXTURE:
        {
            result_ptr = "CubeTexture";

            break;
        }

        case ObjectType::DEVICE:
        {
            result_ptr = "Device";

            break;
        }

        case ObjectType::DIRECT3D8:
        {
            result_ptr = "Direct3D8";

            break;
        }

        case ObjectType::INDEX_BUFFER:
        {
            result_ptr = "IndexBuffer";

            break;
        }

        case ObjectType::SURFACE:
        {
            result_ptr = "Surface";

            break;
        }

        case ObjectType::SWAP_CHAIN:
        {
            result_ptr = "SwapChain";

            break;
        }

        case ObjectType::TEXTURE:
        {
            result_ptr = "Texture";

            break;
        }

        case ObjectType::VERTEX_BUFFER:
        {
            result_ptr = "VertexBuffer";

            break;
        }

        case ObjectType::VOLUME:
        {
            result_ptr = "Volume";

            break;
        }

        case ObjectType::VOLUME_TEXTURE:
        {
            result_ptr = "VolumeTexture";

            break;
        }

        case ObjectType::NONE:
        {
            break;
        }

        default:
        {
            AI_FAIL_UNSUPPORTED(in_object_type);

            break;
        }
    }

    return result_ptr;
}
