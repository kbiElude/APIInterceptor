# The dumper and the printer of a capture.
if (APIINTERCEPTOR_BUILD_TOOLS)
    file(GLOB APIDumperDLLIncludes CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/APIDumperDLL/*.h")
    file(GLOB APIDumperDLLSources CONFIGURE_DEPENDS   "${APIInterceptor_SOURCE_DIR}/src/APIDumperDLL/*.cpp")
    file(GLOB APIDumpPrinterSources CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/src/APIDumpPrinter/*.cpp")

    add_executable(APIDumper           "${APIInterceptor_SOURCE_DIR}/src/APIDumper/main.cpp")
    add_executable(APIDumpPrinter      ${APIDumpPrinterSources})
    add_library   (APIDumperDLL SHARED ${APIDumperDLLIncludes} ${APIDumperDLLSources})

    target_link_libraries(APIDumper      Detours)
    target_link_libraries(APIDumperDLL   APIInterceptor Zstd)
    target_link_libraries(APIDumpPrinter APIDumpLoader D3D8Utils OpenGLUtils)

    add_dependencies(APIDumper APIDumperDLL)

    source_group ("APIDumperDLL include files"  FILES ${APIDumperDLLIncludes})
    source_group ("APIDumperDLL source files"   FILES ${APIDumperDLLSources})
    source_group ("APIDumpPrinter source files" FILES ${APIDumpPinterSources})

    include_directories("${APIInterceptor_SOURCE_DIR}/include/APIDumperDLL")
endif()
