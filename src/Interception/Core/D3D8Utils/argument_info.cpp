/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Core/D3D8Utils/argument_info.h"
#include "Interception/Core/D3D8Utils/signature_info.h"

bool Interception::Core::D3D8Utils::get_argument_info(const APIInterceptor::APIFunction&       in_function,
                                                      const uint32_t&                          in_n_argument,
                                                      Interception::Hooks::D3D8::ArgumentInfo* out_argument_info_ptr)
{
    /* DWORD arguments which hold flags or a color, or whose meaning depends on another argument. */
    static const Interception::Hooks::D3D8::ArgumentOverride argument_override_array[] =
    {
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CHECKDEVICEFORMAT,          Interception::Hooks::D3D8::ValueKind::USAGE_FLAGS,               4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3D8_CREATEDEVICE,               Interception::Hooks::D3D8::ValueKind::CREATE_FLAGS,              4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT,        Interception::Hooks::D3D8::ValueKind::LOCK_FLAGS,                5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DCUBETEXTURE8_LOCKRECT,        Interception::Hooks::D3D8::ValueKind::RECT,                      6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,                Interception::Hooks::D3D8::ValueKind::CLEAR_FLAGS,               3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,                Interception::Hooks::D3D8::ValueKind::COLOR,                     4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CLEAR,                Interception::Hooks::D3D8::ValueKind::RECT_ARRAY,                7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS,            Interception::Hooks::D3D8::ValueKind::RECT_ARRAY,                6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_COPYRECTS,            Interception::Hooks::D3D8::ValueKind::POINT_ARRAY,               7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATECUBETEXTURE,    Interception::Hooks::D3D8::ValueKind::USAGE_FLAGS,               3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEINDEXBUFFER,    Interception::Hooks::D3D8::ValueKind::USAGE_FLAGS,               2},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATETEXTURE,        Interception::Hooks::D3D8::ValueKind::USAGE_FLAGS,               4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXBUFFER,   Interception::Hooks::D3D8::ValueKind::USAGE_FLAGS,               2},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVERTEXBUFFER,   Interception::Hooks::D3D8::ValueKind::FVF_FLAGS,                 3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_CREATEVOLUMETEXTURE,  Interception::Hooks::D3D8::ValueKind::USAGE_FLAGS,               5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWRECTPATCH,        Interception::Hooks::D3D8::ValueKind::FLOAT_ARRAY,               4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_DRAWTRIPATCH,         Interception::Hooks::D3D8::ValueKind::FLOAT_ARRAY,               4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,              Interception::Hooks::D3D8::ValueKind::RECT,                      5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,              Interception::Hooks::D3D8::ValueKind::RECT,                      6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,              Interception::Hooks::D3D8::ValueKind::RECT_ARRAY,                7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETCLIPPLANE,         Interception::Hooks::D3D8::ValueKind::FLOAT_ARRAY,               3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETRENDERSTATE,       Interception::Hooks::D3D8::ValueKind::RENDER_STATE_VALUE,        2},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETTEXTURESTAGESTATE, Interception::Hooks::D3D8::ValueKind::TEXTURE_STAGE_STATE_VALUE, 3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_SETVERTEXSHADER,      Interception::Hooks::D3D8::ValueKind::FVF_FLAGS,                 1},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DINDEXBUFFER8_LOCK,            Interception::Hooks::D3D8::ValueKind::LOCK_FLAGS,                4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_LOCKRECT,            Interception::Hooks::D3D8::ValueKind::LOCK_FLAGS,                3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSURFACE8_LOCKRECT,            Interception::Hooks::D3D8::ValueKind::RECT,                      4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSWAPCHAIN8_PRESENT,           Interception::Hooks::D3D8::ValueKind::RECT,                      5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSWAPCHAIN8_PRESENT,           Interception::Hooks::D3D8::ValueKind::RECT,                      6},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSWAPCHAIN8_PRESENT,           Interception::Hooks::D3D8::ValueKind::RECT_ARRAY,                7},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,            Interception::Hooks::D3D8::ValueKind::LOCK_FLAGS,                4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DTEXTURE8_LOCKRECT,            Interception::Hooks::D3D8::ValueKind::RECT,                      5},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVERTEXBUFFER8_LOCK,           Interception::Hooks::D3D8::ValueKind::LOCK_FLAGS,                4},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUME8_LOCKBOX,              Interception::Hooks::D3D8::ValueKind::LOCK_FLAGS,                3},
        {APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DVOLUMETEXTURE8_LOCKBOX,       Interception::Hooks::D3D8::ValueKind::LOCK_FLAGS,                4},
    };

    const bool result = Interception::Core::Common::find_argument_info(get_signature_entry_ptr(in_function),
                                                                       argument_override_array,
                                                                       sizeof(argument_override_array) / sizeof(argument_override_array[0]),
                                                                       in_function,
                                                                       in_n_argument,
                                                                       out_argument_info_ptr);

    return result;
}

uint32_t Interception::Core::D3D8Utils::get_n_arguments(const APIInterceptor::APIFunction& in_function)
{
    const Interception::Hooks::D3D8::SignatureEntry* signature_entry = get_signature_entry_ptr(in_function);
    uint32_t              result          = 0;

    if (signature_entry != nullptr)
    {
        result = static_cast<uint32_t>(signature_entry->get_argument_info_vec_func_ptr().size() );
    }

    return result;
}

bool Interception::Core::D3D8Utils::get_return_info(const APIInterceptor::APIFunction&       in_function,
                                                    Interception::Hooks::D3D8::ArgumentInfo* out_return_info_ptr)
{
    const Interception::Hooks::D3D8::SignatureEntry* signature_entry = get_signature_entry_ptr(in_function);
    bool                  result          = false;

    if (signature_entry != nullptr)
    {
        *out_return_info_ptr = signature_entry->get_return_info_func_ptr();

        result = true;
    }

    return result;
}

const Interception::Hooks::D3D8::SignatureEntry* Interception::Core::D3D8Utils::get_signature_entry_ptr(const APIInterceptor::APIFunction& in_function)
{
    static const Interception::Hooks::D3D8::SignatureEntry signature_entry_array[] =
    {
        #define D3D8_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
            {&SignatureInfo<Interception::Hooks::D3D8::PFN_##INTERFACE_TAG##_##METHOD_TAG>::get_argument_info_vec, \
             &SignatureInfo<Interception::Hooks::D3D8::PFN_##INTERFACE_TAG##_##METHOD_TAG>::get_return_info},
        #include "Interception/Hooks/D3D8/d3d8_methods.inl"
        #undef D3D8_METHOD
    };

    const Interception::Hooks::D3D8::SignatureEntry* result = nullptr;

    if (in_function >= APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_D3D8_METHODS_LAST)
    {
        result = &signature_entry_array[in_function - APIInterceptor::APIFUNCTION_D3D8_METHODS_FIRST];
    }

    return result;
}
