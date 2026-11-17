/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_GL_REPLAY_CONTEXT_H
#define REPLAYENGINEDLL_GL_REPLAY_CONTEXT_H

#include "call_context.h"
#include <deque>
#include <map>
#include <string>
#include <tuple>
#include <vector>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* One entry of the GL function table (see gl_replay_table.inl). */
        struct GLFunctionInfo
        {
            bool                    has_explicit_program;  /* the uniform locations' program is the first parameter */
            uint32_t                ignored_param_mask;    /* parameters not replayed (passed as null)              */
            const char*             name_ptr;
            std::vector<ObjectKind> param_kind_vec;
            ObjectKind              return_kind;
        };

        /* Per-call replay context. Object names go through the remapper; program-assigned locations and indices (uniforms, blocks,
         * subroutines...) are kept here.
         */
        class GLReplayContext : public CallContext
        {
        public:
            GLReplayContext(ObjectRemapper* in_remapper_ptr);

            /* Memory valid until the end of the call, for arguments the replay makes up. */
            std::vector<uint8_t>* allocate_scratch(const size_t& in_n_bytes);

            std::string* allocate_string();

            /* Pointers standing for the strings of a string array argument. */
            std::vector<const char*>* allocate_string_pointers();

            /* Starts a call; state of the previous call is discarded. */
            void begin_call(const Capture::APIDumpLoader::DumpedAPICall* in_call_ptr,
                            const IChunkSource*                          in_chunk_source_ptr,
                            const size_t&                                in_n_head_arguments,
                            const GLFunctionInfo*                        in_function_info_ptr);

            void forget_locations();

            /* Dumped name of the program set by glUseProgram(). */
            uint64_t get_current_program() const;

            uint64_t   get_live_return ()                            const;
            ObjectKind get_param_kind  (const size_t& in_n_argument) const;
            bool       is_param_ignored(const size_t& in_n_argument) const;
            bool       is_skipped      ()                            const;

            /* True if a buffer is bound to the pixel pack target: the pointer of glReadPixels and similar calls is then a buffer offset. */
            bool is_pixel_pack_buffer_bound() const;

            /* Bytes the driver writes through a pointer the dump has no data for (the dumper cannot know), for calls writing a known
             * size into the dumped process's memory. 0 for any other pointer (the replay cannot provide memory).
             */
            size_t get_unrecorded_output_n_bytes(const size_t& in_n_argument) const;

            /* Maps a dumped numeric argument (name, location or index) to the replay's; unseen values pass through unchanged. */
            uint32_t map_argument(const size_t&   in_n_argument,
                                  const uint32_t& in_dumped_value) const;

            uint32_t map_attrib_location(const uint32_t& in_dumped_location) const;

            /* Indices are per program (and per shader stage for subroutines): the scope is the shader type, or 0. */
            uint32_t map_index(const ObjectKind& in_kind,
                               const uint64_t&   in_dumped_program,
                               const uint32_t&   in_scope,
                               const uint32_t&   in_dumped_index) const;

            uint32_t map_name                (const ObjectKind& in_kind,
                                              const uint32_t&   in_dumped_name) const;
            int32_t  map_uniform_location    (const int32_t&    in_dumped_location) const;
            void     register_attrib_location(const uint32_t&   in_dumped_location,
                                              const uint32_t&   in_live_location);
            void     register_index          (const ObjectKind& in_kind,
                                              const uint64_t&   in_dumped_program,
                                              const uint32_t&   in_scope,
                                              const uint32_t&   in_dumped_index,
                                              const uint32_t&   in_live_index);
            void     register_name           (const ObjectKind& in_kind,
                                              const uint32_t&   in_dumped_name,
                                              const uint32_t&   in_live_name);

            /* The call returned an object name, or the first of a range. */
            void register_returned_name(const uint64_t& in_live_value);

            void register_uniform_location(const uint64_t& in_dumped_program,
                                           const int32_t&  in_dumped_location,
                                           const int32_t&  in_live_location);
            void request_skip             ();
            void set_current_program      (const uint64_t& in_dumped_program);
            void set_live_return          (const uint64_t& in_value);
            void set_pixel_pack_buffer_bound(const bool&     in_is_bound);

        private:
            /* Kind, dumped program, scope, dumped index. */
            typedef std::tuple<ObjectKind, uint64_t, uint32_t, uint32_t> IndexKey;

            /* The program named by the call's first parameter, else the current one. */
            uint64_t get_index_program() const;

            /* Components per pixel of the format, and bytes per component (per pixel for packed types); never below the true value for unknown formats/types. */
            static uint64_t get_pixel_n_components(const uint32_t& in_format);
            static uint64_t get_pixel_type_n_bytes(const uint32_t& in_type);

            uint64_t get_uniform_program() const;

            std::map<uint32_t, uint32_t>          m_attrib_location_map;
            uint64_t                              m_current_program;
            const GLFunctionInfo*                 m_function_info_ptr;
            std::map<IndexKey, uint32_t>          m_index_map;
            bool                                  m_is_pixel_pack_buffer_bound;
            bool                                  m_is_skipped;
            uint64_t                              m_live_return;
            std::deque<std::vector<uint8_t> >     m_scratch_deque;
            std::deque<std::vector<const char*> > m_string_pointers_deque;
            std::deque<std::string>               m_string_deque;
            std::map<uint64_t, int32_t>           m_uniform_location_map;
        };
    }
}

#endif /* REPLAYENGINEDLL_GL_REPLAY_CONTEXT_H */
