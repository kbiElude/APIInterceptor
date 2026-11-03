/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Names the objects of an API by the order they are created in: Texture#3 is the third texture the dump made. An object which was
 * not seen being made is named by its address.
 */
#ifndef APIDUMPPRINTER_OBJECT_NAMER_H
#define APIDUMPPRINTER_OBJECT_NAMER_H

#include <map>
#include <stdint.h>
#include <string>

namespace Capture
{
    namespace APIDumpPrinter
    {
        class ObjectNamer
        {
        public:
            /* Returns "NULL" for a null pointer, "<type>#<n>" if the object has been registered, "<type>@0x<address>" otherwise. */
            std::string get_name(const void* in_object_ptr,
                                 const char* in_type_name_ptr) const;

            /* Names the object, unless it has a name already; in_is_new says that it has been created by the call, so that an
             * address which was used by an object that is gone gets a new name.
             */
            void register_object(const void* in_object_ptr,
                                 const char* in_type_name_ptr,
                                 const bool& in_is_new);

        private:
            std::map<const void*, std::string> m_object_name_map;
            std::map<std::string, uint32_t>    m_n_created_objects_map; /* by type name */
        };
    }
}

#endif /* APIDUMPPRINTER_OBJECT_NAMER_H */
