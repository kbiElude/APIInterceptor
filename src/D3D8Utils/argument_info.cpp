/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "D3D8Utils/argument_info.h"
#include "D3D8Utils/signature_info.h"

bool D3D8::Utils::get_argument_info(const APIInterceptor::APIFunction& in_function,
                                    const uint32_t&                    in_n_argument,
                                    ArgumentInfo*                      out_argument_info_ptr)
{
    /* DWORD arguments which hold flags or a color, or whose meaning depends on another argument. */
    static const ArgumentOverride argument_override_array[] =
    {
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CHECKDEVICEFORMAT,          ValueKind::UsageFlags,             4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CREATEDEVICE,               ValueKind::CreateFlags,            4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT,        ValueKind::LockFlags,              5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT,        ValueKind::Rect,                   6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,                ValueKind::ClearFlags,             3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,                ValueKind::Color,                  4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,                ValueKind::RectArray,              7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS,            ValueKind::RectArray,              6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS,            ValueKind::PointArray,             7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATECUBETEXTURE,    ValueKind::UsageFlags,             3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEINDEXBUFFER,    ValueKind::UsageFlags,             2},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATETEXTURE,        ValueKind::UsageFlags,             4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXBUFFER,   ValueKind::UsageFlags,             2},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXBUFFER,   ValueKind::FvfFlags,               3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVOLUMETEXTURE,  ValueKind::UsageFlags,             5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETRENDERSTATE,       ValueKind::RenderStateValue,       2},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETTEXTURESTAGESTATE, ValueKind::TextureStageStateValue, 3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETVERTEXSHADER,      ValueKind::FvfFlags,               1},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DINDEXBUFFER8_LOCK,            ValueKind::LockFlags,              4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_LOCKRECT,            ValueKind::LockFlags,              3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_LOCKRECT,            ValueKind::Rect,                   4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,            ValueKind::LockFlags,              4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,            ValueKind::Rect,                   5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVERTEXBUFFER8_LOCK,           ValueKind::LockFlags,              4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_LOCKBOX,              ValueKind::LockFlags,              3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX,       ValueKind::LockFlags,              4},
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
        #include "D3D8/d3d8_methods.inl"
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
