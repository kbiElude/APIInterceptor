/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "capture/api_dump_loader/api_info.h"
#include "capture/api_dump_loader/verbatim_state_effect_describer.h"
#include "common/macros.h"

Capture::APIDumpLoader::VerbatimStateEffectDescriber::VerbatimStateEffectDescriber(const APIGroup& in_group)
    :m_group(in_group)
{
    AI_ASSERT_ALWAYS(in_group == APIGroup::D3D7 ||
                     in_group == APIGroup::D3D8,
                     "A verbatim describer is made for Direct3D 7 or 8 only.");
}

Capture::APIDumpLoader::StateEffect Capture::APIDumpLoader::VerbatimStateEffectDescriber::describe(const DumpedAPICall& in_call)
{
    StateEffect result;

    AI_ASSERT_ALWAYS(get_api_group(in_call.func) == m_group,
                     "A call was given to the describer of another API.");

    result.kind = StateEffectKind::BARRIER;

    return result;
}

Capture::APIDumpLoader::APIGroup Capture::APIDumpLoader::VerbatimStateEffectDescriber::get_group() const
{
    return m_group;
}
