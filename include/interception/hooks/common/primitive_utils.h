/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the hooks of Direct3D 7 and 8 need to know about the primitives that are drawn.
 */
#ifndef HOOKS_COMMON_PRIMITIVE_UTILS_H
#define HOOKS_COMMON_PRIMITIVE_UTILS_H

#include "interception/hooks/common/types.h"

#include <cstdint>

namespace Interception
{
    namespace Hooks
    {
        namespace Common
        {
            /* The number of vertices that draw the given number of primitives; 0 for a type which is not known. */
            uint32_t get_n_vertices(const PrimitiveType& in_primitive_type,
                                    const uint32_t&      in_primitive_count);
        }
    }
}

#endif /* HOOKS_COMMON_PRIMITIVE_UTILS_H */
