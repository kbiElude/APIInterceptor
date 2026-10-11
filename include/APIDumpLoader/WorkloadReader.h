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
#include <memory>
#include <stdio.h>
#include <vector>

namespace APIDumpLoader
{
    class WorkloadReader;

    typedef std::unique_ptr<WorkloadReader> WorkloadReaderUniquePtr;

    class WorkloadReader
    {
    public:
        /* Returns nullptr if the file cannot be opened. */
        static WorkloadReaderUniquePtr create(const char* in_filename_ptr);

        ~WorkloadReader();

        /* True if the file ended in the middle of a segment. */
        bool is_truncated() const;

        /* Reads the next segment, replacing the contents of *out_workload_ptr. Returns false once there is no segment
         * left. If the file ends in the middle of a segment, the part which is complete is returned, and
         * is_truncated() starts to return true; the next call returns false.
         */
        bool read_next_segment(Workload* out_workload_ptr);

    private:
        WorkloadReader();

        /* Makes n bytes available at the front of the buffer, unless the file ends first. Returns the number of bytes
         * available, which may be smaller than asked.
         */
        size_t peek(const size_t& in_n_bytes);

        /* The read_* functions return false if the file ends before the item is complete. */
        bool read_api_call  (DumpedAPICall* out_api_call_ptr);
        bool read_bytes     (void*          out_data_ptr,
                             const size_t&  in_n_bytes);
        bool read_data_chunk(DataChunk*     out_data_chunk_ptr);
        bool read_surface   (DumpedSurface* out_surface_ptr);

        std::vector<uint8_t> m_buffer_u8_vec;
        size_t               m_buffer_end;
        size_t               m_buffer_start;
        FILE*                m_file_handle;
        bool                 m_is_finished;
        bool                 m_is_truncated;
        uint32_t             m_n_data_chunks_read;
    };
}

#endif /* APIDUMPLOADER_WORKLOAD_READER_H */
