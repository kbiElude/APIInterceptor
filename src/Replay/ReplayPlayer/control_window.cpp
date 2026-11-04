/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "control_window.h"
#include "state_names.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include <algorithm>
#include <cmath>
#include <d3d11.h>

/* Declared by the backend only inside a disabled block. */
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND   in_window,
                                                             UINT   in_message,
                                                             WPARAM in_wparam,
                                                             LPARAM in_lparam);

static constexpr const wchar_t* WINDOW_CLASS_NAME = L"ReplayPlayerControlWindow";

/* Posted by the replay thread: the window of the replay has been put in place. */
static constexpr UINT WM_PLACE_BELOW_REPLAY_WINDOW = WM_APP + 1;

Replay::ReplayPlayer::ControlWindow::ControlWindow(Replay::ReplayEngineDLL::IPlaybackController* in_controller_ptr,
                                                           const std::string&                    in_title)
    :m_content_height        (0),
     m_content_width         (0),
     m_controller_ptr        (in_controller_ptr),
     m_device_context_ptr    (nullptr),
     m_device_ptr            (nullptr),
     m_hwnd                  (nullptr),
     m_is_imgui_ready        (false),
     m_is_placed             (false),
     m_last_placement        (),
     m_render_target_view_ptr(nullptr),
     m_swap_chain_ptr        (nullptr),
     m_title                 (in_title)
{
    /* Stub */
}

Replay::ReplayPlayer::ControlWindow::~ControlWindow()
{
    if (m_is_imgui_ready)
    {
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();

        ImGui::DestroyContext();
    }

    destroy_render_target();

    if (m_swap_chain_ptr != nullptr)
    {
        m_swap_chain_ptr->Release();
    }

    if (m_device_context_ptr != nullptr)
    {
        m_device_context_ptr->Release();
    }

    if (m_device_ptr != nullptr)
    {
        m_device_ptr->Release();
    }

    if (m_hwnd != nullptr)
    {
        ::DestroyWindow(m_hwnd);
    }

    ::UnregisterClassW(WINDOW_CLASS_NAME,
                       ::GetModuleHandleW(nullptr) );
}

bool Replay::ReplayPlayer::ControlWindow::create(std::string* out_error_ptr)
{
    constexpr int   CLIENT_HEIGHT = 150;
    constexpr int   CLIENT_WIDTH  = 420;
    constexpr POINT ORIGIN        = {0, 0};

    RECT          client_rect   = {};
    const HMODULE module_handle = ::GetModuleHandleW(nullptr);
    bool          result        = false;
    float         scale         = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(ORIGIN,
                                                                                         MONITOR_DEFAULTTOPRIMARY) );
    WNDCLASSEXW   window_class  = {};
    const DWORD   window_style  = WS_CAPTION | WS_SYSMENU;

    client_rect.bottom = static_cast<LONG>(CLIENT_HEIGHT * scale);
    client_rect.right  = static_cast<LONG>(CLIENT_WIDTH  * scale);

    window_class.cbSize        = sizeof(window_class);
    window_class.hCursor       = ::LoadCursorA(nullptr,
                                               IDC_ARROW);
    window_class.hInstance     = module_handle;
    window_class.lpfnWndProc   = &ControlWindow::window_proc;
    window_class.lpszClassName = WINDOW_CLASS_NAME;

    if (::RegisterClassExW(&window_class) == 0)
    {
        *out_error_ptr = "The class of the control window cannot be registered.";

        goto end;
    }

    ::AdjustWindowRect(&client_rect,
                       window_style,
                       FALSE);

    /* The window stays above the windows of the replay, which are made by the replayed app, and can cover it. */
    m_hwnd = ::CreateWindowExW(WS_EX_TOPMOST,
                               WINDOW_CLASS_NAME,
                               nullptr, /* the title is set below */
                               window_style,
                               CW_USEDEFAULT,
                               CW_USEDEFAULT,
                               client_rect.right  - client_rect.left,
                               client_rect.bottom - client_rect.top,
                               nullptr,
                               nullptr,
                               module_handle,
                               this);

    if (m_hwnd == nullptr)
    {
        *out_error_ptr = "The control window cannot be created.";

        goto end;
    }

    ::SetWindowTextA(m_hwnd,
                     m_title.c_str() );

    if (create_device() == false)
    {
        *out_error_ptr = "The Direct3D 11 device of the control window cannot be created.";

        goto end;
    }

    create_render_target();

    ImGui::CreateContext();

    ImGui::GetIO().IniFilename = nullptr;

    ImGui::StyleColorsDark();

    /* The sizes and the text follow the DPI of the monitor. */
    ImGui::GetStyle().ScaleAllSizes(scale);

    ImGui::GetStyle().FontScaleDpi = scale;

    m_is_imgui_ready = true;

    if (ImGui_ImplWin32_Init(m_hwnd) == false)
    {
        *out_error_ptr = "ImGui cannot be set up for the control window.";

        goto end;
    }

    if (ImGui_ImplDX11_Init(m_device_ptr,
                            m_device_context_ptr) == false)
    {
        *out_error_ptr = "ImGui cannot be set up for the control window.";

        goto end;
    }

    result = true;

end:
    return result;
}

bool Replay::ReplayPlayer::ControlWindow::create_device()
{
    constexpr UINT N_BUFFERS = 2;

    D3D_FEATURE_LEVEL       feature_level         = D3D_FEATURE_LEVEL_10_0;
    const D3D_FEATURE_LEVEL feature_level_array[] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0};
    bool                    result                = false;
    DXGI_SWAP_CHAIN_DESC    swap_chain_desc       = {};

    swap_chain_desc.BufferCount       = N_BUFFERS;
    swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swap_chain_desc.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swap_chain_desc.OutputWindow      = m_hwnd;
    swap_chain_desc.SampleDesc.Count  = 1;
    swap_chain_desc.SwapEffect        = DXGI_SWAP_EFFECT_DISCARD;
    swap_chain_desc.Windowed          = TRUE;

    result = SUCCEEDED(::D3D11CreateDeviceAndSwapChain(nullptr, /* adapter */
                                                       D3D_DRIVER_TYPE_HARDWARE,
                                                       nullptr, /* software module */
                                                       0,       /* flags           */
                                                       feature_level_array,
                                                       static_cast<UINT>(sizeof(feature_level_array) / sizeof(feature_level_array[0]) ),
                                                       D3D11_SDK_VERSION,
                                                      &swap_chain_desc,
                                                      &m_swap_chain_ptr,
                                                      &m_device_ptr,
                                                      &feature_level,
                                                      &m_device_context_ptr) );

    return result;
}

void Replay::ReplayPlayer::ControlWindow::create_render_target()
{
    ID3D11Texture2D* back_buffer_ptr = nullptr;

    if (SUCCEEDED(m_swap_chain_ptr->GetBuffer(0,
                                              IID_PPV_ARGS(&back_buffer_ptr) )) )
    {
        m_device_ptr->CreateRenderTargetView(back_buffer_ptr,
                                             nullptr,
                                            &m_render_target_view_ptr);

        back_buffer_ptr->Release();
    }
}

void Replay::ReplayPlayer::ControlWindow::destroy_render_target()
{
    if (m_render_target_view_ptr != nullptr)
    {
        m_render_target_view_ptr->Release();

        m_render_target_view_ptr = nullptr;
    }
}

void Replay::ReplayPlayer::ControlWindow::draw_controls()
{
    constexpr float BUTTON_WIDTH_N_EMS = 6.0f;

    const float       button_width = BUTTON_WIDTH_N_EMS * ImGui::GetFontSize();
    const ImVec2      display_size = ImGui::GetIO().DisplaySize;
    float             max_bottom   = 0.0f;
    float             max_right    = 0.0f;
    const auto        status       = m_controller_ptr->get_status();
    const ImGuiStyle& style        = ImGui::GetStyle();
    const bool        is_ended     = (status.state == Replay::ReplayEngineDLL::PlaybackState::FAILED   ||
                                              status.state == Replay::ReplayEngineDLL::PlaybackState::FINISHED);
    const bool        is_playing   = (status.state == Replay::ReplayEngineDLL::PlaybackState::PLAYING);

    /* What the window has to hold: the corner of the last item of each kind, found while they are drawn. */
    const auto extend_func = [&]()
    {
        max_bottom = std::max<float>(max_bottom,
                                     ImGui::GetItemRectMax().y);
        max_right  = std::max<float>(max_right,
                                     ImGui::GetItemRectMax().x);
    };

    ImGui::SetNextWindowPos (ImVec2(0.0f,
                                    0.0f) );
    ImGui::SetNextWindowSize(display_size);

    ImGui::Begin("Controls",
                 nullptr,
                 ImGuiWindowFlags_NoCollapse      |
                 ImGuiWindowFlags_NoMove          |
                 ImGuiWindowFlags_NoResize        |
                 ImGuiWindowFlags_NoSavedSettings |
                 ImGuiWindowFlags_NoTitleBar);

    ImGui::Text("State: %s",
                StateNames::get_state_name_ptr(status.state) );

    extend_func();

    /* The number of the frame which was presented last; right after a reset, it is the first one: frame 0. */
    ImGui::Text("Frame: %u",
                (status.n_frames_presented > 0) ? status.n_frames_presented - 1
                                                : 0);

    extend_func();

    ImGui::Text("Calls: %llu",
                static_cast<unsigned long long>(status.n_calls_executed) );

    extend_func();

    ImGui::Separator();

    /* After the end, only a reset starts the replay again. */
    ImGui::BeginDisabled(is_ended);

    if (ImGui::Button((is_playing) ? "Pause"
                                   : "Play",
                      ImVec2(button_width,
                             0.0f) ))
    {
        if (is_playing)
        {
            m_controller_ptr->pause();
        }
        else
        {
            m_controller_ptr->play();
        }
    }

    ImGui::EndDisabled();

    extend_func();

    ImGui::SameLine();

    if (ImGui::Button("Reset",
                      ImVec2(button_width,
                             0.0f) ))
    {
        m_controller_ptr->reset();
    }

    extend_func();

    /* The message does not make the window wider than the buttons do. */
    if (status.state == Replay::ReplayEngineDLL::PlaybackState::FAILED)
    {
        ImGui::PushTextWrapPos(max_right);
        ImGui::TextColored(ImVec4(1.0f,
                                  0.4f,
                                  0.4f,
                                  1.0f),
                           "%s",
                           status.error_message.c_str() );
        ImGui::PopTextWrapPos();

        extend_func();
    }

    ImGui::End();

    m_content_height = static_cast<int>(std::ceil(max_bottom + style.WindowPadding.y) );
    m_content_width  = static_cast<int>(std::ceil(max_right  + style.WindowPadding.x) );
}

void Replay::ReplayPlayer::ControlWindow::enable_dpi_awareness()
{
    ImGui_ImplWin32_EnableDpiAwareness();
}

void Replay::ReplayPlayer::ControlWindow::fit_to_content()
{
    RECT client_rect = {};
    RECT outer_rect  = {};

    ::GetClientRect(m_hwnd,
                   &client_rect);

    if (m_content_height > 0 &&
        m_content_width  > 0 &&
        (client_rect.bottom != m_content_height ||
         client_rect.right  != m_content_width) )
    {
        outer_rect.bottom = m_content_height;
        outer_rect.right  = m_content_width;

        ::AdjustWindowRectEx(&outer_rect,
                             static_cast<DWORD>(::GetWindowLongW(m_hwnd,
                                                                 GWL_STYLE) ),
                             FALSE,
                             static_cast<DWORD>(::GetWindowLongW(m_hwnd,
                                                                 GWL_EXSTYLE) ));

        ::SetWindowPos(m_hwnd,
                       nullptr,
                       0,
                       0,
                       outer_rect.right  - outer_rect.left,
                       outer_rect.bottom - outer_rect.top,
                       SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);

        /* The window is wider or narrower now: it is centered under the replay window again. */
        m_is_placed = false;

        place_below_replay_window();
    }
}

LRESULT Replay::ReplayPlayer::ControlWindow::handle_message(const HWND&   in_window,
                                                            const UINT&   in_message,
                                                            const WPARAM& in_wparam,
                                                            const LPARAM& in_lparam)
{
    LRESULT result = 0;

    if (ImGui_ImplWin32_WndProcHandler(in_window,
                                       in_message,
                                       in_wparam,
                                       in_lparam) != 0)
    {
        result = 1;

        goto end;
    }

    switch (in_message)
    {
        case WM_DESTROY:
        {
            ::PostQuitMessage(0);

            break;
        }

        case WM_PLACE_BELOW_REPLAY_WINDOW:
        {
            place_below_replay_window();

            break;
        }

        case WM_SIZE:
        {
            if (in_wparam != SIZE_MINIMIZED)
            {
                resize(LOWORD(in_lparam),
                       HIWORD(in_lparam) );
            }

            break;
        }

        case WM_SYSCOMMAND:
        {
            /* The menu of the Alt key would take the keyboard from the window. */
            if ((in_wparam & 0xfff0) == SC_KEYMENU)
            {
                goto end;
            }

            result = ::DefWindowProcW(in_window,
                                      in_message,
                                      in_wparam,
                                      in_lparam);

            break;
        }

        default:
        {
            result = ::DefWindowProcW(in_window,
                                      in_message,
                                      in_wparam,
                                      in_lparam);

            break;
        }
    }

end:
    return result;
}

void Replay::ReplayPlayer::ControlWindow::on_error(const std::string& in_message)
{
    (void) in_message;
}

void Replay::ReplayPlayer::ControlWindow::on_frame_presented(const uint32_t& in_n_frame)
{
    (void) in_n_frame;
}

void Replay::ReplayPlayer::ControlWindow::on_state_changed(const Replay::ReplayEngineDLL::PlaybackState& in_old_state,
                                                                   const Replay::ReplayEngineDLL::PlaybackState& in_new_state)
{
    (void) in_old_state;
    (void) in_new_state;
}

void Replay::ReplayPlayer::ControlWindow::on_window_closed()
{
    /* Stub */
}

void Replay::ReplayPlayer::ControlWindow::on_window_placed(const Replay::ReplayEngineDLL::WindowPlacement& in_placement)
{
    {
        std::lock_guard<std::mutex> lock(m_replay_window.mutex);

        m_replay_window.is_known  = true;
        m_replay_window.placement = in_placement;
    }

    /* The window is moved by the thread which owns it. */
    ::PostMessageW(m_hwnd,
                   WM_PLACE_BELOW_REPLAY_WINDOW,
                   0,
                   0);
}

void Replay::ReplayPlayer::ControlWindow::place_below_replay_window()
{
    constexpr int GAP_N_PIXELS      = 8;
    constexpr int N_PARTS_TO_CENTER = 2;

    RECT                             control_rect = {};
    bool                             is_known     = false;
    MONITORINFO                      monitor_info = {};
    Replay::ReplayEngineDLL::WindowPlacement placement;
    RECT                             replay_rect  = {};
    int                              x            = 0;
    int                              y            = 0;

    {
        std::lock_guard<std::mutex> lock(m_replay_window.mutex);

        is_known  = m_replay_window.is_known;
        placement = m_replay_window.placement;
    }

    /* A window of the replay which comes back in another place (it was made anew) takes the controls with it. */
    if (is_known &&
        (m_is_placed      == false                   ||
         placement.height != m_last_placement.height ||
         placement.width  != m_last_placement.width  ||
         placement.x      != m_last_placement.x      ||
         placement.y      != m_last_placement.y) )
    {
        replay_rect.bottom = placement.y + placement.height;
        replay_rect.left   = placement.x;
        replay_rect.right  = placement.x + placement.width;
        replay_rect.top    = placement.y;

        monitor_info.cbSize = sizeof(monitor_info);

        ::GetWindowRect(m_hwnd,
                       &control_rect);
        ::GetMonitorInfoW(::MonitorFromRect(&replay_rect,
                                            MONITOR_DEFAULTTONEAREST),
                         &monitor_info);

        /* Under the window of the replay, in the middle; if that leaves the screen, it is moved back into it. */
        x = placement.x + (placement.width - (control_rect.right - control_rect.left) ) / N_PARTS_TO_CENTER;
        y = placement.y + placement.height + GAP_N_PIXELS;

        x = std::max<int>(monitor_info.rcWork.left,
                          std::min<int>(x,
                                        monitor_info.rcWork.right - (control_rect.right - control_rect.left) ));
        y = std::max<int>(monitor_info.rcWork.top,
                          std::min<int>(y,
                                        monitor_info.rcWork.bottom - (control_rect.bottom - control_rect.top) ));

        ::SetWindowPos(m_hwnd,
                       HWND_TOPMOST,
                       x,
                       y,
                       0,
                       0,
                       SWP_NOACTIVATE | SWP_NOSIZE);

        m_is_placed      = true;
        m_last_placement = placement;
    }
}

void Replay::ReplayPlayer::ControlWindow::render_frame()
{
    const float clear_color_fp32vec4[] = {0.1f, 0.1f, 0.12f, 1.0f};

    /* The size which the last frame needed. */
    fit_to_content();

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();

    draw_controls();

    ImGui::Render();

    m_device_context_ptr->OMSetRenderTargets(1,
                                            &m_render_target_view_ptr,
                                             nullptr);
    m_device_context_ptr->ClearRenderTargetView(m_render_target_view_ptr,
                                                clear_color_fp32vec4);

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData() );

    m_swap_chain_ptr->Present(1,  /* sync interval */
                              0); /* flags         */
}

void Replay::ReplayPlayer::ControlWindow::resize(const UINT& in_width,
                                                 const UINT& in_height)
{
    if (m_swap_chain_ptr != nullptr)
    {
        destroy_render_target();

        m_swap_chain_ptr->ResizeBuffers(0,
                                        in_width,
                                        in_height,
                                        DXGI_FORMAT_UNKNOWN,
                                        0);

        create_render_target();
    }
}

void Replay::ReplayPlayer::ControlWindow::run()
{
    constexpr DWORD MINIMIZED_SLEEP_MS = 20;

    MSG message = {};

    /* The window takes the size of what it shows before it is on the screen. */
    render_frame();
    render_frame();

    ::ShowWindow(m_hwnd,
                 SW_SHOWNORMAL);

    while (message.message != WM_QUIT)
    {
        if (::PeekMessageW(&message,
                           nullptr,
                           0,
                           0,
                           PM_REMOVE) )
        {
            ::TranslateMessage(&message);
            ::DispatchMessageW(&message);

            continue;
        }

        if (::IsIconic(m_hwnd) )
        {
            ::Sleep(MINIMIZED_SLEEP_MS);

            continue;
        }

        render_frame();
    }
}

LRESULT CALLBACK Replay::ReplayPlayer::ControlWindow::window_proc(HWND   in_window,
                                                                  UINT   in_message,
                                                                  WPARAM in_wparam,
                                                                  LPARAM in_lparam)
{
    ControlWindow* window_ptr = nullptr;

    if (in_message == WM_NCCREATE)
    {
        window_ptr = static_cast<ControlWindow*>(reinterpret_cast<CREATESTRUCTW*>(in_lparam)->lpCreateParams);

        ::SetWindowLongPtrW(in_window,
                            GWLP_USERDATA,
                            reinterpret_cast<LONG_PTR>(window_ptr) );
    }
    else
    {
        window_ptr = reinterpret_cast<ControlWindow*>(::GetWindowLongPtrW(in_window,
                                                                          GWLP_USERDATA) );
    }

    return (window_ptr != nullptr) ? window_ptr->handle_message(in_window,
                                                                in_message,
                                                                in_wparam,
                                                                in_lparam)
                                   : ::DefWindowProcW(in_window,
                                                      in_message,
                                                      in_wparam,
                                                      in_lparam);
}
