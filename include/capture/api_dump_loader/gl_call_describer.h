/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Describes the calls of OpenGL. Calls between glNewList and glEndList make the list and are state.
 */
#ifndef APIDUMPLOADER_GL_CALL_DESCRIBER_H
#define APIDUMPLOADER_GL_CALL_DESCRIBER_H

#include "capture/api_dump_loader/i_call_describer.h"

namespace Capture
{
    namespace APIDumpLoader
    {
        class GLCallDescriber : public ICallDescriber
        {
        public:
            GLCallDescriber();

            CallClass describe(const DumpedAPICall& in_call) override;
            APIGroup  get_group() const override;

            /* Whether a display list is being recorded: between glNewList and glEndList. */
            bool is_recording() const;

            /* The class of the function outside a recorded list. */
            static CallClass get_function_class(const APIInterceptor::APIFunction& in_function);

        private:
            bool m_is_recording; /* between glNewList and glEndList */
        };
    }
}

#endif /* APIDUMPLOADER_GL_CALL_DESCRIBER_H */
