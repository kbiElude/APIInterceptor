/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Turns an argument of a D3D8 call into an API call argument (see D3D8/argument_capture_selector.h).
 */
#ifndef D3D8_ARGUMENT_CAPTURE_H
#define D3D8_ARGUMENT_CAPTURE_H

#include "D3D8/argument_capture_selector.h"

namespace D3D8
{
    template<typename T>
    struct ArgumentCapture : public ArgumentCaptureSelector<T, Utils::ArgumentCategoryOf<T>::value>
    {
        /* Stub */
    };
}

#endif /* D3D8_ARGUMENT_CAPTURE_H */
