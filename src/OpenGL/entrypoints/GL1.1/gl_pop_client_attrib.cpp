/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_pop_client_attrib.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiPopClientAttrib()
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glPopClientAttrib()");

    reinterpret_cast<PFNGLPOPCLIENTATTRIBPROC>(OpenGL::g_cached_gl_pop_client_attrib)();
}