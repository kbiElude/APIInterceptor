/* API Dumper (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#if !defined(APIDUMPER_H)
#define APIDUMPER_H

#include <memory>

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
        APIInterceptor::APIFunction         api_func      = APIInterceptor::APIFunction::APIFUNCTION_UNKNOWN;
        APIInterceptor::APIFunctionArgument args[10]      {};
        uint32_t                            n_args        = 0;
        APIInterceptor::APIFunctionArgument returned_value{};
    };

    /* Private funcs */
    APIDumper();

    bool init();

    static void on_post_callback(APIInterceptor::APIFunction                in_api_func,
                                 void*                                      in_user_arg_ptr,
                                 const APIInterceptor::APIFunctionArgument* in_returned_value_ptr);
    static void on_pre_callback (APIInterceptor::APIFunction                in_api_func,
                                 uint32_t                                   in_n_args,
                                 const APIInterceptor::APIFunctionArgument* in_args_ptr,
                                 void*                                      in_user_arg_ptr,
                                 bool*                                      out_should_pass_through_ptr);

    /* Private vars */
    std::vector<DumpedAPICall> m_dumped_api_call_vec;
};

#endif /* APIDUMPER_H */