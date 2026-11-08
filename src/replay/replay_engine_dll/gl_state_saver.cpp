/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "gl_state_saver.h"
#include <algorithm>
#include <Windows.h>

namespace
{
    typedef void (APIENTRY* PFNACTIVETEXTUREPROC)   (unsigned int);
    typedef void (APIENTRY* PFNGETFLOATVPROC)       (unsigned int, float*);
    typedef void (APIENTRY* PFNGETINTEGERVPROC)     (unsigned int, int*);
    typedef void (APIENTRY* PFNLOADMATRIXFPROC)     (const float*);
    typedef void (APIENTRY* PFNMATRIXMODEPROC)      (unsigned int);
    typedef void (APIENTRY* PFNPOPATTRIBPROC)       ();
    typedef void (APIENTRY* PFNPOPCLIENTATTRIBPROC) ();
    typedef void (APIENTRY* PFNPUSHATTRIBPROC)      (unsigned int);
    typedef void (APIENTRY* PFNPUSHCLIENTATTRIBPROC)(unsigned int);

    constexpr unsigned int ACTIVE_TEXTURE         = 0x84E0;
    constexpr unsigned int ALL_ATTRIB_BITS        = 0x000FFFFF;
    constexpr unsigned int CLIENT_ALL_ATTRIB_BITS = 0xFFFFFFFF;
    constexpr unsigned int MATRIX_MODE            = 0x0BA0;
    constexpr unsigned int MAX_TEXTURE_UNITS      = 0x84E2;
    constexpr unsigned int MODELVIEW              = 0x1700;
    constexpr unsigned int MODELVIEW_MATRIX       = 0x0BA6;
    constexpr unsigned int PROJECTION             = 0x1701;
    constexpr unsigned int PROJECTION_MATRIX      = 0x0BA7;
    constexpr unsigned int TEXTURE                = 0x1702;
    constexpr unsigned int TEXTURE0               = 0x84C0;
    constexpr unsigned int TEXTURE_MATRIX         = 0x0BA8;

    /* More units than this are not kept: a program of the age of fixed-function GL does not use them. */
    constexpr int MAX_N_SAVED_TEXTURE_UNITS = 8;
}

Replay::ReplayEngineDLL::GlStateSaver::GlStateSaver(ResolveFunc in_resolve_func)
    :m_has_saved_state(false),
     m_resolve_func   (in_resolve_func)
{
    /* Stub */
}

bool Replay::ReplayEngineDLL::GlStateSaver::has_saved_state() const
{
    return m_has_saved_state;
}

void Replay::ReplayEngineDLL::GlStateSaver::pop_attributes()
{
    const auto pop_attrib_func_ptr        = reinterpret_cast<PFNPOPATTRIBPROC>      (m_resolve_func("glPopAttrib") );
    const auto pop_client_attrib_func_ptr = reinterpret_cast<PFNPOPCLIENTATTRIBPROC>(m_resolve_func("glPopClientAttrib") );

    if (pop_attrib_func_ptr        != nullptr &&
        pop_client_attrib_func_ptr != nullptr)
    {
        pop_attrib_func_ptr       ();
        pop_client_attrib_func_ptr();
    }
}

void Replay::ReplayEngineDLL::GlStateSaver::restore()
{
    const auto active_texture_func_ptr = reinterpret_cast<PFNACTIVETEXTUREPROC>(m_resolve_func("glActiveTexture") );
    const auto load_matrix_func_ptr    = reinterpret_cast<PFNLOADMATRIXFPROC>   (m_resolve_func("glLoadMatrixf") );
    const auto matrix_mode_func_ptr    = reinterpret_cast<PFNMATRIXMODEPROC>    (m_resolve_func("glMatrixMode") );

    if (m_has_saved_state == false)
    {
        goto end;
    }

    m_has_saved_state = false;

    if (::wglGetCurrentContext() == nullptr ||
        load_matrix_func_ptr     == nullptr ||
        matrix_mode_func_ptr     == nullptr)
    {
        goto end;
    }

    /* The stacks first: they hold the matrix mode and the unit that the loads below change, which are set again last. */
    pop_attributes();

    matrix_mode_func_ptr(MODELVIEW);
    load_matrix_func_ptr(m_matrices.modelview_f32mat.data() );

    matrix_mode_func_ptr(PROJECTION);
    load_matrix_func_ptr(m_matrices.projection_f32mat.data() );

    matrix_mode_func_ptr(TEXTURE);

    for (size_t n_unit = 0;
                n_unit < m_matrices.texture_f32mat_vec.size();
              ++n_unit)
    {
        if (active_texture_func_ptr != nullptr)
        {
            active_texture_func_ptr(TEXTURE0 + static_cast<unsigned int>(n_unit) );
        }

        load_matrix_func_ptr(m_matrices.texture_f32mat_vec.at(n_unit).data() );
    }

    if (active_texture_func_ptr != nullptr)
    {
        active_texture_func_ptr(static_cast<unsigned int>(m_matrices.active_texture_unit) );
    }

    matrix_mode_func_ptr(static_cast<unsigned int>(m_matrices.matrix_mode) );

end:
    return;
}

void Replay::ReplayEngineDLL::GlStateSaver::save()
{
    const auto active_texture_func_ptr     = reinterpret_cast<PFNACTIVETEXTUREPROC>   (m_resolve_func("glActiveTexture") );
    const auto get_floatv_func_ptr         = reinterpret_cast<PFNGETFLOATVPROC>       (m_resolve_func("glGetFloatv") );
    const auto get_integerv_func_ptr       = reinterpret_cast<PFNGETINTEGERVPROC>     (m_resolve_func("glGetIntegerv") );
    const auto push_attrib_func_ptr        = reinterpret_cast<PFNPUSHATTRIBPROC>      (m_resolve_func("glPushAttrib") );
    const auto push_client_attrib_func_ptr = reinterpret_cast<PFNPUSHCLIENTATTRIBPROC>(m_resolve_func("glPushClientAttrib") );

    int n_units = 1;

    if (::wglGetCurrentContext()    == nullptr ||
        get_floatv_func_ptr         == nullptr ||
        get_integerv_func_ptr       == nullptr ||
        push_attrib_func_ptr        == nullptr ||
        push_client_attrib_func_ptr == nullptr)
    {
        goto end;
    }

    /* A state that is still held was never taken back (the frame that saved it failed): it is popped, so that the stacks do not fill, and the state of now is kept. */
    if (m_has_saved_state)
    {
        pop_attributes();
    }

    m_matrices = SavedMatrices();

    get_integerv_func_ptr(MATRIX_MODE,
                         &m_matrices.matrix_mode);
    get_floatv_func_ptr  (MODELVIEW_MATRIX,
                          m_matrices.modelview_f32mat.data() );
    get_floatv_func_ptr  (PROJECTION_MATRIX,
                          m_matrices.projection_f32mat.data() );

    /* A driver with multitexture has a texture matrix for each unit, which is read with the unit active. */
    if (active_texture_func_ptr != nullptr)
    {
        get_integerv_func_ptr(ACTIVE_TEXTURE,
                             &m_matrices.active_texture_unit);
        get_integerv_func_ptr(MAX_TEXTURE_UNITS,
                             &n_units);

        n_units = (std::min)((std::max)(n_units,
                                        1),
                             MAX_N_SAVED_TEXTURE_UNITS);
    }

    for (int n_unit = 0;
             n_unit < n_units;
           ++n_unit)
    {
        Matrix texture_matrix = {};

        if (active_texture_func_ptr != nullptr)
        {
            active_texture_func_ptr(TEXTURE0 + static_cast<unsigned int>(n_unit) );
        }

        get_floatv_func_ptr(TEXTURE_MATRIX,
                            texture_matrix.data() );

        m_matrices.texture_f32mat_vec.push_back(texture_matrix);
    }

    if (active_texture_func_ptr != nullptr)
    {
        active_texture_func_ptr(static_cast<unsigned int>(m_matrices.active_texture_unit) );
    }

    push_attrib_func_ptr       (ALL_ATTRIB_BITS);
    push_client_attrib_func_ptr(CLIENT_ALL_ATTRIB_BITS);

    m_has_saved_state = true;

end:
    return;
}
