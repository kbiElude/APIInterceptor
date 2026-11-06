/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the hooks of Direct3D 7 and 8 need to know about the primitives that are drawn.
 */
#ifndef HOOKS_COMMON_PRIMITIVE_UTILS_H
#define HOOKS_COMMON_PRIMITIVE_UTILS_H

#include <cstdint>

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            /* The values of D3DPRIMITIVETYPE, which are the same in Direct3D 7 and 8. */
            enum class PrimitiveType : uint32_t
            {
                POINT_LIST     = 1,
                LINE_LIST      = 2,
                LINE_STRIP     = 3,
                TRIANGLE_LIST  = 4,
                TRIANGLE_STRIP = 5,
                TRIANGLE_FAN   = 6
            };

            /* The number of vertices that draw the given number of primitives; 0 for a type which is not known. */
            uint32_t get_n_vertices(const PrimitiveType& in_primitive_type,
                                    const uint32_t&      in_primitive_count);
        }
    }
}

#endif /* HOOKS_COMMON_PRIMITIVE_UTILS_H */
