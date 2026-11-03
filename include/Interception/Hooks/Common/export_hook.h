/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hook of a function which a DLL exports (e.g. Direct3DCreate8 of d3d8.dll). The DLL is not linked against, so the function is
 * found, and hooked, once the DLL is loaded.
 *
 * An ExportHook has to outlive the time the interceptors are attached, as the load of the DLL is reported to it.
 */
#ifndef HOOKS_COMMON_EXPORT_HOOK_H
#define HOOKS_COMMON_EXPORT_HOOK_H

#include <Windows.h>
#include <mutex>

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            class ExportHook
            {
            public:
                /* The name of the export and of the module are not copied. */
                ExportHook(const wchar_t* in_module_name_ptr,
                           const char*    in_export_name_ptr,
                           void*          in_hook_function_ptr);

                /* The function to call for what the application asked for. Null until the export is hooked; set before the hook
                 * can run, and not changed while it is hooked.
                 */
                void* get_original_function_ptr() const;

                /* Call after the interceptors are attached. Hooks the export now if the module is loaded, otherwise once it gets loaded. */
                void on_attach();

                /* Call before the interceptors are detached. */
                void on_detach();

            private:
                /* The state of the hook: what the Detours transaction changes, and whether it did. */
                struct HookState
                {
                    bool       is_hooked             = false;
                    std::mutex mutex;
                    void*      original_function_ptr = nullptr;
                };

                void attach_to_module(HMODULE in_module);

                /* Interception::Hooks::Kernel32::PFNLIBRARYLOADEDCALLBACKPROC */
                static void on_library_loaded(HMODULE in_module,
                                              void*   in_user_argument_ptr);

                const char*    m_export_name_ptr;
                void*          m_hook_function_ptr;
                const wchar_t* m_module_name_ptr;
                HookState      m_state;
            };
        }
    }
}

#endif /* HOOKS_COMMON_EXPORT_HOOK_H */
