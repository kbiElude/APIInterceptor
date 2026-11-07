/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/core/D3D7Utils/argument_info.h"
#include "interception/core/D3D7Utils/signature_info.h"

bool Interception::Core::D3D7Utils::get_argument_info(const APIInterceptor::APIFunction&       in_function,
                                                      const uint32_t&                          in_n_argument,
                                                      Interception::Hooks::D3D7::ArgumentInfo* out_argument_info_ptr)
{
    /* DWORD arguments which hold flags or a color, or whose meaning depends on another argument; the objects that QueryInterface
     * makes (their type is the one of the interface asked for); and the extra arguments of the hooks.
     */
    static const Interception::Hooks::D3D7::ArgumentOverride argument_override_array[] =
    {
        {APIInterceptor::APIFUNCTION_D3D7_DIRECTDRAWCREATEEX,                            Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3D7_QUERYINTERFACE,                     Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_CLEAR,                        Interception::Hooks::D3D7::ValueKind::CLEAR_FLAGS,                   3},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_CLEAR,                        Interception::Hooks::D3D7::ValueKind::COLOR,                         4},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_CLEAR,                        Interception::Hooks::D3D7::ValueKind::RECT_ARRAY,                    7},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVE,         Interception::Hooks::D3D7::ValueKind::FVF_FLAGS,                     2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVE,         Interception::Hooks::D3D7::ValueKind::DRAW_FLAGS,                    7},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVESTRIDED,  Interception::Hooks::D3D7::ValueKind::FVF_FLAGS,                     2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVESTRIDED,  Interception::Hooks::D3D7::ValueKind::DRAW_FLAGS,                    7},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVESTRIDED,  Interception::Hooks::D3D7::ValueKind::STRIDED_VERTEX_ARRAYS,         9},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWINDEXEDPRIMITIVEVB,       Interception::Hooks::D3D7::ValueKind::DRAW_FLAGS,                    7},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVE,                Interception::Hooks::D3D7::ValueKind::FVF_FLAGS,                     2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVE,                Interception::Hooks::D3D7::ValueKind::DRAW_FLAGS,                    5},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVESTRIDED,         Interception::Hooks::D3D7::ValueKind::FVF_FLAGS,                     2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVESTRIDED,         Interception::Hooks::D3D7::ValueKind::DRAW_FLAGS,                    5},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVESTRIDED,         Interception::Hooks::D3D7::ValueKind::STRIDED_VERTEX_ARRAYS,         6},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_DRAWPRIMITIVEVB,              Interception::Hooks::D3D7::ValueKind::DRAW_FLAGS,                    5},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_GETRENDERSTATE,               Interception::Hooks::D3D7::ValueKind::RENDER_STATE_VALUE,            2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_GETTEXTURESTAGESTATE,         Interception::Hooks::D3D7::ValueKind::TEXTURE_STAGE_STATE_VALUE,     3},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_QUERYINTERFACE,               Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_SETRENDERSTATE,               Interception::Hooks::D3D7::ValueKind::RENDER_STATE_VALUE,            2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_SETTEXTURESTAGESTATE,         Interception::Hooks::D3D7::ValueKind::TEXTURE_STAGE_STATE_VALUE,     3},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DVERTEXBUFFER7_LOCK,                   Interception::Hooks::D3D7::ValueKind::LOCK_FLAGS,                    1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DVERTEXBUFFER7_PROCESSVERTICES,        Interception::Hooks::D3D7::ValueKind::VERTEX_OPERATION_FLAGS,        1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DVERTEXBUFFER7_PROCESSVERTICESSTRIDED, Interception::Hooks::D3D7::ValueKind::VERTEX_OPERATION_FLAGS,        1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DVERTEXBUFFER7_QUERYINTERFACE,         Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW_QUERYINTERFACE,                    Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_CREATEPALETTE,                    Interception::Hooks::D3D7::ValueKind::PALETTE_FLAGS,                 1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_CREATEPALETTE,                    Interception::Hooks::D3D7::ValueKind::PALETTE_ENTRIES,               5},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_ENUMDISPLAYMODES,                 Interception::Hooks::D3D7::ValueKind::ENUM_DISPLAY_MODES_FLAGS,      1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_ENUMSURFACES,                     Interception::Hooks::D3D7::ValueKind::ENUM_SURFACES_FLAGS,           1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_QUERYINTERFACE,                   Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_SETCOOPERATIVELEVEL,              Interception::Hooks::D3D7::ValueKind::COOPERATIVE_LEVEL_FLAGS,       2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_SETDISPLAYMODE,                   Interception::Hooks::D3D7::ValueKind::SET_DISPLAY_MODE_FLAGS,        5},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAW7_WAITFORVERTICALBLANK,             Interception::Hooks::D3D7::ValueKind::WAIT_FOR_VERTICAL_BLANK_FLAGS, 1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWCLIPPER_QUERYINTERFACE,             Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWCOLORCONTROL_QUERYINTERFACE,        Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWGAMMACONTROL_QUERYINTERFACE,        Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWPALETTE_INITIALIZE,                 Interception::Hooks::D3D7::ValueKind::PALETTE_FLAGS,                 2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWPALETTE_INITIALIZE,                 Interception::Hooks::D3D7::ValueKind::PALETTE_ENTRIES,               4},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWPALETTE_QUERYINTERFACE,             Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWPALETTE_SETENTRIES,                 Interception::Hooks::D3D7::ValueKind::PALETTE_ENTRIES,               5},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT,                       Interception::Hooks::D3D7::ValueKind::BLT_FLAGS,                     4},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT,                       Interception::Hooks::D3D7::ValueKind::BOOLEAN,                       6}, /* is the destination the primary surface */
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLTFAST,                   Interception::Hooks::D3D7::ValueKind::BLT_FAST_FLAGS,                5},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLTFAST,                   Interception::Hooks::D3D7::ValueKind::BOOLEAN,                       6}, /* ... */
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_FLIP,                      Interception::Hooks::D3D7::ValueKind::FLIP_FLAGS,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_GETCOLORKEY,               Interception::Hooks::D3D7::ValueKind::COLOR_KEY_FLAGS,               1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_GETOVERLAYPOSITION,        Interception::Hooks::D3D7::ValueKind::PLAIN,                         1}, /* LONGs are not HRESULTs */
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_GETOVERLAYPOSITION,        Interception::Hooks::D3D7::ValueKind::PLAIN,                         2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_LOCK,                      Interception::Hooks::D3D7::ValueKind::LOCK_FLAGS,                    3},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_QUERYINTERFACE,            Interception::Hooks::D3D7::ValueKind::OBJECT_OUT,                    2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_SETCOLORKEY,               Interception::Hooks::D3D7::ValueKind::COLOR_KEY_FLAGS,               1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_SETOVERLAYPOSITION,        Interception::Hooks::D3D7::ValueKind::PLAIN,                         1},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_SETOVERLAYPOSITION,        Interception::Hooks::D3D7::ValueKind::PLAIN,                         2},
        {APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_UPDATEOVERLAY,             Interception::Hooks::D3D7::ValueKind::OVERLAY_FLAGS,                 4},
    };

    const Interception::Hooks::D3D7::SignatureEntry* signature_entry_ptr = get_signature_entry_ptr(in_function);

    const bool result = Interception::Core::Common::find_argument_info(signature_entry_ptr,
                                                                       argument_override_array,
                                                                       sizeof(argument_override_array) / sizeof(argument_override_array[0]),
                                                                       in_function,
                                                                       in_n_argument,
                                                                       out_argument_info_ptr);

    return result;
}

uint32_t Interception::Core::D3D7Utils::get_n_arguments(const APIInterceptor::APIFunction& in_function)
{
    const Interception::Hooks::D3D7::SignatureEntry* signature_entry_ptr = get_signature_entry_ptr(in_function);
    uint32_t                                         result              = 0;

    if (signature_entry_ptr != nullptr)
    {
        result = static_cast<uint32_t>(signature_entry_ptr->get_argument_info_vec_func_ptr().size() );
    }

    return result;
}

bool Interception::Core::D3D7Utils::get_return_info(const APIInterceptor::APIFunction&       in_function,
                                                    Interception::Hooks::D3D7::ArgumentInfo* out_return_info_ptr)
{
    const Interception::Hooks::D3D7::SignatureEntry* signature_entry_ptr = get_signature_entry_ptr(in_function);
    bool                                             result              = false;

    if (signature_entry_ptr != nullptr)
    {
        *out_return_info_ptr = signature_entry_ptr->get_return_info_func_ptr();

        result = true;
    }

    return result;
}

const Interception::Hooks::D3D7::SignatureEntry* Interception::Core::D3D7Utils::get_signature_entry_ptr(const APIInterceptor::APIFunction& in_function)
{
    /* In the order of the functions: the exports, in the order of the enum of the functions. */
    static const Interception::Hooks::D3D7::SignatureEntry export_signature_entry_array[] =
    {
        {&SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWCREATEPROC>::get_argument_info_vec,        &SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWCREATEPROC>::get_return_info},
        {&SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWCREATECLIPPERPROC>::get_argument_info_vec, &SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWCREATECLIPPERPROC>::get_return_info},
        {&SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWCREATEEXPROC>::get_argument_info_vec,      &SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWCREATEEXPROC>::get_return_info},
        {&SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWENUMERATEPROC>::get_argument_info_vec,     &SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWENUMERATEPROC>::get_return_info},
        {&SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWENUMERATEEXPROC>::get_argument_info_vec,   &SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWENUMERATEEXPROC>::get_return_info},
        {&SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWENUMERATEEXPROC>::get_argument_info_vec,   &SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWENUMERATEEXPROC>::get_return_info},
        {&SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWENUMERATEPROC>::get_argument_info_vec,     &SignatureInfo<Interception::Hooks::D3D7::PFNDIRECTDRAWENUMERATEPROC>::get_return_info}
    };

    static const Interception::Hooks::D3D7::SignatureEntry method_signature_entry_array[] =
    {
        #define D3D7_METHOD(INTERFACE_TAG, interface_name, METHOD_TAG, method_name, vtable_index, return_type, parameters) \
            {&SignatureInfo<Interception::Hooks::D3D7::PFN_##INTERFACE_TAG##_##METHOD_TAG>::get_argument_info_vec, \
             &SignatureInfo<Interception::Hooks::D3D7::PFN_##INTERFACE_TAG##_##METHOD_TAG>::get_return_info},
        #include "interception/hooks/D3D7/d3d7_methods.inl"
        #undef D3D7_METHOD
    };

    const Interception::Hooks::D3D7::SignatureEntry* result_ptr = nullptr;

    if (in_function >= APIInterceptor::APIFUNCTION_D3D7_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_D3D7_EXPORTS_LAST)
    {
        result_ptr = &export_signature_entry_array[in_function - APIInterceptor::APIFUNCTION_D3D7_FIRST];
    }
    else
    if (in_function >= APIInterceptor::APIFUNCTION_D3D7_METHODS_FIRST &&
        in_function <= APIInterceptor::APIFUNCTION_D3D7_METHODS_LAST)
    {
        result_ptr = &method_signature_entry_array[in_function - APIInterceptor::APIFUNCTION_D3D7_METHODS_FIRST];
    }

    return result_ptr;
}
