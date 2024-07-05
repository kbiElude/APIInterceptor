/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_edge_flag.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiEdgeFlag(GLboolean flag)
{
    AI_TRACE("glEdgeFlag(flag=[%d])",
             static_cast<uint32_t>(flag) );

    reinterpret_cast<PFNGLEDGEFLAGPROC>(OpenGL::g_cached_gl_edge_flag)(flag);
}