/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interceptor_registry.h"
#include "capture/api_dump_loader/api_info.h"
#include <algorithm>

Replay::ReplayEngineDLL::InterceptorRegistry::InterceptorRegistry()
    :m_table_ptr(nullptr)
{
    /* Stub */
}

void Replay::ReplayEngineDLL::InterceptorRegistry::add(ICallInterceptor* in_interceptor_ptr)
{
    Entry entry;

    entry.group_vec       = in_interceptor_ptr->get_api_groups();
    entry.interceptor_ptr = in_interceptor_ptr;

    /* None named: all. */
    if (entry.group_vec.empty() )
    {
        entry.group_vec = Capture::APIDumpLoader::get_api_groups();

        entry.group_vec.push_back(Capture::APIDumpLoader::APIGroup::UNKNOWN);
    }

    std::lock_guard<std::mutex> lock(m_mutex);

    m_entry_vec.push_back(entry);

    publish_table();
}

const std::vector<Replay::ReplayEngineDLL::ICallInterceptor*>& Replay::ReplayEngineDLL::InterceptorRegistry::get_interceptor_ptr_vec(const Capture::APIDumpLoader::APIGroup& in_group) const
{
    static const std::vector<ICallInterceptor*> NO_INTERCEPTORS;

    const Table* const table_ptr = m_table_ptr;

    return (table_ptr != nullptr) ? table_ptr->at(static_cast<size_t>(in_group) )
                                  : NO_INTERCEPTORS;
}

void Replay::ReplayEngineDLL::InterceptorRegistry::publish_table()
{
    std::unique_ptr<Table> table_ptr(new Table() );

    for (const auto& entry : m_entry_vec)
    {
        for (const auto& group : entry.group_vec)
        {
            auto& interceptor_ptr_vec = table_ptr->at(static_cast<size_t>(group) );

            /* An interceptor that names a group twice is called once. */
            if (std::find(interceptor_ptr_vec.begin(),
                          interceptor_ptr_vec.end  (),
                          entry.interceptor_ptr) == interceptor_ptr_vec.end() )
            {
                interceptor_ptr_vec.push_back(entry.interceptor_ptr);
            }
        }
    }

    m_table_ptr_deque.push_back(std::move(table_ptr) );

    m_table_ptr = m_table_ptr_deque.back().get();
}

void Replay::ReplayEngineDLL::InterceptorRegistry::remove(ICallInterceptor* in_interceptor_ptr)
{
    std::lock_guard<std::mutex> lock(m_mutex);

    const auto is_interceptor_func = [in_interceptor_ptr](const Entry& in_entry)
    {
        return (in_entry.interceptor_ptr == in_interceptor_ptr);
    };

    m_entry_vec.erase(std::remove_if(m_entry_vec.begin(),
                                     m_entry_vec.end  (),
                                     is_interceptor_func),
                      m_entry_vec.end() );

    publish_table();
}
