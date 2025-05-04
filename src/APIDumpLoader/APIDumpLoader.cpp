/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "APIDumpLoader/APIDumpLoader.h"
#include <assert.h>

APIDumpLoader::DumpedAPICallVectorUniquePtr APIDumpLoader::create_dumped_api_call_vec_from_file(const char* in_filename_ptr)
{
    std::vector<uint8_t>                        file_data_u8_vec;
    FILE*                                       file_handle      = nullptr;
    APIDumpLoader::DumpedAPICallVectorUniquePtr result_ptr;

    /* Read file contents.. */
    {
        long file_size = 0;

        file_handle = ::fopen(in_filename_ptr,
                              "rb");

        if (file_handle == nullptr)
        {
            assert(file_handle != nullptr);

            goto end;
        }

        if (::fseek(file_handle,
                    0,
                    SEEK_END) != 0)
        {
            assert(false);

            goto end;
        }

        file_size = ::ftell(file_handle);

        if (::fseek(file_handle,
                    0,
                    SEEK_SET) != 0)
        {
            assert(false);

            goto end;
        }

        file_data_u8_vec.resize(file_size);

        if (::fread(file_data_u8_vec.data(),
                    file_size,
                    1,
                    file_handle) != 1)
        {
            assert(false);

            goto end;
        }
    }

    /* Parse the file.. */
    result_ptr.reset(new DumpedAPICallVector() );

    {
        uint8_t* data_u8_ptr   = file_data_u8_vec.data();
        uint32_t n_api_calls   = 0;
        uint32_t n_data_chunks = 0;

        n_api_calls  = *reinterpret_cast<uint32_t*>(data_u8_ptr);
        data_u8_ptr += sizeof(uint32_t);

        n_data_chunks  = *reinterpret_cast<uint32_t*>(data_u8_ptr);
        data_u8_ptr   += sizeof(uint32_t);

        result_ptr->resize(n_api_calls);

        for (uint32_t n_api_call = 0;
                      n_api_call < n_api_calls;
                    ++n_api_call)
        {
            auto     current_api_call_func   = APIInterceptor::APIFunction::APIFUNCTION_UNKNOWN;
            auto     current_api_call_ptr    = &result_ptr->at(n_api_call);
            uint32_t n_current_api_call_args = 0;

            current_api_call_func  = *reinterpret_cast<const APIInterceptor::APIFunction*>(data_u8_ptr);
            data_u8_ptr           += sizeof(APIInterceptor::APIFunction);

            n_current_api_call_args  = *reinterpret_cast<const uint32_t*>(data_u8_ptr);
            data_u8_ptr             += sizeof(uint32_t);

            current_api_call_ptr->arg_vec.resize(n_current_api_call_args);

            for (uint32_t n_api_call_arg = 0;
                          n_api_call_arg < n_current_api_call_args;
                        ++n_api_call_arg)
            {
                data_u8_ptr += current_api_call_ptr->arg_vec.at(n_api_call_arg).deserialize_from_u8_ptr(data_u8_ptr);
            }

            {
                APIInterceptor::APIFunctionArgument returned_value;

                data_u8_ptr += returned_value.deserialize_from_u8_ptr(data_u8_ptr);

                if (returned_value.type != APIInterceptor::APIFunctionArgumentType::UNKNOWN)
                {
                    current_api_call_ptr->returned_value.reset(
                        new APIInterceptor::APIFunctionArgument(returned_value)
                    );
                }
            }

            current_api_call_ptr->func = current_api_call_func;
        }
    }
end:
    if (file_handle != nullptr)
    {
        ::fclose(file_handle);
    }

    return result_ptr;
}