/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_ENUMS_H
#define AI_TYPES_ENUMS_H

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

namespace OpenGL
{
    enum class BitfieldType
    {
        Blit_Mask,           // glBlitFramebuffer()
        Buffer_Access_Mask,  // glMapBufferRange()
        Clear_Buffer_Mask,   // glClear()
        Sync_Condition_Mask, // glFenceSync()
        Wait_Sync_Mask,      // glClientWaitSync()
    };

    enum class BufferBindingTarget
    {
        ARRAY_BUFFER,
        ELEMENT_ARRAY_BUFFER,

        COUNT
    };

    enum class BufferMappingAccess
    {
        READ_ONLY,
        READ_WRITE,
        WRITE_ONLY,

        UNKNOWN
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
};

#endif /* AI_TYPES_ENUMS_H */