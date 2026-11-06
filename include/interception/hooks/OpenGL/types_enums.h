/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_ENUMS_H
#define AI_TYPES_ENUMS_H

#include <cstdint>

/* Compatibility-profile GL 1.4 point-parameter tokens removed from the core profile.
 * glcorearb.h and glext.h cannot be included together, so these are defined manually
 * using their canonical values from the OpenGL registry. */
#ifndef GL_POINT_SIZE_MIN
    #define GL_POINT_SIZE_MIN             0x8126
#endif
#ifndef GL_POINT_SIZE_MAX
    #define GL_POINT_SIZE_MAX             0x8127
#endif
#ifndef GL_POINT_DISTANCE_ATTENUATION
    #define GL_POINT_DISTANCE_ATTENUATION 0x8129
#endif

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            enum class BitfieldType
            {
                BLIT_MASK,           // glBlitFramebuffer()
                BUFFER_ACCESS_MASK,  // glMapBufferRange()
                CLEAR_BUFFER_MASK,   // glClear()
                SYNC_CONDITION_MASK, // glFenceSync()
                WAIT_SYNC_MASK,      // glClientWaitSync()
            };

            enum class BufferBindingTarget
            {
                ARRAY_BUFFER,
                ATOMIC_COUNTER_BUFFER,
                COPY_READ_BUFFER,
                COPY_WRITE_BUFFER,
                DISPATCH_INDIRECT_BUFFER,
                DRAW_INDIRECT_BUFFER,
                ELEMENT_ARRAY_BUFFER,
                PIXEL_PACK_BUFFER,
                PIXEL_UNPACK_BUFFER,
                QUERY_BUFFER,
                SHADER_STORAGE_BUFFER,
                TEXTURE_BUFFER,
                TRANSFORM_FEEDBACK_BUFFER,
                UNIFORM_BUFFER,

                COUNT
            };

            /* The values are stored in workload files (see ClientArrayManager). */
            enum class ClientArrayKind : uint32_t
            {
                COLOR           = 0,
                EDGE_FLAG       = 1,
                FOG_COORD       = 2,
                GENERIC         = 3,
                INDEX           = 4,
                NORMAL          = 5,
                SECONDARY_COLOR = 6,
                TEX_COORD       = 7,
                VERTEX          = 8,
            };

            enum class TextureBindingTarget
            {
                TEXTURE_1D,
                TEXTURE_1D_ARRAY,
                TEXTURE_2D,
                TEXTURE_2D_ARRAY,
                TEXTURE_3D,
                TEXTURE_BUFFER,
                TEXTURE_CUBE_MAP,
                TEXTURE_RECTANGLE,

                COUNT,
                UNKNOWN
            };
        }
    }
}

#endif /* AI_TYPES_ENUMS_H */