/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>
#include "capture/api_dump_loader/api_dump_loader.h"
#include "capture/api_dump_loader/workload_index.h"
#include "capture/api_dump_loader/workload_reader.h"
#include "capture/api_dump_loader/api_info.h"
#include "capture/api_dump_names/function_names.h"
#include "d3d7_decoder.h"
#include "d3d8_decoder.h"
#include "formatter.h"
#include "printer.h"

bool Capture::APIDumpPrinter::parse_api_list(const char* in_argument_ptr,
                                              Options*    inout_options_ptr)
{
    std::string list(in_argument_ptr);
    bool        result = true;
    size_t      start  = 0;

    while (start <= list.size() )
    {
        const size_t            separator_position = list.find(',',
                                                               start);
        const auto              group_name         = list.substr(start,
                                                                 (separator_position == std::string::npos) ? std::string::npos
                                                                                                           : (separator_position - start) );
        Capture::APIDumpLoader::APIGroup group;

        if (Capture::APIDumpLoader::parse_api_group_name(group_name.c_str(),
                                                        &group) == false)
        {
            result = false;

            fprintf(stderr,
                    "[!] Unknown API [%s] in --api list.\n",
                    group_name.c_str() );

            break;
        }

        inout_options_ptr->allowed_api_group_set.insert(group);

        if (separator_position == std::string::npos)
        {
            break;
        }

        start = separator_position + 1;
    }

    return result;
}

bool Capture::APIDumpPrinter::parse_arguments(int      in_argc,
                                               char*    in_argv[],
                                               Options* out_options_ptr)
{
    bool result = false;

    for (int n_argument = 1; n_argument < in_argc; ++n_argument)
    {
        const std::string argument(in_argv[n_argument]);
        const bool        has_value = (n_argument + 1 < in_argc);

        if (argument == "--index")
        {
            out_options_ptr->makes_index_only = true;
        }
        else
        if (argument == "--stats")
        {
            out_options_ptr->show_statistics = true;
        }
        else
        if (argument == "--unreplayed-functions")
        {
            out_options_ptr->lists_unreplayed_functions = true;
        }
        else
        if (argument == "--verify")
        {
            out_options_ptr->verifies_replay = true;
        }
        else
        if (argument == "--frame"       ||
            argument == "--api"         ||
            argument == "--compare"     ||
            argument == "--dump-chunks" ||
            argument == "--hexdump")
        {
            if (has_value == false)
            {
                fprintf(stderr,
                        "[!] %s must be followed by a value.\n",
                        argument.c_str() );

                goto end;
            }

            const char* value_ptr = in_argv[++n_argument];

            if (argument == "--frame")
            {
                if (parse_frame_range(value_ptr,
                                      out_options_ptr) == false)
                {
                    fprintf(stderr,
                            "[!] --frame expects N, A-B or A-.\n");

                    goto end;
                }
            }
            else
            if (argument == "--api")
            {
                if (parse_api_list(value_ptr,
                                   out_options_ptr) == false)
                {
                    goto end;
                }
            }
            else
            if (argument == "--dump-chunks")
            {
                out_options_ptr->chunk_dump_directory = value_ptr;
            }
            else
            if (argument == "--compare")
            {
                out_options_ptr->compare_filename_ptr = value_ptr;
            }
            else
            if (argument == "--hexdump")
            {
                out_options_ptr->n_hexdump_bytes = static_cast<uint32_t>(strtoul(value_ptr,
                                                                                 nullptr,
                                                                                 10) );
            }
        }
        else
        if (argument.size() >  1 &&
            argument[0]     == '-')
        {
            fprintf(stderr,
                    "[!] Unrecognized option [%s].\n",
                    argument.c_str() );

            goto end;
        }
        else
        if (out_options_ptr->workload_filename_ptr == nullptr)
        {
            out_options_ptr->workload_filename_ptr = in_argv[n_argument];
        }
        else
        {
            fprintf(stderr,
                    "[!] More than one workload file specified.\n");

            goto end;
        }
    }

    result = (out_options_ptr->workload_filename_ptr != nullptr ||
              out_options_ptr->lists_unreplayed_functions);
end:
    return result;
}

bool Capture::APIDumpPrinter::parse_frame_range(const char* in_argument_ptr,
                                                 Options*    inout_options_ptr)
{
    unsigned int first_value = 0;
    unsigned int last_value  = 0;
    char         separator   = 0;
    const int    n_parsed    = sscanf(in_argument_ptr,
                                      "%u%c%u",
                                     &first_value,
                                     &separator,
                                     &last_value);
    bool         result      = false;

    if (n_parsed == 1)
    {
        inout_options_ptr->first_frame = first_value;
        inout_options_ptr->last_frame  = first_value;

        result = true;
    }
    else
    if (n_parsed  >= 2 &&
        separator == '-')
    {
        inout_options_ptr->first_frame = first_value;
        inout_options_ptr->last_frame  = (n_parsed == 3) ? last_value
                                                         : UINT32_MAX;

        result = (inout_options_ptr->first_frame <= inout_options_ptr->last_frame);
    }

    return result;
}

void Capture::APIDumpPrinter::print_statistics(const std::map<APIInterceptor::APIFunction, uint32_t>&      in_call_count_map,
                                                const std::map<Capture::APIDumpLoader::APIGroup, uint32_t>& in_group_count_map,
                                                const uint32_t&                                             in_n_calls_selected,
                                                const uint32_t&                                             in_n_frames_total,
                                                const WorkloadTotals&                                       in_totals)
{
    std::vector<std::pair<uint32_t, APIInterceptor::APIFunction> > sorted_vec;

    for (const auto& item : in_call_count_map)
    {
        sorted_vec.emplace_back(item.second,
                                item.first);
    }

    std::sort(sorted_vec.begin(),
              sorted_vec.end  (),
              [](const std::pair<uint32_t, APIInterceptor::APIFunction>& in_item_a,
                 const std::pair<uint32_t, APIInterceptor::APIFunction>& in_item_b)
              {
                  return (in_item_a.first != in_item_b.first) ? (in_item_a.first > in_item_b.first)
                                                              : (std::string(Capture::APIDumpNames::get_function_name(in_item_a.second)) < std::string(Capture::APIDumpNames::get_function_name(in_item_b.second)));
              });

    fprintf(stdout,
            "Workload summary (whole file):\n");
    fprintf(stdout,
            "  API calls:     %u\n",
            in_totals.n_api_calls);
    fprintf(stdout,
            "  Frames:        %u\n",
            in_n_frames_total);
    fprintf(stdout,
            "  Data chunks:   %u (%llu bytes)\n",
            in_totals.n_data_chunks,
            static_cast<unsigned long long>(in_totals.n_data_chunk_bytes) );
    fprintf(stdout,
            "  Surfaces:      %u\n\n",
            in_totals.n_surfaces);

    fprintf(stdout,
            "Selected calls: %u\n",
            in_n_calls_selected);

    for (const auto& item : in_group_count_map)
    {
        const char* group_name_ptr = Capture::APIDumpLoader::get_api_group_name(item.first);

        fprintf(stdout,
                "  %-8s %u\n",
                group_name_ptr,
                item.second);
    }

    fprintf(stdout,
            "\nCalls per function:\n");

    for (const auto& item : sorted_vec)
    {
        const char* function_name_ptr = Capture::APIDumpNames::get_function_name(item.second);

        fprintf(stdout,
                "  %8u  %s\n",
                item.first,
                function_name_ptr);
    }
}

void Capture::APIDumpPrinter::print_usage()
{
    fprintf(stdout,
            "Usage:\n"
            "\n"
            "APIDumpPrinter [options] drive:\\path\\to\\file.workload\n"
            "\n"
            "Every call is printed with ALL of its input arguments and its returned value. If the implementation\n"
            "updated any arguments by reference (e.g. IDs written by glGenTextures), they are listed as\n"
            "[out: argN=value].\n"
            "\n"
            "Options:\n"
            "  --frame A[-B]       Only print calls from frame A (or frames A..B, inclusive). Frames are counted\n"
            "                      from 0; a frame ends with a swapchain present call. \"A-\" means A..last frame.\n"
            "  --api LIST          Only print calls from the specified comma-separated APIs.\n"
            "                      Valid values: gdi32, gl, wgl, user32, d3d8, d3d7. Default: all.\n"
            "  --stats             Instead of listing calls, print a call histogram and workload summary.\n"
            "                      Honors --frame and --api.\n"
            "  --compare FILE      Instead of listing calls: read the workload and FILE and say what they have in common (calls, frames, data, and the functions called a\n"
            "                      different number of times) and where their calls first differ, by function (the arguments have addresses and times in them). Exits with\n"
            "                      1 if they differ.\n"
            "  --verify            Instead of listing calls: read the workload and say what a replay of it would fail on, without replaying it (calls\n"
            "                      of functions the replay has no code for, and data chunks that are not in the file). Exits with 1 if it would fail.\n"
            "  --unreplayed-functions  Needs no workload: list the functions that are recorded and cannot be replayed.\n"
            "  --index             Make the index of the workload (it is kept in a file next to it, and says where its frames are),\n"
            "                      and say what it holds. --frame uses it to read the file from the segment of the first frame, without\n"
            "                      the data chunks of the segments before it: it is made the first time that it is needed.\n"
            "  --dump-chunks DIR   Write each data chunk referenced by the selected calls to DIR\\chunk_NNNNNN.bin.\n"
            "  --hexdump N         Under each call, hex-dump the first N bytes of every data chunk it references.\n"
            "\n"
            "If any surface dumps are included in the workload, they will be stored in the working directory.\n");
}

int Capture::APIDumpPrinter::run(int   in_argc,
                                  char* in_argv[])
{
    typedef std::map<Capture::APIDumpLoader::APIGroup, IAPIDecoder*> DecoderPtrMap;

    /* The threads that read segments ahead of the printer when the index is used (a 32-bit process holds the segments in its 4 GB). */
    const uint32_t N_READER_THREADS                  = (sizeof(void*) == sizeof(uint64_t) ) ? 6 : 3;
    constexpr uint32_t PREFIX_SKIP_CHUNKS_ABOVE_N_BYTES = 256; /* the names of objects need the chunks that name their types, which are small */

    std::map<APIInterceptor::APIFunction, uint32_t>      call_count_map;
    D3D7Decoder                                          d3d7_decoder;
    D3D8Decoder                                          d3d8_decoder;
    DecoderPtrMap                                        decoder_ptr_map   = {{Capture::APIDumpLoader::APIGroup::D3D7, &d3d7_decoder},
                                                                              {Capture::APIDumpLoader::APIGroup::D3D8, &d3d8_decoder}};
    std::map<Capture::APIDumpLoader::APIGroup, uint32_t> group_count_map;
    uint32_t                                             last_header_frame = UINT32_MAX;
    uint32_t                                             n_calls_selected  = 0;
    uint32_t                                             n_chunks_written  = 0;
    uint32_t                                             n_frame           = 0;
    size_t                                               n_prefix_segments = 0;
    size_t                                               n_segments_read   = 0;
    Options                                              options;
    Capture::APIDumpLoader::WorkloadReader::Options      prefix_options;
    Capture::APIDumpLoader::WorkloadReader::Options      range_options;
    std::string                                          reader_error;
    Capture::APIDumpLoader::WorkloadReaderUniquePtr      reader_ptr;
    std::set<APIInterceptor::DataChunkID>                referenced_chunk_set;
    int                                                  result            = EXIT_FAILURE;
    Capture::APIDumpLoader::Workload                     segment;
    WorkloadTotals                                       totals;

    if (parse_arguments(in_argc,
                        in_argv,
                       &options) == false)
    {
        print_usage();

        goto end;
    }

    if (options.compare_filename_ptr != nullptr)
    {
        result = compare_workloads(options);

        goto end;
    }

    if (options.lists_unreplayed_functions)
    {
        result = list_unreplayed_functions();

        goto end;
    }

    if (options.verifies_replay)
    {
        result = verify_replay(options);

        goto end;
    }

    /* What is before the first frame is only to be read for the names of the objects, which are given by the order of their creation: with the index, the
     * segments before the one that has the first frame are read without their big data chunks, and from there on the file is read in full.
     */
    if (options.first_frame != 0 &&
        options.show_statistics == false)
    {
        Capture::APIDumpLoader::WorkloadIndex index;
        bool                                  was_built = false;
        size_t                                n_segment = 0;
        std::string                           index_error;

        if (Capture::APIDumpLoader::WorkloadIndex::load_or_build(options.workload_filename_ptr,
                                                                 N_READER_THREADS,
                                                                &index,
                                                                &was_built,
                                                                &index_error) )
        {
            if (was_built)
            {
                const std::string index_filename = Capture::APIDumpLoader::WorkloadIndex::get_default_filename(options.workload_filename_ptr);

                fprintf(stderr,
                        "[*] The index of the workload has been made, and is kept in %s.\n",
                        index_filename.c_str() );
            }

            if (index.find_segment_of_frame(options.first_frame,
                                           &n_segment) &&
                n_segment != 0)
            {
                n_prefix_segments           = n_segment;
                prefix_options.n_threads                      = N_READER_THREADS;
                prefix_options.skip_data_chunks_above_n_bytes = PREFIX_SKIP_CHUNKS_ABOVE_N_BYTES;
                range_options.n_threads                       = N_READER_THREADS;
                range_options                                 = index.make_reader_options(n_segment,
                                                                                          range_options);
            }
        }
        else
        {
            fprintf(stderr,
                    "[!] The index of the workload cannot be made (%s): the file is read from its start.\n",
                    index_error.c_str() );
        }
    }

    if (options.makes_index_only)
    {
        Capture::APIDumpLoader::WorkloadIndex index;
        bool                                  was_built = false;
        std::string                           index_error;

        if (Capture::APIDumpLoader::WorkloadIndex::load_or_build(options.workload_filename_ptr,
                                                                 N_READER_THREADS,
                                                                &index,
                                                                &was_built,
                                                                &index_error) == false)
        {
            fprintf(stderr,
                    "[!] The index of the workload cannot be made: %s\n",
                    index_error.c_str() );

            goto end;
        }

        const std::string index_filename = Capture::APIDumpLoader::WorkloadIndex::get_default_filename(options.workload_filename_ptr);

        fprintf(stdout,
                "%s the index %s\n"
                "  Segments: %zu\n"
                "  Calls:    %llu\n"
                "  Frames:   %llu%s\n",
                (was_built) ? "Made" : "Read",
                index_filename.c_str(),
                index.get_segment_vec().size(),
                static_cast<unsigned long long>(index.get_n_calls() ),
                static_cast<unsigned long long>(index.get_n_frames() ),
                (index.is_truncated() ) ? " (the file ends in the middle of a segment)" : "");

        result = EXIT_SUCCESS;

        goto end;
    }

    reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(options.workload_filename_ptr,
                                                                prefix_options,
                                                               &reader_error);

    if (reader_ptr == nullptr)
    {
        fprintf(stderr,
                "[!] Could not open the specified workload: %s\n",
                reader_error.c_str() );

        goto end;
    }

    /* The workload is read, and printed, one segment at a time. */
    for (;;)
    {
        /* The last of the segments that are only for the names: the rest is read from the one which has the first frame. */
        if (n_prefix_segments != 0 &&
            n_segments_read   == n_prefix_segments)
        {
            reader_ptr = Capture::APIDumpLoader::WorkloadReader::create(options.workload_filename_ptr,
                                                                        range_options,
                                                                       &reader_error);

            n_prefix_segments = 0;

            if (reader_ptr == nullptr)
            {
                fprintf(stderr,
                        "[!] Could not open the specified workload: %s\n",
                        reader_error.c_str() );

                goto end;
            }
        }

        if (reader_ptr->read_next_segment(&segment) == false)
        {
            break;
        }

        n_segments_read++;

        /* Walk through the calls, tracking frames. */
        for (const auto& current_api_call : *segment.dumped_api_call_vec_ptr)
        {
            const auto api_group         = Capture::APIDumpLoader::get_api_group(current_api_call.func);
            const bool is_in_frame_range = (n_frame >= options.first_frame &&
                                            n_frame <= options.last_frame);
            const bool is_api_allowed    = options.allowed_api_group_set.empty() ||
                                           options.allowed_api_group_set.find(api_group) != options.allowed_api_group_set.end();

            /* Objects are named in the order they are created, whether or not their creation is printed. */
            const auto   decoder_iterator = decoder_ptr_map.find(api_group);
            IAPIDecoder* decoder_ptr      = (decoder_iterator != decoder_ptr_map.end() ) ? decoder_iterator->second
                                                                                         : nullptr;

            if (decoder_ptr != nullptr)
            {
                decoder_ptr->register_created_objects(current_api_call,
                                                      segment);
            }

            if (is_in_frame_range &&
                is_api_allowed)
            {
                n_calls_selected++;

                if (options.show_statistics)
                {
                    call_count_map [current_api_call.func]++;
                    group_count_map[api_group]++;
                }
                else
                {
                    if (last_header_frame != n_frame)
                    {
                        last_header_frame = n_frame;

                        fprintf(stdout,
                                "=== Frame %u ===\n",
                                n_frame);
                    }

                    print_call(stdout,
                               current_api_call,
                               segment,
                               options.n_hexdump_bytes,
                              &referenced_chunk_set,
                               decoder_ptr);
                }
            }

            /* An object which is released for the last time has no name any more: the address may be given to another one. */
            if (decoder_ptr != nullptr)
            {
                decoder_ptr->forget_released_objects(current_api_call);
            }

            /* A frame boundary is detected regardless of --api, so that frame numbering stays stable. */
            if (Capture::APIDumpLoader::is_frame_boundary(current_api_call) )
            {
                n_frame++;
            }
        }

        if (options.chunk_dump_directory.empty() == false)
        {
            n_chunks_written += write_chunks(options.chunk_dump_directory,
                                             segment,
                                             referenced_chunk_set);

            referenced_chunk_set.clear();
        }

        /* Any surfaces included in the segment? */
        if (options.show_statistics                       == false &&
            segment.dumped_surface_vec_ptr->size()        >  0)
        {
            write_surfaces(segment,
                           totals.n_surfaces);
        }

        totals.n_api_calls   += static_cast<uint32_t>(segment.dumped_api_call_vec_ptr->size() );
        totals.n_data_chunks += static_cast<uint32_t>(segment.data_chunk_ptr_vec.size() );
        totals.n_surfaces    += static_cast<uint32_t>(segment.dumped_surface_vec_ptr->size() );

        for (const auto& current_data_chunk_ptr : segment.data_chunk_ptr_vec)
        {
            totals.n_data_chunk_bytes += current_data_chunk_ptr->size();
        }

        /* What has been read so far is out before the next segment is read. */
        fflush(stdout);

        /* No need to read on once the requested frames are past; statistics, though, cover the whole file. */
        if (options.show_statistics == false &&
            n_frame                 >  options.last_frame)
        {
            break;
        }
    }

    if (options.show_statistics)
    {
        print_statistics(call_count_map,
                         group_count_map,
                         n_calls_selected,
                         n_frame,
                         totals);
    }

    if (options.chunk_dump_directory.empty() == false)
    {
        fprintf(stderr,
                "[*] Wrote %u data chunk(s) to [%s].\n",
                n_chunks_written,
                options.chunk_dump_directory.c_str() );
    }

    if (reader_ptr->is_truncated() )
    {
        fprintf(stderr,
                "[!] The workload ends unexpectedly. Everything up to that point has been printed.\n");
    }

    result = EXIT_SUCCESS;
end:
    return result;
}

uint32_t Capture::APIDumpPrinter::write_chunks(const std::string&                           in_directory,
                                                const Capture::APIDumpLoader::Workload&      in_workload,
                                                const std::set<APIInterceptor::DataChunkID>& in_chunk_id_set)
{
    uint32_t result = 0;

    const bool is_directory_created = (::CreateDirectoryA(in_directory.c_str(),
                                                          nullptr) != FALSE);

    if (is_directory_created == false)
    {
        if (::GetLastError() != ERROR_ALREADY_EXISTS)
        {
            fprintf(stderr,
                    "[!] Could not create directory [%s].\n",
                    in_directory.c_str() );

            goto end;
        }
    }

    for (const auto& chunk_id : in_chunk_id_set)
    {
        const std::vector<uint8_t>* chunk_u8_vec_ptr = Capture::APIDumpLoader::get_data_chunk_ptr(in_workload,
                                                                                                  chunk_id);
        char                        filename_i8vec260[MAX_PATH];
        FILE*                       file_handle      = nullptr;

        if (chunk_u8_vec_ptr == nullptr)
        {
            continue;
        }

        snprintf(filename_i8vec260,
                 sizeof(filename_i8vec260),
                 "%s\\chunk_%06u.bin",
                 in_directory.c_str(),
                 chunk_id);

        file_handle = ::fopen(filename_i8vec260,
                              "wb");

        if (file_handle == nullptr)
        {
            fprintf(stderr,
                    "[!] Could not open [%s] for writing.\n",
                    filename_i8vec260);

            continue;
        }

        if (chunk_u8_vec_ptr->empty() == false)
        {
            ::fwrite(chunk_u8_vec_ptr->data(),
                     chunk_u8_vec_ptr->size(),
                     1,
                     file_handle);
        }

        ::fclose(file_handle);

        result++;
    }

end:
    return result;
}

void Capture::APIDumpPrinter::write_surfaces(const Capture::APIDumpLoader::Workload& in_workload,
                                              const uint32_t&                         in_first_surface_index)
{
    std::string target_directory;

    {
        const DWORD          n_bytes_needed          = ::GetCurrentDirectoryA(0,        /* nBufferLength */
                                                                              nullptr); /* lpBuffer      */
        std::vector<uint8_t> target_directory_u8_vec(n_bytes_needed);

        ::GetCurrentDirectoryA(n_bytes_needed,
                               reinterpret_cast<LPTSTR>(target_directory_u8_vec.data() ));

        target_directory = std::string(reinterpret_cast<char*>(target_directory_u8_vec.data() ));
    }

    for (uint32_t n_surface = 0;
                  n_surface < in_workload.dumped_surface_vec_ptr->size();
                ++n_surface)
    {
        auto              surface_props_ptr = &in_workload.dumped_surface_vec_ptr->at(n_surface);
        const std::string filename          = target_directory                                      +
                                              "\\surface_"                                          +
                                              std::to_string(in_first_surface_index + n_surface)    +
                                              "_"                                                   +
                                              std::to_string(surface_props_ptr->extents_u32vec2[0]) +
                                              "x"                                                   +
                                              std::to_string(surface_props_ptr->extents_u32vec2[1]) +
                                              ".raw";
        FILE*             file_handle       = ::fopen(filename.c_str(),
                                                      "wb");

        if (file_handle == nullptr)
        {
            fprintf(stderr,
                    "[!] Could not open [%s] for writing.\n",
                    filename.c_str() );

            continue;
        }

        ::fwrite(surface_props_ptr->data_u8_vec.data(),
                 surface_props_ptr->data_u8_vec.size(),
                 1,
                 file_handle);
        ::fclose(file_handle);
    }
}

int main(int   in_argc,
         char* in_argv[])
{
    return Capture::APIDumpPrinter::run(in_argc,
                                         in_argv);
}
