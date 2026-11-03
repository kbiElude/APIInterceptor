/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Interception/Hooks/Common/primitive_utils.h"

uint32_t Interception::Hooks::Common::get_n_vertices(const PrimitiveType& in_primitive_type,
                                                     const uint32_t&      in_primitive_count)
{
    constexpr uint32_t LINE_N_VERTICES                 = 2;
    constexpr uint32_t LINE_STRIP_N_EXTRA_VERTICES     = 1; /* strips and fans share vertices between primitives */
    constexpr uint32_t TRIANGLE_N_VERTICES             = 3;
    constexpr uint32_t TRIANGLE_STRIP_N_EXTRA_VERTICES = 2;

    uint32_t result = 0;

    switch (in_primitive_type)
    {
        case PrimitiveType::POINT_LIST:
        {
            result = in_primitive_count;

            break;
        }

        case PrimitiveType::LINE_LIST:
        {
            result = in_primitive_count * LINE_N_VERTICES;

            break;
        }

        case PrimitiveType::LINE_STRIP:
        {
            result = in_primitive_count + LINE_STRIP_N_EXTRA_VERTICES;

            break;
        }

        case PrimitiveType::TRIANGLE_LIST:
        {
            result = in_primitive_count * TRIANGLE_N_VERTICES;

            break;
        }

        case PrimitiveType::TRIANGLE_FAN:
        case PrimitiveType::TRIANGLE_STRIP:
        {
            result = in_primitive_count + TRIANGLE_STRIP_N_EXTRA_VERTICES;

            break;
        }

        default:
        {
            break;
        }
    }

    return result;
}
