# API Interceptor

A library that hooks the graphics API calls of a Windows program and stores them, with their data, in **workload files**. Projects link it to capture a program, to read what was captured, and to build on both.

DirectDraw 7 with Direct3D 7, and Direct3D 8, have the deepest sets of hooks: the printer decodes their arguments and the replay engine plays their calls again. OpenGL and the Win32 windowing calls (WGL, GDI32, User32) are covered too, and the code is arranged for more.

**Documentation: [docs/index.html](docs/index.html)** (open it in a browser; the pages are plain HTML and link to each other).

![Capturing a program and using the capture](docs/images/overview.svg)

## What you get

| Part | What it is |
| --- | --- |
| `APIDumper` + `APIDumperDLL` | Start a program with a DLL injected; the DLL hooks every API call and writes the workload. Built for 32 and 64 bits, since the program that is captured is of either. |
| `APIDumpLoader` | Library that reads a workload, segment by segment, so a workload larger than memory can be read. |
| `APIDumpPrinter` | Prints a workload as text, every call with every input and result. |
| `ReplayEngineDLL` + `ReplayPlayer` | Execute the calls of a workload again, without the program, in a window. Useful to check a capture. |
| `InjectionLauncher` | Library that starts any program with a DLL in it (reads the architecture, injects with Detours while the program is suspended). |
| `D3D7Utils`, `D3D8Utils`, `OpenGLUtils` | What is known about an API besides its hooks: interfaces, methods, argument kinds, readers of values. |

## What happens to one call

A hook runs the pre callbacks, makes the original call, then the post callbacks. The structures the call reads or writes are copied into data chunks, and the call record refers to them by number.

![What happens to one call](docs/images/call-path.svg)

## How the source is arranged

![How the source tree is layered](docs/images/layers.svg)

Public headers are in `include/` and sources in `src/`, with the same groups. Namespaces follow the path (`Interception::Hooks::D3D7`, `Interception::Hooks::D3D8`, `Capture::APIDumpLoader`, `Replay::ReplayEngineDLL`). Third-party code is in `deps/`; see [THIRD_PARTY_NOTICES.txt](THIRD_PARTY_NOTICES.txt).

## Using it from another project

![Using API Interceptor from another project](docs/images/use-as-library.svg)

As a submodule, with the options set before it:

```cmake
set(APIINTERCEPTOR_BUILD_TESTS OFF)
add_subdirectory(deps/APIInterceptor EXCLUDE_FROM_ALL)

target_link_libraries(my_tool APIDumpLoader)
```

As an installed package (the static libraries and their headers):

```cmake
find_package(APIInterceptor REQUIRED)

target_link_libraries(my_tool APIInterceptor::APIDumpLoader)
```

The hooks themselves (the `APIInterceptor` library) are built through `add_subdirectory`, since a DLL that is injected has to contain them. See [Building](docs/building.html#subproject) for the options and for what a package contains.

## Building

CMake, MSVC, C++14. The build is made twice, for 32 and 64 bits.

```
build.bat                    :: incremental, x86 + x64, outputs in build_final\
build.bat --from-scratch     :: wipe, configure, build
build.bat --debug            :: Debug instead of Release
```

`build_final\` has `tools\APIDumper` (the dumper, its DLL, the printer) and `tools\Replay` (the replay engine and player), and can be zipped as it is. The tests are one googletest program, `APIInterceptorTests`.

## License

MIT; see [LICENSE.txt](LICENSE.txt).

---

Built by Dominik Witczak in his spare time, with help from the Sonnet AI model. Dominik steers, reviews and makes the calls.
