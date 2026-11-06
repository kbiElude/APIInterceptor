/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Where the frames of a workload are in its file. A workload is a sequence of segments, each a Zstandard frame of its own, and the index says for each of
 * them where it starts, how many calls it has, and which frames it holds, so that a tool which looks at a few frames reads the segments of those and
 * not all of the file (see WorkloadReader::Options::start_offset_n_bytes).
 *
 * Frames are counted as the printer counts them: from 0, a frame ends with a call that APIDumpLoader::is_frame_boundary() says presents.
 *
 * The index is made by reading the workload once (the segments are decoded with the data chunks left out, which is most of a workload), and is kept in
 * a file next to it. It knows the workload it is of (its size, and hashes of 4 KiB from its start, its middle and its end), and is not used for another.
 */
#ifndef APIDUMPLOADER_WORKLOAD_INDEX_H
#define APIDUMPLOADER_WORKLOAD_INDEX_H

#include "capture/api_dump_loader/workload_reader.h"
#include <stdint.h>
#include <string>
#include <vector>

namespace Capture
{
    namespace APIDumpLoader
    {
        /* One segment of the workload. */
        struct SegmentIndexEntry
        {
            uint64_t file_offset_n_bytes = 0; /* of its frame in the file                                                                   */
            uint64_t first_call_index    = 0; /* of the calls of the whole workload                                                          */
            uint64_t first_frame_index   = 0; /* the number of the frame that its first call is in: the frames which ended before it        */
            uint32_t first_data_chunk_id = 0; /* the number of data chunks before it                                                         */
            uint32_t n_calls             = 0;
            uint64_t n_compressed_bytes  = 0;
            uint32_t n_data_chunks       = 0;
            uint32_t n_frames_ended      = 0; /* the calls in it which end a frame                                                           */
        };

        class WorkloadIndex
        {
        public:
            WorkloadIndex();

            /* The index of the workload: its own name and a suffix. */
            static std::string get_default_filename(const std::string& in_workload_filename);

            /* Reads the index file, or makes the index of the workload and writes it if there is none, or there is one of another workload (or of this one
             * as it was). Failing to write it is not a failure: the index is returned all the same.
             */
            static bool load_or_build(const char*    in_workload_filename_ptr,
                                      const uint32_t& in_n_threads,
                                      WorkloadIndex*  out_index_ptr,
                                      bool*           out_was_built_ptr,
                                      std::string*    out_error_ptr);

            /* Reads the workload, segment by segment, and makes the index of it. */
            static bool build(const char*     in_workload_filename_ptr,
                              const uint32_t& in_n_threads,
                              WorkloadIndex*  out_index_ptr,
                              std::string*    out_error_ptr);

            /* False, and why, if the file is not an index of this version. */
            static bool load(const char*    in_index_filename_ptr,
                             WorkloadIndex* out_index_ptr,
                             std::string*   out_error_ptr);

            /* The segment which has the first call of the frame, or an earlier one if the frame started in it; false if the workload has no such frame. */
            bool find_segment_of_frame(const uint64_t& in_frame_index,
                                       size_t*         out_n_segment_ptr) const;

            uint64_t get_n_calls() const;

            /* The frames which ended, and the one that is still going on if calls follow the last of them. */
            uint64_t get_n_frames() const;

            const std::vector<SegmentIndexEntry>& get_segment_vec() const;

            /* True if the index was made of this file, as it is now. */
            bool is_of(const char* in_workload_filename_ptr) const;

            /* True if the file ended in the middle of a segment: what follows was not read. */
            bool is_truncated() const;

            /* The options of a reader which starts at the segment, with its numbers of data chunks; the other options are the ones that are given. */
            WorkloadReader::Options make_reader_options(const size_t&                   in_n_segment,
                                                        const WorkloadReader::Options& in_options) const;

            /* False, and why, if the file cannot be written. */
            bool save(const char*  in_index_filename_ptr,
                      std::string* out_error_ptr) const;

        private:
            /* What the file is, as far as the index can tell (see is_of()). */
            struct Identity
            {
                uint64_t head_hash = 0;
                uint64_t middle_hash = 0;
                uint64_t n_bytes   = 0;
                uint64_t tail_hash = 0;
            };

            /* False if the file cannot be read. */
            static bool get_identity(const char* in_workload_filename_ptr,
                                     Identity*   out_identity_ptr);

            Identity                       m_identity;
            bool                           m_is_truncated;
            uint64_t                       m_n_calls;
            uint64_t                       m_n_frames;
            std::vector<SegmentIndexEntry> m_segment_vec;
        };
    }
}

#endif /* APIDUMPLOADER_WORKLOAD_INDEX_H */
