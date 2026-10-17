/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef WGL_UTILS_H
#define WGL_UTILS_H

#include <cstdint>

namespace WGL
{
    namespace Utils
    {
        /* Number of ints in an attribute list of wglCreateContextAttribsARB(): the name and value pairs, and the zero
         * which ends the list. A null list has none.
         */
        uint32_t get_n_context_attrib_list_ints(const int* in_attrib_list_ptr);
    }
}

#endif /* WGL_UTILS_H */
