/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "capture/api_dump_loader/api_info.h"
#include "capture/api_dump_loader/call_describer_set.h"
#include "capture/api_dump_loader/d3d7_call_describer.h"
#include "capture/api_dump_loader/d3d8_call_describer.h"
#include "capture/api_dump_loader/gl_call_describer.h"

Capture::APIDumpLoader::CallDescriberSet::CallDescriberSet()
{
    m_describer_ptr_vec.emplace_back(new D3D7CallDescriber() );
    m_describer_ptr_vec.emplace_back(new D3D8CallDescriber() );
    m_describer_ptr_vec.emplace_back(new GLCallDescriber() );
}

Capture::APIDumpLoader::CallClass Capture::APIDumpLoader::CallDescriberSet::describe(const DumpedAPICall& in_call)
{
    const APIGroup group  = get_api_group(in_call.func);
    CallClass      result = CallClass::STATE;

    for (const auto& describer_ptr : m_describer_ptr_vec)
    {
        if (describer_ptr->get_group() == group)
        {
            result = describer_ptr->describe(in_call);

            break;
        }
    }

    return result;
}

Capture::APIDumpLoader::CallClass Capture::APIDumpLoader::CallDescriberSet::get_function_class(const APIInterceptor::APIFunction& in_function)
{
    const APIGroup group  = get_api_group(in_function);
    CallClass      result = CallClass::STATE;

    switch (group)
    {
        case APIGroup::D3D7:
        {
            result = D3D7CallDescriber::get_function_class(in_function);

            break;
        }

        case APIGroup::D3D8:
        {
            result = D3D8CallDescriber::get_function_class(in_function);

            break;
        }

        case APIGroup::GL:
        {
            result = GLCallDescriber::get_function_class(in_function);

            break;
        }

        default:
        {
            break;
        }
    }

    return result;
}
