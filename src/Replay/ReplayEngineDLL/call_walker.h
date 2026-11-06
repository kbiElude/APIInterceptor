/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_CALL_WALKER_H
#define REPLAYENGINEDLL_CALL_WALKER_H

#include "Capture/APIDumpLoader/api_dump_loader.h"
#include "Capture/APIDumpLoader/workload_reader.h"
#include "i_chunk_source.h"
#include <condition_variable>
#include <mutex>
#include <string>
#include <thread>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* Walks the calls of a workload file in the order they were made. A thread of its own reads the next segment (and frees
         * the previous one) while the current one is replayed, so the replay does not wait for the disk.
         */
        class CallWalker : public IChunkSource
        {
        public:
             CallWalker();
            ~CallWalker();

            /* Returns nullptr for a chunk which is not part of the segment of the current call. */
            const Capture::APIDumpLoader::DataChunk* get_data_chunk_ptr(const uint32_t& in_data_chunk_id) const override;

            uint32_t get_pointer_n_bytes() const override;

            const Capture::APIDumpLoader::Workload& get_segment() const;

            /* Opens the file. */
            bool open(const char*  in_filename_ptr,
                      std::string* out_error_ptr);

            /* False once there is no call left. The call (and its chunks) stay valid until the next call of this function. */
            bool read_next_call(const Capture::APIDumpLoader::DumpedAPICall** out_call_ptr_ptr);

            /* Goes back to the start of the file opened before. */
            bool rewind(std::string* out_error_ptr);

            /* The data chunks that the function says no call needs are left out when the file is opened (again), as far as the index of the file is
             * there to say where its segments are (see WorkloadReader::Options::chunk_wanted_func). Empty: all chunks are read. Any thread.
             */
            void set_chunk_wanted_func(const Capture::APIDumpLoader::ChunkWantedFunc& in_func);

        private:
            /* The chunk filter that the next opening of the file uses. */
            struct ChunkFilter
            {
                Capture::APIDumpLoader::ChunkWantedFunc func;
                bool                                    is_pending = false; /* set after the reader was started, so the segments yet to be read are to be read with it */
                std::mutex                              mutex;
            };

            /* The segment which the thread has read ahead, shared with it. */
            struct Prefetch
            {
                std::condition_variable          cv;
                bool                             is_finished       = false; /* the file has no segment left                         */
                bool                             is_ready          = false; /* segment is the next one; otherwise, one to destroy */
                bool                             is_stop_requested = false;
                std::mutex                       mutex;
                Capture::APIDumpLoader::Workload segment;
            };

            void prefetch_main    ();
            bool read_next_segment();

            /* Starts the reader (and the thread that reads ahead with it) at the segment that starts at the offset, with the filter that is set. The old reader
             * goes only if the new one can be started.
             */
            bool start_reader(const char*     in_filename_ptr,
                              const uint64_t& in_start_offset_n_bytes,
                              const uint32_t& in_n_data_chunks_before,
                              std::string*    out_error_ptr);

            void stop_prefetching ();

            /* Whether a filter was set since the reader was started; clears that. */
            bool takes_pending_chunk_filter();

            /* The start of each segment of the file by its index; false if the file has no index (of the file as it is). */
            static bool read_segment_starts(const char*                                                        in_filename_ptr,
                                            std::vector<Capture::APIDumpLoader::WorkloadReader::SegmentStart>* out_start_vec_ptr);

            ChunkFilter                                     m_chunk_filter;
            std::string                                     m_filename;
            size_t                                          m_n_next_call;
            Prefetch                                        m_prefetch;
            std::thread                                     m_prefetch_thread;
            Capture::APIDumpLoader::WorkloadReaderUniquePtr m_reader_ptr;
            Capture::APIDumpLoader::Workload                m_segment;
        };
    }
}

#endif /* REPLAYENGINEDLL_CALL_WALKER_H */
