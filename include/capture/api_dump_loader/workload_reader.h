/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Reads a workload file one segment at a time (see common/workload_format.h for the file layout), so that a dump needs not fit
 * in memory. A file which is still being written, or which ends abruptly, can be read as far as it goes.
 *
 * Each segment is a Zstandard frame of its own, so the segments can be decompressed and read at the same time: with threads (see Options),
 * the reader works on the next segments while the caller works on the one it has, and hands them out in the order of the file all the same.
 * What a caller sees is the same with and without them.
 */
#if !defined(APIDUMPLOADER_WORKLOAD_READER_H)
#define APIDUMPLOADER_WORKLOAD_READER_H

#include "capture/api_dump_loader/api_dump_loader.h"
#include "capture/api_dump_loader/api_info.h"
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
            /* How a reader goes about it. */
            /* Where a segment is in the file and what it numbers from, as the index of the workload has it (see WorkloadIndex). */
            struct SegmentStart
            {
                uint64_t file_offset_n_bytes = 0;
                uint32_t first_data_chunk_id = 0;
                uint64_t first_frame_index   = 0;
            };

            struct Options
            {
                /* Asked of each call, with the number of its frame: the data chunks that calls refer to and none of them wants come as empty chunks (the
                 * chunks after them keep their numbers). For a replay that leaves out what some frames make. It is asked by the threads of the reader, as
                 * a segment is decoded, and only of the segments that segment_start_vec has. Empty: all chunks are wanted.
                 */
                ChunkWantedFunc chunk_wanted_func;

                /* The checksums which the dumper writes with each compressed frame are not checked: a quarter of the time of reading a workload goes to them. For the
                 * replay of a workload which was checked when it was made or read before; the tools which say what is in a workload check them. false: they are.
                 */
                bool ignores_checksums = false;

                /* The segments which are being read or are waiting for the caller, at most; each is held in memory in full (a segment is as
                 * large as the dumper's memory was when it spilled). 0 is n_threads + 2.
                 */
                uint32_t n_segments_in_flight = 0;

                /* The number of data chunks in the segments before the one that the reader starts at (see start_offset_n_bytes): the chunks of the segments it
                 * reads are numbered as they are in the dump. The index of a workload has it (see WorkloadIndex).
                 */
                uint32_t n_data_chunks_before = 0;

                /* The threads which read segments ahead of the caller. 0: the caller reads a segment itself when it asks for it. */
                uint32_t n_threads = 0;

                /* The segments (by file offset, ascending) whose chunks chunk_wanted_func is asked about: the segments of the workload, from its index. */
                std::vector<SegmentStart> segment_start_vec;

                /* A data chunk of more bytes than this comes as an empty one (the chunks after it keep their numbers), and is not copied
                 * anywhere: for tools which look at the calls and not at the vertices and pixels, which are most of a workload. 0: none is left out.
                 */
                uint32_t skip_data_chunks_above_n_bytes = 0;

                /* Where in the file the reader starts: at the start of a segment (a frame of the file, see Workload::file_offset_n_bytes). 0: after the header,
                 * which is the start of the file. The calls of the segments before it are not read, so what a tool follows from call to call is not
                 * what it would be if it read them (the names of objects, for one).
                 */
                uint64_t start_offset_n_bytes = 0;
            };

            ~WorkloadReader();

            /* Returns nullptr if the file cannot be opened, or is not a workload this version can read. In that case,
             * *out_error_ptr (if not null) says why.
             */
            static WorkloadReaderUniquePtr create(const char*  in_filename_ptr,
                                                  std::string* out_error_ptr = nullptr);
            static WorkloadReaderUniquePtr create(const char*    in_filename_ptr,
                                                  const Options& in_options,
                                                  std::string*   out_error_ptr = nullptr);


            /* Reads on until it meets a call of the group. The segments which were read are gone, so this is for a reader
             * which has not been used for anything else. Returns false if the file has no such call.
             */
            bool contains_api_group(const APIGroup& in_group);

            /* Of the process which was dumped. */
            uint32_t get_pointer_n_bytes() const;

            /* True if the file ended in the middle of a segment. */
            bool is_truncated() const;

            /* Reads the next segment, replacing the contents of *out_workload_ptr. Returns false once there is no segment
             * left. If the file ends in the middle of a segment, the part which is complete is returned, and
             * is_truncated() starts to return true; the next call returns false.
             */
            bool read_next_segment(Workload* out_workload_ptr);

        private:
            struct FrameSource;
            struct Pipeline;

            /* A segment, as a frame of the file made it. */
            struct DecodedSegment
            {
                uint64_t                  file_offset_n_bytes = 0; /* of the frame, in the file                                        */
                bool                      has_segment  = false; /* the frame held at least the counts of a segment */
                bool                      is_truncated = false; /* the frame was cut or damaged, or the segment is short of what its counts say */
                uint64_t                  n_compressed_bytes  = 0; /* of the frame                                                      */
                std::unique_ptr<Workload> workload_ptr;
            };

            /* What the next frame of the file came to. */
            enum class Fetch
            {
                CLEAN_END,
                DAMAGED_END, /* a frame which cannot be told to be one: nothing more can be read */
                SEGMENT
            };

            WorkloadReader();

            /* Makes a segment of the bytes of a frame. A frame which is cut is decompressed as far as it goes. */
            static void decode_frame(ZSTD_DCtx*                  in_decompressor_ptr,
                                     const std::vector<uint8_t>& in_frame_byte_vec,
                                     const uint64_t&             in_file_offset_n_bytes,
                                     const Options&              in_options,
                                     DecodedSegment*             out_segment_ptr);

            /* The next segment of the file, in order. */
            Fetch fetch_next_segment(DecodedSegment* out_segment_ptr);

            ZSTD_DCtx*                     m_decompressor_ptr;    /* for the caller's own reading, without threads */
            FILE*                          m_file_handle;
            std::unique_ptr<FrameSource>   m_frame_source_ptr;
            bool                           m_is_finished;
            bool                           m_is_truncated;
            uint32_t                       m_n_data_chunks_read;
            Options                        m_options;
            std::unique_ptr<Pipeline>      m_pipeline_ptr;        /* the threads, if there are any */
            uint32_t                       m_pointer_n_bytes;
            uint64_t                       m_qpc_frequency;
        };
    }
}

#endif /* APIDUMPLOADER_WORKLOAD_READER_H */
