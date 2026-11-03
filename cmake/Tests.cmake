# The tests.
if (APIINTERCEPTOR_BUILD_TESTS)
    add_subdirectory(deps/gtest)

    file(GLOB APIInterceptorTestsSources CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/src/Tests/*.cpp")

    list(FILTER APIInterceptorTestsSources EXCLUDE REGEX ".*/fixtures\.cpp$")

    # Where the data files of the tests are, and the names the tests use: shared with a project which builds on this one.
    add_library(APIInterceptorTestSupport STATIC "${APIInterceptor_SOURCE_DIR}/src/Tests/fixtures.cpp"
                                                 "${APIInterceptor_SOURCE_DIR}/src/Tests/fixtures.h")

    target_compile_definitions(APIInterceptorTestSupport PUBLIC APIINTERCEPTOR_TESTS_DATA_DIR="${APIInterceptor_SOURCE_DIR}/src/Tests/data")
    target_include_directories(APIInterceptorTestSupport PUBLIC "${APIInterceptor_SOURCE_DIR}/src/Tests")

    # Sources under test which are not part of a library.
    add_executable(APIInterceptorTests ${APIInterceptorTestsSources}
                                       "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/call_context.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/call_walker.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/frame_pacer.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/gl_index_replayer.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/gl_replay_context.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/object_remapper.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Common/api_call_gate.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Common/callback_registry.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Common/callbacks.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Common/data_chunk_store.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Common/memory_chunk.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/buffer_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/buffer_mapping_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/client_array_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/param_counts.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/pixel_store_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/string_array_chunk.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/string_chunk.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/texture_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/utils.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/WGL/utils.cpp")

    target_include_directories(APIInterceptorTests PRIVATE "${APIInterceptor_SOURCE_DIR}/src"
                                                           "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL")
    target_link_libraries(APIInterceptorTests gtest_main APIInterceptorTestSupport APIDumpLoader ReplayEngineDLL D3D7Utils D3D8Utils InjectionLauncher)

    enable_testing()
    add_test(NAME APIInterceptorTests COMMAND APIInterceptorTests)
endif()
