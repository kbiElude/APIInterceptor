/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef APIDUMPPLAYER_CONTROL_WINDOW_H
#define APIDUMPPLAYER_CONTROL_WINDOW_H

#include "Replay/ReplayEngineDLL/i_playback_controller.h"
#include "Replay/ReplayEngineDLL/i_replay_observer.h"
#include <mutex>
#include <string>
#include <Windows.h>

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct IDXGISwapChain;

namespace APIDumpPlayer
{
    /* The window with the playback controls: play / pause, reset, and what has been replayed so far. It is drawn with
     * ImGui over a Direct3D 11 device of its own, and lives on the thread which runs it, apart from the windows of the
     * replay, so that what the replay does to its API state is not touched.
     */
    class ControlWindow : public APIDumpReplayer::IReplayObserver
    {
    public:
        ControlWindow(APIDumpReplayer::IPlaybackController* in_controller_ptr,
                      const std::string&                    in_title);
        ~ControlWindow();

        /* Creates the window and the device. Returns false, with the reason, if that fails. */
        bool create(std::string* out_error_ptr);

        /* Shows the window and returns when the user closes it. */
        void run();

        void on_error          (const std::string&                    in_message) override;
        void on_frame_presented(const uint32_t&                       in_n_frame) override;
        void on_state_changed  (const APIDumpReplayer::PlaybackState& in_old_state,
                                const APIDumpReplayer::PlaybackState& in_new_state) override;

        /* The window which the replay puts in place decides where this one goes: below it, in the middle. Any thread. */
        void on_window_placed(const APIDumpReplayer::WindowPlacement& in_placement) override;

        /* Process-wide; before any window of the replay is made, so that sizes are in pixels. */
        static void enable_dpi_awareness();

    private:
        /* The placement of the window of the replay. Lock order: no other lock is taken while it is held. */
        struct ReplayWindow
        {
            bool                              is_known = false;
            std::mutex                        mutex;
            APIDumpReplayer::WindowPlacement  placement;
        };

        bool    create_device            ();
        void    create_render_target     ();
        void    destroy_render_target    ();
        void    draw_controls            ();
        void    fit_to_content           ();
        LRESULT handle_message           (const HWND&   in_window,
                                          const UINT&   in_message,
                                          const WPARAM& in_wparam,
                                          const LPARAM& in_lparam);
        void    place_below_replay_window();
        void    render_frame             ();
        void    resize                   (const UINT&   in_width,
                                          const UINT&   in_height);

        static LRESULT CALLBACK window_proc(HWND   in_window,
                                            UINT   in_message,
                                            WPARAM in_wparam,
                                            LPARAM in_lparam);

        int                                   m_content_height;
        int                                   m_content_width;
        APIDumpReplayer::IPlaybackController* m_controller_ptr;
        ID3D11DeviceContext*                  m_device_context_ptr;
        ID3D11Device*                         m_device_ptr;
        HWND                                  m_hwnd;
        bool                                  m_is_imgui_ready;
        bool                                  m_is_placed;
        APIDumpReplayer::WindowPlacement      m_last_placement;
        ID3D11RenderTargetView*               m_render_target_view_ptr;
        ReplayWindow                          m_replay_window;
        IDXGISwapChain*                       m_swap_chain_ptr;
        std::string                           m_title;
    };
}

#endif /* APIDUMPPLAYER_CONTROL_WINDOW_H */
