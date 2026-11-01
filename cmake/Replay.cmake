# The replayer and the programs which play a workload.
# The replayer needs the D3D8 description of the interceptor (D3D8Utils).
if (APIINTERCEPTOR_BUILD_INTERCEPTOR AND APIINTERCEPTOR_BUILD_LIBS)
    file(GLOB APIDumpReplayerIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Replay/ReplayEngineDLL/*.h")
    file(GLOB APIDumpReplayerSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/*.cpp"
                                                        "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL/*.h")

    add_library(APIDumpReplayer SHARED ${APIDumpReplayerIncludes} ${APIDumpReplayerSources})

    target_compile_definitions(APIDumpReplayer PRIVATE APIDUMPREPLAYER_BUILDING_DLL)
    target_include_directories(APIDumpReplayer PRIVATE "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayEngineDLL")
    target_link_libraries     (APIDumpReplayer APIDumpLoader D3D8Utils gdi32 opengl32 user32 winmm)

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

    file(GLOB APIDumpPlayerSources CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayPlayer/*.cpp"
                                                     "${APIInterceptor_SOURCE_DIR}/src/Replay/ReplayPlayer/*.h")

    add_executable(APIDumpPlayer ${APIDumpPlayerSources})

    target_link_libraries(APIDumpPlayer APIDumpLoader APIDumpReplayer ImGui comdlg32)

    # The 32-bit pair has its own names, so that the 64-bit player can find it next to itself (see PlayerLauncher).
    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        set_target_properties(APIDumpPlayer   PROPERTIES OUTPUT_NAME "APIDumpPlayer_x86")
        set_target_properties(APIDumpReplayer PROPERTIES OUTPUT_NAME "APIDumpReplayer_x86")
    endif()

    source_group ("APIDump Replayer include files" FILES ${APIDumpReplayerIncludes})
    source_group ("APIDump Replayer source files"  FILES ${APIDumpReplayerSources})
endif()
