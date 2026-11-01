/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Turns an argument of a D3D8 call into an API call argument (see D3D8/argument_capture_selector.h).
 */
#ifndef D3D8_ARGUMENT_CAPTURE_H
#define D3D8_ARGUMENT_CAPTURE_H

#include "Interception/Hooks/D3D8/argument_capture_selector.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D8
        {
            template<typename T>
            struct ArgumentCapture : public ArgumentCaptureSelector<T, Interception::Core::D3D8Utils::ArgumentCategoryOf<T>::value>
            {
                /* Stub */
            };
        }
    }
}

#endif /* D3D8_ARGUMENT_CAPTURE_H */
