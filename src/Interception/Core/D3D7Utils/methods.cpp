/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "Interception/Core/Common/method_table.h"
#include "Interception/Core/D3D7Utils/methods.h"
#include <assert.h>

namespace
{
    /* What the lookups of the table are made with (see MethodTable). */
    struct MethodTableTraits
    {
        typedef Interception::Hooks::D3D7::Interface  Interface;
        typedef Interception::Hooks::D3D7::MethodInfo MethodInfo;

        static const MethodInfo* get_method_info_array_ptr(uint32_t* out_n_methods_ptr)
        {
            return Interception::Core::D3D7Utils::get_method_info_array_ptr(out_n_methods_ptr);
        }

        static APIInterceptor::APIFunction get_first_function()
        {
            return APIInterceptor::APIFUNCTION_D3D7_METHODS_FIRST;
        }

        static APIInterceptor::APIFunction get_last_function()
        {
            return APIInterceptor::APIFUNCTION_D3D7_METHODS_LAST;
        }
    };

    typedef Interception::Core::Common::MethodTable<MethodTableTraits> Table;
}

APIInterceptor::APIFunction Interception::Core::D3D7Utils::get_api_function(const Interception::Hooks::D3D7::Interface& in_interface,
                                                                            const uint32_t&                             in_vtable_index)
{
    return Table::get_api_function(in_interface,
                                   in_vtable_index);
}

const char* Interception::Core::D3D7Utils::get_function_name_ptr(const APIInterceptor::APIFunction& in_function)
{
    const Interception::Hooks::D3D7::MethodInfo* method_info_ptr = get_method_info_ptr(in_function);
    const char*                                  result_ptr      = nullptr;

    switch (in_function)
    {
        case APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATE:
        {
            result_ptr = "DirectDrawCreate";

            break;
        }

        case APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATECLIPPER:
        {
            result_ptr = "DirectDrawCreateClipper";

            break;
        }

        case APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX:
        {
            result_ptr = "DirectDrawCreateEx";

            break;
        }

        case APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWENUMERATEA:
        {
            result_ptr = "DirectDrawEnumerateA";

            break;
        }

        case APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWENUMERATEEXA:
        {
            result_ptr = "DirectDrawEnumerateExA";

            break;
        }

        case APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWENUMERATEEXW:
        {
            result_ptr = "DirectDrawEnumerateExW";

            break;
        }

        case APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWENUMERATEW:
        {
            result_ptr = "DirectDrawEnumerateW";

            break;
        }

        default:
        {
            if (method_info_ptr != nullptr)
            {
                result_ptr = method_info_ptr->full_name_ptr;
            }

            break;
        }
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
    return Table::get_method_info_ptr(in_function);
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
    return Table::get_n_methods(in_interface);
}

const char* Interception::Core::D3D7Utils::get_object_type_name_ptr(const ObjectType& in_object_type)
{
    struct ObjectTypeName
    {
        ObjectType  object_type;
        const char* name_ptr;
    };

    static const ObjectTypeName object_type_name_array[] =
    {
        {ObjectType::CLIPPER,       "Clipper"},
        {ObjectType::COLOR_CONTROL, "ColorControl"},
        {ObjectType::DEVICE,        "Device"},
        {ObjectType::DIRECT3D7,     "Direct3D7"},
        {ObjectType::DIRECT_DRAW,   "DirectDraw"},
        {ObjectType::DIRECT_DRAW7,  "DirectDraw7"},
        {ObjectType::GAMMA_CONTROL, "GammaControl"},
        {ObjectType::PALETTE,       "Palette"},
        {ObjectType::SURFACE,       "Surface"},
        {ObjectType::VERTEX_BUFFER, "VertexBuffer"}
    };

    const char* result_ptr = nullptr;

    for (const auto& object_type_name : object_type_name_array)
    {
        if (object_type_name.object_type == in_object_type)
        {
            result_ptr = object_type_name.name_ptr;

            break;
        }
    }

    return result_ptr;
}
