/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_interleaved_arrays.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiInterleavedArrays(GLenum        format,
                                             GLsizei       stride,
                                             const GLvoid* pointer)
{
    AI_TRACE("glInterleavedArrays(format=[%s], stride=[%d], pointer=[%p])",
             OpenGL::Utils::get_raw_string_for_gl_enum(format),
             stride,
             pointer);

    reinterpret_cast<PFNGLINTERLEAVEDARRAYSPROC>(OpenGL::g_cached_gl_interleaved_arrays)(format,
                                                                                         stride,
                                                                                         pointer);
}