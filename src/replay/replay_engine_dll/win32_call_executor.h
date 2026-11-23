/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_WIN32_CALL_EXECUTOR_H
#define REPLAYENGINEDLL_WIN32_CALL_EXECUTOR_H

#include "common/api_function_argument.h"
#include "i_call_executor.h"
#include "object_remapper.h"
#include "replay/replay_engine_dll/types.h"
#include <functional>
#include <map>
#include <set>
#include <string>
#include <Windows.h>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* Replays the windowing calls (USER32, GDI32) and the WGL ones, on the replay thread. The windows are created from
         * scratch: the window classes the app registered are not part of the dump, so a class of the same name is
         * registered here. Calls which only ask something (e.g. GetPixelFormat), or which the driver made on its own
         * (e.g. GetDC of no window), are not replayed: the driver makes them again.
         */
        class Win32CallExecutor : public ICallExecutor
        {
        public:
            /* Called, from the replay thread, when the user has asked to close one of the windows of the replay. */
            typedef std::function<void()> WindowClosedFunc;

            /* Called, from the replay thread, when the replay has put one of its windows in place. */
            typedef std::function<void(const WindowPlacement&)> WindowPlacedFunc;

            Win32CallExecutor(ObjectRemapper*         in_remapper_ptr,
                              const WindowClosedFunc& in_window_closed_func,
                              const WindowPlacedFunc& in_window_placed_func);
            ~Win32CallExecutor();

            bool        execute         (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                         const IChunkSource&                          in_chunk_source,
                                         std::string*                                 out_error_ptr) override;
            CallSupport get_call_support(const APIInterceptor::APIFunction&           in_function) const override;

            /* The swap of the buffers of a window is after the executions of a frame, as the present of Direct3D is: what the frame drew is read from the
             * back buffer before it, and what a swap leaves in the back buffer is the driver's.
             */
            ExecutionClass get_execution_class(const Capture::APIDumpLoader::DumpedAPICall& in_call) const override;

            void on_frame_presented ()                           override;
            void on_idle            ()                           override;
            void reset              ()                           override;
            void set_windows_visible(const bool& in_are_visible) override;
            void shutdown           ()                           override;

        private:
            /* What makes a window of the app the one to use again after a reset. */
            struct WindowSignature
            {
                std::wstring class_name;
                DWORD        ex_style = 0;
                int          height   = 0;
                DWORD        style    = 0;
                std::wstring title;
                int          width    = 0;
            };

            typedef bool (Win32CallExecutor::*HandlerFuncPtr)(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                              const IChunkSource&                          in_chunk_source,
                                                              std::string*                                 out_error_ptr);

            bool  create_window_ex             (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                const bool&                                  in_is_wide,
                                                std::string*                                 out_error_ptr);
            void  destroy_parked_windows       ();
            /* How much larger the outer size of a window must be so that its area for drawing is as large as the app's frame gave it: the replay makes
             * its windows with a thinner frame (see make_non_scalable()). in_app_style is the style the app made the window with.
             */
            static void get_frame_growth       (const DWORD&                                 in_ex_style,
                                                const DWORD&                                 in_app_style,
                                                const DWORD&                                 in_replay_style,
                                                int*                                         out_height_ptr,
                                                int*                                         out_width_ptr);
            /* How large the frame of a window with this style is at this DPI: what its outer size has more than the area for drawing. */
            static void get_frame_size         (const DWORD&                                 in_ex_style,
                                                const DWORD&                                 in_style,
                                                const UINT&                                  in_dpi,
                                                int*                                         out_height_ptr,
                                                int*                                         out_width_ptr);
            bool  get_live_handle              (const ObjectKind&                            in_kind,
                                                const APIInterceptor::APIFunctionArgument&   in_argument,
                                                void**                                       out_live_handle_ptr,
                                                std::string*                                 out_error_ptr) const;
            void* get_wgl_function_ptr         (const HDC&                                   in_hdc,
                                                const char*                                  in_name_ptr) const;
            /* True for a window that has a title bar and is not a child: the one whose size takes its frame into account. */
            static bool has_own_frame          (const DWORD&                                 in_style);
            void  make_non_scalable            (const DWORD&                                 in_ex_style,
                                                DWORD*                                       inout_style_ptr,
                                                int*                                         inout_width_ptr,
                                                int*                                         inout_height_ptr);
            bool  on_copy_context              (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_create_context            (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_create_context_attribs_arb(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_create_layer_context      (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_create_window_ex_a        (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_create_window_ex_w        (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_delete_context            (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_get_dc                    (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_ignored_call              (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_make_current              (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_move_window               (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_release_dc                (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_set_pixel_format          (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_set_window_pos            (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_share_lists               (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_swap_buffers              (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_swap_interval_ext         (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            bool  on_swap_layer_buffers        (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                const IChunkSource&                          in_chunk_source,
                                                std::string*                                 out_error_ptr);
            /* Makes the release of the context that on_make_current() put off. */
            void  flush_release                ();
            void  place_window                 (const HWND&                                  in_window);
            void  pump_messages                ();
            bool  register_window_class        (const std::wstring&                          in_name);
            /* Gives the window the area for drawing that the dump says the program's window had after the call: the outer size is that area plus the frame the
             * replay's window has (the frame of the program depends on the system and on its DPI-awareness, so it is not worked out from the outer size). The
             * window is put in view again.
             */
            void  resize_window                (const HWND&                                  in_live_window,
                                                const int&                                   in_client_width,
                                                const int&                                   in_client_height);
            bool  take_parked_window           (const WindowSignature&                       in_signature,
                                                HWND*                                        out_window_ptr);


            static std::wstring     get_wide_string(const Capture::APIDumpLoader::DataChunk& in_chunk,
                                                    const bool&                              in_is_wide);
            static LRESULT CALLBACK window_proc    (HWND                                     in_hwnd,
                                                    UINT                                     in_message,
                                                    WPARAM                                   in_wparam,
                                                    LPARAM                                   in_lparam);


            bool                                                  m_are_windows_visible;
            std::set<HGLRC>                                       m_context_set;
            HDC                                                   m_current_hdc;      /* what the driver has current, as far as the executor made it so */
            HGLRC                                                 m_current_rc;
            std::map<APIInterceptor::APIFunction, HandlerFuncPtr> m_handler_func_ptr_map;
            bool                                                  m_has_last_placement;
            bool                                                  m_is_release_pending; /* wglMakeCurrent(0, 0) is not made until another call needs it; a context that is made current again at once is never released */
            WindowPlacement                                       m_last_placement;
            std::map<HWND, WindowSignature>                       m_parked_window_map;
            std::set<std::wstring>                                m_registered_class_name_set;
            ObjectRemapper*                                       m_remapper_ptr;
            WindowClosedFunc                                      m_window_closed_func;
            WindowPlacedFunc                                      m_window_placed_func;
            std::map<HWND, WindowSignature>                       m_window_signature_map;
        };
    }
}

#endif /* REPLAYENGINEDLL_WIN32_CALL_EXECUTOR_H */
