/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "WGL/entrypoints/WGL_ARB_create_context/wgl_create_context_attribs_arb.h"
#include "WGL/entrypoints/wgl_copy_context.h"
#include "WGL/entrypoints/wgl_create_context.h"
#include "WGL/entrypoints/wgl_create_layer_context.h"
#include "WGL/entrypoints/wgl_delete_context.h"
#include "WGL/entrypoints/wgl_get_current_context.h"
#include "WGL/entrypoints/wgl_get_current_dc.h"
#include "WGL/entrypoints/wgl_get_proc_address.h"
#include "WGL/entrypoints/wgl_make_current.h"
#include "WGL/entrypoints/wgl_share_lists.h"
#include "WGL/entrypoints/wgl_swap_layer_buffers.h"
#include "WGL/globals.h"
#include "WGL/interceptors.h"

std::vector<APIInterceptor::FunctionInterceptor> WGL::get_function_interceptors()
{
    return std::vector<APIInterceptor::FunctionInterceptor>
    {
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_copy_context_func_ptr,         WGL::copy_context),
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_create_context_func_ptr,       WGL::create_context),
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_create_layer_context_func_ptr, WGL::create_layer_context),
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_delete_context_func_ptr,       WGL::delete_context),
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_get_current_context_func_ptr,  WGL::get_current_context),
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_get_current_dc_func_ptr,       WGL::get_current_dc),
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_get_proc_address_func_ptr,     WGL::get_proc_address),
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_make_current_func_ptr,         WGL::make_current),
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_share_lists_func_ptr,          WGL::share_lists),
        APIInterceptor::FunctionInterceptor(&(PVOID&) WGL::g_cached_swap_layer_buffers_func_ptr,   WGL::swap_layer_buffers),
    };
}