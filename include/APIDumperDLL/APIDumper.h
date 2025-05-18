/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(APIDUMPER_H)
#define APIDUMPER_H

#include <array>
#include <memory>
#include <thread>

/* Forward decls */
class                              APIDumper;
typedef std::unique_ptr<APIDumper> APIDumperUniquePtr;

class APIDumper
{
public:
    /* Public funcs */
    static APIDumperUniquePtr create();

    ~APIDumper();

private:
    /* Private types */
    struct DumpedAPICall
    {
        APIInterceptor::APIFunction         api_func         = APIInterceptor::APIFunction::APIFUNCTION_UNKNOWN;
        APIInterceptor::APIFunctionArgument args_in [14]     {};
        APIInterceptor::APIFunctionArgument args_out[14]     {};
        uint32_t                            n_args_in        = 0;
        uint32_t                            n_args_out       = 0;
        APIInterceptor::APIFunctionArgument returned_value{};
        std::thread::id                     thread_id;
    };

    struct DumpedSurface
    {
        std::array<uint32_t, 2>                extents_u32vec2;
        std::unique_ptr<std::vector<uint8_t> > u8_vec_ptr;
    };

    /* Private funcs */
    APIDumper();

    bool init();

    static void on_post_callback(APIInterceptor::APIFunction                in_api_func,
                                 void*                                      in_user_arg_ptr,
                                 uint32_t                                   in_n_args_out,
                                 const APIInterceptor::APIFunctionArgument* in_args_out_ptr,
                                 const APIInterceptor::APIFunctionArgument* in_returned_value_ptr);
    static void on_pre_callback (APIInterceptor::APIFunction                in_api_func,
                                 uint32_t                                   in_n_args_in,
                                 const APIInterceptor::APIFunctionArgument* in_args_in_ptr,
                                 void*                                      in_user_arg_ptr,
                                 bool*                                      out_should_pass_through_ptr);

    /* Private vars */
    std::vector<DumpedAPICall> m_dumped_api_call_vec;
    std::vector<DumpedSurface> m_dumped_surface_vec;
    bool                       m_dump_swapchain_on_present;
    uint32_t                   m_n_frames_dumped;
    uint32_t                   m_n_frames_to_dump;
};

#endif /* APIDUMPER_H */