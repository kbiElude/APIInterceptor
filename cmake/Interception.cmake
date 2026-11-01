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

    file(GLOB OpenGL32EntrypointsIncludes_GL1_0 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL1.0/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL1_1 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL1.1/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL1_2 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL1.2/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL1_3 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL1.3/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL1_4 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL1.4/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL1_5 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL1.5/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL2_0 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL2.0/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL2_1 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL2.1/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL3_0 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL3.0/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL3_1 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL3.1/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL3_2 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL3.2/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL3_3 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL3.3/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL4_0 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL4.0/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL4_1 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL4.1/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL4_2 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL4.2/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL4_3 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL4.3/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL4_4 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL4.4/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL4_5 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL4.5/*.h")

    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_color_buffer_float CONFIGURE_DEPENDS    "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_color_buffer_float/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_copy_buffer CONFIGURE_DEPENDS           "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_copy_buffer/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_depth_buffer_float CONFIGURE_DEPENDS    "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_depth_buffer_float/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_depth_clamp CONFIGURE_DEPENDS           "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_depth_clamp/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_depth_texture CONFIGURE_DEPENDS         "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_depth_texture/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_draw_buffers CONFIGURE_DEPENDS          "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_draw_buffers/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_draw_elements_base_vertex CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_draw_elements_base_vertex/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_draw_instanced CONFIGURE_DEPENDS        "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_draw_instanced/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_fragment_coord_conventions CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_fragment_coord_conventions/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_fragment_program_shadow CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_fragment_program_shadow/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_fragment_shader CONFIGURE_DEPENDS       "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_fragment_shader/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_framebuffer_object CONFIGURE_DEPENDS    "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_framebuffer_object/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_framebuffer_sRGB CONFIGURE_DEPENDS      "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_framebuffer_sRGB/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_half_float_pixel CONFIGURE_DEPENDS      "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_half_float_pixel/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_half_float_vertex CONFIGURE_DEPENDS     "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_half_float_vertex/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_instanced_arrays CONFIGURE_DEPENDS      "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_instanced_arrays/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_map_buffer_range CONFIGURE_DEPENDS      "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_map_buffer_range/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_multisample CONFIGURE_DEPENDS           "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_multisample/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_multitexture CONFIGURE_DEPENDS          "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_multitexture/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_occlusion_query CONFIGURE_DEPENDS       "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_occlusion_query/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_pixel_buffer_object CONFIGURE_DEPENDS   "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_pixel_buffer_object/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_point_parameters CONFIGURE_DEPENDS      "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_point_parameters/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_point_sprite CONFIGURE_DEPENDS          "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_point_sprite/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_provoking_vertex CONFIGURE_DEPENDS      "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_provoking_vertex/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_seamless_cube_map CONFIGURE_DEPENDS     "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_seamless_cube_map/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_shader_texture_lod CONFIGURE_DEPENDS    "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_shader_texture_lod/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_shading_language_100 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_shading_language_100/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_shadow CONFIGURE_DEPENDS                "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_shadow/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_sync CONFIGURE_DEPENDS                  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_sync/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_border_clamp CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_border_clamp/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_buffer_object CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_buffer_object/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_compression CONFIGURE_DEPENDS   "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_compression/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_compression_rgtc CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_compression_rgtc/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_cube_map CONFIGURE_DEPENDS      "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_cube_map/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_cube_map_array CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_cube_map_array/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_float CONFIGURE_DEPENDS         "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_float/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_gather CONFIGURE_DEPENDS        "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_gather/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_mirrored_repeat CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_mirrored_repeat/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_multisample CONFIGURE_DEPENDS   "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_multisample/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_non_power_of_two CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_non_power_of_two/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_query_lod CONFIGURE_DEPENDS     "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_query_lod/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_rectangle CONFIGURE_DEPENDS     "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_rectangle/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_texture_rg CONFIGURE_DEPENDS            "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_texture_rg/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_uniform_buffer_object CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_uniform_buffer_object/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_array_bgra CONFIGURE_DEPENDS     "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_vertex_array_bgra/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_array_object CONFIGURE_DEPENDS   "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_vertex_array_object/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_buffer_object CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_program CONFIGURE_DEPENDS        "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_vertex_program/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_ARB_vertex_shader CONFIGURE_DEPENDS         "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_ARB_vertex_shader/*.h")
    file(GLOB OpenGL32EntrypointsIncludes_GL_EXT_texture_object CONFIGURE_DEPENDS        "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/entrypoints/GL_EXT_texture_object/*.h")

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
        ${OpenGL32EntrypointsIncludes_GL3_3}
        ${OpenGL32EntrypointsIncludes_GL4_0}
        ${OpenGL32EntrypointsIncludes_GL4_1}
        ${OpenGL32EntrypointsIncludes_GL4_2}
        ${OpenGL32EntrypointsIncludes_GL4_3}
        ${OpenGL32EntrypointsIncludes_GL4_4}
        ${OpenGL32EntrypointsIncludes_GL4_5}
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

    file(GLOB OpenGL32EntrypointsSources_GL1_0 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL1.0/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL1_1 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL1.1/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL1_2 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL1.2/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL1_3 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL1.3/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL1_4 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL1.4/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL1_5 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL1.5/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL2_0 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL2.0/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL2_1 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL2.1/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL3_0 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL3.0/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL3_1 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL3.1/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL3_2 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL3.2/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL3_3 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL3.3/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL4_0 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL4.0/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL4_1 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL4.1/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL4_2 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL4.2/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL4_3 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL4.3/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL4_4 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL4.4/*.cpp")
    file(GLOB OpenGL32EntrypointsSources_GL4_5 CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/entrypoints/GL4.5/*.cpp")

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
        ${OpenGL32EntrypointsSources_GL3_2}
        ${OpenGL32EntrypointsSources_GL3_3}
        ${OpenGL32EntrypointsSources_GL4_0}
        ${OpenGL32EntrypointsSources_GL4_1}
        ${OpenGL32EntrypointsSources_GL4_2}
        ${OpenGL32EntrypointsSources_GL4_3}
        ${OpenGL32EntrypointsSources_GL4_4}
        ${OpenGL32EntrypointsSources_GL4_5})

    file(GLOB OpenGL32Includes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/OpenGL/*.h")
    file(GLOB OpenGL32Sources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/OpenGL/*.cpp")

    file(GLOB OpenGL32UtilsIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Core/OpenGLUtils/*.h")
    file(GLOB OpenGL32UtilsSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Core/OpenGLUtils/*.cpp")

    add_library(OpenGLUtils STATIC ${OpenGL32UtilsIncludes}
                                   ${OpenGL32UtilsSources})

    file(GLOB D3D8Includes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/D3D8/*.h"
                                             "${APIInterceptor_SOURCE_DIR}/include/Interception/Hooks/D3D8/*.inl")
    file(GLOB D3D8Sources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/D3D8/*.cpp"
                                             "${APIInterceptor_SOURCE_DIR}/src/Interception/Hooks/D3D8/entrypoints/*.cpp")

    file(GLOB D3D8UtilsIncludes CONFIGURE_DEPENDS "${APIInterceptor_SOURCE_DIR}/include/Interception/Core/D3D8Utils/*.h")
    file(GLOB D3D8UtilsSources CONFIGURE_DEPENDS  "${APIInterceptor_SOURCE_DIR}/src/Interception/Core/D3D8Utils/*.cpp")

    add_library(D3D8Utils STATIC ${D3D8Includes}
                                 ${D3D8UtilsIncludes}
                                 ${D3D8UtilsSources})

    add_library          (D3D8 STATIC ${CommonIncludes}
                                      ${D3D8Includes}
                                      ${D3D8Sources})
    add_dependencies     (D3D8 D3D8Utils Kernel32)
    target_link_libraries(D3D8 D3D8Utils Kernel32)

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

    source_group ("D3D8 include files"       FILES ${D3D8Includes})
    source_group ("D3D8 source files"        FILES ${D3D8Sources})
    source_group ("D3D8 Utils include files" FILES ${D3D8UtilsIncludes})
    source_group ("D3D8 Utils source files"  FILES ${D3D8UtilsSources})
    source_group ("GDI32 include files"      FILES ${GDI32Includes})
    source_group ("GDI32 source files"       FILES ${GDI32Sources})
    source_group ("Kernel32 include files"   FILES ${Kernel32Includes})
    source_group ("Kernel32 source files"    FILES ${Kernel32Sources})
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
    source_group ("Entrypoint include files\\GL3.3"  FILES ${OpenGL32EntrypointsIncludes_GL3_3})
    source_group ("Entrypoint include files\\GL4.0"  FILES ${OpenGL32EntrypointsIncludes_GL4_0})
    source_group ("Entrypoint include files\\GL4.1"  FILES ${OpenGL32EntrypointsIncludes_GL4_1})
    source_group ("Entrypoint include files\\GL4.2"  FILES ${OpenGL32EntrypointsIncludes_GL4_2})
    source_group ("Entrypoint include files\\GL4.3"  FILES ${OpenGL32EntrypointsIncludes_GL4_3})
    source_group ("Entrypoint include files\\GL4.4"  FILES ${OpenGL32EntrypointsIncludes_GL4_4})
    source_group ("Entrypoint include files\\GL4.5"  FILES ${OpenGL32EntrypointsIncludes_GL4_5})
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
    source_group ("Entrypoint source files\\GL3.3"  FILES ${OpenGL32EntrypointsSources_GL3_3})
    source_group ("Entrypoint source files\\GL4.0"  FILES ${OpenGL32EntrypointsSources_GL4_0})
    source_group ("Entrypoint source files\\GL4.1"  FILES ${OpenGL32EntrypointsSources_GL4_1})
    source_group ("Entrypoint source files\\GL4.2"  FILES ${OpenGL32EntrypointsSources_GL4_2})
    source_group ("Entrypoint source files\\GL4.3"  FILES ${OpenGL32EntrypointsSources_GL4_3})
    source_group ("Entrypoint source files\\GL4.4"  FILES ${OpenGL32EntrypointsSources_GL4_4})
    source_group ("Entrypoint source files\\GL4.5"  FILES ${OpenGL32EntrypointsSources_GL4_5})
    source_group ("OpenGL32 include files"   FILES ${OpenGL32Includes})
    source_group ("OpenGL32 source files"    FILES ${OpenGL32Sources})
    source_group ("User32 include files"     FILES ${User32Includes})
    source_group ("User32 source files"      FILES ${User32Sources})
    source_group ("WGL include files"        FILES ${WGLIncludes})
    source_group ("WGL source files"         FILES ${WGLSources})
endif()
