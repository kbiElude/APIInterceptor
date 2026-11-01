cmake_minimum_required (VERSION 3.10)
project (APIInterceptor)

option(APIINTERCEPTOR_BUILD_INTERCEPTOR "Build API interceptor projects"             ON)
option(APIINTERCEPTOR_BUILD_LIBS        "Build static libs (API Dump Loader)"        ON)
option(APIINTERCEPTOR_BUILD_TESTS       "Build automated tests"                      OFF)
option(APIINTERCEPTOR_BUILD_TOOLS       "Build tools (API Dumper, API Dump Printer)" ON)
option(APIINTERCEPTOR_DUMP_API_CALLS    "Dump API calls to text files (debugging)"   OFF)

# DO NOT MODIFY BELOW THIS LINE
configure_file("${APIInterceptor_SOURCE_DIR}/include/config.h.in" "${APIInterceptor_BINARY_DIR}/apitracer_config.h")

if (NOT APIINTERCEPTOR_BUILD_INTERCEPTOR AND APIINTERCEPTOR_BUILD_TOOLS)
    message(FATAL_ERROR "APIINTERCEPTOR_BUILD_TOOLS option requires APIINTERCEPTOR_BUILD_INTERCEPTOR option to be enabled.")
endif()

if (NOT APIINTERCEPTOR_BUILD_LIBS AND APIINTERCEPTOR_BUILD_TOOLS)
    message(FATAL_ERROR "APIINTERCEPTOR_BUILD_TOOLS option requires APIINTERCEPTOR_BUILD_LIBS option to be enabled.")
endif()

if (NOT APIINTERCEPTOR_BUILD_INTERCEPTOR AND APIINTERCEPTOR_BUILD_TESTS)
    message(FATAL_ERROR "APIINTERCEPTOR_BUILD_TESTS option requires APIINTERCEPTOR_BUILD_INTERCEPTOR option to be enabled.")
endif()

if (NOT APIINTERCEPTOR_BUILD_LIBS AND APIINTERCEPTOR_BUILD_TESTS)
    message(FATAL_ERROR "APIINTERCEPTOR_BUILD_TESTS option requires APIINTERCEPTOR_BUILD_LIBS option to be enabled.")
endif()

unset(CMAKE_DEBUG_POSTFIX CACHE)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif (MSVC)

set(CMAKE_INCLUDE_PATH             "${APIInterceptor_SOURCE_DIR}/include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${APIInterceptor_BINARY_DIR}/bin")

include_directories("${APIInterceptor_BINARY_DIR}"
                    "${APIInterceptor_SOURCE_DIR}/deps"
                    "${APIInterceptor_SOURCE_DIR}/include"
                    "${APIInterceptor_SOURCE_DIR}/deps/Khronos")

file(GLOB CommonIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Common/*.h")
file(GLOB CommonSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Common/*.cpp")

include(cmake/Interception.cmake)
include(cmake/Libraries.cmake)
include(cmake/Replay.cmake)
include(cmake/Tools.cmake)
include(cmake/Tests.cmake)
