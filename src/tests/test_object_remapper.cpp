/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the mapping of the handles of a dumped process to the ones of the replay.
 */
#include <gtest/gtest.h>
#include "object_remapper.h"

TEST(ObjectRemapper, ZeroStandsForItself)
{
    Replay::ReplayEngineDLL::ObjectRemapper remapper;
    uint64_t                                live_value = 123;

    EXPECT_TRUE(remapper.get(Replay::ReplayEngineDLL::ObjectKind::HWND,
                             0,
                            &live_value) );
    EXPECT_EQ  (live_value,
                0u);
}

TEST(ObjectRemapper, KindsAreMappedApart)
{
    Replay::ReplayEngineDLL::ObjectRemapper remapper;
    uint64_t                                live_value = 0;

    remapper.add(Replay::ReplayEngineDLL::ObjectKind::HDC,
                 10,
                 20);

    EXPECT_TRUE (remapper.get(Replay::ReplayEngineDLL::ObjectKind::HDC,
                              10,
                             &live_value) );
    EXPECT_EQ   (live_value,
                 20u);
    EXPECT_FALSE(remapper.get(Replay::ReplayEngineDLL::ObjectKind::HWND,
                              10,
                             &live_value) );
}

TEST(ObjectRemapper, ARemovedOrClearedValueIsUnknown)
{
    Replay::ReplayEngineDLL::ObjectRemapper remapper;
    uint64_t                                live_value = 0;

    remapper.add   (Replay::ReplayEngineDLL::ObjectKind::HDC,
                    1,
                    2);
    remapper.add   (Replay::ReplayEngineDLL::ObjectKind::HDC,
                    3,
                    4);
    remapper.remove(Replay::ReplayEngineDLL::ObjectKind::HDC,
                    1);

    EXPECT_FALSE(remapper.get(Replay::ReplayEngineDLL::ObjectKind::HDC,
                              1,
                             &live_value) );

    remapper.clear();

    EXPECT_FALSE(remapper.get(Replay::ReplayEngineDLL::ObjectKind::HDC,
                              3,
                             &live_value) );
}

TEST(ObjectRemapper, ALiveValueIsFoundByTheDumpedOneItStandsFor)
{
    Replay::ReplayEngineDLL::ObjectRemapper remapper;
    uint64_t                                dumped_value = 0;

    remapper.add(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                 10,
                 20);
    remapper.add(Replay::ReplayEngineDLL::ObjectKind::BUFFER,
                 11,
                 20);

    /* The kind is told apart: a live buffer of 20 is not the texture of 20. */
    EXPECT_TRUE (remapper.find_dumped(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                                      20,
                                     &dumped_value) );
    EXPECT_EQ   (dumped_value,
                 10u);
    EXPECT_FALSE(remapper.find_dumped(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                                      21,
                                     &dumped_value) );
}

TEST(ObjectRemapper, WhatIsMappedAgainIsFoundByTheLiveValueItHasNow)
{
    Replay::ReplayEngineDLL::ObjectRemapper remapper;
    uint64_t                                dumped_value = 0;

    remapper.add(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                 10,
                 20);
    remapper.add(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                 10,
                 30);

    EXPECT_FALSE(remapper.find_dumped(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                                      20,
                                     &dumped_value) );
    EXPECT_TRUE (remapper.find_dumped(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                                      30,
                                     &dumped_value) );
    EXPECT_EQ   (dumped_value,
                 10u);
}
