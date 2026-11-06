/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(APIDUMPER_H)
#define APIDUMPER_H

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
    /* mutex is held while a segment is being cut, and taken before RecordedState::mutex. writer_thread must only be
     * accessed with it held (bar the destructor).
     */
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

    /* What has been recorded and not handed over to the writer yet. Everything but n_frames_dumped, which is also read
     * without the lock, must only be accessed with mutex held.
     */
    struct RecordedState
    {
        std::deque<DumpedAPICall>  api_call_deque;                  /* no big reallocations on the render thread                 */
        uint32_t                   chunk_scan_cursor     = 0;       /* first data chunk not yet counted in n_chunk_bytes_counted */
        FILE*                      file_handle           = nullptr;
        bool                       is_workload_written   = false;
        std::mutex                 mutex;
        uint64_t                   n_chunk_bytes_counted = 0;       /* of the data chunks which are not handed over yet           */
        uint32_t                   n_data_chunks_written = 0;       /* handed over, to be precise                                 */
        std::atomic<uint32_t>      n_frames_dumped;
        uint64_t                   n_surface_bytes       = 0;       /* of the surfaces which are not handed over yet              */
        std::vector<DumpedSurface> surface_vec;

        RecordedState()
            :n_frames_dumped(0)
        {
            /* Stub */
        }
    };

    /* A segment of the workload, handed over to the writer thread. Follows the types it is made of. */
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
        uint64_t n_bytes_before_spill      = 0;          /* spill threshold; see APIDumper --spill-threshold-mb */
        uint32_t n_frames_to_dump          = UINT32_MAX;
    };

    /* Private funcs */
    APIDumper();

    /* Cuts the workload at a frame boundary: hands over what has been recorded, if enough has piled up (or if the dump
     * is complete, in which case the last segment is written). Must be called without the dumper's mutex held, from
     * within an intercepted API call. Other threads are held back from entering intercepted calls for the time of the
     * cut, so that no call ends up split between two segments.
     */
    void cut_segment(const bool& in_is_last);

    /* Bytes held in memory by what has not been handed over to the writer yet. */
    uint64_t get_n_unwritten_bytes();

    bool init();

    /* Called once a frame has been presented. Decides whether to cut the workload. */
    void on_frame_presented();

    /* Does the work of cut_segment(), with m_cut.mutex held. */
    void perform_cut(const bool& in_is_last);

    /* Keeps a surface which was read, so that it is written with the segment it belongs to. Takes the mutex of the recorded state. */
    void store_surface(DumpedSurface in_surface);

    /* Hands over what has been recorded to the writer thread, which writes it out as a segment. Blocks only until the
     * previous segment is on disk. Must be called with the dumper's mutex held.
     */
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

    /* Reads the frame which a call is about to present, if the call is one which presents a frame of an API the dumper can
     * read. Every reader is of one API; this is the only place which tells which is which. False if there is nothing to store.
     */
    static bool read_frame_surface(const APIInterceptor::APIFunction&         in_api_func,
                                   const uint32_t&                            in_n_arguments_in,
                                   const APIInterceptor::APIFunctionArgument* in_arguments_in_ptr,
                                   DumpedSurface*                             out_surface_ptr);

    static void write_segment     (SegmentJobUniquePtr                        in_job_ptr);

    /* Private vars */
    CutState      m_cut;
    RecordedState m_recorded;
    Settings      m_settings;
};

#endif /* APIDUMPER_H */
