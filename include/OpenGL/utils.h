/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_UTILS_H
#define AI_UTILS_H

#include "OpenGL/types.h"

namespace OpenGL
{
    namespace Utils
    {
        uint32_t get_n_bytes_for_type       (const GLenum&   in_type);
        uint32_t get_n_components_for_format(const GLenum&   in_format);
        uint32_t get_n_texture_data_bytes   (const uint32_t& in_width,
                                             const uint32_t& in_height,
                                             const uint32_t& in_depth,
                                             const GLenum&   in_format,
                                             const GLenum&   in_type);
    }
};

#endif /* AI_UTILS_H */