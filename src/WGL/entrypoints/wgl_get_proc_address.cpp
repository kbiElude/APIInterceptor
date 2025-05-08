/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "apitracer_config.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/WGL_ARB_create_context/wgl_create_context_attribs_arb.h"
#include "WGL/entrypoints/WGL_ARB_extensions_string/wgl_get_extensions_string_arb.h"
#include "WGL/entrypoints/WGL_EXT_swap_control/wgl_get_swap_interval_ext.h"
#include "WGL/entrypoints/WGL_EXT_swap_control/wgl_swap_interval_ext.h"
#include "WGL/entrypoints/wgl_get_proc_address.h"
#include <unordered_map>

#include "OpenGL/interceptors.h"

PROC WINAPI WGL::get_proc_address(LPCSTR in_name)
{
    AI_TRACE("wglGetProcAddress(in_name=[%s])",
             in_name);

    const auto opengl_func_ptrs = OpenGL::get_func_name_to_func_ptr_map();
    PROC       result           = nullptr;

    static const std::unordered_map<std::string, void*> wgl_func_ptrs =
    {
        /* WGL_ARB_create_context */
        {"wglCreateContextAttribsARB", WGL::create_context_attribs_arb},

        /* WGL_ARB_extensions_string */
        {"wglGetExtensionsStringARB", WGL::get_extensions_string_arb},

        /* WGL_EXT_swap_control */
        {"wglGetSwapIntervalEXT", WGL::get_swap_interval_ext},
        {"wglSwapIntervalEXT",    WGL::swap_interval_ext},
    };

    const std::unordered_map<std::string, void*> func_ptr_data[] =
    {
        opengl_func_ptrs,
        wgl_func_ptrs,
    };

    for (const auto& current_func_map : func_ptr_data)
    {
        auto iterator = current_func_map.find(in_name);

        if (iterator != current_func_map.end() )
        {
            result = reinterpret_cast<PROC>(iterator->second);

            break;
        }
    }

    WGL::g_cached_create_context_attribs_arb_func_ptr = reinterpret_cast<PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("wglCreateContextAttribsARB");
    WGL::g_cached_get_extensions_string_arb_func_ptr  = reinterpret_cast<PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("wglGetExtensionsStringARB");
    WGL::g_cached_get_swap_interval_ext_func_ptr      = reinterpret_cast<PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("wglGetSwapIntervalEXT");
    WGL::g_cached_swap_interval_ext_func_ptr          = reinterpret_cast<PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)("wglSwapIntervalEXT");

    if (result == nullptr)
    {
        AI_WARN("[!] Application called wglGetProcAddress() for an unsupported entrypoint [%s].",
                in_name);

        result = reinterpret_cast<PFNWGLGETPROCADDRESSPROC>(g_cached_get_proc_address_func_ptr)(in_name);
    }

    return result;
}
