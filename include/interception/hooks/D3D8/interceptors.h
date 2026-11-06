/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef D3D8_INTERCEPTORS_H
#define D3D8_INTERCEPTORS_H

namespace Interception
{
    namespace Hooks
    {
        namespace D3D8
        {
            /* Call after the interceptors are attached. Hooks D3D8 now if d3d8.dll is loaded, otherwise once it gets loaded. */
            void on_attach();

            /* Call before the interceptors are detached. */
            void on_detach();
        }
    }
}

#endif /* D3D8_INTERCEPTORS_H */
