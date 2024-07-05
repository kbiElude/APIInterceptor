/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "Khronos/GL/glcorearb.h"
#include "Khronos/GL/wglext.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_create_layer_context.h"

HGLRC WINAPI WGL::create_layer_context(HDC in_hdc,
                                       int in_layer_plane_index)
{
    AI_TRACE("wglCreateLayerContext(in_hdc=[%p] in_layer_plane_index=[%d])",
               in_hdc,
               in_layer_plane_index);

    return reinterpret_cast<PFNWGLCREATELAYERCONTEXTPROC>(WGL::g_cached_create_layer_context_func_ptr)(in_hdc,
                                                                                                       in_layer_plane_index);
}
