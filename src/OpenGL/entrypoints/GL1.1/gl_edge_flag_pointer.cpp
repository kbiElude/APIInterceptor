/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_edge_flag_pointer.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEdgeFlagPointer(GLsizei       stride,
                                           const GLvoid* pointer)
{
    AI_TRACE("glEdgeFlagPointer(stride=[%d] pointer=[%p])",
             stride,
             pointer);

    reinterpret_cast<PFNGLEDGEFLAGPOINTERPROC>(OpenGL::g_cached_gl_edge_flag_pointer)(stride,
                                                                                      pointer);
}