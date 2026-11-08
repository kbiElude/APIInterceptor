/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Keeps the state of the GL context at the start of a frame that is executed twice, and puts it back before the second execution, so that the second starts where the
 * first did. The state is that of the attribute stacks (glPushAttrib and glPushClientAttrib with all the bits: enables, bindings, the current color, the viewport, the
 * pixel store, the arrays and so on), and the matrices, which the attribute stacks do not hold: the model-view and the projection matrix, and the texture matrix of each
 * unit. What the objects hold (the pixels of a texture, a list that was defined) is not state and is not put back.
 */
#ifndef REPLAYENGINEDLL_GL_STATE_SAVER_H
#define REPLAYENGINEDLL_GL_STATE_SAVER_H

#include <array>
#include <functional>
#include <stdint.h>
#include <vector>

namespace Replay
{
    namespace ReplayEngineDLL
    {
        class GlStateSaver
        {
        public:
            /* The way to the functions of GL by name (those of opengl32.dll and of the driver). */
            typedef std::function<void*(const char*)> ResolveFunc;

            explicit GlStateSaver(ResolveFunc in_resolve_func);

            /* True after save(), until restore() takes the state back. */
            bool has_saved_state() const;

            /* Puts back the state that save() found, and lets go of it. Does nothing if none is held, or if no context is current. */
            void restore();

            /* Remembers the state of the current context. A state that is still held (the frame that saved it failed, and nobody took it back) is popped first, so that
             * the stacks do not fill; that puts it back, and the state of then is what is kept. Does nothing if no context is current.
             */
            void save();

        private:
            typedef std::array<float, 16> Matrix;

            /* The matrices, and which of them the next call of a matrix function is about. */
            struct SavedMatrices
            {
                int32_t             active_texture_unit = 0; /* GL_TEXTURE0 + the unit                                       */
                int32_t             matrix_mode         = 0;
                Matrix              modelview_f32mat    = {};
                Matrix              projection_f32mat   = {};
                std::vector<Matrix> texture_f32mat_vec;      /* the unit 0 first; one only if the driver has no multitexture */
            };

            /* Pops the attribute stacks, which puts back what they hold. */
            void pop_attributes();

            bool          m_has_saved_state;
            SavedMatrices m_matrices;
            ResolveFunc   m_resolve_func;
        };
    }
}

#endif /* REPLAYENGINEDLL_GL_STATE_SAVER_H */
