/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/WGL/globals.h"

void* Interception::Hooks::WGL::g_cached_copy_context_func_ptr         = wglCopyContext;
void* Interception::Hooks::WGL::g_cached_create_context_func_ptr       = wglCreateContext;
void* Interception::Hooks::WGL::g_cached_create_layer_context_func_ptr = wglCreateLayerContext;
void* Interception::Hooks::WGL::g_cached_delete_context_func_ptr       = wglDeleteContext;
void* Interception::Hooks::WGL::g_cached_get_current_context_func_ptr  = wglGetCurrentContext;
void* Interception::Hooks::WGL::g_cached_get_current_dc_func_ptr       = wglGetCurrentDC;
void* Interception::Hooks::WGL::g_cached_get_proc_address_func_ptr     = wglGetProcAddress;
void* Interception::Hooks::WGL::g_cached_make_current_func_ptr         = wglMakeCurrent;
void* Interception::Hooks::WGL::g_cached_share_lists_func_ptr          = wglShareLists;
void* Interception::Hooks::WGL::g_cached_swap_layer_buffers_func_ptr   = wglSwapLayerBuffers;

void* Interception::Hooks::WGL::g_cached_create_context_attribs_arb_func_ptr = nullptr;
void* Interception::Hooks::WGL::g_cached_get_extensions_string_arb_func_ptr  = nullptr;
void* Interception::Hooks::WGL::g_cached_get_swap_interval_ext_func_ptr      = nullptr;
void* Interception::Hooks::WGL::g_cached_swap_interval_ext_func_ptr          = nullptr;