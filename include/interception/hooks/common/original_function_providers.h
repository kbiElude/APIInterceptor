/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Where a hook (see common/generic_hook.h) gets the function it forwards the call to from: the table of methods of the object
 * the call is made on, or the export of a DLL which was hooked.
 */
#ifndef HOOKS_COMMON_ORIGINAL_FUNCTION_PROVIDERS_H
#define HOOKS_COMMON_ORIGINAL_FUNCTION_PROVIDERS_H

#include "interception/hooks/common/export_hook.h"
#include "interception/hooks/common/vtable_registry.h"

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            /* A function exported by a DLL. The hook is that of the API (see common/export_hook.h). */
            template<ExportHook* export_hook_ptr>
            struct ExportOriginalFunction
            {
                template<typename... Arguments>
                static void* get_ptr(const Arguments&...)
                {
                    return export_hook_ptr->get_original_function_ptr();
                }

                /* An export is not put back by anyone. */
                template<typename... Arguments>
                static void repair_after_call(const Arguments&...)
                {
                    /* Stub */
                }
            };

            /* A method of a COM object: the first argument is the object. */
            template<uint32_t vtable_index>
            struct VTableOriginalFunction
            {
                template<typename Self, typename... Rest>
                static void* get_ptr(const Self& in_self,
                                     const Rest&...)
                {
                    return VTableRegistry::get_ptr()->get_original_function_ptr(in_self,
                                                                                vtable_index);
                }

                /* See VTableRegistry::repair_vtable(). */
                template<typename Self, typename... Rest>
                static void repair_after_call(const Self& in_self,
                                              const Rest&...)
                {
                    VTableRegistry::get_ptr()->repair_vtable(in_self);
                }
            };
        }
    }
}

#endif /* HOOKS_COMMON_ORIGINAL_FUNCTION_PROVIDERS_H */
