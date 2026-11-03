/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The GUIDs of DirectDraw and Direct3D 7 which a program passes to the API: the interfaces it asks an object for, and the types of
 * devices it creates.
 */
#ifndef D3D7UTILS_GUIDS_H
#define D3D7UTILS_GUIDS_H

#include "Interception/Core/D3D7Utils/types.h"

namespace Interception
{
    namespace Core
    {
        namespace D3D7Utils
        {
            struct KnownGuid
            {
                GUID                                  guid;
                const char*                           name_ptr;       /* e.g. IID_IDirect3D7 */
                Interception::Hooks::D3D7::Interface  interface_type; /* the interface that an object asked for with the GUID is; UNKNOWN for a device type */
                ObjectType                            object_type;    /* NONE for a device type */
            };

            /* Returns nullptr if the GUID is not known. */
            const KnownGuid* find_known_guid(const GUID& in_guid);
        }
    }
}

#endif /* D3D7UTILS_GUIDS_H */
