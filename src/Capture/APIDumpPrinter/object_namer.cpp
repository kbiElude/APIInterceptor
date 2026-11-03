/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "object_namer.h"
#include <stdio.h>

std::string Capture::APIDumpPrinter::ObjectNamer::get_name(const void* in_object_ptr,
                                                           const char* in_type_name_ptr) const
{
    constexpr size_t OBJECT_ADDRESS_TEXT_N_BYTES = 3 + 16 + 1; /* "@0x", 16 hex digits and NUL */

    const auto  map_iterator = m_object_name_map.find(in_object_ptr);
    std::string result;

    if (in_object_ptr == nullptr)
    {
        result = "NULL";
    }
    else
    if (map_iterator != m_object_name_map.end() )
    {
        result = map_iterator->second;
    }
    else
    {
        char buffer_i8vec20[OBJECT_ADDRESS_TEXT_N_BYTES];

        snprintf(buffer_i8vec20,
                 sizeof(buffer_i8vec20),
                 "@0x%llx",
                 static_cast<unsigned long long>(reinterpret_cast<uintptr_t>(in_object_ptr) ));

        result = std::string((in_type_name_ptr != nullptr) ? in_type_name_ptr
                                                           : "Object") + buffer_i8vec20;
    }

    return result;
}

void Capture::APIDumpPrinter::ObjectNamer::register_object(const void* in_object_ptr,
                                                           const char* in_type_name_ptr,
                                                           const bool& in_is_new)
{
    if (in_object_ptr != nullptr &&
        (in_is_new                                           ||
         m_object_name_map.find(in_object_ptr) == m_object_name_map.end() ))
    {
        const std::string type_name(in_type_name_ptr);
        const auto        n_object = ++m_n_created_objects_map[type_name];

        m_object_name_map[in_object_ptr] = type_name + "#" + std::to_string(n_object);
    }
}
