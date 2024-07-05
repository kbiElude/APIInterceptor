/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_H
#define AI_TYPES_H

#include "Khronos/GL/glcorearb.h"
#include <cstdint>
#include <chrono>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#define AI_APIENTRY KHRONOS_APIENTRY

#include "Common/types.h"
#include "OpenGL/types_enums.h"

namespace OpenGL
{
    /* Forward declarations */
    class  Context;
    struct DispatchTable;
}

#include "OpenGL/types_typedefs.h"
#include "OpenGL/types_structs.h"
#include "OpenGL/types_interfaces.h"

#endif /* AI_TYPES_H */