/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the tracking of mapped buffers, and of what is handed over to the GPU by unmapping and flushing them.
 */
#include <gtest/gtest.h>
#include "interception/hooks/OpenGL/buffer_mapping_manager.h"
#include "interception/hooks/OpenGL/types.h"

TEST(BufferMappingManager, UnmappingHandsOverTheWholeMappedRange)
{
    uint8_t                  memory_u8vec64[64] = {};
    Interception::Hooks::OpenGL::BufferMappingManager   mappings;

    mappings.on_buffer_mapped(7,
                              memory_u8vec64 + 16,
                              16,
                              32,
                              GL_MAP_WRITE_BIT);

    EXPECT_TRUE(mappings.is_mapped(7) );

    const auto region = mappings.get_unmap_region(7);

    EXPECT_EQ(region.data_ptr,
              memory_u8vec64 + 16);
    EXPECT_EQ(region.n_bytes,
              32u);

    mappings.on_buffer_unmapped(7);

    EXPECT_FALSE(mappings.is_mapped(7) );
    EXPECT_EQ(mappings.get_unmap_region(7).n_bytes,
              0u);
}

TEST(BufferMappingManager, ExplicitFlushHandsOverOnlyTheFlushedRange)
{
    uint8_t                memory_u8vec32[32] = {};
    Interception::Hooks::OpenGL::BufferMappingManager mappings;

    mappings.on_buffer_mapped(3,
                              memory_u8vec32,
                              0,
                              32,
                              GL_MAP_WRITE_BIT | GL_MAP_FLUSH_EXPLICIT_BIT);

    /* Unmapping hands nothing over: the flushed ranges were. */
    EXPECT_EQ(mappings.get_unmap_region(3).n_bytes,
              0u);

    const auto flush_region = mappings.get_flush_region(3,
                                                        8,
                                                        8);

    EXPECT_EQ(flush_region.data_ptr,
              memory_u8vec32 + 8);
    EXPECT_EQ(flush_region.n_bytes,
              8u);

    /* Outside of the mapping. */
    EXPECT_EQ(mappings.get_flush_region(3,
                                        28,
                                        8).n_bytes,
              0u);
}

TEST(BufferMappingManager, FlushingAMappingWhichIsNotExplicitHandsOverNothing)
{
    uint8_t                memory_u8vec32[32] = {};
    Interception::Hooks::OpenGL::BufferMappingManager mappings;

    mappings.on_buffer_mapped(3,
                              memory_u8vec32,
                              0,
                              32,
                              GL_MAP_WRITE_BIT);

    EXPECT_EQ(mappings.get_flush_region(3,
                                        0,
                                        8).n_bytes,
              0u);
}

TEST(BufferMappingManager, ReadOnlyMappingsAreNotWrittenBack)
{
    uint8_t                memory_u8vec16[16] = {};
    Interception::Hooks::OpenGL::BufferMappingManager mappings;

    mappings.on_buffer_mapped(1,
                              memory_u8vec16,
                              0,
                              16,
                              GL_MAP_READ_BIT);

    EXPECT_EQ(mappings.get_unmap_region(1).n_bytes,
              0u);
    EXPECT_EQ(mappings.get_initial_region(1).n_bytes,
              16u);
}

TEST(BufferMappingManager, InvalidatingMappingsHaveNoInitialContents)
{
    uint8_t                memory_u8vec16[16] = {};
    Interception::Hooks::OpenGL::BufferMappingManager mappings;

    mappings.on_buffer_mapped(1,
                              memory_u8vec16,
                              0,
                              16,
                              GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_RANGE_BIT);

    EXPECT_EQ(mappings.get_initial_region(1).n_bytes,
              0u);
    EXPECT_EQ(mappings.get_unmap_region(1).n_bytes,
              16u);
}

TEST(BufferMappingManager, FailedMapsAndDeletedBuffersLeaveNothingBehind)
{
    uint8_t                memory_u8vec16[16] = {};
    Interception::Hooks::OpenGL::BufferMappingManager mappings;

    mappings.on_buffer_mapped(5,
                              nullptr,
                              0,
                              16,
                              GL_MAP_WRITE_BIT);

    EXPECT_FALSE(mappings.is_mapped(5) );

    mappings.on_buffer_mapped(6,
                              memory_u8vec16,
                              0,
                              16,
                              GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT);

    EXPECT_TRUE(mappings.is_persistent(6) );

    mappings.on_buffer_deleted(6);

    EXPECT_FALSE(mappings.is_mapped(6) );
    EXPECT_FALSE(mappings.is_persistent(6) );
}

TEST(BufferMappingManager, AccessTokensStandForMapFlags)
{
    EXPECT_EQ(Interception::Hooks::OpenGL::BufferMappingManager::get_flags_for_access(GL_READ_ONLY),
              static_cast<uint32_t>(GL_MAP_READ_BIT) );
    EXPECT_EQ(Interception::Hooks::OpenGL::BufferMappingManager::get_flags_for_access(GL_WRITE_ONLY),
              static_cast<uint32_t>(GL_MAP_WRITE_BIT) );
    EXPECT_EQ(Interception::Hooks::OpenGL::BufferMappingManager::get_flags_for_access(GL_READ_WRITE),
              static_cast<uint32_t>(GL_MAP_READ_BIT | GL_MAP_WRITE_BIT) );
}
