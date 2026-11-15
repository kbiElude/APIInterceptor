/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_API_CALL_SCOPE_H
#define COMMON_API_CALL_SCOPE_H

#include "callbacks.h"

namespace APIInterceptor
{
    /* Counts the thread as being inside an intercepted API call while it lives, and says whether this is the outermost such call
     * (is_top_level_api_call()): only that one is recorded, not the calls that a driver makes from within it.
     */
    class APICallScope
    {
    public:
        /* Public funcs */
        APICallScope()
            :m_is_top_level(APIInterceptor::on_api_call_interception_started() )
        {
            /* Stub */
        }

        ~APICallScope()
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

#endif /* COMMON_API_CALL_SCOPE_H */