/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The enumerations of DirectDraw and Direct3D call a function of the application for each thing they find, from within the call. The
 * calls that the application makes in it (it creates its DirectDraw object there, usually) are its own, and not the driver's, which the
 * tracker would take them for, as they are made from within an intercepted call. So the callback is replaced by one which has the
 * thread count as outside any call while the application's callback runs (see APIInterceptor::TopLevelScope), and puts the
 * application's own back as soon as the call is over, so that it is what is recorded.
 */
#ifndef D3D7_ENUM_CALLBACK_POLICY_H
#define D3D7_ENUM_CALLBACK_POLICY_H

#include "Common/top_level_scope.h"
#include "Interception/Hooks/D3D7/hook_policy.h"
#include <tuple>

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            /* The application's callback and context, for as long as the call lasts. */
            struct EnumCallbackState
            {
                void* callback_ptr;
                void* context_ptr;
            };

            /* Callbacks whose last argument is the context. */
            template<typename ReturnType, typename... Arguments>
            struct ContextLastTrampoline
            {
                typedef ReturnType (__stdcall* CallbackPtr)(Arguments..., void*);

                static void* get_function_ptr()
                {
                    return reinterpret_cast<void*>(&invoke);
                }

                static ReturnType __stdcall invoke(Arguments... in_arguments,
                                                   void*        in_context_ptr)
                {
                    const EnumCallbackState* state_ptr = static_cast<const EnumCallbackState*>(in_context_ptr);

                    APIInterceptor::TopLevelScope scope;

                    return reinterpret_cast<CallbackPtr>(state_ptr->callback_ptr)(in_arguments...,
                                                                                  state_ptr->context_ptr);
                }
            };

            /* The callback of DirectDrawEnumerateEx has the monitor after the context. */
            template<typename Character>
            struct EnumerateExTrampoline
            {
                typedef int (__stdcall* CallbackPtr)(GUID*, Character*, Character*, void*, HMONITOR);

                static void* get_function_ptr()
                {
                    return reinterpret_cast<void*>(&invoke);
                }

                static int __stdcall invoke(GUID*        in_guid_ptr,
                                            Character*   in_description_ptr,
                                            Character*   in_name_ptr,
                                            void*        in_context_ptr,
                                            HMONITOR     in_monitor)
                {
                    const EnumCallbackState* state_ptr = static_cast<const EnumCallbackState*>(in_context_ptr);

                    APIInterceptor::TopLevelScope scope;

                    return reinterpret_cast<CallbackPtr>(state_ptr->callback_ptr)(in_guid_ptr,
                                                                                  in_description_ptr,
                                                                                  in_name_ptr,
                                                                                  state_ptr->context_ptr,
                                                                                  in_monitor);
                }
            };

            /* The context and the callback are the arguments with the numbers. */
            template<typename Trampoline, size_t context_index, size_t callback_index>
            struct EnumCallbackPolicy : public HookPolicyBase
            {
                template<typename... Arguments>
                static void on_call_starting(Arguments&... io_arguments)
                {
                    auto  arguments = std::tie(io_arguments...);
                    void*& callback_ptr = std::get<callback_index>(arguments);
                    void*& context_ptr  = std::get<context_index> (arguments);

                    if (callback_ptr != nullptr)
                    {
                        context_ptr  = new EnumCallbackState{callback_ptr,
                                                             context_ptr};
                        callback_ptr = Trampoline::get_function_ptr();
                    }
                }

                template<typename... Arguments>
                static void on_call_finished(const bool&,
                                             Arguments&... io_arguments)
                {
                    auto  arguments = std::tie(io_arguments...);
                    void*& callback_ptr = std::get<callback_index>(arguments);
                    void*& context_ptr  = std::get<context_index> (arguments);

                    if (callback_ptr == Trampoline::get_function_ptr() )
                    {
                        const EnumCallbackState* state_ptr = static_cast<const EnumCallbackState*>(context_ptr);

                        callback_ptr = state_ptr->callback_ptr;
                        context_ptr  = state_ptr->context_ptr;

                        delete state_ptr;
                    }
                }
            };

            typedef ContextLastTrampoline<int,  GUID*, char*,    char*>    DirectDrawEnumerateATrampoline;
            typedef ContextLastTrampoline<int,  GUID*, wchar_t*, wchar_t*> DirectDrawEnumerateWTrampoline;
            typedef ContextLastTrampoline<long, char*, char*,    D3DDEVICEDESC7*> DevicesTrampoline;
            typedef ContextLastTrampoline<long, DDPIXELFORMAT*>            PixelFormatsTrampoline;
            typedef ContextLastTrampoline<long, DDSURFACEDESC2*>           SurfaceDescriptionsTrampoline;
            typedef ContextLastTrampoline<long, IDirectDrawSurface7*, DDSURFACEDESC2*> SurfacesTrampoline;

            #define D3D7_ENUM_POLICY(function_tag, trampoline, context_index, callback_index) \
                template<> \
                struct HookPolicy<APIInterceptor::APIFUNCTION_D3D7_##function_tag> : public EnumCallbackPolicy<trampoline, context_index, callback_index> \
                { \
                    /* Stub */ \
                };

            D3D7_ENUM_POLICY(DIRECTDRAWENUMERATEA,                    DirectDrawEnumerateATrampoline,  1, 0)
            D3D7_ENUM_POLICY(DIRECTDRAWENUMERATEEXA,                  EnumerateExTrampoline<char>,     1, 0)
            D3D7_ENUM_POLICY(DIRECTDRAWENUMERATEEXW,                  EnumerateExTrampoline<wchar_t>,  1, 0)
            D3D7_ENUM_POLICY(DIRECTDRAWENUMERATEW,                    DirectDrawEnumerateWTrampoline,  1, 0)
            D3D7_ENUM_POLICY(IDIRECT3D7_ENUMDEVICES,                  DevicesTrampoline,               2, 1)
            D3D7_ENUM_POLICY(IDIRECT3D7_ENUMZBUFFERFORMATS,           PixelFormatsTrampoline,          3, 2)
            D3D7_ENUM_POLICY(IDIRECT3DDEVICE7_ENUMTEXTUREFORMATS,     PixelFormatsTrampoline,          2, 1)
            D3D7_ENUM_POLICY(IDIRECTDRAW7_ENUMDISPLAYMODES,           SurfaceDescriptionsTrampoline,   3, 4)
            D3D7_ENUM_POLICY(IDIRECTDRAW7_ENUMSURFACES,               SurfacesTrampoline,              3, 4)
            D3D7_ENUM_POLICY(IDIRECTDRAWSURFACE7_ENUMATTACHEDSURFACES, SurfacesTrampoline,             1, 2)
            D3D7_ENUM_POLICY(IDIRECTDRAWSURFACE7_ENUMOVERLAYZORDERS,  SurfacesTrampoline,              2, 3)
            #undef D3D7_ENUM_POLICY
        }
    }
}

#endif /* D3D7_ENUM_CALLBACK_POLICY_H */
