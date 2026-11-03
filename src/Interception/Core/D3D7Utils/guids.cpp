/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Core/D3D7Utils/guids.h"
#include <string.h>

const Interception::Core::D3D7Utils::KnownGuid* Interception::Core::D3D7Utils::find_known_guid(const GUID& in_guid)
{
    typedef Interception::Hooks::D3D7::Interface Interface;

    static const KnownGuid known_guid_array[] =
    {
        {{0x6c14db80, 0xa733, 0x11ce, {0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60} }, "IID_IDirectDraw",              Interface::IDIRECTDRAW,              ObjectType::DIRECT_DRAW},
        {{0x6c14db84, 0xa733, 0x11ce, {0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60} }, "IID_IDirectDrawPalette",       Interface::IDIRECTDRAWPALETTE,       ObjectType::PALETTE},
        {{0x6c14db85, 0xa733, 0x11ce, {0xa5, 0x21, 0x00, 0x20, 0xaf, 0x0b, 0xe5, 0x60} }, "IID_IDirectDrawClipper",       Interface::IDIRECTDRAWCLIPPER,       ObjectType::CLIPPER},
        {{0x15e65ec0, 0x3b9c, 0x11d2, {0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b} }, "IID_IDirectDraw7",             Interface::IDIRECTDRAW7,             ObjectType::DIRECT_DRAW7},
        {{0x06675a80, 0x3b9b, 0x11d2, {0xb9, 0x2f, 0x00, 0x60, 0x97, 0x97, 0xea, 0x5b} }, "IID_IDirectDrawSurface7",      Interface::IDIRECTDRAWSURFACE7,      ObjectType::SURFACE},
        {{0x4b9f0ee0, 0x0d7e, 0x11d0, {0x9b, 0x06, 0x00, 0xa0, 0xc9, 0x03, 0xa3, 0xb8} }, "IID_IDirectDrawColorControl",  Interface::IDIRECTDRAWCOLORCONTROL,  ObjectType::COLOR_CONTROL},
        {{0x69c11c3e, 0xb46b, 0x11d1, {0xad, 0x7a, 0x00, 0xc0, 0x4f, 0xc2, 0x9b, 0x4e} }, "IID_IDirectDrawGammaControl",  Interface::IDIRECTDRAWGAMMACONTROL,  ObjectType::GAMMA_CONTROL},
        {{0xf5049e77, 0x4861, 0x11d2, {0xa4, 0x07, 0x00, 0xa0, 0xc9, 0x06, 0x29, 0xa8} }, "IID_IDirect3D7",               Interface::IDIRECT3D7,               ObjectType::DIRECT3D7},
        {{0xf5049e79, 0x4861, 0x11d2, {0xa4, 0x07, 0x00, 0xa0, 0xc9, 0x06, 0x29, 0xa8} }, "IID_IDirect3DDevice7",         Interface::IDIRECT3DDEVICE7,         ObjectType::DEVICE},
        {{0xf5049e7d, 0x4861, 0x11d2, {0xa4, 0x07, 0x00, 0xa0, 0xc9, 0x06, 0x29, 0xa8} }, "IID_IDirect3DVertexBuffer7",   Interface::IDIRECT3DVERTEXBUFFER7,   ObjectType::VERTEX_BUFFER},

        {{0xa4665c60, 0x2673, 0x11cf, {0xa3, 0x1a, 0x00, 0xaa, 0x00, 0xb9, 0x33, 0x56} }, "IID_IDirect3DRGBDevice",       Interface::UNKNOWN,                  ObjectType::NONE},
        {{0x84e63de0, 0x46aa, 0x11cf, {0x81, 0x6f, 0x00, 0x00, 0xc0, 0x20, 0x15, 0x6e} }, "IID_IDirect3DHALDevice",       Interface::UNKNOWN,                  ObjectType::NONE},
        {{0x881949a1, 0xd6f3, 0x11d0, {0x89, 0xab, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29} }, "IID_IDirect3DMMXDevice",       Interface::UNKNOWN,                  ObjectType::NONE},
        {{0x50936643, 0x13e9, 0x11d1, {0x89, 0xaa, 0x00, 0xa0, 0xc9, 0x05, 0x41, 0x29} }, "IID_IDirect3DRefDevice",       Interface::UNKNOWN,                  ObjectType::NONE},
        {{0xf5049e78, 0x4861, 0x11d2, {0xa4, 0x07, 0x00, 0xa0, 0xc9, 0x06, 0x29, 0xa8} }, "IID_IDirect3DTnLHalDevice",    Interface::UNKNOWN,                  ObjectType::NONE},
        {{0x8767df22, 0xbacc, 0x11d1, {0x89, 0x36, 0x00, 0xa0, 0xc9, 0x06, 0x3f, 0xfa} }, "IID_IDirect3DNullDevice",      Interface::UNKNOWN,                  ObjectType::NONE}
    };

    const KnownGuid* result_ptr = nullptr;

    for (const auto& known_guid : known_guid_array)
    {
        if (memcmp(&known_guid.guid,
                   &in_guid,
                   sizeof(GUID) ) == 0)
        {
            result_ptr = &known_guid;

            break;
        }
    }

    return result_ptr;
}
