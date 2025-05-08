/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.0/gl_generate_mipmap.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiGenerateMipmap(GLenum target)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glGenerateMipmap(target=[%s])",
             OpenGL::Utils::get_raw_string_for_gl_enum(target) );

    reinterpret_cast<PFNGLGENERATEMIPMAPPROC>(OpenGL::g_cached_gl_generate_mipmap)(target);
}