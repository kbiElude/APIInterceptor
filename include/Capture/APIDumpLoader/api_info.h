/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * What the tools which read a workload need to know about the API functions: which API a function belongs to, and
 * whether it ends a frame.
 */
#ifndef APIDUMPLOADER_API_INFO_H
#define APIDUMPLOADER_API_INFO_H

#include "Common/types.h"
#include <vector>

namespace Capture
{
    namespace APIDumpLoader
    {
        enum class APIGroup
        {
            GDI32,
            GL,
            WGL,
            USER32,
            D3D8,

            UNKNOWN
        };

        APIGroup    get_api_group     (const APIInterceptor::APIFunction& in_function);
        const char* get_api_group_name(const APIGroup&                    in_group);

        /* Every group but Unknown, in the order of the enum. */
        const std::vector<APIGroup>& get_api_groups();

        /* True for calls which end a frame (a swapchain present). */
        bool is_frame_boundary(const APIInterceptor::APIFunction& in_function);

        bool parse_api_group_name(const char* in_name_ptr,
                                  APIGroup*   out_group_ptr);
    }
}

#endif /* APIDUMPLOADER_API_INFO_H */
