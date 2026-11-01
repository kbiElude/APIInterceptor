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
    target_include_directories(Zstd PUBLIC  "$<BUILD_INTERFACE:${APIInterceptor_SOURCE_DIR}/deps/zstd/lib>"
                                           "$<INSTALL_INTERFACE:include>")

    file(GLOB APIDumpLoaderIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Capture/APIDumpLoader/*.h")
    file(GLOB APIDumpLoaderSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Capture/APIDumpLoader/*.cpp"
                                                      "${APIInterceptor_SOURCE_DIR}/src/Common/fatal_error.cpp"
                                                      "${APIInterceptor_SOURCE_DIR}/src/Common/types.cpp")

    add_library(APIDumpLoader STATIC ${APIDumpLoaderIncludes} ${APIDumpLoaderSources})

    target_link_libraries(APIDumpLoader PUBLIC Zstd)

    # The launcher needs Detours, which the interceptor builds.
    if (APIINTERCEPTOR_BUILD_INTERCEPTOR)
        file(GLOB InjectionLauncherIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Capture/InjectionLauncher/*.h")
        file(GLOB InjectionLauncherSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Capture/InjectionLauncher/*.cpp")

        # Starting an application with a DLL in it: shared by the dumper and the programs which build on this project.
        add_library(InjectionLauncher STATIC ${InjectionLauncherIncludes} ${InjectionLauncherSources})

        target_link_libraries(InjectionLauncher PUBLIC Detours)

        source_group ("InjectionLauncher include files" FILES ${InjectionLauncherIncludes})
        source_group ("InjectionLauncher source files"  FILES ${InjectionLauncherSources})
    endif()

    source_group ("APIDump Loader include files"  FILES ${APIDumpLoaderIncludes})
    source_group ("APIDump Loader source files"   FILES ${APIDumpLoaderSources})

endif()
