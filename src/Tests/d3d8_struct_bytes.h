/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Builds the bytes in which the dumper stores D3D8 structures, for the tests.
 */
#ifndef TESTS_D3D8_STRUCT_BYTES_H
#define TESTS_D3D8_STRUCT_BYTES_H

#include "Interception/Hooks/D3D8/types.h"
#include <stddef.h>
#include <stdint.h>
#include <vector>

namespace Tests
{
    class D3D8StructBytes
    {
    public:
        static std::vector<uint8_t> build_matrix(const Interception::Hooks::D3D8::D3DMATRIX& in_matrix);

        /* 800x600 X8R8G8B8, two back buffers, a D24S8 depth buffer; the window is as wide as the pointers (4 or 8 bytes) of
         * the dumped process.
         */
        static std::vector<uint8_t> build_present_parameters(const size_t& in_pointer_n_bytes);

        static std::vector<uint8_t> build_viewport(const Interception::Hooks::D3D8::D3DVIEWPORT8& in_viewport);
    };
}

#endif /* TESTS_D3D8_STRUCT_BYTES_H */
