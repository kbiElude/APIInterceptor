/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_TRACKER_H
#define COMMON_TRACKER_H

#include "callbacks.h"

namespace APIInterceptor
{
    class Tracker
    {
    public:
        /* Public funcs */
        Tracker()
            :m_is_top_level(APIInterceptor::on_api_call_interception_started() )
        {
            /* Stub */
        }

        ~Tracker()
        {
            APIInterceptor::on_api_call_interception_finished();
        }

        const bool& is_top_level_api_call()
        {
            return m_is_top_level;
        }
    private:
        /* Private vars */
        const bool m_is_top_level;
    };
}

#endif /* COMMON_TRACKER_H */