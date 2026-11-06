/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the tracking of the buffer bindings and of the sizes of buffers.
 */
#include <gtest/gtest.h>
#include "interception/hooks/OpenGL/buffer_manager.h"

TEST(BufferManager, NothingIsBoundInitially)
{
    Interception::Hooks::OpenGL::BufferManager manager;

    EXPECT_EQ(manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ARRAY_BUFFER),
              0u);
    EXPECT_EQ(manager.get_size(1),
              0u);
}

TEST(BufferManager, BindingsAreTrackedPerTarget)
{
    Interception::Hooks::OpenGL::BufferManager manager;

    manager.on_buffer_bound(Interception::Hooks::OpenGL::BufferBindingTarget::ARRAY_BUFFER,
                            7);
    manager.on_buffer_bound(Interception::Hooks::OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER,
                            8);

    EXPECT_EQ(manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ARRAY_BUFFER),
              7u);
    EXPECT_EQ(manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER),
              8u);
}

TEST(BufferManager, SizesAreNotLimitedTo32Bits)
{
    Interception::Hooks::OpenGL::BufferManager manager;

    manager.set_size(2,
                     6ull * 1024 * 1024 * 1024);

    EXPECT_EQ(manager.get_size(2),
              6ull * 1024 * 1024 * 1024);
}

TEST(BufferManager, DeletingABufferForgetsItAndUnbindsIt)
{
    Interception::Hooks::OpenGL::BufferManager manager;

    manager.set_size(5,
                     128);
    manager.on_buffer_bound(Interception::Hooks::OpenGL::BufferBindingTarget::ARRAY_BUFFER,
                            5);
    manager.on_buffer_bound(Interception::Hooks::OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER,
                            6);

    manager.on_buffer_deleted(5);

    EXPECT_EQ(manager.get_size(5),
              0u);
    EXPECT_EQ(manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ARRAY_BUFFER),
              0u);
    EXPECT_EQ(manager.get_bound_buffer(Interception::Hooks::OpenGL::BufferBindingTarget::ELEMENT_ARRAY_BUFFER),
              6u);
}
