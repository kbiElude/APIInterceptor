/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/logger.h"
#include "OpenGL/entrypoints/GL3.1/gl_draw_elements_instanced.h"
#include "OpenGL/globals.h"
#include "OpenGLUtils/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiDrawElementsInstanced(GLenum      mode,
                                                 GLsizei     count,
                                                 GLenum      type,
                                                 const void* indices,
                                                 GLsizei     instancecount)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glDrawElementsInstanced(mode=[%s] count=[%d] type=[%s] indices=[%p] instancecount=[%d])",
             OpenGL::Utils::get_raw_string_for_gl_enum(mode),
             static_cast<int32_t>(count),
             OpenGL::Utils::get_raw_string_for_gl_enum(type),
             indices,
             static_cast<int32_t>(instancecount) );

    reinterpret_cast<PFNGLDRAWELEMENTSINSTANCEDPROC>(OpenGL::g_cached_gl_draw_elements_instanced)(mode,
                                                                                                  count,
                                                                                                  type,
                                                                                                  indices,
                                                                                                  instancecount);
}