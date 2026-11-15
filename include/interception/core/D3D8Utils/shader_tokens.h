/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The length of the token streams that D3D8 shaders are given in. A stream does not say how long it is.
 */
#ifndef D3D8UTILS_SHADER_TOKENS_H
#define D3D8UTILS_SHADER_TOKENS_H

#include "interception/hooks/D3D8/types.h"

namespace Interception
{
    namespace Core
    {
        namespace D3D8Utils
        {
            /* Number of tokens of a vertex or pixel shader (version 1.x), the end token included. */
            uint32_t get_n_shader_function_tokens(const DWORD* in_function_ptr);

            /* Number of tokens of a vertex shader declaration, the end token included. */
            uint32_t get_n_vertex_declaration_tokens(const DWORD* in_declaration_ptr);
        }
    }
}

#endif /* D3D8UTILS_SHADER_TOKENS_H */
