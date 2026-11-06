/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Names the objects of an API by the order they are created in: Texture#3 is the third texture the dump made. An object which was
 * not seen being made is named by its address. The printer and the analysis name objects the same way, so that what one says about
 * an object can be looked up in the other.
 */
#ifndef APIDUMPLOADER_OBJECT_NAMER_H
#define APIDUMPLOADER_OBJECT_NAMER_H

#include "Capture/APIDumpLoader/api_dump_loader.h"
#include <map>
#include <stdint.h>
#include <string>

namespace Capture
{
    namespace APIDumpLoader
    {
        class ObjectNamer
        {
        public:
            /* The call released the object which is its first argument: if it returned 0, that was the last reference, and the object is gone. */
            void forget_after_release(const DumpedAPICall& in_call);

            /* An object is gone, and the address may be given to another one: it has no name until it is registered again. */
            void forget_object(const uint64_t& in_address);

            /* Returns "NULL" for a null address, "<type>#<n>" if the object has been registered, "<type>@0x<address>" otherwise. */
            std::string get_name(const uint64_t& in_address,
                                 const char*     in_type_name_ptr) const;

            /* Names the object, unless it has a name already; in_is_new says that it has been created by the call, so that an
             * address which was used by an object that is gone gets a new name.
             */
            void register_object(const uint64_t& in_address,
                                 const char*     in_type_name_ptr,
                                 const bool&     in_is_new);

        private:
            std::map<uint64_t, std::string> m_name_map;            /* by address   */
            std::map<std::string, uint32_t> m_n_named_objects_map; /* by type name */
        };
    }
}

#endif /* APIDUMPLOADER_OBJECT_NAMER_H */
