/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "capture/api_dump_loader/object_namer.h"
#include <stdio.h>

void Capture::APIDumpLoader::ObjectNamer::forget_after_release(const DumpedAPICall& in_call)
{
    if (in_call.arg_in_vec.empty()       == false                       &&
        in_call.returned_value_ptr       != nullptr                     &&
        in_call.returned_value_ptr->type == APIInterceptor::ARGTYPE_U32)
    {
        const uint32_t returned_value = in_call.returned_value_ptr->get_u32();

        if (returned_value == 0)
        {
            const uint64_t released_address = in_call.arg_in_vec.at(0).get_ptr_as_u64();

            forget_object(released_address);
        }
    }
}

void Capture::APIDumpLoader::ObjectNamer::forget_object(const uint64_t& in_address)
{
    m_name_map.erase(in_address);
}

std::string Capture::APIDumpLoader::ObjectNamer::get_name(const uint64_t& in_address,
                                                          const char*     in_type_name_ptr) const
{
    constexpr size_t ADDRESS_TEXT_N_BYTES = 3 + 16 + 1; /* "@0x", 16 hex digits and NUL */

    const auto  name_iterator = m_name_map.find(in_address);
    std::string result;

    if (in_address == 0)
    {
        result = "NULL";
    }
    else
    if (name_iterator != m_name_map.end() )
    {
        result = name_iterator->second;
    }
    else
    {
        char address_i8vec20[ADDRESS_TEXT_N_BYTES];

        snprintf(address_i8vec20,
                 sizeof(address_i8vec20),
                 "@0x%llx",
                 static_cast<unsigned long long>(in_address) );

        result = std::string((in_type_name_ptr != nullptr) ? in_type_name_ptr
                                                           : "Object") + address_i8vec20;
    }

    return result;
}

void Capture::APIDumpLoader::ObjectNamer::register_object(const uint64_t& in_address,
                                                          const char*     in_type_name_ptr,
                                                          const bool&     in_is_new)
{
    if (in_address != 0)
    {
        const auto name_iterator = m_name_map.find(in_address);
        const bool is_named      = (name_iterator != m_name_map.end() );

        if (in_is_new         ||
            is_named == false)
        {
            const std::string type_name(in_type_name_ptr);
            const auto        n_object = ++m_n_named_objects_map[type_name];

            m_name_map[in_address] = type_name + "#" + std::to_string(n_object);
        }
    }
}
