/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_ENUMS_H
#define AI_TYPES_ENUMS_H

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
};

#endif /* AI_TYPES_ENUMS_H */