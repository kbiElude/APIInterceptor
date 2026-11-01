# What a release is made of, and where each part goes. build.bat empties build_final\ and then installs both build trees into it:
#
#   cmake --install build_x86 --config <Config> --prefix build_final
#   cmake --install build_x64 --config <Config> --prefix build_final
#
# Only what is named here is installed: no libraries, no debug information, and no program of an earlier build that is not a target any
# more. A program that has both architectures has them side by side, the 64-bit one with the suffix _x64 and the 32-bit one with _x86
# (the replay programs have _x86 in the name of the 32-bit target, see Replay.cmake), since each looks for its partners next to itself.
#
#   build_final\tools\APIDumper\     the dumper, its DLL and the printer of a capture
#   build_final\tools\Replay\        the replay player and the replay engine

# A project which builds this one as a subproject has a release of its own.
if (NOT CMAKE_SOURCE_DIR STREQUAL APIInterceptor_SOURCE_DIR)
    return()
endif()

include(${APIInterceptor_SOURCE_DIR}/cmake/InstallHelpers.cmake)

if (APIINTERCEPTOR_BUILD_TOOLS)
    install_with_suffix(APIDumper    "tools/APIDumper")
    install_with_suffix(APIDumperDLL "tools/APIDumper")
endif()

if (APIINTERCEPTOR_BUILD_INTERCEPTOR AND APIINTERCEPTOR_BUILD_LIBS)
    install_as_built(ReplayEngineDLL "tools/Replay")
    install_as_built(ReplayPlayer    "tools/Replay")
endif()

# What is not needed in 32 bits: the 64-bit tree installs it alone.
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    if (APIINTERCEPTOR_BUILD_TOOLS)
        install_as_built(APIDumpPrinter "tools/APIDumper")
    endif()
endif()
