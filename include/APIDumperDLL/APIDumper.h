/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(APIDUMPER_H)
#define APIDUMPER_H

#include <array>
#include <deque>
#include <memory>
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
    static APIDumperUniquePtr create();

    ~APIDumper();

private:
    /* Private types */
    struct DumpedAPICall
    {
        APIInterceptor::APIFunction         api_func         = APIInterceptor::APIFunction::APIFUNCTION_UNKNOWN;
        APIInterceptor::APIFunctionArgument args_in [14]     {};
        APIInterceptor::APIFunctionArgument args_out[14]     {};
        uint32_t                            n_args_in        = 0;
        uint32_t                            n_args_out       = 0;
        APIInterceptor::APIFunctionArgument returned_value{};
        std::thread::id                     thread_id;
    };

    struct DumpedSurface
    {
        std::array<uint32_t, 2>                extents_u32vec2;
        std::unique_ptr<std::vector<uint8_t> > u8_vec_ptr;
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

    /* Private funcs */
    APIDumper();

    /* Bytes held in memory by what has not been handed over to the writer yet. */
    uint64_t get_n_unwritten_bytes();

    bool init();

    /* Hands over what has been recorded to the writer thread, which writes it out as a segment. Blocks only until the
     * previous segment is on disk. Must be called with the dumper's mutex held.
     */
    void submit_segment(const bool& in_is_last);

    void wait_for_writer();
    void write_workload ();

    static void on_post_callback  (APIInterceptor::APIFunction                in_api_func,
                                   void*                                      in_user_arg_ptr,
                                   uint32_t                                   in_n_args_out,
                                   const APIInterceptor::APIFunctionArgument* in_args_out_ptr,
                                   const APIInterceptor::APIFunctionArgument* in_returned_value_ptr);
    static void on_pre_callback   (APIInterceptor::APIFunction                in_api_func,
                                   uint32_t                                   in_n_args_in,
                                   const APIInterceptor::APIFunctionArgument* in_args_in_ptr,
                                   void*                                      in_user_arg_ptr,
                                   bool*                                      out_should_pass_through_ptr);
    static void on_process_exiting(void*                                      in_user_arg_ptr);
    static void write_segment     (SegmentJobUniquePtr                        in_job_ptr);

    /* Private vars */
    uint32_t                   m_chunk_scan_cursor;     /* first data chunk not yet counted in m_n_chunk_bytes_counted */
    std::deque<DumpedAPICall>  m_dumped_api_call_deque; /* no big reallocations on the render thread                   */
    std::vector<DumpedSurface> m_dumped_surface_vec;
    bool                       m_dump_swapchain_on_present;
    bool                       m_is_workload_written;
    uint64_t                   m_n_bytes_before_spill;  /* spill threshold; see APIDumper --spill-threshold-mb */
    uint64_t                   m_n_chunk_bytes_counted; /* of the data chunks which are not handed over yet    */
    uint32_t                   m_n_data_chunks_written; /* handed over, to be precise                          */
    uint32_t                   m_n_frames_dumped;
    uint32_t                   m_n_frames_to_dump;
    uint64_t                   m_n_surface_bytes;       /* of the surfaces which are not handed over yet       */
    FILE*                      m_workload_file_handle;
    std::thread                m_writer_thread;
};

#endif /* APIDUMPER_H */
