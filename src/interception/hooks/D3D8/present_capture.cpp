/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/common/argument_factory.h"
#include "interception/hooks/D3D8/present_capture.h"
#include <algorithm>

void Interception::Hooks::D3D8::PresentCapture::create_arguments(APIInterceptor::APIFunctionArgument* out_arguments_ptr,
                                                                 const RECT*                          in_source_rect_ptr,
                                                                 const RECT*                          in_dest_rect_ptr,
                                                                 const RGNDATA*                       in_dirty_region_ptr)
{
    constexpr uint32_t MAX_N_RECTS = 4096; /* sanity limit */

    const uint8_t* dirty_rects_ptr = nullptr;
    uint32_t       n_dirty_rects   = 0;

    if (in_dirty_region_ptr != nullptr)
    {
        dirty_rects_ptr = reinterpret_cast<const uint8_t*>(in_dirty_region_ptr->Buffer);
        n_dirty_rects   = std::min<uint32_t>(in_dirty_region_ptr->rdh.nCount,
                                             MAX_N_RECTS);
    }

    out_arguments_ptr[0] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_source_rect_ptr,
                                                                                      static_cast<uint32_t>(sizeof(RECT) ));
    out_arguments_ptr[1] = Interception::Hooks::Common::ArgumentFactory::create_chunk(in_dest_rect_ptr,
                                                                                      static_cast<uint32_t>(sizeof(RECT) ));
    out_arguments_ptr[2] = Interception::Hooks::Common::ArgumentFactory::create_chunk(dirty_rects_ptr,
                                                                                      n_dirty_rects * static_cast<uint32_t>(sizeof(RECT) ));
}
