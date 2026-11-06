/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * The table of methods of an object, as the hooks of the COM-based APIs patch it.
 */
#include <gtest/gtest.h>
#include "interception/hooks/common/vtable_registry.h"
#include <array>

/* A COM object is a pointer to a pointer to a table of functions. The functions are not called: their addresses only have to differ. */
struct FakeComObject
{
    void** vtable_ptr;
};

TEST(VTableRegistry, PatchedSlotsHoldTheHooksAndRememberTheOriginals)
{
    typedef std::array<Interception::Hooks::Common::HookEntry, 2> HookEntryArray;

    static void*          vtable_ptr_array[4] = {reinterpret_cast<void*>(0x1000), reinterpret_cast<void*>(0x1001), reinterpret_cast<void*>(0x1002), reinterpret_cast<void*>(0x1003)};
    FakeComObject         object              = {vtable_ptr_array};
    const HookEntryArray  hook_entry_array    = {{ {reinterpret_cast<void*>(0x2001), 1}, {reinterpret_cast<void*>(0x2002), 2} }};

    auto registry_ptr = Interception::Hooks::Common::VTableRegistry::get_ptr();

    ASSERT_TRUE(registry_ptr->patch_vtable(0xffff0001,
                                           4,
                                          &object,
                                           hook_entry_array.data(),
                                           static_cast<uint32_t>(hook_entry_array.size() ) ) );

    EXPECT_EQ(vtable_ptr_array[0], reinterpret_cast<void*>(0x1000) );
    EXPECT_EQ(vtable_ptr_array[1], reinterpret_cast<void*>(0x2001) );
    EXPECT_EQ(vtable_ptr_array[2], reinterpret_cast<void*>(0x2002) );
    EXPECT_EQ(vtable_ptr_array[3], reinterpret_cast<void*>(0x1003) );

    EXPECT_EQ(registry_ptr->get_original_function_ptr(&object, 1), reinterpret_cast<void*>(0x1001) );
    EXPECT_EQ(registry_ptr->get_original_function_ptr(&object, 2), reinterpret_cast<void*>(0x1002) );
    EXPECT_EQ(registry_ptr->get_original_function_ptr(&object, 0), nullptr); /* not hooked */
}

TEST(VTableRegistry, HooksWhichTheRuntimeOverwroteArePutBack)
{
    typedef std::array<Interception::Hooks::Common::HookEntry, 2> HookEntryArray;

    static void*          vtable_ptr_array[4] = {reinterpret_cast<void*>(0x3000), reinterpret_cast<void*>(0x3001), reinterpret_cast<void*>(0x3002), reinterpret_cast<void*>(0x3003)};
    FakeComObject         object              = {vtable_ptr_array};
    const HookEntryArray  hook_entry_array    = {{ {reinterpret_cast<void*>(0x4001), 1}, {reinterpret_cast<void*>(0x4002), 2} }};

    auto registry_ptr = Interception::Hooks::Common::VTableRegistry::get_ptr();

    registry_ptr->patch_vtable(0xffff0002,
                               4,
                              &object,
                               hook_entry_array.data(),
                               static_cast<uint32_t>(hook_entry_array.size() ) );

    /* The runtime puts a function of its own where the hook was. */
    vtable_ptr_array[1] = reinterpret_cast<void*>(0x5001);

    registry_ptr->repair_vtable(&object);

    EXPECT_EQ(vtable_ptr_array[1], reinterpret_cast<void*>(0x4001) ) << "the hook is back";
    EXPECT_EQ(vtable_ptr_array[2], reinterpret_cast<void*>(0x4002) ) << "what was not touched is left as it is";
    EXPECT_EQ(vtable_ptr_array[3], reinterpret_cast<void*>(0x3003) ) << "a slot which is not hooked is left alone";

    EXPECT_EQ(registry_ptr->get_original_function_ptr(&object, 1), reinterpret_cast<void*>(0x5001) ) << "the function the runtime put there is the original now";
    EXPECT_EQ(registry_ptr->get_original_function_ptr(&object, 2), reinterpret_cast<void*>(0x3002) );
}

TEST(VTableRegistry, RepairOfAnObjectWhichWasNeverPatchedChangesNothing)
{
    static void*  vtable_ptr_array[2] = {reinterpret_cast<void*>(0x6000), reinterpret_cast<void*>(0x6001)};
    FakeComObject object              = {vtable_ptr_array};

    Interception::Hooks::Common::VTableRegistry::get_ptr()->repair_vtable(&object);
    Interception::Hooks::Common::VTableRegistry::get_ptr()->repair_vtable(nullptr);

    EXPECT_EQ(vtable_ptr_array[0], reinterpret_cast<void*>(0x6000) );
    EXPECT_EQ(vtable_ptr_array[1], reinterpret_cast<void*>(0x6001) );
}
