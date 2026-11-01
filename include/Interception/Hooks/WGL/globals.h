/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef WGL_GLOBALS_H
#define WGL_GLOBALS_H

#include <windows.h>
#include "Common/globals.h"

namespace WGL
{
    /* Forward declarations */
    typedef BOOL  (WINAPI* PFNWGLCOPYCONTEXTPROC)            (HGLRC, HGLRC, UINT);
    typedef HGLRC (WINAPI* PFNWGLCREATECONTEXTPROC)          (HDC);
    typedef HGLRC (WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int*);
    typedef HGLRC (WINAPI* PFNWGLCREATELAYERCONTEXTPROC)     (HDC, int);
    typedef BOOL  (WINAPI* PFNWGLDELETECONTEXTPROC)          (HGLRC);
    typedef HGLRC (WINAPI* PFNWGLGETCURRENTCONTEXTPROC)      ();
    typedef HDC   (WINAPI* PFNWGLGETCURRENTDCPROC)           ();
    typedef PROC  (WINAPI* PFNWGLGETPROCADDRESSPROC)         (LPCSTR);
    typedef BOOL  (WINAPI* PFNWGLMAKECURRENTPROC)            (HDC, HGLRC);
    typedef BOOL  (WINAPI* PFNWGLSHARELISTSPROC)             (HGLRC, HGLRC);
    typedef BOOL  (WINAPI* PFNWGLSWAPLAYERBUFFERSPROC)       (HDC, UINT);

    typedef const char* (WINAPI* PFNWGLGETEXTENSIONSSTRINGARGPROC)(HDC);
    typedef int         (WINAPI* PFNWGLGETSWAPINTERVALEXTPROC)    ();
    typedef BOOL        (WINAPI* PFNWGLSWAPINTERVALEXTPROC)       (int);

    extern void* g_cached_copy_context_func_ptr;
    extern void* g_cached_create_context_attribs_arb_func_ptr;
    extern void* g_cached_create_context_func_ptr;
    extern void* g_cached_create_layer_context_func_ptr;
    extern void* g_cached_delete_context_func_ptr;
    extern void* g_cached_get_current_context_func_ptr;
    extern void* g_cached_get_current_dc_func_ptr;
    extern void* g_cached_get_proc_address_func_ptr;
    extern void* g_cached_make_current_func_ptr;
    extern void* g_cached_share_lists_func_ptr;
    extern void* g_cached_swap_layer_buffers_func_ptr;

    /* WGL_ARB_extensions_string */
    extern void* g_cached_get_extensions_string_arb_func_ptr;

    /* WGL_EXT_swap_control */
    extern void* g_cached_get_swap_interval_ext_func_ptr;
    extern void* g_cached_swap_interval_ext_func_ptr; 
}

#endif /* WGL_GLOBALS_H */