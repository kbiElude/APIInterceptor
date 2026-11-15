/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/core/D3D8Utils/shader_tokens.h"
#include <algorithm>

uint32_t Interception::Core::D3D8Utils::get_n_shader_function_tokens(const DWORD* in_function_ptr)
{
    constexpr uint32_t D3DSI_COMMENTSIZE_MASK  = 0x7fff0000;
    constexpr uint32_t D3DSI_COMMENTSIZE_SHIFT = 16;
    constexpr uint32_t D3DSI_INSTLENGTH_MASK   = 0x0f000000;
    constexpr uint32_t D3DSI_INSTLENGTH_SHIFT  = 24;
    constexpr uint32_t D3DSI_OPCODE_MASK       = 0x0000ffff;
    constexpr uint32_t D3DSIO_COMMENT          = 0x0000fffe;
    constexpr uint32_t D3DSIO_END              = 0x0000ffff;
    constexpr uint32_t MAX_N_TOKENS            = 16384; /* sanity limit */

    bool           is_done      = (in_function_ptr == nullptr);
    uint32_t       n_tokens     = (in_function_ptr != nullptr) ? 1 /* the version token */
                                                               : 0;

    while (is_done == false      &&
           n_tokens < MAX_N_TOKENS)
    {
        const DWORD token = in_function_ptr[n_tokens];

        if ((token & D3DSI_OPCODE_MASK) == D3DSIO_END)
        {
            /* D3DSIO_END */
            n_tokens++;
            is_done = true;
        }
        else
        if ((token & D3DSI_OPCODE_MASK) == D3DSIO_COMMENT)
        {
            /* D3DSIO_COMMENT: the size is in the token. */
            n_tokens += 1 + ((token & D3DSI_COMMENTSIZE_MASK) >> D3DSI_COMMENTSIZE_SHIFT);
        }
        else
        {
            n_tokens += 1 + ((token & D3DSI_INSTLENGTH_MASK) >> D3DSI_INSTLENGTH_SHIFT);
        }
    }

    return std::min<uint32_t>(n_tokens,
                              MAX_N_TOKENS);
}

uint32_t Interception::Core::D3D8Utils::get_n_vertex_declaration_tokens(const DWORD* in_declaration_ptr)
{
    constexpr uint32_t D3DVSD_CONSTCOUNT_MASK  = 0x1e000000;
    constexpr uint32_t D3DVSD_CONSTCOUNT_SHIFT = 25;
    constexpr uint32_t D3DVSD_END              = 0xffffffff;
    constexpr uint32_t D3DVSD_TOKENTYPE_CONST  = 4;
    constexpr uint32_t D3DVSD_TOKENTYPE_SHIFT  = 29;
    constexpr uint32_t MAX_N_TOKENS            = 16384; /* sanity limit */
    constexpr uint32_t N_TOKENS_PER_CONSTANT   = 4;     /* a constant is a vector of four floats */

    bool           is_done      = (in_declaration_ptr == nullptr);
    uint32_t       n_tokens     = 0;

    while (is_done == false      &&
           n_tokens < MAX_N_TOKENS)
    {
        const DWORD token = in_declaration_ptr[n_tokens];

        n_tokens++;

        if (token == D3DVSD_END)
        {
            is_done = true;
        }
        else
        if ((token >> D3DVSD_TOKENTYPE_SHIFT) == D3DVSD_TOKENTYPE_CONST)
        {
            n_tokens += ((token & D3DVSD_CONSTCOUNT_MASK) >> D3DVSD_CONSTCOUNT_SHIFT) * N_TOKENS_PER_CONSTANT;
        }
    }

    return std::min<uint32_t>(n_tokens,
                              MAX_N_TOKENS);
}
