/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The call interceptors of an engine, by the API whose calls each wants (see ICallInterceptor::get_api_groups()).
 */
#ifndef REPLAYENGINEDLL_INTERCEPTOR_REGISTRY_H
#define REPLAYENGINEDLL_INTERCEPTOR_REGISTRY_H

#include "replay/replay_engine_dll/i_call_interceptor.h"
#include <array>
#include <atomic>
#include <deque>
#include <memory>
#include <mutex>
#include <vector>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        class InterceptorRegistry
        {
        public:
            InterceptorRegistry();

            /* For the APIs the interceptor names, or all of them. Any thread. */
            void add(ICallInterceptor* in_interceptor_ptr);

            /* The interceptors of the API, in the order they were added. Any thread, without a lock; the list stays valid after a change. */
            const std::vector<ICallInterceptor*>& get_interceptor_ptr_vec(const Capture::APIDumpLoader::APIGroup& in_group) const;

            /* Any thread. */
            void remove(ICallInterceptor* in_interceptor_ptr);

        private:
            struct Entry
            {
                std::vector<Capture::APIDumpLoader::APIGroup> group_vec;
                ICallInterceptor*                             interceptor_ptr = nullptr;
            };

            typedef std::array<std::vector<ICallInterceptor*>, static_cast<size_t>(Capture::APIDumpLoader::APIGroup::UNKNOWN) + 1> Table;

            /* Makes the table of the entries and makes it the one that is read. The caller holds the lock. */
            void publish_table();

            std::vector<Entry>                 m_entry_vec;
            std::mutex                         m_mutex;
            std::atomic<const Table*>          m_table_ptr;
            std::deque<std::unique_ptr<Table> > m_table_ptr_deque; /* a replaced table is kept: the replay thread may be reading it */
        };
    }
}

#endif /* REPLAYENGINEDLL_INTERCEPTOR_REGISTRY_H */
