/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Reads a workload file one segment at a time (layout: common/workload_format.h); a file still being written or cut off is read as far
 * as it goes. With threads (see Options) segments are decompressed ahead but handed out in file order; results are the same.
 */
#if !defined(APIDUMPLOADER_WORKLOAD_READER_H)
#define APIDUMPLOADER_WORKLOAD_READER_H

#include "capture/api_dump_loader/api_dump_loader.h"
#include "capture/api_dump_loader/api_info.h"
#include "capture/api_dump_loader/types.h"
#include "zstd.h"
#include <memory>
#include <stdio.h>
#include <string>
#include <vector>

namespace Capture
{
    namespace APIDumpLoader
    {
        class WorkloadReader;

        typedef std::unique_ptr<WorkloadReader> WorkloadReaderUniquePtr;


        class WorkloadReader
        {
        public:
            /* Where a segment is in the file and what it numbers from, as an index of the workload kept by the host says. */
            struct SegmentStart
            {
                uint64_t file_offset_n_bytes  = 0;
                uint32_t first_data_chunk_id  = 0;
                uint64_t first_frame_index    = 0;
                uint32_t n_frames_ended       = 0;
                uint64_t n_compressed_bytes   = 0;
                uint64_t state_n_bytes        = 0; /* in the index file; 0: none */
                uint64_t state_offset_n_bytes = 0; /* in the index file */
            };

            struct Options
            {
                /* Makes, per segment, the function that says which calls are kept (see CallKeptFunc); others never reach the caller.
                 * Only for segments in segment_start_vec. Empty: all calls are kept.
                 */
                CallKeptFuncFactory call_kept_func_factory;

                /* Asked per call (with its frame number); chunks that no call wants come as empty chunks (numbering is kept). Called on
                 * reader threads while decoding, only for segments in segment_start_vec. Empty: all chunks are wanted.
                 */
                ChunkWantedFunc chunk_wanted_func;

                /* true: the dumper's per-frame checksums are not checked, for workloads already verified. */
                bool ignores_checksums = false;

                /* Maximum segments being read or waiting for the caller; each is held in memory in full. 0: n_threads + 2. */
                uint32_t n_segments_in_flight = 0;

                /* Data chunks in the segments before start_offset_n_bytes, so chunk numbers match the dump (an index of the workload kept by the host has it). */
                uint32_t n_data_chunks_before = 0;

                /* Threads reading ahead. 0: the caller reads a segment itself when it asks for it. */
                uint32_t n_threads = 0;

                /* Segments (file offset, ascending) that chunk_wanted_func applies to; taken from the index. */
                std::vector<SegmentStart> segment_start_vec;

                /* Data chunks above this size come as empty chunks (numbering is kept) and are not copied. 0: none is left out. */
                uint32_t skip_data_chunks_above_n_bytes = 0;

                /* The index file; segments of segment_start_vec with a state frame that state_only_func wants as state only come from it. */
                std::string state_filename;
                StateOnlyFunc state_only_func;

                /* Swap chain images come as empty ones (sizes are kept and counted). */
                bool skip_surfaces = false;

                /* Start of the segment to begin at (see Workload::file_offset_n_bytes). 0: the start of the file. Earlier calls are not read,
                 * so state a tool follows across calls (object names) is incomplete.
                 */
                uint64_t start_offset_n_bytes = 0;
            };

            ~WorkloadReader();

            /* Returns nullptr (and sets *out_error_ptr if not null) if the file cannot be opened or is not a readable workload. */
            static WorkloadReaderUniquePtr create(const char*    in_filename_ptr,
                                                  std::string*   out_error_ptr = nullptr);
            static WorkloadReaderUniquePtr create(const char*    in_filename_ptr,
                                                  const Options& in_options,
                                                  std::string*   out_error_ptr = nullptr);


            /* Reads until a call of the group; the segments read are consumed, so use only on an unused reader. False if there is none. */
            bool contains_api_group(const APIGroup& in_group);

            /* Pointer size of the dumped process. */
            uint32_t get_pointer_n_bytes() const;

            /* True if the file ended in the middle of a segment. */
            bool is_truncated() const;

            /* Replaces *out_workload_ptr with the next segment; false when none is left. A cut-off segment is returned as far as it is
             * complete and is_truncated() turns true; the next call returns false.
             */
            bool read_next_segment(Workload* out_workload_ptr);

        private:
            struct FrameSource;
            struct Pipeline;

            /* A segment decoded from a file frame. */
            struct DecodedSegment
            {
                uint64_t                  file_offset_n_bytes = 0; /* of the frame */
                bool                      has_segment  = false; /* the frame held at least a segment's counts */
                bool                      is_truncated = false; /* frame cut or damaged, or segment short of its counts */
                uint64_t                  n_compressed_bytes  = 0; /* of the frame */
                std::unique_ptr<Workload> workload_ptr;
            };

            WorkloadReader();

            /* Decodes a frame's bytes; a cut frame is decompressed as far as it goes. */
            static void decode_frame(ZSTD_DCtx*                  in_decompressor_ptr,
                                     const std::vector<uint8_t>& in_frame_byte_vec,
                                     const uint64_t&             in_file_offset_n_bytes,
                                     const Options&              in_options,
                                     DecodedSegment*             out_segment_ptr);

            /* Next segment in file order. */
            FrameFetch fetch_next_segment(DecodedSegment* out_segment_ptr);

            ZSTD_DCtx*                     m_decompressor_ptr;    /* for reading without threads */
            FILE*                          m_file_handle;
            std::unique_ptr<FrameSource>   m_frame_source_ptr;
            bool                           m_is_finished;
            bool                           m_is_truncated;
            uint32_t                       m_n_data_chunks_read;
            Options                        m_options;
            std::unique_ptr<Pipeline>      m_pipeline_ptr;        /* null without threads */
            uint32_t                       m_pointer_n_bytes;
            uint64_t                       m_qpc_frequency;
        };
    }
}

#endif /* APIDUMPLOADER_WORKLOAD_READER_H */
