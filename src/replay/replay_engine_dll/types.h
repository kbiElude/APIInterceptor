/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef REPLAYENGINEDLL_INTERNAL_TYPES_H
#define REPLAYENGINEDLL_INTERNAL_TYPES_H

#include <stddef.h>
#include <stdint.h>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        /* What replaying a call of an API function comes to. */
        enum class CallSupport
        {
            REPLAYED,   /* the call is made again                                                                              */
            SKIPPED,    /* the replay does without it: it only asks about the API, or the executor leaves it out               */
            UNSUPPORTED /* the replay has no code for it, and fails on it                                                      */
        };

        /* Where the arguments of a Direct3D 7 draw call are; NO_ARGUMENT for one the call does not have. */
        struct D3D7DrawLayout
        {
            static constexpr size_t NO_ARGUMENT = static_cast<size_t>(-1);

            size_t flags         = NO_ARGUMENT;
            size_t fvf           = NO_ARGUMENT;
            size_t n_indices     = NO_ARGUMENT;
            size_t n_vertices    = NO_ARGUMENT;
            size_t start_vertex  = NO_ARGUMENT;
            size_t type          = NO_ARGUMENT;
            size_t vertex_buffer = NO_ARGUMENT;
        };

        /* The values read by a D3D7DrawLayout; 0 or nullptr for what the layout does not have. */
        struct D3D7DrawValues
        {
            void*    device_ptr        = nullptr;
            uint32_t flags             = 0;
            uint32_t fvf               = 0;
            uint32_t n_indices         = 0;
            uint32_t n_vertices        = 0;
            uint32_t start_vertex      = 0;
            uint32_t type              = 0;
            void*    vertex_buffer_ptr = nullptr;
        };

        /* When the calls of a frame that is executed more than once are executed. */
        enum class ExecutionClass
        {
            AFTER_ALL,      /* once, after the last execution: what destroys objects, and the present */
            EVERY_TIME,     /* in every execution: state, draws, uploads                              */
            FIRST_TIME_ONLY /* once, in the first execution: what creates objects                     */
        };

        enum class LockKind
        {
            BOX,
            BUFFER,
            RECT
        };

        /* What a handle or an ID of the dumped process stands for. An object is told apart by the kind and the value it had
         * in the dump (see ObjectRemapper). NONE stands for a value which is not one of those.
         */
        enum class ObjectKind
        {
            ATTRIB_LOCATION,
            BUFFER,
            D3D7_OBJECT,
            D3D8_OBJECT,
            D3D8_PIXEL_SHADER,
            D3D8_STATE_BLOCK,
            D3D8_VERTEX_SHADER,
            DISPLAY_LIST,
            FRAG_DATA_LOCATION,
            FRAMEBUFFER,
            HDC,
            HGLRC,
            HWND,
            NONE,
            PROGRAM,
            PROGRAM_PIPELINE,
            PROGRAM_RESOURCE_INDEX,
            QUERY,
            RENDERBUFFER,
            SAMPLER,
            SHADER,
            SUBROUTINE_INDEX,
            SUBROUTINE_UNIFORM_LOCATION,
            SYNC,
            TEXTURE,
            TRANSFORM_FEEDBACK,
            UNIFORM_BLOCK_INDEX,
            UNIFORM_LOCATION,
            VERTEX_ARRAY
        };

        namespace GLRestore
        {
            enum class ArgumentCategory
            {
                FUNCTION,
                NUMBER,
                POINTER,
                STRING,
                STRING_ARRAY,
                SYNC
            };
        }
    }
}

#endif /* REPLAYENGINEDLL_INTERNAL_TYPES_H */
