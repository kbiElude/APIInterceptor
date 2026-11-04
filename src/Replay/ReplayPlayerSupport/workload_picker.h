/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYPLAYERSUPPORT_WORKLOAD_PICKER_H
#define REPLAYPLAYERSUPPORT_WORKLOAD_PICKER_H

#include <string>

namespace Replay
{
    namespace ReplayPlayerSupport
    {
        /* Lets the user choose the workload to replay, if the command line did not say which. */
        class WorkloadPicker
        {
        public:
            /* Shows the file selection window. Returns false if the user closes it without choosing a file. */
            static bool pick(std::string* out_path_ptr);
        };
    }
}

#endif /* REPLAYPLAYERSUPPORT_WORKLOAD_PICKER_H */
