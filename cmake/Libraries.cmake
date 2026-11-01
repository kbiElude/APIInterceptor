# The libraries of the capture.
set(LIBRARY_OUTPUT_PATH ${APIInterceptor_BINARY_DIR}/bin)

source_group ("Common include files" FILES ${CommonIncludes})

if (APIINTERCEPTOR_BUILD_LIBS)
    # Zstandard compresses the segments of workload files. Only the parts which are needed are built.
    file(GLOB ZstdSources CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/deps/zstd/lib/common/*.c"
                                            "${APIInterceptor_SOURCE_DIR}/deps/zstd/lib/compress/*.c"
                                            "${APIInterceptor_SOURCE_DIR}/deps/zstd/lib/decompress/*.c")

    add_library(Zstd STATIC ${ZstdSources})

    target_compile_definitions(Zstd PRIVATE ZSTD_DISABLE_ASM)
    target_include_directories(Zstd PUBLIC  "${APIInterceptor_SOURCE_DIR}/deps/zstd/lib")

    file(GLOB APIDumpLoaderIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Capture/APIDumpLoader/*.h")
    file(GLOB APIDumpLoaderSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Capture/APIDumpLoader/*.cpp"
                                                      "${APIInterceptor_SOURCE_DIR}/src/Common/fatal_error.cpp"
                                                      "${APIInterceptor_SOURCE_DIR}/src/Common/types.cpp")

    add_library(APIDumpLoader STATIC ${APIDumpLoaderIncludes} ${APIDumpLoaderSources})

    target_link_libraries(APIDumpLoader PUBLIC Zstd)

    source_group ("APIDump Loader include files"  FILES ${APIDumpLoaderIncludes})
    source_group ("APIDump Loader source files"   FILES ${APIDumpLoaderSources})

endif()
