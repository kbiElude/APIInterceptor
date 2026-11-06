/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_I_CONTEXT_H
#define AI_I_CONTEXT_H

namespace Interception
{
    namespace Hooks
    {
        namespace OpenGL
        {
            class IContext
            {
            public:
                virtual ~IContext()
                {
                    /* Stub */
                }

                virtual const Interception::Hooks::OpenGL::DispatchTable* get_dispatch_table      () const = 0;
                virtual const std::vector<std::string>&                   get_supported_extensions() const = 0;
            };
        }
    }
}

#endif /* AI_I_CONTEXT_H */