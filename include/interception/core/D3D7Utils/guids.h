/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The GUIDs of DirectDraw and Direct3D 7 which a program passes to the API: the interfaces it asks an object for, and the types of
 * devices it creates.
 */
#ifndef D3D7UTILS_GUIDS_H
#define D3D7UTILS_GUIDS_H

#include "interception/core/D3D7Utils/methods.h"
#include "interception/core/D3D7Utils/types.h"
#include <stddef.h>

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

            /* The calls which are given the IID of the interface they make an object of (QueryInterface, DirectDrawCreateEx): the number of the
             * argument that holds it. False for the other calls.
             */
            bool get_iid_argument_index(const APIInterceptor::APIFunction& in_function,
                                        uint32_t*                          out_index_ptr);

            /* The name of the type of the object that an IID asks for (see get_object_type_name_ptr); nullptr if the bytes are not a GUID that is
             * known to make an object.
             */
            const char* get_object_type_name_ptr_for_iid(const void*   in_data_ptr,
                                                         const size_t& in_n_bytes);
        }
    }
}

#endif /* D3D7UTILS_GUIDS_H */
