cmake_minimum_required (VERSION 2.8)    
project (APIInterceptor)

option(APIINTERCEPTOR_DUMP_API_CALLS "Dump API calls to text files (debugging)" ON)

# DO NOT MODIFY BELOW THIS LINE
configure_file("${APIInterceptor_SOURCE_DIR}/include/config.h.in" "${APIInterceptor_BINARY_DIR}/apitracer_config.h")

add_subdirectory(deps/Detours_AI)

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

file(GLOB APIInterceptorIncludes "${APIInterceptor_SOURCE_DIR}/include/APIInterceptor/*.h")
file(GLOB APIInterceptorSources  "${APIInterceptor_SOURCE_DIR}/src/APIInterceptor/*.cpp")

find_package(OpenGL)

file(GLOB GDI32Includes "${APIInterceptor_SOURCE_DIR}/include/GDI32/*.h"
                        "${APIInterceptor_SOURCE_DIR}/include/GDI32/entrypoints/*.h")
file(GLOB GDI32Sources  "${APIInterceptor_SOURCE_DIR}/src/GDI32/*.cpp"
                        "${APIInterceptor_SOURCE_DIR}/src/GDI32/entrypoints/*.cpp")

add_library(GDI32 STATIC ${CommonIncludes}
                         ${GDI32Sources}
                         ${GDI32Includes})

FILE(GLOB KhronosIncludes "${APIInterceptor_SOURCE_DIR}/include/Khronos/GL/*.h"
                          "${APIInterceptor_SOURCE_DIR}/include/Khronos/KHR/*.h")

FILE(GLOB OpenGL32EntrypointsIncludes "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_color_buffer_float/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_copy_buffer/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_depth_buffer_float/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_depth_clamp/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_depth_texture/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_draw_buffers/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_draw_elements_base_vertex/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_draw_instanced/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_fragment_coord_conventions/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_fragment_program_shadow/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_framebuffer_object/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_framebuffer_sRGB/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_half_float_pixel/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_half_float_vertex/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_instanced_arrays/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_map_buffer_range/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_multisample/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_multitexture/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_occlusion_query/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_point_parameters/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_point_sprite/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_provoking_vertex/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_seamless_cube_map/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_shader_texture_lod/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_shading_language_100/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_shadow/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_sync/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_border_clamp/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_buffer_object/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_compression/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_compression_rgtc/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_cube_map/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_cube_map_array/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_float/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_gather/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_mirrored_repeat/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_multisample/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_non_power_of_two/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_query_lod/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_rectangle/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_texture_rg/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_uniform_buffer_object/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_array_bgra/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_array_object/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_program/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL_ARB_vertex_shader/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.0/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.1/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.2/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.3/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.4/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL1.5/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL2.0/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL2.1/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL3.0/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL3.1/*.h"
                                      "${APIInterceptor_SOURCE_DIR}/include/OpenGL/entrypoints/GL3.2/*.h"
                                                                                                    )
FILE(GLOB OpenGL32EntrypointsSources  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.0/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.1/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.2/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.3/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.4/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL1.5/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL2.0/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL2.1/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL3.0/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL3.1/*.cpp"
                                      "${APIInterceptor_SOURCE_DIR}/src/OpenGL/entrypoints/GL3.2/*.cpp")

FILE(GLOB OpenGL32Includes "${APIInterceptor_SOURCE_DIR}/include/OpenGL/*.h")
FILE(GLOB OpenGL32Sources  "${APIInterceptor_SOURCE_DIR}/src/OpenGL/*.cpp")

add_library(OpenGL STATIC ${CommonIncludes}
                          ${KhronosIncludes}
                          ${OpenGL32EntrypointsSources}
                          ${OpenGL32EntrypointsIncludes}
                          ${OpenGL32Sources}
                          ${OpenGL32Includes})


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

add_dependencies     (APIInterceptor WGL)
target_link_libraries(APIInterceptor WGL ${OPENGL_gl_LIBRARY})

set(LIBRARY_OUTPUT_PATH ${APIInterceptor_BINARY_DIR}/bin)

source_group ("Common include files"     FILES ${CommonIncludes})
source_group ("GDI32 include files"      FILES ${GDI32Includes})
source_group ("GDI32 source files"       FILES ${GDI32Sources})
source_group ("Khronos include files"    FILES ${KhronosIncludes})
source_group ("Entrypoint include files" FILES ${OpenGL32EntrypointsIncludes})
source_group ("Entrypoint source files"  FILES ${OpenGL32EntrypointsSources})
source_group ("OpenGL32 include files"   FILES ${OpenGL32Includes})
source_group ("OpenGL32 source files"    FILES ${OpenGL32Sources})
source_group ("WGL include files"        FILES ${WGLIncludes})
source_group ("WGL source files"         FILES ${WGLSources})