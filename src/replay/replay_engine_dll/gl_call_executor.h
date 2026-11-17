/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_GL_CALL_EXECUTOR_H
#define REPLAYENGINEDLL_GL_CALL_EXECUTOR_H

#include "gl_client_array_replayer.h"
#include "gl_frame_reader.h"
#include "gl_index_replayer.h"
#include "gl_mapping_replayer.h"
#include "gl_replay_context.h"
#include "gl_state_saver.h"
#include "i_call_executor.h"
#include "object_remapper.h"
#include <map>
#include <string>
#include <vector>
#include <Windows.h>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* Replays the GL calls on the GL context that the WGL calls of the dump made current. The functions are the ones of
         * the system's driver; the names of the objects (textures, buffers...) and the locations of uniforms are mapped to
         * what the driver hands out to the replay.
         */
        class GLCallExecutor : public ICallExecutor
        {
        public:
             GLCallExecutor(ObjectRemapper* in_remapper_ptr);
            ~GLCallExecutor();

            bool           execute            (const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                               const IChunkSource&                          in_chunk_source,
                                               std::string*                                 out_error_ptr)       override;
            CallSupport    get_call_support   (const APIInterceptor::APIFunction&           in_function)   const override;
            ExecutionClass get_execution_class(const Capture::APIDumpLoader::DumpedAPICall& in_call)       const override;
            void           on_frame_presented ()                                                                 override;
            bool           read_back_buffer   (std::vector<uint8_t>*                        out_pixel_u8_vec_ptr,
                                               FrameImage*                                  out_image_ptr)       override;
            void           reset              ()                                                                 override;
            void           restore_state      ()                                                                 override;
            void           save_state         ()                                                                 override;

        protected:
            /* The function of GL by name (those of opengl32.dll and of the driver); null if there is none. */
            void* get_proc_ptr(const char* in_name_ptr);

        private:
            typedef bool (*InvokeFuncPtr)(GLReplayContext* in_context_ptr,
                                          void*            in_function_ptr,
                                          std::string*     out_error_ptr);

            /* A function of the table, and the way to replay it. */
            struct FunctionEntry
            {
                GLFunctionInfo info;
                InvokeFuncPtr  invoke_func_ptr;
                size_t         n_head_arguments;
                void*          proc_ptr = nullptr; /* the function in the driver, once it is looked up; forgotten by reset() */
            };

            void  add_function           (const APIInterceptor::APIFunction&           in_function,
                                          const char*                                  in_name_ptr,
                                          const ObjectKind&                            in_return_kind,
                                          const std::vector<ObjectKind>&               in_param_kind_vec,
                                          const uint32_t&                              in_ignored_param_mask,
                                          const InvokeFuncPtr&                         in_invoke_func_ptr,
                                          const size_t&                                in_n_head_arguments);
            void  after_call             (const Capture::APIDumpLoader::DumpedAPICall& in_call);
            /* Whether the call only reads state into the memory of the application (glGetFloatv, glReadPixels with no pixel pack buffer bound): what the app computed of it
             * is in the calls that follow, as it was dumped, and a replay has no use for the values, so it does not make the call.
             */
            bool  is_readback_into_memory(const Capture::APIDumpLoader::DumpedAPICall& in_call) const;
            void  register_returned_index(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                          const ObjectKind&                            in_kind,
                                          const bool&                                  in_has_scope);

            /* wglGetProcAddress() says a function is not there by one of these. */
            static bool is_valid_proc(const void* in_proc_ptr);

            GLClientArrayReplayer                                m_client_array_replayer;
            GLReplayContext                                      m_context;
            GLIndexReplayer                                      m_index_replayer;
            std::map<APIInterceptor::APIFunction, FunctionEntry> m_entry_map;
            std::vector<FunctionEntry*>                          m_entry_ptr_vec; /* by function, into m_entry_map; nullptr: not replayed */
            GLFrameReader                                        m_frame_reader;
            GLMappingReplayer                                    m_mapping_replayer;
            HMODULE                                              m_opengl32_module;
            std::map<std::string, void*>                         m_proc_ptr_map;
            GLStateSaver                                         m_state_saver;
        };
    }
}

#endif /* REPLAYENGINEDLL_GL_CALL_EXECUTOR_H */
