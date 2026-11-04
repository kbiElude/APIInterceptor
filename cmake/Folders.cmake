# The projects of the solution in folders, by what they are for.
include(${APIInterceptor_SOURCE_DIR}/cmake/FolderHelpers.cmake)

assign_folder("Interception/Hooks"     D3D7 D3D8 GDI32 HooksCommon Kernel32 OpenGL User32 WGL)
assign_folder("Interception/Core"      APIInterceptor D3D7Utils D3D8Utils OpenGLUtils)
assign_folder("Capture"                APIDumper APIDumperDLL APIDumpLoader APIDumpPrinter InjectionLauncher)
assign_folder("Replay"                 ReplayEngineCore ReplayEngineDLL ReplayPlayer ReplayPlayerSupport)
assign_folder("Tests"                  APIInterceptorTests APIInterceptorTestSupport)
assign_folder("Third party"            ImGui Zstd)

assign_folder_to_directory("Third party/Detours" "${APIInterceptor_SOURCE_DIR}/deps/Detours_AI")
if (TARGET gtest)
    assign_folder("Third party/googletest" gmock gmock_main gtest gtest_main)
endif()
