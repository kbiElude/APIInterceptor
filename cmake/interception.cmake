# The hooks of the APIs and what they are built on.
if (APIINTERCEPTOR_BUILD_INTERCEPTOR)
    add_subdirectory(deps/Detours_AI)

    file(GLOB APIInterceptorIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/APIInterceptor/*.h")
    file(GLOB APIInterceptorSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/APIInterceptor/*.cpp")

    find_package(OpenGL)

    file(GLOB GDI32Includes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/GDI32/*.h"
                            "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/GDI32/entrypoints/*.h")
    file(GLOB GDI32Sources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/GDI32/*.cpp"
                            "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/GDI32/entrypoints/*.cpp")

    file(GLOB User32Includes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/User32/*.h"
                             "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/User32/entrypoints/*.h")
    file(GLOB User32Sources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/User32/*.cpp"
                             "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/User32/entrypoints/*.cpp")

    add_library(GDI32  STATIC ${CommonIncludes}
                              ${GDI32Sources}
                              ${GDI32Includes})
    add_library(User32 STATIC ${CommonIncludes}
                              ${User32Sources}
                              ${User32Includes})

    file(GLOB Kernel32Includes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/Kernel32/*.h")
    file(GLOB Kernel32Sources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/Kernel32/*.cpp"
                               "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/Kernel32/entrypoints/*.cpp")

    add_library(Kernel32 STATIC ${CommonIncludes}
                                ${Kernel32Sources}
                                ${Kernel32Includes})

    file(GLOB KhronosIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/deps/Khronos/GL/*.h"
                              "${APIInterceptor_SOURCE_DIR}/deps/Khronos/KHR/*.h")

    # The entry points of OpenGL are in a directory for each version or extension, which is a folder of its own in the IDE.
    file(GLOB_RECURSE OpenGL32EntrypointsIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/*.h")
    file(GLOB_RECURSE OpenGL32EntrypointsSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/*.cpp")

    file(GLOB OpenGL32Includes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/*.h")
    file(GLOB OpenGL32Sources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/*.cpp")

    file(GLOB OpenGL32UtilsIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Core/OpenGLUtils/*.h")
    file(GLOB OpenGL32UtilsSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Core/OpenGLUtils/*.cpp")

    add_library(OpenGLUtils STATIC ${OpenGL32UtilsIncludes}
                                   ${OpenGL32UtilsSources})

    file(GLOB D3D7Includes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/D3D7/*.h"
                           "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/D3D7/*.inl")
    file(GLOB D3D7Sources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/D3D7/*.cpp")

    file(GLOB D3D7UtilsIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Core/D3D7Utils/*.h")
    file(GLOB D3D7UtilsSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Core/D3D7Utils/*.cpp")

    add_library(D3D7Utils STATIC ${D3D7Includes}
                                 ${D3D7UtilsIncludes}
                                 ${D3D7UtilsSources})

    file(GLOB D3D8Includes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/D3D8/*.h"
                           "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/D3D8/*.inl")
    file(GLOB D3D8Sources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/D3D8/*.cpp"
                           "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/D3D8/entrypoints/*.cpp")

    file(GLOB D3D8UtilsIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Core/D3D8Utils/*.h")
    file(GLOB D3D8UtilsSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Core/D3D8Utils/*.cpp")

    add_library(D3D8Utils STATIC ${D3D8Includes}
                                 ${D3D8UtilsIncludes}
                                 ${D3D8UtilsSources})

    # What the hooks of the COM-based APIs (D3D8...) have in common.
    file(GLOB HooksCommonIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/Common/*.h")
    file(GLOB HooksCommonSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/Common/*.cpp")

    add_library          (HooksCommon STATIC ${CommonIncludes}
                                             ${HooksCommonIncludes}
                                             ${HooksCommonSources})
    add_dependencies     (HooksCommon Detours Kernel32)
    target_link_libraries(HooksCommon Detours Kernel32)

    add_library          (D3D8 STATIC ${CommonIncludes}
                                      ${D3D8Includes}
                                      ${D3D8Sources})
    add_dependencies     (D3D8 D3D8Utils HooksCommon Kernel32)
    target_link_libraries(D3D8 D3D8Utils HooksCommon Kernel32)

    add_library          (D3D7 STATIC ${CommonIncludes}
                                      ${D3D7Includes}
                                      ${D3D7Sources})
    add_dependencies     (D3D7 D3D7Utils HooksCommon Kernel32)
    target_link_libraries(D3D7 D3D7Utils HooksCommon Kernel32)

    add_library          (OpenGL STATIC ${CommonIncludes}
                                         ${KhronosIncludes}
                                         ${OpenGL32EntrypointsSources}
                                         ${OpenGL32EntrypointsIncludes}
                                         ${OpenGL32Sources}
                                         ${OpenGL32Includes})
    add_dependencies     (OpenGL OpenGLUtils)
    target_link_libraries(OpenGL OpenGLUtils)

    file(GLOB WGLIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/WGL/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/WGL/entrypoints/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/WGL/entrypoints/WGL_ARB_create_context/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/WGL/entrypoints/WGL_ARB_extensions_string/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/WGL/entrypoints/WGL_ARB_framebuffer_sRGB/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/WGL/entrypoints/WGL_EXT_swap_control/*.h"
                        )
    file(GLOB WGLSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/WGL/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/WGL/entrypoints/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/WGL/entrypoints/WGL_ARB_create_context/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/WGL/entrypoints/WGL_ARB_extensions_string/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/WGL/entrypoints/WGL_ARB_framebuffer_sRGB/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/WGL/entrypoints/WGL_EXT_swap_control/*.cpp"
                        )

    add_library(WGL STATIC ${CommonIncludes}
                        ${WGLSources}
                        ${WGLIncludes})

    add_library(APIInterceptor OBJECT ${CommonSources}
                                    ${APIInterceptorIncludes}
                                    ${APIInterceptorSources})

    target_link_libraries(APIInterceptor Detours)

    add_dependencies     (APIInterceptor D3D7)
    target_link_libraries(APIInterceptor D3D7)

    add_dependencies     (APIInterceptor D3D8)
    target_link_libraries(APIInterceptor D3D8)

    add_dependencies     (APIInterceptor GDI32)
    target_link_libraries(APIInterceptor GDI32)

    add_dependencies     (APIInterceptor Kernel32)
    target_link_libraries(APIInterceptor Kernel32)

    add_dependencies     (APIInterceptor OpenGL)
    target_link_libraries(APIInterceptor OpenGL ${OPENGL_gl_LIBRARY})

    add_dependencies     (APIInterceptor User32)
    target_link_libraries(APIInterceptor User32)

    add_dependencies     (APIInterceptor WGL)
    target_link_libraries(APIInterceptor WGL ${OPENGL_gl_LIBRARY})

    source_group ("D3D7 include files"       FILES ${D3D7Includes})
    source_group ("D3D7 source files"        FILES ${D3D7Sources})
    source_group ("D3D7 Utils include files" FILES ${D3D7UtilsIncludes})
    source_group ("D3D7 Utils source files"  FILES ${D3D7UtilsSources})
    source_group ("D3D8 include files"       FILES ${D3D8Includes})
    source_group ("D3D8 source files"        FILES ${D3D8Sources})
    source_group ("D3D8 Utils include files" FILES ${D3D8UtilsIncludes})
    source_group ("D3D8 Utils source files"  FILES ${D3D8UtilsSources})
    source_group ("GDI32 include files"      FILES ${GDI32Includes})
    source_group ("Hooks Common include files" FILES ${HooksCommonIncludes})
    source_group ("Hooks Common source files"  FILES ${HooksCommonSources})
    source_group ("GDI32 source files"       FILES ${GDI32Sources})
    source_group ("Kernel32 include files"   FILES ${Kernel32Includes})
    source_group ("Kernel32 source files"    FILES ${Kernel32Sources})
    source_group ("Khronos include files"    FILES ${KhronosIncludes})
    source_group (TREE "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints" PREFIX "Entrypoint include files" FILES ${OpenGL32EntrypointsIncludes})
    source_group (TREE "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints"     PREFIX "Entrypoint source files"  FILES ${OpenGL32EntrypointsSources})
    source_group ("OpenGL32 include files"   FILES ${OpenGL32Includes})
    source_group ("OpenGL32 source files"    FILES ${OpenGL32Sources})
    source_group ("User32 include files"     FILES ${User32Includes})
    source_group ("User32 source files"      FILES ${User32Sources})
    source_group ("WGL include files"        FILES ${WGLIncludes})
    source_group ("WGL source files"         FILES ${WGLSources})
endif()
