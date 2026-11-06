/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "common/macros.h"
#include "interception/hooks/common/export_hook.h"
#include "Detours/src/detours.h"
#include "interception/hooks/Kernel32/callbacks.h"

Interception::Hooks::Common::ExportHook::ExportHook(const wchar_t* in_module_name_ptr,
                                                    const char*    in_export_name_ptr,
                                                    void*          in_hook_function_ptr)
    :m_export_name_ptr  (in_export_name_ptr),
     m_hook_function_ptr(in_hook_function_ptr),
     m_module_name_ptr  (in_module_name_ptr)
{
    /* Stub */
}

void Interception::Hooks::Common::ExportHook::attach_to_module(HMODULE in_module)
{
    {
        std::lock_guard<std::mutex> lock(m_state.mutex);

        if (m_state.is_hooked == false)
        {
            void* export_function_ptr = reinterpret_cast<void*>(::GetProcAddress(in_module,
                                                                                 m_export_name_ptr) );

            if (export_function_ptr != nullptr)
            {
                m_state.original_function_ptr = export_function_ptr;

                ::DetourTransactionBegin();
                ::DetourUpdateThread    (::GetCurrentThread() );
                ::DetourAttach          (&m_state.original_function_ptr,
                                          m_hook_function_ptr);

                if (::DetourTransactionCommit() == NO_ERROR)
                {
                    m_state.is_hooked = true;
                }
                else
                {
                    AI_ASSERT_FAIL();

                    m_state.original_function_ptr = nullptr;
                }
            }
        }
    }
}

void* Interception::Hooks::Common::ExportHook::get_original_function_ptr() const
{
    return m_state.original_function_ptr;
}

void Interception::Hooks::Common::ExportHook::on_attach()
{
    /* Registered first, so that a load happening right now cannot be missed. */
    Interception::Hooks::Kernel32::register_for_library_loaded_callback(on_library_loaded,
                                                                        this);

    /* Covers the module having been loaded already. */
    {
        const HMODULE module = ::GetModuleHandleW(m_module_name_ptr);

        on_library_loaded(module,
                          this);
    }
}

void Interception::Hooks::Common::ExportHook::on_detach()
{
    {
        std::lock_guard<std::mutex> lock(m_state.mutex);

        if (m_state.is_hooked)
        {
            ::DetourTransactionBegin();
            ::DetourUpdateThread    (::GetCurrentThread() );
            ::DetourDetach          (&m_state.original_function_ptr,
                                      m_hook_function_ptr);
            ::DetourTransactionCommit();

            m_state.is_hooked = false;
        }
    }
}

void Interception::Hooks::Common::ExportHook::on_library_loaded(HMODULE in_module,
                                                                void*   in_user_argument_ptr)
{
    ExportHook* export_hook_ptr = static_cast<ExportHook*>(in_user_argument_ptr);
    bool        is_hooked       = false;

    {
        std::lock_guard<std::mutex> lock(export_hook_ptr->m_state.mutex);

        is_hooked = export_hook_ptr->m_state.is_hooked;
    }

    if (in_module != nullptr &&
        is_hooked == false)
    {
        if (in_module == ::GetModuleHandleW(export_hook_ptr->m_module_name_ptr) )
        {
            export_hook_ptr->attach_to_module(in_module);
        }
    }
}
