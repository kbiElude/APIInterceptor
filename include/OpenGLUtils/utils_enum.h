/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_UTILS_ENUM_H
#define AI_UTILS_ENUM_H

#include "OpenGL/types.h"

namespace OpenGL
{
    namespace Utils
    {
        const char* get_raw_string_for_gl_bitfield(const OpenGL::BitfieldType& in_bitfield,
                                                   const GLenum&               in_enum);
        const char* get_raw_string_for_gl_enum    (const GLenum&               in_enum);
    }
};

#endif /* AI_UTILS_ENUM_H */