/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Compile-time description of D3D7 argument types. Shared by the interceptor (what to capture) and the printer (how to
 * decode it).
 */
#ifndef D3D7UTILS_TYPES_H
#define D3D7UTILS_TYPES_H

#include "Interception/Hooks/D3D7/types.h"
#include <type_traits>

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            /* How an argument is captured (see Hooks/Common/types.h). */
            typedef Interception::Hooks::Common::ArgumentCategory ArgumentCategory;

            /* D3D7 interfaces. Interface::UNKNOWN means the interface has no entry in the method table. */
            template<typename T>
            struct InterfaceTraits
            {
                static const bool                                 is_object       = false;
                static const Interception::Hooks::D3D7::Interface interface_value = Interception::Hooks::D3D7::Interface::UNKNOWN;
            };

            /* The pointed-to type of a pointer argument, without cv-qualifiers. */
            template<typename T>
            using PointeeOf = Interception::Hooks::Common::PointeeOf<T>;

            /* Integers which can be written through a pointer. */
            template<typename T>
            struct ScalarOutTraits
            {
                static const bool is_supported = false;
            };

            /* Structures which are captured when passed by pointer. A structure which is both read and written by a call (the
             * descriptions of a surface are) is captured before the call, too.
             */
            template<typename T>
            struct StructTraits
            {
                static const bool is_captured     = false;
                static const bool is_input_output = false;
            };

            #define D3D7_INTERFACE_TRAITS(type, interface_name) \
                template<> struct InterfaceTraits<type> \
                { \
                    static const bool                                 is_object       = true; \
                    static const Interception::Hooks::D3D7::Interface interface_value = Interception::Hooks::D3D7::Interface::interface_name; \
                };

            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirect3D7,             IDIRECT3D7)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirect3DDevice7,       IDIRECT3DDEVICE7)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirect3DVertexBuffer7, IDIRECT3DVERTEXBUFFER7)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirectDraw7,           IDIRECTDRAW7)
            D3D7_INTERFACE_TRAITS(Interception::Hooks::D3D7::IDirectDrawSurface7,    IDIRECTDRAWSURFACE7)
            #undef D3D7_INTERFACE_TRAITS

            #define D3D7_SCALAR_OUT_TRAITS(type) \
                template<> struct ScalarOutTraits<type> { static const bool is_supported = true; };

            D3D7_SCALAR_OUT_TRAITS(int)
            D3D7_SCALAR_OUT_TRAITS(long)
            D3D7_SCALAR_OUT_TRAITS(unsigned int)
            D3D7_SCALAR_OUT_TRAITS(unsigned long)
            #undef D3D7_SCALAR_OUT_TRAITS

            #define D3D7_STRUCT_TRAITS(type, is_input_output_value) \
                template<> struct StructTraits<type> \
                { \
                    static const bool is_captured     = true; \
                    static const bool is_input_output = is_input_output_value; \
                };

            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DLIGHT7,            false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DMATERIAL7,         false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DMATRIX,            false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DRECT,              false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DVERTEXBUFFERDESC,  true)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::D3DVIEWPORT7,         false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDCOLORKEY,           false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDPIXELFORMAT,        false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDSCAPS2,             false)
            D3D7_STRUCT_TRAITS(Interception::Hooks::D3D7::DDSURFACEDESC2,       true)
            #undef D3D7_STRUCT_TRAITS

            template<typename T>
            struct ArgumentCategoryOf
            {
                static const ArgumentCategory value = ArgumentCategory::SCALAR;
            };

            template<typename S>
            struct ArgumentCategoryOf<const S*>
            {
                static const ArgumentCategory value = StructTraits<S>::is_captured ? ArgumentCategory::CONST_STRUCT
                                                                                   : ArgumentCategory::SCALAR;
            };

            template<typename S>
            struct ArgumentCategoryOf<S*>
            {
                static const ArgumentCategory value = StructTraits<S>::is_captured     ? ArgumentCategory::MUTABLE_STRUCT
                                                    : InterfaceTraits<S>::is_object    ? ArgumentCategory::OBJECT
                                                    : ScalarOutTraits<S>::is_supported ? ArgumentCategory::SCALAR_OUT
                                                                                       : ArgumentCategory::SCALAR;
            };

            template<typename I>
            struct ArgumentCategoryOf<I**>
            {
                static const ArgumentCategory value = InterfaceTraits<I>::is_object ? ArgumentCategory::OBJECT_OUT
                                                                                    : ArgumentCategory::SCALAR;
            };

            template<>
            struct ArgumentCategoryOf<void**>
            {
                static const ArgumentCategory value = ArgumentCategory::POINTER_OUT;
            };

            template<>
            struct ArgumentCategoryOf<const GUID&>
            {
                static const ArgumentCategory value = ArgumentCategory::GUID;
            };
        }
    }
}

#endif /* D3D7UTILS_TYPES_H */
