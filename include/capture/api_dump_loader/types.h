/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The enums and small types of the loader of workloads.
 */
#ifndef APIDUMPLOADER_TYPES_H
#define APIDUMPLOADER_TYPES_H

#include <array>
#include <stdint.h>

namespace Capture
{
    namespace APIDumpLoader
    {
        enum class APIGroup
        {
            D3D7,
            D3D8,
            GDI32,
            GL,
            USER32,
            WGL,

            UNKNOWN
        };

        /* What a call does to the frames a replay makes (see ICallDescriber). */
        enum class CallClass
        {
            CONDITIONAL, /* content or state, by what it refers to (a display list call) */
            CONTENT,     /* draws, clears, copies, uploads, locks                        */
            STATE        /* everything else                                              */
        };

        /* What the next frame of the file came to. */
        enum class FrameFetch
        {
            CLEAN_END,
            DAMAGED_END, /* a frame which cannot be told to be one: nothing more can be read */
            SEGMENT
        };

        /* How a call acts on the state that dead frames carry from call to call (see IStateEffectDescriber). */
        enum class StateEffectKind
        {
            ASSIGN,   /* sets a piece of state whatever it was: only the last such call before a reader is needed */
            BARRIER,  /* may read or change anything: all earlier calls come first; selectors are unknown after it */
            ORDERED,  /* reads some domains and selectors, changes no tracked state: made in place               */
            RECORDED, /* inside a recorded list: changes no state yet, made in place                              */
            SELECT    /* chooses what later calls act on: only the choice in force at a user is needed           */
        };

        /* A piece of state, named exactly (no hashing: a collision would lose a call). */
        typedef std::array<uint32_t, 4> StateKey;

        /* What a call does to state. Domains and selectors are small numbers of the API describer: a domain is a bit of domain_mask, a selector a bit of selector_mask. */
        struct StateEffect
        {
            uint32_t        domain_mask    = 0;                       /* ASSIGN: the domain written; ORDERED: the domains read */
            StateKey        key            = {{0, 0, 0, 0}};          /* ASSIGN: the piece of state, without what selectors choose */
            StateEffectKind kind           = StateEffectKind::BARRIER;
            uint32_t        selector       = 0;                       /* SELECT: the selector, below 32 */
            uint32_t        selector_mask  = 0;                       /* ASSIGN, ORDERED: the selectors the call uses */
            uint64_t        selector_value = 0;                       /* SELECT: what is chosen */
        };
    }
}

#endif /* APIDUMPLOADER_TYPES_H */
