/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_push_client_attrib.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPushClientAttrib(GLbitfield mask)
{
    AI_TRACE("glPushClientAttrib(mask=[%d])",
             mask);

    reinterpret_cast<PFNGLPUSHCLIENTATTRIBPROC>(OpenGL::g_cached_gl_push_client_attrib)(mask);
}