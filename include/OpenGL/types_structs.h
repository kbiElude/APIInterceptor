/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_STRUCTS_H
#define AI_TYPES_STRUCTS_H

#include "OpenGL/types_interfaces.h"

namespace OpenGL
{
    struct DispatchTable
    {
        Context* bound_context_ptr;

        DispatchTable();
    };
}

#endif /* AI_TYPES_STRUCTS_H */