#include "common/api_function_argument.h"
/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(APIDUMPER_H)
#define APIDUMPER_H

#include "frame_rate_limiter.h"
#include <array>
#include <atomic>
#include <deque>
#include <memory>
#include <mutex>
#include <stdio.h>
#include <thread>
#include <vector>

/* Forward decls */
class                              APIDumper;
typedef std::unique_ptr<APIDumper> APIDumperUniquePtr;

class APIDumper
{
public:
    /* Public funcs */
    ~APIDumper();

    static APIDumperUniquePtr create();

private:
    /* Private types */
    /* mutex is held while a segment is cut and taken before RecordedState::mutex; writer_thread needs it (except in the destructor). */
    struct CutState
    {
        std::mutex  mutex;
        std::thread writer_thread;
    };

    struct DumpedAPICall
    {
        APIInterceptor::APIFunction         api_func                                                = APIInterceptor::APIFunction::APIFUNCTION_UNKNOWN;
        APIInterceptor::APIFunctionArgument arguments_in [APIInterceptor::MAX_N_FUNCTION_ARGUMENTS] {};
        APIInterceptor::APIFunctionArgument arguments_out[APIInterceptor::MAX_N_FUNCTION_ARGUMENTS] {};
        bool                                is_completed                                            = false; /* post-callback seen            */
        uint32_t                            n_arguments_in                                          = 0;
        uint32_t                            n_arguments_out                                         = 0;
        APIInterceptor::APIFunctionArgument returned_value                                          {};
        uint32_t                            thread_id                                               = 0;
        uint64_t                            timestamp_qpc                                           = 0;     /* when the call was intercepted */
    };

    struct DumpedSurface
    {
        std::array<uint32_t, 2>                extents_u32vec2;
        std::unique_ptr<std::vector<uint8_t> > u8_vec_ptr;
    };

    /* Recorded and not yet handed to the writer. All but n_frames_dumped (also read unlocked) need mutex held. */
    struct RecordedState
    {
        std::deque<DumpedAPICall>  api_call_deque;                  /* no big reallocations on the render thread */
        uint32_t                   chunk_scan_cursor     = 0;       /* first chunk not yet in n_chunk_bytes_counted */
        FILE*                      file_handle           = nullptr;
        bool                       is_workload_written   = false;
        std::mutex                 mutex;
        uint64_t                   n_chunk_bytes_counted = 0;       /* of the chunks not handed over yet   */
        uint32_t                   n_data_chunks_written = 0;       /* handed over                         */
        std::atomic<uint32_t>      n_frames_dumped;
        uint64_t                   n_surface_bytes       = 0;       /* of the surfaces not handed over yet */
        std::vector<DumpedSurface> surface_vec;

        RecordedState()
            :n_frames_dumped(0)
        {
            /* Stub */
        }
    };

    /* A workload segment handed to the writer thread. */
    struct SegmentJob
    {
        std::deque<DumpedAPICall>          api_call_deque;
        std::vector<std::vector<uint8_t> > data_chunk_vec;
        FILE*                              file_handle       = nullptr;
        bool                               should_close_file = false;
        std::vector<DumpedSurface>         surface_vec;
    };

    typedef std::unique_ptr<SegmentJob> SegmentJobUniquePtr;

    /* Set once while initializing, read-only afterwards. */
    struct Settings
    {
        bool     dump_swapchain_on_present = false;
        uint32_t max_frames_per_second     = 0;          /* 0: the app is not held; see APIDumper --max-frame-rate */
        uint64_t n_bytes_before_spill      = 0;          /* spill threshold; see APIDumper --spill-threshold-mb */
        uint32_t n_frames_to_dump          = UINT32_MAX;
    };

    /* Private funcs */
    APIDumper();

    /* Cuts at a frame boundary: hands over the recording if enough has piled up, or the last segment if the dump is complete. Call
     * without the dumper's mutex, from within an intercepted call. Other threads are held out of intercepted calls meanwhile, so no
     * call is split between segments.
     */
    void cut_segment(const bool& in_is_last);

    /* Run when the data chunk store is full (see APIInterceptor::set_data_chunk_drain()). Any thread. Releases all chunks once the dump
     * is complete; during the dump it frees nothing (segments are cut only between frames), so a frame larger than the store ends the process.
     */
    void drain_data_chunks();

    /* Bytes held by what has not been handed to the writer. */
    uint64_t get_n_unwritten_bytes();

    bool init();

    /* After a frame is presented; decides whether to cut. */
    void on_frame_presented();

    /* Does the work of cut_segment(), with m_cut.mutex held. */
    void perform_cut(const bool& in_is_last);

    /* Keeps a read surface for its segment. Takes the recorded state's mutex. */
    void store_surface(DumpedSurface in_surface);

    /* Hands the recording to the writer thread as a segment; blocks only until the previous segment is on disk. Needs the dumper's mutex. */
    void submit_segment(const bool& in_is_last);

    void wait_for_writer();
    void write_workload ();


    static void on_post_callback  (APIInterceptor::APIFunction                in_api_func,
                                   void*                                      in_user_arg_ptr,
                                   uint32_t                                   in_n_arguments_out,
                                   const APIInterceptor::APIFunctionArgument* in_arguments_out_ptr,
                                   const APIInterceptor::APIFunctionArgument* in_returned_value_ptr);
    static void on_pre_callback   (APIInterceptor::APIFunction                in_api_func,
                                   uint32_t                                   in_n_arguments_in,
                                   const APIInterceptor::APIFunctionArgument* in_arguments_in_ptr,
                                   void*                                      in_user_arg_ptr,
                                   bool*                                      out_should_pass_through_ptr);
    static void on_process_exiting(void*                                      in_user_arg_ptr);

    /* Reads the frame a presenting call is about to show, for APIs the dumper can read (the only place that tells which). False if nothing to store. */
    static bool read_frame_surface(const APIInterceptor::APIFunction&         in_api_func,
                                   const uint32_t&                            in_n_arguments_in,
                                   const APIInterceptor::APIFunctionArgument* in_arguments_in_ptr,
                                   DumpedSurface*                             out_surface_ptr);

    static void write_segment     (SegmentJobUniquePtr                        in_job_ptr);

    /* Private vars */
    CutState                                    m_cut;
    Capture::APIDumperDLL::FrameRateLimiterUniquePtr m_frame_rate_limiter_ptr; /* null: the app is not held */
    std::atomic<bool> m_is_dump_complete = {false}; /* last segment handed over; read unlocked by drain_data_chunks() */
    RecordedState     m_recorded;
    Settings          m_settings;
};

#endif /* APIDUMPER_H */
