/* VKGL (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef VKGL_CONVERTERS_H
#define VKGL_CONVERTERS_H

#include "Interception/Hooks/OpenGL/types.h"


namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            namespace Converters
            {
                void convert(const Interception::Hooks::OpenGL::GetSetArgumentType& in_src_type,
                             const void*                                            in_vals_ptr,
                             const uint32_t&                                        in_n_vals,
                             const Interception::Hooks::OpenGL::GetSetArgumentType& in_dst_type,
                             void*                                                  out_result_ptr);
            }
        }
    }
}

#endif /* VKGL_CONVERTERS_H */