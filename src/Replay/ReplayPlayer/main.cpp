/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Replays a workload file. This is the front-end of APIDumpReplayer.dll: a window with the playback controls, or the
 * console (--console), which also gives the speed.
 */
#include "Replay/ReplayEngineDLL/entrypoints.h"
#include "control_window.h"
#include "player_launcher.h"
#include "state_names.h"
#include "workload_picker.h"
#include <algorithm>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <Windows.h>

namespace APIDumpPlayer
{
    /* Reports what happens to the replay on the console, and how steady the frames come. */
    class ConsoleObserver : public APIDumpReplayer::IReplayObserver
    {
    public:
        ConsoleObserver();

        void on_error          (const std::string&                    in_message) override;
        void on_frame_presented(const uint32_t&                       in_n_frame) override;
        void on_state_changed  (const APIDumpReplayer::PlaybackState& in_old_state,
                                const APIDumpReplayer::PlaybackState& in_new_state) override;
        void on_window_placed  (const APIDumpReplayer::WindowPlacement& in_placement) override;

    private:
        void print_frame_times();

        std::vector<double> m_frame_time_ms_vec;
        double              m_last_frame_ms;
        double              m_ms_per_tick;
    };

    int  run        (int                                   in_argc,
                  char*                                 in_argv[]);
    void run_console(APIDumpReplayer::IPlaybackController* in_controller_ptr);
}

APIDumpPlayer::ConsoleObserver::ConsoleObserver()
    :m_last_frame_ms(0.0),
     m_ms_per_tick  (0.0)
{
    LARGE_INTEGER frequency;

    ::QueryPerformanceFrequency(&frequency);

    m_ms_per_tick = 1000.0 / static_cast<double>(frequency.QuadPart);
}

void APIDumpPlayer::ConsoleObserver::on_error(const std::string& in_message)
{
    fprintf(stderr,
            "[!] %s\n",
            in_message.c_str() );
}

void APIDumpPlayer::ConsoleObserver::on_frame_presented(const uint32_t& in_n_frame)
{
    LARGE_INTEGER ticks;

    ::QueryPerformanceCounter(&ticks);

    const double now_ms = static_cast<double>(ticks.QuadPart) * m_ms_per_tick;

    /* The time since the frame before; the first one has none. */
    if (in_n_frame != 0 &&
        m_last_frame_ms != 0.0)
    {
        m_frame_time_ms_vec.push_back(now_ms - m_last_frame_ms);
    }

    m_last_frame_ms = now_ms;
}

void APIDumpPlayer::ConsoleObserver::on_state_changed(const APIDumpReplayer::PlaybackState& in_old_state,
                                                      const APIDumpReplayer::PlaybackState& in_new_state)
{
    (void) in_old_state;

    fprintf(stdout,
            "[*] %s\n",
            StateNames::get_state_name_ptr(in_new_state) );

    /* A pause, or the end, closes a stretch of frames; the time to the next one does not count. */
    if (in_new_state != APIDumpReplayer::PlaybackState::PLAYING)
    {
        print_frame_times();

        m_frame_time_ms_vec.clear();

        m_last_frame_ms = 0.0;
    }
}

void APIDumpPlayer::ConsoleObserver::on_window_placed(const APIDumpReplayer::WindowPlacement& in_placement)
{
    (void) in_placement;
}

void APIDumpPlayer::ConsoleObserver::print_frame_times()
{
    constexpr size_t N_PERCENT = 100;

    std::vector<double> sorted_ms_vec = m_frame_time_ms_vec;

    if (sorted_ms_vec.empty() == false)
    {
        std::sort(sorted_ms_vec.begin(),
                  sorted_ms_vec.end  () );

        fprintf(stdout,
                "[*] frame times: %zu frames, median %.2f ms, 99%% %.2f ms, worst %.2f ms\n",
                sorted_ms_vec.size(),
                sorted_ms_vec.at(sorted_ms_vec.size() / 2),
                sorted_ms_vec.at(sorted_ms_vec.size() * (N_PERCENT - 1) / N_PERCENT),
                sorted_ms_vec.back() );
    }
}

int APIDumpPlayer::run(int   in_argc,
                       char* in_argv[])
{
    APIDumpReplayer::IPlaybackController* controller_ptr  = nullptr;
    APIDumpReplayer::IReplayEngine*       engine_ptr      = nullptr;
    std::string                           error;
    int                                   exit_code       = EXIT_FAILURE;
    bool                                  is_console      = false;
    bool                                  is_usage_error  = false;
    ConsoleObserver                       observer;
    int                                   result          = EXIT_FAILURE;
    std::string                           workload_path;

    for (int n_argument = 1;
             n_argument < in_argc;
           ++n_argument)
    {
        if (std::string(in_argv[n_argument]) == "--console")
        {
            is_console = true;
        }
        else
        if (workload_path.empty() )
        {
            workload_path = in_argv[n_argument];
        }
        else
        {
            is_usage_error = true;
        }
    }

    if (is_usage_error)
    {
        fprintf(stderr,
                "Usage: APIDumpPlayer [--console] [file.workload]\n"
                "Without a file, a window asks for one. The window has the play / pause and reset buttons. With --console,\n"
                "the commands are typed instead:\n"
                "p = play / pause, r = reset, s = status, x <speed> = speed (1 = the recorded pace, 0 = unlimited), q = quit\n");

        goto end;
    }

    if (workload_path.empty() &&
        WorkloadPicker::pick(&workload_path) == false)
    {
        fprintf(stdout,
                "[*] No workload has been selected.\n");

        result = EXIT_SUCCESS;

        goto end;
    }

    /* D3D8 can only be replayed by the 32-bit player. */
    if (PlayerLauncher::is_handover_needed(workload_path.c_str() ) )
    {
        if (PlayerLauncher::run_x86_player(workload_path,
                                           is_console,
                                          &exit_code,
                                          &error) )
        {
            result = exit_code;
        }
        else
        {
            fprintf(stderr,
                    "[!] %s\n",
                    error.c_str() );
        }

        goto end;
    }

    engine_ptr = APIDumpReplayer::aiCreateReplayEngine();

    engine_ptr->add_replay_observer(&observer);

    if (engine_ptr->load(workload_path.c_str(),
                        &error) == false)
    {
        fprintf(stderr,
                "[!] %s\n",
                error.c_str() );

        goto end;
    }

    controller_ptr = engine_ptr->get_playback_controller_ptr();

    if (is_console)
    {
        controller_ptr->play();

        run_console(controller_ptr);

        result = EXIT_SUCCESS;
    }
    else
    {
        ControlWindow window(controller_ptr,
                             "API Dump Player");

        if (window.create(&error) == false)
        {
            fprintf(stderr,
                    "[!] %s\n",
                    error.c_str() );

            goto end;
        }

        /* The window is up before the replay makes its own, so that it can be put below it. */
        engine_ptr->add_replay_observer(&window);

        controller_ptr->play();

        window.run();

        engine_ptr->remove_replay_observer(&window);

        result = EXIT_SUCCESS;
    }

end:
    if (engine_ptr != nullptr)
    {
        engine_ptr->remove_replay_observer(&observer);

        APIDumpReplayer::aiDestroyReplayEngine(engine_ptr);
    }

    return result;
}

void APIDumpPlayer::run_console(APIDumpReplayer::IPlaybackController* in_controller_ptr)
{
    for (std::string command; std::getline(std::cin,
                                           command); )
    {
        if (command == "q")
        {
            break;
        }

        if (command == "p")
        {
            const auto status = in_controller_ptr->get_status();

            if (status.state == APIDumpReplayer::PlaybackState::PLAYING)
            {
                in_controller_ptr->pause();
            }
            else
            {
                in_controller_ptr->play();
            }
        }

        if (command == "r")
        {
            in_controller_ptr->reset();
        }

        if (command == "s")
        {
            const auto status = in_controller_ptr->get_status();

            fprintf(stdout,
                    "[*] %s: %llu calls, %u frames\n",
                    StateNames::get_state_name_ptr(status.state),
                    static_cast<unsigned long long>(status.n_calls_executed),
                    status.n_frames_presented);
        }

        if (command.compare(0,
                            2,
                            "x ") == 0)
        {
            in_controller_ptr->set_speed(::atof(command.c_str() + 2) );
        }
    }
}

int main(int   in_argc,
         char* in_argv[])
{
    return APIDumpPlayer::run(in_argc,
                              in_argv);
}
