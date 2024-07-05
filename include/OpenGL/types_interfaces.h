/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef AI_TYPES_INTERFACES_H
#define AI_TYPES_INTERFACES_H

namespace OpenGL
{
    class IContext
    {
    public:
        virtual ~IContext()
        {
            /* Stub */
        }

        virtual const OpenGL::DispatchTable*    get_dispatch_table      () const = 0;
        virtual const std::vector<std::string>& get_supported_extensions() const = 0;
    };
};

#endif /* AI_TYPES_INTERFACES_H */