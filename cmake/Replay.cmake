# The replayer and the programs which play a workload.
# The replayer needs the D3D8 description of the interceptor (D3D8Utils).
if (APIINTERCEPTOR_BUILD_INTERCEPTOR AND APIINTERCEPTOR_BUILD_LIBS)
    file(GLOB ReplayEngineDLLIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Replay/ReplayEngineDLL/*.h")
    file(GLOB ReplayEngineCoreSources CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/*.cpp"
                                                        "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/*.h")

    # The engine itself. A program which replays more than the plain sequence of calls links it and plugs its own executors
    # and frame executor in (see ReplayEngine); the DLL below is the engine as the player uses it.
    list(REMOVE_ITEM ReplayEngineCoreSources "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/entrypoints.cpp")

    add_library(ReplayEngineCore STATIC ${ReplayEngineDLLIncludes} ${ReplayEngineCoreSources})

    target_include_directories(ReplayEngineCore PUBLIC "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL")
    target_link_libraries     (ReplayEngineCore PUBLIC APIDumpLoader D3D7Utils D3D8Utils gdi32 opengl32 user32 winmm)

    add_library(ReplayEngineDLL SHARED ${ReplayEngineDLLIncludes} "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/entrypoints.cpp")

    target_compile_definitions(ReplayEngineDLL PRIVATE REPLAYENGINEDLL_BUILDING_DLL)
    target_link_libraries     (ReplayEngineDLL ReplayEngineCore)

    # The control window of the player. Win32 + Direct3D 11 backends of Dear ImGui.
    add_library(ImGui STATIC "${APIInterceptor_SOURCE_DIR}/deps/imgui/imgui.cpp"
                             "${APIInterceptor_SOURCE_DIR}/deps/imgui/imgui_draw.cpp"
                             "${APIInterceptor_SOURCE_DIR}/deps/imgui/imgui_tables.cpp"
                             "${APIInterceptor_SOURCE_DIR}/deps/imgui/imgui_widgets.cpp"
                             "${APIInterceptor_SOURCE_DIR}/deps/imgui/backends/imgui_impl_dx11.cpp"
                             "${APIInterceptor_SOURCE_DIR}/deps/imgui/backends/imgui_impl_win32.cpp")

    target_include_directories(ImGui PUBLIC "${APIInterceptor_SOURCE_DIR}/deps/imgui"
                                            "${APIInterceptor_SOURCE_DIR}/deps/imgui/backends")
    target_link_libraries     (ImGui d3d11 d3dcompiler dxgi dwmapi)

    file(GLOB ReplayPlayerSources CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayPlayer/*.cpp"
                                                     "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayPlayer/*.h")

    add_executable(ReplayPlayer ${ReplayPlayerSources})

    target_link_libraries(ReplayPlayer APIDumpLoader ReplayEngineDLL ImGui comdlg32)

    # The 32-bit pair has its own names, so that the 64-bit player can find it next to itself (see PlayerLauncher).
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        set_target_properties(ReplayPlayer   PROPERTIES OUTPUT_NAME "ReplayPlayer_x86")
        set_target_properties(ReplayEngineDLL PROPERTIES OUTPUT_NAME "ReplayEngineDLL_x86")
    endif()

    source_group ("Replay Engine include files" FILES ${ReplayEngineDLLIncludes})
    source_group ("Replay Engine source files"  FILES ${ReplayEngineCoreSources})
endif()
