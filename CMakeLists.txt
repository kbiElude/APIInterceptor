cmake_minimum_required (VERSION 2.8)    
project (APIInterceptor)

option(APIINTERCEPTOR_BUILD_INTERCEPTOR "Build API interceptor projects"             ON)
option(APIINTERCEPTOR_BUILD_LIBS        "Build static libs (API Dump Loader)"        ON)
option(APIINTERCEPTOR_BUILD_TOOLS       "Build tools (API Dumper, API Dump Printer)" ON)
option(APIINTERCEPTOR_DUMP_API_CALLS    "Dump API calls to text files (debugging)"   OFF)

# DO NOT MODIFY BELOW THIS LINE
configure_file("${APIInterceptor_SOURCE_DIR}/include/config.h.in" "${APIInterceptor_BINARY_DIR}/apitracer_config.h")

if (NOT APIINTERCEPTOR_BUILD_INTERCEPTOR AND APIINTERCEPTOR_BUILD_TOOLS)
    message(FATAL_ERROR "APIINTERCEPTOR_BUILD_TOOLS option requires APIINTERCEPTOR_BUILD_INTERCEPTOR option to be enabled.")
endif()

if (NOT APIINTERCEPTOR_BUILD_LIBS AND APIINTERCEPTOR_BUILD_TOOLS)
    message(FATAL_ERROR "APIINTERCEPTOR_BUILD_TOOLS option requires APIINTERCEPTOR_BUILD_LIBS option to be enabled.")
endif()

unset(CMAKE_DEBUG_POSTFIX CACHE)

if (MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif (MSVC)

set(CMAKE_INCLUDE_PATH             "${APIInterceptor_SOURCE_DIR}/include")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${APIInterceptor_BINARY_DIR}/bin")

include_directories("${APIInterceptor_BINARY_DIR}"
                    "${APIInterceptor_SOURCE_DIR}/deps"
                    "${APIInterceptor_SOURCE_DIR}/include"
                    "${APIInterceptor_SOURCE_DIR}/include/Khronos")

file(GLOB CommonIncludes "${APIInterceptor_SOURCE_DIR}/include/Common/*.h")
file(GLOB CommonSources  "${APIInterceptor_SOURCE_DIR}/src/Common/*.cpp")

if (APIINTERCEPTOR_BUILD_INTERCEPTOR)
    add_subdirectory(deps/Detours_AI)

    file(GLOB APIInterceptorIncludes "${APIInterceptor_SOURCE_DIR}/include/APIInterceptor/*.h")
    file(GLOB APIInterceptorSources  "${APIInterceptor_SOURCE_DIR}/src/APIInterceptor/*.cpp")

    find_package(OpenGL)

    file(GLOB GDI32Includes "${APIInterceptor_SOURCE_DIR}/include/GDI32/*.h"
                            "${APIInterceptor_SOURCE_DIR}/include/GDI32/entrypoints/*.h")
    file(GLOB GDI32Sources  "${APIInterceptor_SOURCE_DIR}/src/GDI32/*.cpp"
                            "${APIInterceptor_SOURCE_DIR}/src/GDI32/entrypoints/*.cpp")

    file(GLOB User32Includes "${APIInterceptor_SOURCE_DIR}/include/User32/*.h"
                             "${APIInterceptor_SOURCE_DIR}/include/User32/entrypoints/*.h")
    file(GLOB User32Sources  "${APIInterceptor_SOURCE_DIR}/src/User32/*.cpp"
                             "${APIInterceptor_SOURCE_DIR}/src/User32/entrypoints/*.cpp")

    add_library(GDI32  STATIC ${CommonIncludes}
                              ${GDI32Sources}
                              ${GDI32Includes})
    add_library(User32 STATIC ${CommonIncludes}
                              ${User32Sources}
                              ${User32Includes})

    FILE(GLOB KhronosIncludes "${APIInterceptor_SOURCE_DIR}/include/Khronos/GL/*.h"
                              "${APIInterceptor_SOURCE_DIR}/include/Khronos/KHR/*.h")

    FILE(GLOB OpenGL32EntrypointsIncludes_GL1_0  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.0/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL1_1  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.1/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL1_2  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.2/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL1_3  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.3/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL1_4  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.4/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL1_5  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.5/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL2_0  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL2.0/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL2_1  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL2.1/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL3_0  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL3.0/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL3_1  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL3.1/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL3_2  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL3.2/*.h")

    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_color_buffer_float    "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_color_buffer_float/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_copy_buffer           "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_copy_buffer/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_depth_buffer_float    "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_depth_buffer_float/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_depth_clamp           "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_depth_clamp/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_depth_texture         "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_depth_texture/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_draw_buffers          "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_draw_buffers/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_draw_elements_base_vertex "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_draw_elements_base_vertex/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_draw_instanced        "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_draw_instanced/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_fragment_coord_conventions "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_fragment_coord_conventions/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_fragment_program_shadow "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_fragment_program_shadow/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_fragment_shader       "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_fragment_shader/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_framebuffer_object    "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_framebuffer_object/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_framebuffer_sRGB      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_framebuffer_sRGB/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_half_float_pixel      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_half_float_pixel/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_half_float_vertex     "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_half_float_vertex/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_instanced_arrays      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_instanced_arrays/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_map_buffer_range      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_map_buffer_range/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_multisample           "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_multisample/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_multitexture          "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_multitexture/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_occlusion_query       "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_occlusion_query/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_pixel_buffer_object   "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_pixel_buffer_object/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_point_parameters      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_point_parameters/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_point_sprite          "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_point_sprite/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_provoking_vertex      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_provoking_vertex/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_seamless_cube_map     "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_seamless_cube_map/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_shader_texture_lod    "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_shader_texture_lod/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_shading_language_100  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_shading_language_100/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_shadow                "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_shadow/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_sync                  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_sync/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_border_clamp  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_border_clamp/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_buffer_object "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_buffer_object/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_compression   "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_compression/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_compression_rgtc "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_compression_rgtc/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_cube_map      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_cube_map/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_cube_map_array "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_cube_map_array/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_float         "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_float/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_gather        "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_gather/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_mirrored_repeat "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_mirrored_repeat/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_multisample   "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_multisample/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_non_power_of_two "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_non_power_of_two/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_query_lod     "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_query_lod/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_rectangle     "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_rectangle/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_rg            "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_rg/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_uniform_buffer_object "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_uniform_buffer_object/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_array_bgra     "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_array_bgra/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_array_object   "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_array_object/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_buffer_object  "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_program        "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_program/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_shader         "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_shader/*.h")
    FILE(GLOB OpenGL32EntrypointsIncludes_GL_EXT_texture_object        "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_EXT_texture_object/*.h")

    set(OpenGL32EntrypointsIncludes
        ${OpenGL32EntrypointsIncludes_GL1_0}
        ${OpenGL32EntrypointsIncludes_GL1_1}
        ${OpenGL32EntrypointsIncludes_GL1_2}
        ${OpenGL32EntrypointsIncludes_GL1_3}
        ${OpenGL32EntrypointsIncludes_GL1_4}
        ${OpenGL32EntrypointsIncludes_GL1_5}
        ${OpenGL32EntrypointsIncludes_GL2_0}
        ${OpenGL32EntrypointsIncludes_GL2_1}
        ${OpenGL32EntrypointsIncludes_GL3_0}
        ${OpenGL32EntrypointsIncludes_GL3_1}
        ${OpenGL32EntrypointsIncludes_GL3_2}
        ${OpenGL32EntrypointsIncludes_GL_ARB_color_buffer_float}
        ${OpenGL32EntrypointsIncludes_GL_ARB_copy_buffer}
        ${OpenGL32EntrypointsIncludes_GL_ARB_depth_buffer_float}
        ${OpenGL32EntrypointsIncludes_GL_ARB_depth_clamp}
        ${OpenGL32EntrypointsIncludes_GL_ARB_depth_texture}
        ${OpenGL32EntrypointsIncludes_GL_ARB_draw_buffers}
        ${OpenGL32EntrypointsIncludes_GL_ARB_draw_elements_base_vertex}
        ${OpenGL32EntrypointsIncludes_GL_ARB_draw_instanced}
        ${OpenGL32EntrypointsIncludes_GL_ARB_fragment_coord_conventions}
        ${OpenGL32EntrypointsIncludes_GL_ARB_fragment_program_shadow}
        ${OpenGL32EntrypointsIncludes_GL_ARB_fragment_shader}
        ${OpenGL32EntrypointsIncludes_GL_ARB_framebuffer_object}
        ${OpenGL32EntrypointsIncludes_GL_ARB_framebuffer_sRGB}
        ${OpenGL32EntrypointsIncludes_GL_ARB_half_float_pixel}
        ${OpenGL32EntrypointsIncludes_GL_ARB_half_float_vertex}
        ${OpenGL32EntrypointsIncludes_GL_ARB_instanced_arrays}
        ${OpenGL32EntrypointsIncludes_GL_ARB_map_buffer_range}
        ${OpenGL32EntrypointsIncludes_GL_ARB_multisample}
        ${OpenGL32EntrypointsIncludes_GL_ARB_multitexture}
        ${OpenGL32EntrypointsIncludes_GL_ARB_occlusion_query}
        ${OpenGL32EntrypointsIncludes_GL_ARB_pixel_buffer_object}
        ${OpenGL32EntrypointsIncludes_GL_ARB_point_parameters}
        ${OpenGL32EntrypointsIncludes_GL_ARB_point_sprite}
        ${OpenGL32EntrypointsIncludes_GL_ARB_provoking_vertex}
        ${OpenGL32EntrypointsIncludes_GL_ARB_seamless_cube_map}
        ${OpenGL32EntrypointsIncludes_GL_ARB_shader_texture_lod}
        ${OpenGL32EntrypointsIncludes_GL_ARB_shading_language_100}
        ${OpenGL32EntrypointsIncludes_GL_ARB_shadow}
        ${OpenGL32EntrypointsIncludes_GL_ARB_sync}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_border_clamp}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_buffer_object}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_compression}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_compression_rgtc}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_cube_map}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_cube_map_array}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_float}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_gather}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_mirrored_repeat}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_multisample}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_non_power_of_two}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_query_lod}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_rectangle}
        ${OpenGL32EntrypointsIncludes_GL_ARB_texture_rg}
        ${OpenGL32EntrypointsIncludes_GL_ARB_uniform_buffer_object}
        ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_array_bgra}
        ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_array_object}
        ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_buffer_object}
        ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_program}
        ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_shader}
        ${OpenGL32EntrypointsIncludes_GL_EXT_texture_object})

    FILE(GLOB OpenGL32EntrypointsSources_GL1_0  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.0/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL1_1  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.1/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL1_2  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.2/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL1_3  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.3/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL1_4  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.4/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL1_5  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.5/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL2_0  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL2.0/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL2_1  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL2.1/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL3_0  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL3.0/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL3_1  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL3.1/*.cpp")
    FILE(GLOB OpenGL32EntrypointsSources_GL3_2  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL3.2/*.cpp")

    set(OpenGL32EntrypointsSources
        ${OpenGL32EntrypointsSources_GL1_0}
        ${OpenGL32EntrypointsSources_GL1_1}
        ${OpenGL32EntrypointsSources_GL1_2}
        ${OpenGL32EntrypointsSources_GL1_3}
        ${OpenGL32EntrypointsSources_GL1_4}
        ${OpenGL32EntrypointsSources_GL1_5}
        ${OpenGL32EntrypointsSources_GL2_0}
        ${OpenGL32EntrypointsSources_GL2_1}
        ${OpenGL32EntrypointsSources_GL3_0}
        ${OpenGL32EntrypointsSources_GL3_1}
        ${OpenGL32EntrypointsSources_GL3_2})

    FILE(GLOB OpenGL32Includes "${APIInterceptor_SOURCE_DIR}/include/OpenGL/*.h")
    FILE(GLOB OpenGL32Sources  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/*.cpp")

    FILE(GLOB OpenGL32UtilsIncludes "${APIInterceptor_SOURCE_DIR}/include/OpenGLUtils/*.h")
    FILE(GLOB OpenGL32UtilsSources  "${APIInterceptor_SOURCE_DIR}/src/OpenGLUtils/*.cpp")

    add_library(OpenGLUtils STATIC ${OpenGL32UtilsIncludes}
                                   ${OpenGL32UtilsSources})

    add_library          (OpenGL STATIC ${CommonIncludes}
                                         ${KhronosIncludes}
                                         ${OpenGL32EntrypointsSources}
                                         ${OpenGL32EntrypointsIncludes}
                                         ${OpenGL32Sources}
                                         ${OpenGL32Includes})
    add_dependencies     (OpenGL OpenGLUtils)
    target_link_libraries(OpenGL OpenGLUtils)

    file(GLOB WGLIncludes "${APIInterceptor_SOURCE_DIR}/include/WGL/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/WGL/entrypoints/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/WGL/entrypoints/WGL_ARB_create_context/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/WGL/entrypoints/WGL_ARB_extensions_string/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/WGL/entrypoints/WGL_ARB_framebuffer_sRGB/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/WGL/entrypoints/WGL_EXT_swap_control/*.h"
                        )
    file(GLOB WGLSources  "${APIInterceptor_SOURCE_DIR}/src/WGL/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/WGL/entrypoints/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/WGL/entrypoints/WGL_ARB_create_context/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/WGL/entrypoints/WGL_ARB_extensions_string/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/WGL/entrypoints/WGL_ARB_framebuffer_sRGB/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/WGL/entrypoints/WGL_EXT_swap_control/*.cpp"
                        )

    add_library(WGL STATIC ${CommonIncludes}
                        ${WGLSources}
                        ${WGLIncludes})

    add_library(APIInterceptor OBJECT ${CommonSources}
                                    ${APIInterceptorIncludes}
                                    ${APIInterceptorSources})

    target_link_libraries(APIInterceptor Detours)

    add_dependencies     (APIInterceptor GDI32)
    target_link_libraries(APIInterceptor GDI32)

    add_dependencies     (APIInterceptor OpenGL)
    target_link_libraries(APIInterceptor OpenGL ${OPENGL_gl_LIBRARY})

    add_dependencies     (APIInterceptor User32)
    target_link_libraries(APIInterceptor User32)

    add_dependencies     (APIInterceptor WGL)
    target_link_libraries(APIInterceptor WGL ${OPENGL_gl_LIBRARY})

    source_group ("GDI32 include files"      FILES ${GDI32Includes})
    source_group ("GDI32 source files"       FILES ${GDI32Sources})
    source_group ("Khronos include files"    FILES ${KhronosIncludes})
    source_group ("Entrypoint include files\\GL1.0"  FILES ${OpenGL32EntrypointsIncludes_GL1_0})
    source_group ("Entrypoint include files\\GL1.1"  FILES ${OpenGL32EntrypointsIncludes_GL1_1})
    source_group ("Entrypoint include files\\GL1.2"  FILES ${OpenGL32EntrypointsIncludes_GL1_2})
    source_group ("Entrypoint include files\\GL1.3"  FILES ${OpenGL32EntrypointsIncludes_GL1_3})
    source_group ("Entrypoint include files\\GL1.4"  FILES ${OpenGL32EntrypointsIncludes_GL1_4})
    source_group ("Entrypoint include files\\GL1.5"  FILES ${OpenGL32EntrypointsIncludes_GL1_5})
    source_group ("Entrypoint include files\\GL2.0"  FILES ${OpenGL32EntrypointsIncludes_GL2_0})
    source_group ("Entrypoint include files\\GL2.1"  FILES ${OpenGL32EntrypointsIncludes_GL2_1})
    source_group ("Entrypoint include files\\GL3.0"  FILES ${OpenGL32EntrypointsIncludes_GL3_0})
    source_group ("Entrypoint include files\\GL3.1"  FILES ${OpenGL32EntrypointsIncludes_GL3_1})
    source_group ("Entrypoint include files\\GL3.2"  FILES ${OpenGL32EntrypointsIncludes_GL3_2})
    source_group ("Entrypoint include files\\GL_ARB_color_buffer_float"     FILES ${OpenGL32EntrypointsIncludes_GL_ARB_color_buffer_float})
    source_group ("Entrypoint include files\\GL_ARB_copy_buffer"            FILES ${OpenGL32EntrypointsIncludes_GL_ARB_copy_buffer})
    source_group ("Entrypoint include files\\GL_ARB_depth_buffer_float"     FILES ${OpenGL32EntrypointsIncludes_GL_ARB_depth_buffer_float})
    source_group ("Entrypoint include files\\GL_ARB_depth_clamp"            FILES ${OpenGL32EntrypointsIncludes_GL_ARB_depth_clamp})
    source_group ("Entrypoint include files\\GL_ARB_depth_texture"          FILES ${OpenGL32EntrypointsIncludes_GL_ARB_depth_texture})
    source_group ("Entrypoint include files\\GL_ARB_draw_buffers"           FILES ${OpenGL32EntrypointsIncludes_GL_ARB_draw_buffers})
    source_group ("Entrypoint include files\\GL_ARB_draw_elements_base_vertex" FILES ${OpenGL32EntrypointsIncludes_GL_ARB_draw_elements_base_vertex})
    source_group ("Entrypoint include files\\GL_ARB_draw_instanced"         FILES ${OpenGL32EntrypointsIncludes_GL_ARB_draw_instanced})
    source_group ("Entrypoint include files\\GL_ARB_fragment_coord_conventions" FILES ${OpenGL32EntrypointsIncludes_GL_ARB_fragment_coord_conventions})
    source_group ("Entrypoint include files\\GL_ARB_fragment_program_shadow" FILES ${OpenGL32EntrypointsIncludes_GL_ARB_fragment_program_shadow})
    source_group ("Entrypoint include files\\GL_ARB_fragment_shader"        FILES ${OpenGL32EntrypointsIncludes_GL_ARB_fragment_shader})
    source_group ("Entrypoint include files\\GL_ARB_framebuffer_object"     FILES ${OpenGL32EntrypointsIncludes_GL_ARB_framebuffer_object})
    source_group ("Entrypoint include files\\GL_ARB_framebuffer_sRGB"       FILES ${OpenGL32EntrypointsIncludes_GL_ARB_framebuffer_sRGB})
    source_group ("Entrypoint include files\\GL_ARB_half_float_pixel"       FILES ${OpenGL32EntrypointsIncludes_GL_ARB_half_float_pixel})
    source_group ("Entrypoint include files\\GL_ARB_half_float_vertex"      FILES ${OpenGL32EntrypointsIncludes_GL_ARB_half_float_vertex})
    source_group ("Entrypoint include files\\GL_ARB_instanced_arrays"       FILES ${OpenGL32EntrypointsIncludes_GL_ARB_instanced_arrays})
    source_group ("Entrypoint include files\\GL_ARB_map_buffer_range"       FILES ${OpenGL32EntrypointsIncludes_GL_ARB_map_buffer_range})
    source_group ("Entrypoint include files\\GL_ARB_multisample"            FILES ${OpenGL32EntrypointsIncludes_GL_ARB_multisample})
    source_group ("Entrypoint include files\\GL_ARB_multitexture"           FILES ${OpenGL32EntrypointsIncludes_GL_ARB_multitexture})
    source_group ("Entrypoint include files\\GL_ARB_occlusion_query"        FILES ${OpenGL32EntrypointsIncludes_GL_ARB_occlusion_query})
    source_group ("Entrypoint include files\\GL_ARB_pixel_buffer_object"    FILES ${OpenGL32EntrypointsIncludes_GL_ARB_pixel_buffer_object})
    source_group ("Entrypoint include files\\GL_ARB_point_parameters"       FILES ${OpenGL32EntrypointsIncludes_GL_ARB_point_parameters})
    source_group ("Entrypoint include files\\GL_ARB_point_sprite"           FILES ${OpenGL32EntrypointsIncludes_GL_ARB_point_sprite})
    source_group ("Entrypoint include files\\GL_ARB_provoking_vertex"       FILES ${OpenGL32EntrypointsIncludes_GL_ARB_provoking_vertex})
    source_group ("Entrypoint include files\\GL_ARB_seamless_cube_map"      FILES ${OpenGL32EntrypointsIncludes_GL_ARB_seamless_cube_map})
    source_group ("Entrypoint include files\\GL_ARB_shader_texture_lod"     FILES ${OpenGL32EntrypointsIncludes_GL_ARB_shader_texture_lod})
    source_group ("Entrypoint include files\\GL_ARB_shading_language_100"   FILES ${OpenGL32EntrypointsIncludes_GL_ARB_shading_language_100})
    source_group ("Entrypoint include files\\GL_ARB_shadow"                 FILES ${OpenGL32EntrypointsIncludes_GL_ARB_shadow})
    source_group ("Entrypoint include files\\GL_ARB_sync"                   FILES ${OpenGL32EntrypointsIncludes_GL_ARB_sync})
    source_group ("Entrypoint include files\\GL_ARB_texture_border_clamp"   FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_border_clamp})
    source_group ("Entrypoint include files\\GL_ARB_texture_buffer_object"  FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_buffer_object})
    source_group ("Entrypoint include files\\GL_ARB_texture_compression"    FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_compression})
    source_group ("Entrypoint include files\\GL_ARB_texture_compression_rgtc" FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_compression_rgtc})
    source_group ("Entrypoint include files\\GL_ARB_texture_cube_map"       FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_cube_map})
    source_group ("Entrypoint include files\\GL_ARB_texture_cube_map_array" FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_cube_map_array})
    source_group ("Entrypoint include files\\GL_ARB_texture_float"          FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_float})
    source_group ("Entrypoint include files\\GL_ARB_texture_gather"         FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_gather})
    source_group ("Entrypoint include files\\GL_ARB_texture_mirrored_repeat" FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_mirrored_repeat})
    source_group ("Entrypoint include files\\GL_ARB_texture_multisample"    FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_multisample})
    source_group ("Entrypoint include files\\GL_ARB_texture_non_power_of_two" FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_non_power_of_two})
    source_group ("Entrypoint include files\\GL_ARB_texture_query_lod"      FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_query_lod})
    source_group ("Entrypoint include files\\GL_ARB_texture_rectangle"      FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_rectangle})
    source_group ("Entrypoint include files\\GL_ARB_texture_rg"             FILES ${OpenGL32EntrypointsIncludes_GL_ARB_texture_rg})
    source_group ("Entrypoint include files\\GL_ARB_uniform_buffer_object"  FILES ${OpenGL32EntrypointsIncludes_GL_ARB_uniform_buffer_object})
    source_group ("Entrypoint include files\\GL_ARB_vertex_array_bgra"      FILES ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_array_bgra})
    source_group ("Entrypoint include files\\GL_ARB_vertex_array_object"    FILES ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_array_object})
    source_group ("Entrypoint include files\\GL_ARB_vertex_buffer_object"   FILES ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_buffer_object})
    source_group ("Entrypoint include files\\GL_ARB_vertex_program"         FILES ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_program})
    source_group ("Entrypoint include files\\GL_ARB_vertex_shader"          FILES ${OpenGL32EntrypointsIncludes_GL_ARB_vertex_shader})
    source_group ("Entrypoint include files\\GL_EXT_texture_object"         FILES ${OpenGL32EntrypointsIncludes_GL_EXT_texture_object})

    source_group ("Entrypoint source files\\GL1.0"  FILES ${OpenGL32EntrypointsSources_GL1_0})
    source_group ("Entrypoint source files\\GL1.1"  FILES ${OpenGL32EntrypointsSources_GL1_1})
    source_group ("Entrypoint source files\\GL1.2"  FILES ${OpenGL32EntrypointsSources_GL1_2})
    source_group ("Entrypoint source files\\GL1.3"  FILES ${OpenGL32EntrypointsSources_GL1_3})
    source_group ("Entrypoint source files\\GL1.4"  FILES ${OpenGL32EntrypointsSources_GL1_4})
    source_group ("Entrypoint source files\\GL1.5"  FILES ${OpenGL32EntrypointsSources_GL1_5})
    source_group ("Entrypoint source files\\GL2.0"  FILES ${OpenGL32EntrypointsSources_GL2_0})
    source_group ("Entrypoint source files\\GL2.1"  FILES ${OpenGL32EntrypointsSources_GL2_1})
    source_group ("Entrypoint source files\\GL3.0"  FILES ${OpenGL32EntrypointsSources_GL3_0})
    source_group ("Entrypoint source files\\GL3.1"  FILES ${OpenGL32EntrypointsSources_GL3_1})
    source_group ("Entrypoint source files\\GL3.2"  FILES ${OpenGL32EntrypointsSources_GL3_2})
    source_group ("OpenGL32 include files"   FILES ${OpenGL32Includes})
    source_group ("OpenGL32 source files"    FILES ${OpenGL32Sources})
    source_group ("User32 include files"     FILES ${User32Includes})
    source_group ("User32 source files"      FILES ${User32Sources})
    source_group ("WGL include files"        FILES ${WGLIncludes})
    source_group ("WGL source files"         FILES ${WGLSources})
endif()

set(LIBRARY_OUTPUT_PATH ${APIInterceptor_BINARY_DIR}/bin)

source_group ("Common include files" FILES ${CommonIncludes})

if (APIINTERCEPTOR_BUILD_LIBS)
    file(GLOB APIDumpLoaderIncludes "${APIInterceptor_SOURCE_DIR}/include/APIDumpLoader/*.h")
    file(GLOB APIDumpLoaderSources  "${APIInterceptor_SOURCE_DIR}/src/APIDumpLoader/*.cpp"
                                    "${APIInterceptor_SOURCE_DIR}/src/Common/types.cpp")

    add_library(APIDumpLoader STATIC ${APIDumpLoaderIncludes} ${APIDumpLoaderSources})

    source_group ("APIDump Loader include files"  FILES ${APIDumpLoaderIncludes})
    source_group ("APIDump Loader source files"   FILES ${APIDumpLoaderSources})
endif()

if (APIINTERCEPTOR_BUILD_TOOLS)
    file(GLOB APIDumperDLLIncludes  "${APIInterceptor_SOURCE_DIR}/include/APIDumperDLL/*.h")
    file(GLOB APIDumperDLLSources   "${APIInterceptor_SOURCE_DIR}/src/APIDumperDLL/*.cpp")
    file(GLOB APIDumpPrinterSources "${APIInterceptor_SOURCE_DIR}/src/APIDumpPrinter/*.cpp")

    add_executable(APIDumper           "${APIInterceptor_SOURCE_DIR}/src/APIDumper/main.cpp")
    add_executable(APIDumpPrinter      ${APIDumpPrinterSources})
    add_library   (APIDumperDLL SHARED ${APIDumperDLLIncludes} ${APIDumperDLLSources})

    target_link_libraries(APIDumper      Detours)
    target_link_libraries(APIDumperDLL   APIInterceptor)
    target_link_libraries(APIDumpPrinter APIDumpLoader OpenGLUtils)

    add_dependencies(APIDumper APIDumperDLL)

    source_group ("APIDumperDLL include files"  FILES ${APIDumperDLLIncludes})
    source_group ("APIDumperDLL source files"   FILES ${APIDumperDLLSources})
    source_group ("APIDumpPrinter source files" FILES ${APIDumpPinterSources})

    include_directories("${APIInterceptor_SOURCE_DIR}/include/APIDumperDLL")
endif()
