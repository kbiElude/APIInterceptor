# The tests.
if (APIINTERCEPTOR_BUILD_TESTS)
    add_subdirectory(deps/gtest)

    file(GLOB APIInterceptorTestsSources CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/src/tests/*.cpp")

    list(FILTER APIInterceptorTestsSources EXCLUDE REGEX ".*/(fixtures|replay_test_doubles).cpp$")

    # Where the data files of the tests are, and the names the tests use: shared with a project which builds on this one.
    add_library(APIInterceptorTestSupport STATIC "${APIInterceptor_SOURCE_DIR}/src/tests/fixtures.cpp"
                                                 "${APIInterceptor_SOURCE_DIR}/src/tests/fixtures.h"
                                                 "${APIInterceptor_SOURCE_DIR}/src/tests/replay_test_doubles.cpp"
                                                 "${APIInterceptor_SOURCE_DIR}/src/tests/replay_test_doubles.h")

    target_link_libraries(APIInterceptorTestSupport PUBLIC ReplayEngineCore)

    target_compile_definitions(APIInterceptorTestSupport PUBLIC APIINTERCEPTOR_TESTS_DATA_DIR="${APIInterceptor_SOURCE_DIR}/src/tests/data")
    target_include_directories(APIInterceptorTestSupport PUBLIC "${APIInterceptor_SOURCE_DIR}/src/Tests")

    # Sources under test which are not part of a library.
    add_executable(APIInterceptorTests ${APIInterceptorTestsSources}
                                       "${APIInterceptor_SOURCE_DIR}/src/common/api_call_gate.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/common/callback_registry.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/common/callbacks.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/common/data_chunk_store.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/common/memory_chunk.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/OpenGL/buffer_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/OpenGL/buffer_mapping_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/OpenGL/client_array_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/OpenGL/param_counts.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/OpenGL/pixel_store_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/OpenGL/string_array_chunk.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/OpenGL/string_chunk.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/OpenGL/texture_manager.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/OpenGL/utils.cpp"
                                       "${APIInterceptor_SOURCE_DIR}/src/interception/hooks/WGL/utils.cpp")

    target_include_directories(APIInterceptorTests PRIVATE "${APIInterceptor_SOURCE_DIR}/src"
                                                           "${APIInterceptor_SOURCE_DIR}/src/replay/replay_engine_dll")
    target_link_libraries(APIInterceptorTests gtest_main APIInterceptorTestSupport APIDumpLoader HooksCommon ReplayEngineCore ReplayEngineDLL D3D7Utils D3D8Utils InjectionLauncher)

    # Direct3D 7 is 32-bit: the program which makes every kind of draw is for the captures of it.
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        add_executable(D3D7DrawKinds "${APIInterceptor_SOURCE_DIR}/src/tests/programs/d3d7_draw_kinds.cpp")

        target_include_directories(D3D7DrawKinds PRIVATE "${APIInterceptor_SOURCE_DIR}/include")
        target_link_libraries     (D3D7DrawKinds user32)
    endif()

    enable_testing()
    add_test(NAME APIInterceptorTests COMMAND APIInterceptorTests)
endif()
