/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_push_attrib.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPushAttrib(GLbitfield mask)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glPushAttrib(mask=[%d])",
             mask);

    reinterpret_cast<PFNGLPUSHATTRIBPROC>(OpenGL::g_cached_gl_push_attrib)(mask);
}