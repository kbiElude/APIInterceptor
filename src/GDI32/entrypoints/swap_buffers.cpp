/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/globals.h"
#include "Common/logger.h"
#include "GDI32/entrypoints/swap_buffers.h"
#include "GDI32/globals.h"

BOOL WINAPI GDI32::swap_buffers(HDC in_hdc)
{
    AI_TRACE("SwapBuffers(in_hdc=[%p])",
             in_hdc);

    APIInterceptor::g_logger_ptr->on_frame_presented();

    return reinterpret_cast<GDI32::PFNSWAPBUFFERSPROC>(GDI32::g_cached_swap_buffers_func_ptr)(in_hdc);
}