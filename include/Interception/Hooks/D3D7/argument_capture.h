/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Turns an argument of a D3D7 call into an API call argument (see Common/argument_capture_selector.h).
 */
#ifndef D3D7_ARGUMENT_CAPTURE_H
#define D3D7_ARGUMENT_CAPTURE_H

#include "Interception/Core/D3D7Utils/types.h"
#include "Interception/Hooks/Common/argument_capture_selector.h"

namespace Interception
{
    namespace Hooks
    {
        namespace D3D7
        {
            /* What the common selector needs to know about D3D7. */
            struct CaptureTraits
            {
                template<typename S>
                using StructTraits = Interception::Core::D3D7Utils::StructTraits<S>;
            };

            template<typename T>
            struct ArgumentCapture : public Interception::Hooks::Common::ArgumentCaptureSelector<CaptureTraits,
                                                                                                 T,
                                                                                                 Interception::Core::D3D7Utils::ArgumentCategoryOf<T>::value>
            {
                /* Stub */
            };
        }
    }
}

#endif /* D3D7_ARGUMENT_CAPTURE_H */
