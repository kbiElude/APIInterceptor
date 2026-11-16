/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "gl_call_executor.h"
#include "gl_function_types.h"
#include "gl_replay_invoker.h"
#include <array>
#include <ctype.h>
#include <string.h>

/* Turns the parenthesized list of the table's entry into the list of an initializer. */
#define GL_UNPACK_KINDS(...) __VA_ARGS__

Replay::ReplayEngineDLL::GLCallExecutor::GLCallExecutor(ObjectRemapper* in_remapper_ptr)
    :m_client_array_replayer(&m_context,
                             [this](const char* in_name_ptr)
                             {
                                 return get_proc_ptr(in_name_ptr);
                             }),
     m_context              (in_remapper_ptr),
     m_frame_reader         ([this](const char* in_name_ptr)
                             {
                                 return get_proc_ptr(in_name_ptr);
                             }),
     m_index_replayer       (&m_context,
                             [this](const char* in_name_ptr)
                             {
                                 return get_proc_ptr(in_name_ptr);
                             }),
     m_mapping_replayer     (&m_context,
                             [this](const char* in_name_ptr)
                             {
                                 return get_proc_ptr(in_name_ptr);
                             }),
     m_opengl32_module      (::LoadLibraryW(L"opengl32.dll") ),
     m_state_saver          ([this](const char* in_name_ptr)
                             {
                                 return get_proc_ptr(in_name_ptr);
                             })
{
    /* Every function of the table. */
    #define GL_REPLAY_FUNCTION(FUNCTION, NAME, FUNCTION_TYPE, RETURN_KIND, KINDS, IGNORED_MASK) \
        { \
            typedef GLReplay::Invoker<FUNCTION_TYPE> FunctionReplay; \
            \
            add_function(FUNCTION, \
                         NAME, \
                         RETURN_KIND, \
                         std::vector<ObjectKind>{GL_UNPACK_KINDS KINDS}, \
                         IGNORED_MASK, \
                         &FunctionReplay::invoke, \
                         FunctionReplay::get_n_arguments()); \
        }

    #include "gl_replay_table.inl"

    #undef GL_REPLAY_FUNCTION
}

Replay::ReplayEngineDLL::GLCallExecutor::~GLCallExecutor()
{
    /* The context belongs to the replay thread: reset() has dropped what refers to it already. */
}

void Replay::ReplayEngineDLL::GLCallExecutor::add_function(const APIInterceptor::APIFunction& in_function,
                                                           const char*                        in_name_ptr,
                                                           const ObjectKind&                  in_return_kind,
                                                           const std::vector<ObjectKind>&     in_param_kind_vec,
                                                           const uint32_t&                    in_ignored_param_mask,
                                                           const InvokeFuncPtr&               in_invoke_func_ptr,
                                                           const size_t&                      in_n_head_arguments)
{
    constexpr char PROGRAM_UNIFORM_PREFIX[] = "glProgramUniform";

    FunctionEntry entry;

    entry.info.has_explicit_program = (::strncmp(in_name_ptr,
                                                 PROGRAM_UNIFORM_PREFIX,
                                                 sizeof(PROGRAM_UNIFORM_PREFIX) - 1) == 0);
    entry.info.ignored_param_mask   = in_ignored_param_mask;
    entry.info.name_ptr             = in_name_ptr;
    entry.info.param_kind_vec       = in_param_kind_vec;
    entry.info.return_kind          = in_return_kind;
    entry.invoke_func_ptr           = in_invoke_func_ptr;
    entry.n_head_arguments          = in_n_head_arguments;

    m_entry_map[in_function] = entry;
}

void Replay::ReplayEngineDLL::GLCallExecutor::after_call(const Capture::APIDumpLoader::DumpedAPICall& in_call)
{
    int64_t dumped_location = 0;
    uint64_t dumped_program = 0;

    switch (in_call.func)
    {
        case APIInterceptor::APIFUNCTION_GL_GLBINDBUFFER:
        {
            /* A buffer bound to GL_PIXEL_PACK_BUFFER makes the pointers of the reads of pixels offsets. */
            constexpr uint32_t PIXEL_PACK_BUFFER = 0x88EB;

            std::array<uint32_t, 2> bind_array = {};
            bool                    are_read   = (in_call.arg_in_vec.size() >= bind_array.size() );

            for (size_t n_value = 0;
                        are_read && n_value < bind_array.size();
                      ++n_value)
            {
                are_read = read_number(in_call.arg_in_vec.at(n_value),
                                       &bind_array.at       (n_value) );
            }

            if (are_read                              &&
                bind_array.at(0) == PIXEL_PACK_BUFFER)
            {
                m_context.set_pixel_pack_buffer_bound(bind_array.at(1) != 0);
            }

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLGETATTRIBLOCATION:
        {
            /* The index that the app uses is the one the dump holds; the driver may hand out another. */
            if (in_call.returned_value_ptr != nullptr)
            {
                read_number(*in_call.returned_value_ptr,
                            &dumped_location);

                const uint64_t live_return = m_context.get_live_return();

                if (dumped_location                   >= 0 &&
                    static_cast<int32_t>(live_return) >= 0)
                {
                    m_context.register_attrib_location(static_cast<uint32_t>(dumped_location),
                                                       static_cast<uint32_t>(live_return) );
                }
            }

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMLOCATION:
        {
            if (in_call.returned_value_ptr != nullptr &&
                in_call.arg_in_vec.empty() == false)
            {
                read_number(*in_call.returned_value_ptr,
                            &dumped_location);
                read_number(in_call.arg_in_vec.at(0),
                            &dumped_program);

                const uint64_t live_return = m_context.get_live_return();

                if (dumped_location                   >= 0 &&
                    static_cast<int32_t>(live_return) >= 0)
                {
                    m_context.register_uniform_location(dumped_program,
                                                        static_cast<int32_t>(dumped_location),
                                                        static_cast<int32_t>(live_return) );
                }
            }

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLGETFRAGDATALOCATION:
        {
            register_returned_index(in_call,
                                    ObjectKind::FRAG_DATA_LOCATION,
                                    false); /* in_has_scope */

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLGETPROGRAMRESOURCEINDEX:
        {
            constexpr uint32_t COMPAT_GL_SHADER_STORAGE_BLOCK = 0x92E6;

            uint32_t program_interface = 0;

            if (in_call.arg_in_vec.size() > 1)
            {
                read_number(in_call.arg_in_vec.at(1),
                            &program_interface);
            }

            /* The indices of the other resources are not used by the app to set anything. */
            if (program_interface == COMPAT_GL_SHADER_STORAGE_BLOCK)
            {
                register_returned_index(in_call,
                                        ObjectKind::PROGRAM_RESOURCE_INDEX,
                                        false); /* in_has_scope */
            }

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLGETSUBROUTINEINDEX:
        {
            register_returned_index(in_call,
                                    ObjectKind::SUBROUTINE_INDEX,
                                    true); /* in_has_scope */

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLGETSUBROUTINEUNIFORMLOCATION:
        {
            register_returned_index(in_call,
                                    ObjectKind::SUBROUTINE_UNIFORM_LOCATION,
                                    true); /* in_has_scope */

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLGETUNIFORMBLOCKINDEX:
        {
            register_returned_index(in_call,
                                    ObjectKind::UNIFORM_BLOCK_INDEX,
                                    false); /* in_has_scope */

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLUSEPROGRAM:
        {
            if (in_call.arg_in_vec.empty() == false)
            {
                read_number(in_call.arg_in_vec.at(0),
                            &dumped_program);

                m_context.set_current_program(dumped_program);
            }

            break;
        }

        default:
        {
            break;
        }
    }

    m_context.register_returned_name(m_context.get_live_return() );
}

bool Replay::ReplayEngineDLL::GLCallExecutor::execute(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                      const IChunkSource&                          in_chunk_source,
                                                      std::string*                                 out_error_ptr)
{
    const auto entry_iterator = m_entry_map.find(in_call.func);
    void*      proc_ptr       = nullptr;
    bool       result         = false;

    if (get_call_support(in_call.func) == CallSupport::UNSUPPORTED)
    {
        *out_error_ptr = "The GL executor does not know the function.";

        goto end;
    }

    if (::wglGetCurrentContext() == nullptr)
    {
        *out_error_ptr = "A GL call is made while no GL context is current.";

        goto end;
    }

    m_context.begin_call(&in_call,
                         &in_chunk_source,
                          entry_iterator->second.n_head_arguments,
                         &entry_iterator->second.info);

    if (GLMappingReplayer::is_mapping_function(in_call.func) )
    {
        result = m_mapping_replayer.replay(in_call,
                                           out_error_ptr);

        goto end;
    }

    if (GLIndexReplayer::is_index_function(in_call.func) )
    {
        result = m_index_replayer.replay(in_call,
                                         out_error_ptr);

        goto end;
    }

    /* What the dumper stored after the arguments of a draw call: the part of the app's vertex arrays which it reads. */
    if (in_call.arg_in_vec.size() > entry_iterator->second.n_head_arguments)
    {
        size_t         n_bytes  = 0;
        const uint8_t* data_ptr = m_context.get_chunk_data_ptr(&in_call.arg_in_vec.at(entry_iterator->second.n_head_arguments),
                                                               &n_bytes);

        if (data_ptr != nullptr)
        {
            m_client_array_replayer.apply(data_ptr,
                                          n_bytes);
        }
    }

    if (is_readback_into_memory(in_call) )
    {
        result = true;

        goto end;
    }

    /* The driver is asked once for a function, not at each call. */
    if (entry_iterator->second.proc_ptr == nullptr)
    {
        entry_iterator->second.proc_ptr = get_proc_ptr(entry_iterator->second.info.name_ptr);
    }

    proc_ptr = entry_iterator->second.proc_ptr;

    if (proc_ptr == nullptr)
    {
        *out_error_ptr = std::string("The driver does not have ") +
                         entry_iterator->second.info.name_ptr     +
                         ".";

        goto end;
    }

    if (entry_iterator->second.invoke_func_ptr(&m_context,
                                               proc_ptr,
                                               out_error_ptr) == false)
    {
        goto end;
    }

    if (m_context.is_skipped() == false)
    {
        after_call(in_call);
    }

    result = true;

end:
    return result;
}

bool Replay::ReplayEngineDLL::GLCallExecutor::is_readback_into_memory(const Capture::APIDumpLoader::DumpedAPICall& in_call) const
{
    bool result = false;

    switch (in_call.func)
    {
        case APIInterceptor::APIFUNCTION_GL_GLGETFLOATV:
        {
            result = true;

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLREADPIXELS:
        {
            /* With a pixel pack buffer bound the pixels go to a buffer of the GPU, which later calls may use. */
            result = (m_context.is_pixel_pack_buffer_bound() == false);

            break;
        }

        default:
        {
            break;
        }
    }

    return result;
}

Replay::ReplayEngineDLL::ExecutionClass Replay::ReplayEngineDLL::GLCallExecutor::get_execution_class(const Capture::APIDumpLoader::DumpedAPICall& in_call) const
{
    constexpr char CREATE_PREFIX[] = "glCreate";
    constexpr char DELETE_PREFIX[] = "glDelete";
    constexpr char GEN_PREFIX[]    = "glGen";

    const auto     entry_iterator = m_entry_map.find(in_call.func);
    ExecutionClass result         = ExecutionClass::EVERY_TIME;

    if (entry_iterator != m_entry_map.end() )
    {
        const char* name_ptr = entry_iterator->second.info.name_ptr;

        /* What makes an object gives it a name that the replay maps to what the driver hands out: it is done once, or the second execution would make others. glGen is
         * followed by the plural of the object (glGenTextures), where glGenerateMipmap has a lowercase letter.
         */
        const bool makes_object = (::strncmp(name_ptr,
                                             CREATE_PREFIX,
                                             sizeof(CREATE_PREFIX) - 1) == 0 ||
                                   (::strncmp(name_ptr,
                                              GEN_PREFIX,
                                              sizeof(GEN_PREFIX) - 1) == 0 &&
                                    ::isupper(static_cast<unsigned char>(name_ptr[sizeof(GEN_PREFIX) - 1]) ) != 0) );

        if (makes_object)
        {
            result = ExecutionClass::FIRST_TIME_ONLY;
        }
        else
        if (::strncmp(name_ptr,
                      DELETE_PREFIX,
                      sizeof(DELETE_PREFIX) - 1) == 0)
        {
            /* What the last execution may still use. */
            result = ExecutionClass::AFTER_ALL;
        }
    }

    return result;
}

Replay::ReplayEngineDLL::CallSupport Replay::ReplayEngineDLL::GLCallExecutor::get_call_support(const APIInterceptor::APIFunction& in_function) const
{
    return (m_entry_map.find(in_function) != m_entry_map.end() ) ? CallSupport::REPLAYED
                                                                 : CallSupport::UNSUPPORTED;
}

void* Replay::ReplayEngineDLL::GLCallExecutor::get_proc_ptr(const char* in_name_ptr)
{
    const auto iterator = m_proc_ptr_map.find(in_name_ptr);
    void*      result   = nullptr;

    if (iterator != m_proc_ptr_map.end() )
    {
        result = iterator->second;

        goto end;
    }

    /* The extensions and the newer versions come from the driver; the oldest functions are exports of opengl32.dll. */
    result = reinterpret_cast<void*>(::wglGetProcAddress(in_name_ptr) );

    if (is_valid_proc(result) == false)
    {
        result = (m_opengl32_module != nullptr) ? reinterpret_cast<void*>(::GetProcAddress(m_opengl32_module,
                                                                                           in_name_ptr) )
                                                : nullptr;
    }

    if (result != nullptr)
    {
        m_proc_ptr_map[in_name_ptr] = result;
    }

end:
    return result;
}

bool Replay::ReplayEngineDLL::GLCallExecutor::is_valid_proc(const void* in_proc_ptr)
{
    constexpr uintptr_t MAX_INVALID_PROC_VALUE = 3;

    const uintptr_t value = reinterpret_cast<uintptr_t>(in_proc_ptr);

    return (value >  MAX_INVALID_PROC_VALUE     &&
            value != static_cast<uintptr_t>(-1) );
}

void Replay::ReplayEngineDLL::GLCallExecutor::on_frame_presented()
{
    /* Stub */
}

void Replay::ReplayEngineDLL::GLCallExecutor::register_returned_index(const Capture::APIDumpLoader::DumpedAPICall& in_call,
                                                                      const ObjectKind&                            in_kind,
                                                                      const bool&                                  in_has_scope)
{
    constexpr uint32_t INVALID_INDEX = 0xFFFFFFFFu;

    int64_t  dumped_index   = -1;
    uint64_t dumped_program = 0;
    uint32_t scope          = 0;

    if (in_call.returned_value_ptr != nullptr &&
        in_call.arg_in_vec.empty() == false)
    {
        read_number(*in_call.returned_value_ptr,
                    &dumped_index);
        read_number(in_call.arg_in_vec.at(0),
                    &dumped_program);

        /* The shader stage is the second argument of the functions which have a scope. */
        if (in_has_scope                  &&
            in_call.arg_in_vec.size() > 1)
        {
            read_number(in_call.arg_in_vec.at(1),
                        &scope);
        }

        /* An index which does not exist is -1, or GL_INVALID_INDEX. */
        const uint64_t live_return = m_context.get_live_return();

        if (dumped_index                        >= 0             &&
            static_cast<uint32_t>(dumped_index) != INVALID_INDEX &&
            static_cast<uint32_t>(live_return)  != INVALID_INDEX)
        {
            m_context.register_index(in_kind,
                                     dumped_program,
                                     scope,
                                     static_cast<uint32_t>(dumped_index),
                                     static_cast<uint32_t>(live_return) );
        }
    }
}

bool Replay::ReplayEngineDLL::GLCallExecutor::read_back_buffer(std::vector<uint8_t>* out_pixel_u8_vec_ptr,
                                                               FrameImage*           out_image_ptr)
{
    return m_frame_reader.read(out_pixel_u8_vec_ptr,
                               out_image_ptr);
}

void Replay::ReplayEngineDLL::GLCallExecutor::reset()
{
    m_context.forget_locations();
    m_mapping_replayer.reset  ();
    m_proc_ptr_map.clear      ();

    for (auto& entry_pair : m_entry_map)
    {
        entry_pair.second.proc_ptr = nullptr;
    }
}

void Replay::ReplayEngineDLL::GLCallExecutor::restore_state()
{
    m_state_saver.restore();
}

void Replay::ReplayEngineDLL::GLCallExecutor::save_state()
{
    m_state_saver.save();
}
