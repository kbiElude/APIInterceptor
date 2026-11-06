# The libraries of the capture as an installed package, for a project which does not build this one as a subproject:
#
#   cmake --install build_x64 --config Release --component Development --prefix <dir>
#
# and then, in the project, find_package(APIInterceptor) and link APIInterceptor::APIDumpLoader, ::D3D8Utils, ::InjectionLauncher (and
# what they need: ::Detours, ::Zstd). The package is a component of its own, so that the release which build.bat collects has none of it.
# The interceptor itself (the hooks, which are compiled into the DLL that hooks) is for a project to build with this one as a subproject.
if (NOT CMAKE_SOURCE_DIR STREQUAL APIInterceptor_SOURCE_DIR OR NOT APIINTERCEPTOR_BUILD_LIBS OR NOT APIINTERCEPTOR_BUILD_INTERCEPTOR)
    return()
endif()

install(TARGETS     APIDumpLoader D3D8Utils Detours InjectionLauncher Zstd
        EXPORT      APIInterceptorTargets
        ARCHIVE     DESTINATION lib
        COMPONENT   Development
        EXCLUDE_FROM_ALL)

install(EXPORT      APIInterceptorTargets
        NAMESPACE   APIInterceptor::
        DESTINATION lib/cmake/APIInterceptor
        COMPONENT   Development
        EXCLUDE_FROM_ALL)

install(FILES       "${APIInterceptor_SOURCE_DIR}/cmake/APIInterceptorConfig.cmake"
        DESTINATION lib/cmake/APIInterceptor
        COMPONENT   Development
        EXCLUDE_FROM_ALL)

# The headers a user of the libraries includes, by the names the sources use.
install(DIRECTORY   "${APIInterceptor_SOURCE_DIR}/include/"
        DESTINATION include
        COMPONENT   Development
        EXCLUDE_FROM_ALL
        FILES_MATCHING PATTERN "*.h" PATTERN "*.inl")

install(DIRECTORY   "${APIInterceptor_SOURCE_DIR}/deps/Khronos/"
        DESTINATION include
        COMPONENT   Development
        EXCLUDE_FROM_ALL
        FILES_MATCHING PATTERN "*.h")

install(FILES       "${APIInterceptor_BINARY_DIR}/apitracer_config.h"
                    "${APIInterceptor_SOURCE_DIR}/deps/zstd/lib/zstd.h"
                    "${APIInterceptor_SOURCE_DIR}/deps/zstd/lib/zstd_errors.h"
                    "${APIInterceptor_SOURCE_DIR}/deps/zstd/lib/zdict.h"
        DESTINATION include
        COMPONENT   Development
        EXCLUDE_FROM_ALL)

install(FILES       "${APIInterceptor_SOURCE_DIR}/deps/Detours/src/detours.h"
        DESTINATION include/Detours/src
        COMPONENT   Development
        EXCLUDE_FROM_ALL)
