/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Core/D3D8Utils/argument_info.h"
#include "Interception/Core/D3D8Utils/signature_info.h"

bool D3D8::Utils::get_argument_info(const APIInterceptor::APIFunction& in_function,
                                    const uint32_t&                    in_n_argument,
                                    ArgumentInfo*                      out_argument_info_ptr)
{
    /* DWORD arguments which hold flags or a color, or whose meaning depends on another argument. */
    static const ArgumentOverride argument_override_array[] =
    {
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CHECKDEVICEFORMAT,          ValueKind::USAGE_FLAGS,               4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CREATEDEVICE,               ValueKind::CREATE_FLAGS,              4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT,        ValueKind::LOCK_FLAGS,                5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT,        ValueKind::RECT,                      6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,                ValueKind::CLEAR_FLAGS,               3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,                ValueKind::COLOR,                     4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,                ValueKind::RECT_ARRAY,                7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS,            ValueKind::RECT_ARRAY,                6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS,            ValueKind::POINT_ARRAY,               7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATECUBETEXTURE,    ValueKind::USAGE_FLAGS,               3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEINDEXBUFFER,    ValueKind::USAGE_FLAGS,               2},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATETEXTURE,        ValueKind::USAGE_FLAGS,               4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXBUFFER,   ValueKind::USAGE_FLAGS,               2},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXBUFFER,   ValueKind::FVF_FLAGS,                 3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVOLUMETEXTURE,  ValueKind::USAGE_FLAGS,               5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWRECTPATCH,        ValueKind::FLOAT_ARRAY,               4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWTRIPATCH,         ValueKind::FLOAT_ARRAY,               4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,              ValueKind::RECT,                      5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,              ValueKind::RECT,                      6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,              ValueKind::RECT_ARRAY,                7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETCLIPPLANE,         ValueKind::FLOAT_ARRAY,               3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETRENDERSTATE,       ValueKind::RENDER_STATE_VALUE,        2},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETTEXTURESTAGESTATE, ValueKind::TEXTURE_STAGE_STATE_VALUE, 3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETVERTEXSHADER,      ValueKind::FVF_FLAGS,                 1},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DINDEXBUFFER8_LOCK,            ValueKind::LOCK_FLAGS,                4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_LOCKRECT,            ValueKind::LOCK_FLAGS,                3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_LOCKRECT,            ValueKind::RECT,                      4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSWAPCHAIN8_PRESENT,           ValueKind::RECT,                      5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSWAPCHAIN8_PRESENT,           ValueKind::RECT,                      6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSWAPCHAIN8_PRESENT,           ValueKind::RECT_ARRAY,                7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,            ValueKind::LOCK_FLAGS,                4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,            ValueKind::RECT,                      5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVERTEXBUFFER8_LOCK,           ValueKind::LOCK_FLAGS,                4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_LOCKBOX,              ValueKind::LOCK_FLAGS,                3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX,       ValueKind::LOCK_FLAGS,                4},
    };

    const ArgumentOverride* override_ptr    = nullptr;
    bool                    result          = false;
    const SignatureEntry*   signature_entry = get_signature_entry_ptr(in_function);

    for (const auto& current_override : argument_override_array)
    {
        if (current_override.function   == in_function &&
            current_override.n_argument == in_n_argument)
        {
            override_ptr = &current_override;

            break;
        }
    }

    if (signature_entry != nullptr)
    {
        const auto& argument_info_vec = signature_entry->get_argument_info_vec_func_ptr();

        if (in_n_argument < argument_info_vec.size() )
        {
            *out_argument_info_ptr = argument_info_vec.at(in_n_argument);

            if (override_ptr != nullptr)
            {
                out_argument_info_ptr->kind = override_ptr->kind;
            }

            result = true;
        }
        else
        if (override_ptr != nullptr)
        {
            /* An argument which follows the ones of the method. Only overrides describe those. */
            out_argument_info_ptr->kind                 = override_ptr->kind;
            out_argument_info_ptr->object_type_name_ptr = nullptr;

            result = true;
        }
    }

    return result;
}

uint32_t D3D8::Utils::get_n_arguments(const APIInterceptor::APIFunction& in_function)
{
    const SignatureEntry* signature_entry = get_signature_entry_ptr(in_function);
    uint32_t              result          = 0;

    if (signature_entry != nullptr)
    {
        result = static_cast<uint32_t>(signature_entry->get_argument_info_vec_func_ptr().size() );
    }

    return result;
}

bool D3D8::Utils::get_return_info(const APIInterceptor::APIFunction& in_function,
                                  ArgumentInfo*                      out_return_info_ptr)
{
    const SignatureEntry* signature_entry = get_signature_entry_ptr(in_function);
    bool                  result          = false;

    if (signature_entry != nullptr)
    {
        *out_return_info_ptr = signature_entry->get_return_info_func_ptr();

        result = true;
    }

    return result;
}

const D3D8::SignatureEntry* D3D8::Utils::get_signature_entry_ptr(const APIInterceptor::APIFunction& in_function)
{
    static const SignatureEntry signature_entry_array[] =
    {
        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
            {&SignatureInfo<PFN_##INTERFACE_TAG##_##METHOD_TAG>::get_argument_info_vec, \
             &SignatureInfo<PFN_##INTERFACE_TAG##_##METHOD_TAG>::get_return_info},
        #include "Interception/Hooks/D3D8/d3d8_methods.inl"
        #undef D3D8_METHOD
    };

    const SignatureEntry* result = nullptr;

    if (in_function >= APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_D3D8_METHODS_LAST)
    {
        result = &signature_entry_array[in_function - APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST];
    }

    return result;
}
