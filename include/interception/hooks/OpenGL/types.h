/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_H
#define AI_TYPES_H

#include "Khronos/GL/glcorearb.h"
#undef GL_VERSION_1_3  /* allow glext.h to define its compat-profile 1.3 typedefs (MultiTexCoord, LoadTransposeMatrix, etc.) */
#undef GL_VERSION_1_4  /* allow glext.h to define its compat-profile 1.4 typedefs (FogCoord, SecondaryColor, WindowPos) */
#include "Khronos/GL/glext.h"
#include <cstdint>
#include <chrono>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#define AI_APIENTRY KHRONOS_APIENTRY

#include "common/types.h"
#include "interception/hooks/OpenGL/types_enums.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            /* Forward declarations */
            class  Context;
            struct DispatchTable;
        }
    }
}

#include "interception/hooks/OpenGL/types_typedefs.h"
#include "interception/hooks/OpenGL/types_structs.h"
#include "interception/hooks/OpenGL/types_interfaces.h"

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            typedef std::unique_ptr<ContextState> ContextStateUniquePtr;
        }
    }
}

#endif /* AI_TYPES_H */