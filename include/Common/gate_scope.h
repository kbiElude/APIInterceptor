/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_GATE_SCOPE_H
#define COMMON_GATE_SCOPE_H

#include "callbacks.h"

namespace APIInterceptor
{
    /* Counts the thread as being inside an intercepted API call, so that the dumper does not cut a segment in the
     * middle of the call (see try_quiesce_api_calls()). A Tracker does that, too; this one does nothing else. In
     * particular, it does not tell the call from the calls it makes: use it in the entrypoints that record calls made
     * from within other intercepted calls, e.g. by drivers.
     */
    class GateScope
    {
    public:
        GateScope()
        {
            APIInterceptor::on_gate_scope_entered();
        }

        ~GateScope()
        {
            APIInterceptor::on_gate_scope_left();
        }

        GateScope(const GateScope&)            = delete;
        GateScope& operator=(const GateScope&) = delete;
    };
}

#endif /* COMMON_GATE_SCOPE_H */
