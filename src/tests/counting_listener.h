/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * A listener for the tests of ListenerList.
 */
#ifndef TESTS_COUNTING_LISTENER_H
#define TESTS_COUNTING_LISTENER_H

namespace Tests
{
    /* Counts what it is told: a listener for the tests of ListenerList. */
    struct CountingListener
    {
        int n_calls = 0;
    };
}

#endif /* TESTS_COUNTING_LISTENER_H */
