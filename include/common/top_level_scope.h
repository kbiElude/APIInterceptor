/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_TOP_LEVEL_SCOPE_H
#define COMMON_TOP_LEVEL_SCOPE_H

#include "callbacks.h"

namespace APIInterceptor
{
    /* The intercepted calls that the thread makes while the scope lives are top-level ones, however deep in an intercepted call the thread
     * is. For a callback of the application, which a driver calls from within an intercepted call (an enumeration): what the application
     * does in it is the application's, unlike the calls that the driver makes itself.
     */
    class TopLevelScope
    {
    public:
        TopLevelScope()
            :m_depth(APIInterceptor::suspend_api_call_nesting() )
        {
            /* Stub */
        }

        ~TopLevelScope()
        {
            APIInterceptor::resume_api_call_nesting(m_depth);
        }

        TopLevelScope           (const TopLevelScope&) = delete;
        TopLevelScope& operator=(const TopLevelScope&) = delete;

    private:
        const uint32_t m_depth;
    };
}

#endif /* COMMON_TOP_LEVEL_SCOPE_H */
