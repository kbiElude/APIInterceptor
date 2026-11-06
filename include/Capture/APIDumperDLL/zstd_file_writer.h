/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Compresses what is written to a file into one Zstandard frame.
 */
#if !defined(APIDUMPERDLL_ZSTD_FILE_WRITER_H)
#define APIDUMPERDLL_ZSTD_FILE_WRITER_H

#include "zstd.h"
#include <memory>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <vector>

namespace Capture
{
    namespace APIDumperDLL
    {
        class ZstdFileWriter;

        typedef std::unique_ptr<ZstdFileWriter> ZstdFileWriterUniquePtr;

        class ZstdFileWriter
        {
        public:
            /* The file is appended to, and stays open. Returns nullptr if the compressor cannot be set up. */
            static ZstdFileWriterUniquePtr create(FILE*      in_file_handle,
                                                  const int& in_compression_level);

            ~ZstdFileWriter();

            /* Ends the frame, so that everything written is in the file. Returns false if the file cannot be written to. */
            bool finish();

            /* Returns false if the data cannot be compressed, or the file cannot be written to. */
            bool write(const void*   in_data_ptr,
                       const size_t& in_n_bytes);


        private:
            ZstdFileWriter();

            /* Feeds the compressor, writing out what it returns. The input is consumed entirely; for ZSTD_e_end, the frame
             * is completed.
             */
            bool compress(const void*              in_data_ptr,
                          const size_t&            in_n_bytes,
                          const ZSTD_EndDirective& in_directive);

            ZSTD_CCtx*           m_compressor_ptr;
            FILE*                m_file_handle;
            std::vector<uint8_t> m_output_u8_vec;
        };
    }
}

#endif /* APIDUMPERDLL_ZSTD_FILE_WRITER_H */
