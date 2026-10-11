/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/macros.h"
#include "D3D8/entrypoints.h"
#include "D3D8/globals.h"
#include "D3D8/interceptors.h"
#include "D3D8/vtable_registry.h"
#include "Detours/src/detours.h"
#include "Kernel32/callbacks.h"

void D3D8::attach_to_module(HMODULE in_d3d8_module)
{
    {
        std::lock_guard<std::mutex> lock(g_hook_mutex);

        if (g_is_direct3d_create8_hooked == false)
        {
            void* direct3d_create8_function_ptr = reinterpret_cast<void*>(::GetProcAddress(in_d3d8_module,
                                                                                            "Direct3DCreate8") );

            if (direct3d_create8_function_ptr != nullptr)
            {
                g_cached_direct3d_create8_function_ptr = direct3d_create8_function_ptr;

                ::DetourTransactionBegin();
                ::DetourUpdateThread    (::GetCurrentThread() );
                ::DetourAttach          (&g_cached_direct3d_create8_function_ptr,
                                         reinterpret_cast<void*>(aiDirect3DCreate8) );

                if (::DetourTransactionCommit() == NO_ERROR)
                {
                    g_is_direct3d_create8_hooked = true;
                }
                else
                {
                    AI_ASSERT_FAIL();

                    g_cached_direct3d_create8_function_ptr = nullptr;
                }
            }
        }
    }
}

void D3D8::on_attach()
{
    /* Registered first, so that a load happening right now cannot be missed. */
    Kernel32::register_for_library_loaded_callback(on_library_loaded,
                                                   nullptr);

    /* Covers d3d8.dll having been loaded already. */
    on_library_loaded(::GetModuleHandleW(L"d3d8.dll"),
                      nullptr);
}

void D3D8::on_detach()
{
    /* Patched vtables are left as is (see D3D8/vtable_registry.h). */
    {
        std::lock_guard<std::mutex> lock(g_hook_mutex);

        if (g_is_direct3d_create8_hooked)
        {
            ::DetourTransactionBegin();
            ::DetourUpdateThread    (::GetCurrentThread() );
            ::DetourDetach          (&g_cached_direct3d_create8_function_ptr,
                                     reinterpret_cast<void*>(aiDirect3DCreate8) );
            ::DetourTransactionCommit();

            g_is_direct3d_create8_hooked = false;
        }
    }
}

void D3D8::on_library_loaded(HMODULE in_module,
                             void*   in_user_argument_ptr)
{
    bool is_hooked = false;

    {
        std::lock_guard<std::mutex> lock(g_hook_mutex);

        is_hooked = g_is_direct3d_create8_hooked;
    }

    if (in_module != nullptr &&
        is_hooked == false)
    {
        if (in_module == ::GetModuleHandleW(L"d3d8.dll") )
        {
            attach_to_module(in_module);
        }
    }
}
