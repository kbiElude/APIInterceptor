/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Hooks an object by the interface id it was asked for (see object_patcher.h for an object that is returned with its type known).
 */
#ifndef D3D7_INTERFACE_PATCHER_H
#define D3D7_INTERFACE_PATCHER_H

#include "interception/hooks/D3D7/types.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            class InterfacePatcher
            {
            public:
                /* Hooks the object that was asked for with QueryInterface by the interface it was asked for, if it is described. */
                static void patch_object_for_iid(const GUID& in_iid,
                                                 void*       in_object_ptr);
            };
        }
    }
}

#endif /* D3D7_INTERFACE_PATCHER_H */
