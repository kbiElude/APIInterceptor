/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Reads a workload file one segment at a time (see APIDumpLoader.cpp for the file layout), so that a dump needs not fit
 * in memory. A file which is still being written, or which ends abruptly, can be read as far as it goes.
 */
#if !defined(APIDUMPLOADER_WORKLOAD_READER_H)
#define APIDUMPLOADER_WORKLOAD_READER_H

#include "APIDumpLoader/APIDumpLoader.h"
#include "APIDumpLoader/api_info.h"
#include "zstd.h"
#include <memory>
#include <stdio.h>
#include <string>
#include <vector>

namespace APIDumpLoader
{
    class WorkloadReader;

    typedef std::unique_ptr<WorkloadReader> WorkloadReaderUniquePtr;

    class WorkloadReader
    {
    public:
        ~WorkloadReader();

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

        /* Returns nullptr if the file cannot be opened, or is not a workload this version can read. In that case,
         * *out_error_ptr (if not null) says why.
         */
        static WorkloadReaderUniquePtr create(const char*  in_filename_ptr,
                                              std::string* out_error_ptr = nullptr);

    private:
        WorkloadReader();

        /* Makes n bytes available at the front of the buffer, unless the file ends first. Returns the number of bytes
         * available, which may be smaller than asked.
         */
        size_t peek(const size_t& in_n_bytes);

        /* The read_* functions return false if the file ends before the item is complete, bar read_decompressed which
         * is the source of them all: it decompresses the next bytes of the file, and returns how many it got.
         */
        bool   read_api_call    (DumpedAPICall* out_api_call_ptr);
        bool   read_bytes       (void*          out_data_ptr,
                                 const size_t&  in_n_bytes);
        bool   read_data_chunk  (DataChunk*     out_data_chunk_ptr);
        size_t read_decompressed(void*          out_data_ptr,
                                 const size_t&  in_n_bytes);
        bool   read_surface     (DumpedSurface* out_surface_ptr);

        std::vector<uint8_t> m_buffer_u8_vec;
        size_t               m_buffer_end;
        size_t               m_buffer_start;
        std::vector<uint8_t> m_compressed_u8_vec;       /* what was read from the file, and not decompressed yet */
        size_t               m_compressed_end;
        size_t               m_compressed_start;
        ZSTD_DCtx*           m_decompressor_ptr;
        FILE*                m_file_handle;
        bool                 m_is_damaged;              /* the decompressor has rejected the data              */
        bool                 m_is_finished;
        bool                 m_is_frame_incomplete;     /* the frame which was being decompressed is not done  */
        bool                 m_is_truncated;
        uint32_t             m_n_data_chunks_read;
        uint32_t             m_pointer_n_bytes;
        uint64_t             m_qpc_frequency;
    };
}

#endif /* APIDUMPLOADER_WORKLOAD_READER_H */
