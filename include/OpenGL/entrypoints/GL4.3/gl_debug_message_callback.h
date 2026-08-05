/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_GL_DEBUG_MESSAGE_CALLBACK_H
#define AI_GL_DEBUG_MESSAGE_CALLBACK_H

#include "OpenGL/types.h"

namespace OpenGL
{
    void AI_APIENTRY aiDebugMessageCallback(GLDEBUGPROC callback, const void* userParam);
}

#endif /* AI_GL_DEBUG_MESSAGE_CALLBACK_H */
