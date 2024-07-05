/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.0/gl_blend_func.h"
#include "OpenGL/entrypoints/GL1.0/gl_clear.h"
#include "OpenGL/entrypoints/GL1.0/gl_clear_color.h"
#include "OpenGL/entrypoints/GL1.0/gl_clear_depth.h"
#include "OpenGL/entrypoints/GL1.0/gl_clear_stencil.h"
#include "OpenGL/entrypoints/GL1.0/gl_color_mask.h"
#include "OpenGL/entrypoints/GL1.0/gl_cull_face.h"
#include "OpenGL/entrypoints/GL1.0/gl_depth_func.h"
#include "OpenGL/entrypoints/GL1.0/gl_depth_mask.h"
#include "OpenGL/entrypoints/GL1.0/gl_depth_range.h"
#include "OpenGL/entrypoints/GL1.0/gl_disable.h"
#include "OpenGL/entrypoints/GL1.0/gl_draw_buffer.h"
#include "OpenGL/entrypoints/GL1.0/gl_enable.h"
#include "OpenGL/entrypoints/GL1.0/gl_finish.h"
#include "OpenGL/entrypoints/GL1.0/gl_flush.h"
#include "OpenGL/entrypoints/GL1.0/gl_front_face.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_booleanv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_doublev.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_error.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_floatv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_integerv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_string.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_image.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_level_parameterfv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_level_parameteriv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_parameterfv.h"
#include "OpenGL/entrypoints/GL1.0/gl_get_tex_parameteriv.h"
#include "OpenGL/entrypoints/GL1.0/gl_hint.h"
#include "OpenGL/entrypoints/GL1.0/gl_is_enabled.h"
#include "OpenGL/entrypoints/GL1.0/gl_line_width.h"
#include "OpenGL/entrypoints/GL1.0/gl_logic_op.h"
#include "OpenGL/entrypoints/GL1.0/gl_pixel_storef.h"
#include "OpenGL/entrypoints/GL1.0/gl_pixel_storei.h"
#include "OpenGL/entrypoints/GL1.0/gl_point_size.h"
#include "OpenGL/entrypoints/GL1.0/gl_polygon_mode.h"
#include "OpenGL/entrypoints/GL1.0/gl_read_buffer.h"
#include "OpenGL/entrypoints/GL1.0/gl_read_pixels.h"
#include "OpenGL/entrypoints/GL1.0/gl_scissor.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_func.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_mask.h"
#include "OpenGL/entrypoints/GL1.0/gl_stencil_op.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_image_1d.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_image_2d.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameterf.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameterfv.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameteri.h"
#include "OpenGL/entrypoints/GL1.0/gl_tex_parameteriv.h"
#include "OpenGL/entrypoints/GL1.0/gl_viewport.h"

#include "OpenGL/entrypoints/GL1.1/gl_accum.h"
#include "OpenGL/entrypoints/GL1.1/gl_alpha_func.h"
#include "OpenGL/entrypoints/GL1.1/gl_are_textures_resident.h"
#include "OpenGL/entrypoints/GL1.1/gl_array_element.h"
#include "OpenGL/entrypoints/GL1.1/gl_begin.h"
#include "OpenGL/entrypoints/GL1.1/gl_bind_texture.h"
#include "OpenGL/entrypoints/GL1.1/gl_bitmap.h"
#include "OpenGL/entrypoints/GL1.1/gl_call_list.h"
#include "OpenGL/entrypoints/GL1.1/gl_call_lists.h"
#include "OpenGL/entrypoints/GL1.1/gl_clear_accum.h"
#include "OpenGL/entrypoints/GL1.1/gl_clear_index.h"
#include "OpenGL/entrypoints/GL1.1/gl_clip_plane.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3b.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3bv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3d.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3f.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3i.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3s.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3ub.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3ubv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3ui.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3uiv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3us.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_3usv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4b.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4bv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4d.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4f.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4i.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4s.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4ub.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4ubv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4ui.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4uiv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4us.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_4usv.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_material.h"
#include "OpenGL/entrypoints/GL1.1/gl_color_pointer.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_pixels.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_image_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_image_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_sub_image_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_copy_tex_sub_image_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_delete_lists.h"
#include "OpenGL/entrypoints/GL1.1/gl_delete_textures.h"
#include "OpenGL/entrypoints/GL1.1/gl_disable_client_state.h"
#include "OpenGL/entrypoints/GL1.1/gl_draw_arrays.h"
#include "OpenGL/entrypoints/GL1.1/gl_draw_elements.h"
#include "OpenGL/entrypoints/GL1.1/gl_draw_pixels.h"
#include "OpenGL/entrypoints/GL1.1/gl_edge_flag.h"
#include "OpenGL/entrypoints/GL1.1/gl_edge_flagv.h"
#include "OpenGL/entrypoints/GL1.1/gl_edge_flag_pointer.h"
#include "OpenGL/entrypoints/GL1.1/gl_enable_client_state.h"
#include "OpenGL/entrypoints/GL1.1/gl_end.h"
#include "OpenGL/entrypoints/GL1.1/gl_end_list.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_1dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_1f.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_1fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_2dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_2f.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_coord_2fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_mesh1.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_mesh2.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_point1.h"
#include "OpenGL/entrypoints/GL1.1/gl_eval_point2.h"
#include "OpenGL/entrypoints/GL1.1/gl_feedback_buffer.h"
#include "OpenGL/entrypoints/GL1.1/gl_fogf.h"
#include "OpenGL/entrypoints/GL1.1/gl_fogfv.h"
#include "OpenGL/entrypoints/GL1.1/gl_fogi.h"
#include "OpenGL/entrypoints/GL1.1/gl_fogiv.h"
#include "OpenGL/entrypoints/GL1.1/gl_frustum.h"
#include "OpenGL/entrypoints/GL1.1/gl_gen_lists.h"
#include "OpenGL/entrypoints/GL1.1/gl_gen_textures.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_clip_plane.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_light_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_light_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_map_dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_map_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_map_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_material_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_material_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_pixel_map_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_pixel_map_uiv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_pixel_map_usv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_pointerv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_polygon_stipple.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_tex_env_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_tex_env_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_tex_gen_dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_get_tex_gen_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_d.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_i.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_mask.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_pointer.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_s.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_ub.h"
#include "OpenGL/entrypoints/GL1.1/gl_index_ubv.h"
#include "OpenGL/entrypoints/GL1.1/gl_init_names.h"
#include "OpenGL/entrypoints/GL1.1/gl_interleaved_arrays.h"
#include "OpenGL/entrypoints/GL1.1/gl_is_list.h"
#include "OpenGL/entrypoints/GL1.1/gl_is_texture.h"
#include "OpenGL/entrypoints/GL1.1/gl_light_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_light_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_light_i.h"
#include "OpenGL/entrypoints/GL1.1/gl_light_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_light_model_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_light_model_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_light_model_i.h"
#include "OpenGL/entrypoints/GL1.1/gl_light_model_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_line_stipple.h"
#include "OpenGL/entrypoints/GL1.1/gl_list_base.h"
#include "OpenGL/entrypoints/GL1.1/gl_load_identity.h"
#include "OpenGL/entrypoints/GL1.1/gl_load_matrix_d.h"
#include "OpenGL/entrypoints/GL1.1/gl_load_matrix_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_load_name.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_1f.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_2f.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_1f.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_map_grid_2f.h"
#include "OpenGL/entrypoints/GL1.1/gl_material_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_material_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_material_i.h"
#include "OpenGL/entrypoints/GL1.1/gl_material_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_matrix_mode.h"
#include "OpenGL/entrypoints/GL1.1/gl_mult_matrix_d.h"
#include "OpenGL/entrypoints/GL1.1/gl_mult_matrix_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_new_list.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3b.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3bv.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3d.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3f.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3i.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3s.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_3sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_normal_pointer.h"
#include "OpenGL/entrypoints/GL1.1/gl_ortho.h"
#include "OpenGL/entrypoints/GL1.1/gl_passthrough.h"
#include "OpenGL/entrypoints/GL1.1/gl_pixel_map_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_pixel_map_uiv.h"
#include "OpenGL/entrypoints/GL1.1/gl_pixel_map_usv.h"
#include "OpenGL/entrypoints/GL1.1/gl_pixel_transfer_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_pixel_transfer_i.h"
#include "OpenGL/entrypoints/GL1.1/gl_pixel_zoom.h"
#include "OpenGL/entrypoints/GL1.1/gl_polygon_offset.h"
#include "OpenGL/entrypoints/GL1.1/gl_polygon_stipple.h"
#include "OpenGL/entrypoints/GL1.1/gl_pop_attrib.h"
#include "OpenGL/entrypoints/GL1.1/gl_pop_client_attrib.h"
#include "OpenGL/entrypoints/GL1.1/gl_pop_matrix.h"
#include "OpenGL/entrypoints/GL1.1/gl_pop_name.h"
#include "OpenGL/entrypoints/GL1.1/gl_prioritize_textures.h"
#include "OpenGL/entrypoints/GL1.1/gl_push_attrib.h"
#include "OpenGL/entrypoints/GL1.1/gl_push_client_attrib.h"
#include "OpenGL/entrypoints/GL1.1/gl_push_matrix.h"
#include "OpenGL/entrypoints/GL1.1/gl_push_name.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2f.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2i.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2s.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_2sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3d.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3f.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3i.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3s.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_3sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4d.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4f.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4i.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4s.h"
#include "OpenGL/entrypoints/GL1.1/gl_raster_pos_4sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_d.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_i.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_s.h"
#include "OpenGL/entrypoints/GL1.1/gl_rect_sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_render_mode.h"
#include "OpenGL/entrypoints/GL1.1/gl_rotate_d.h"
#include "OpenGL/entrypoints/GL1.1/gl_rotate_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_scale_d.h"
#include "OpenGL/entrypoints/GL1.1/gl_scale_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_select_buffer.h"
#include "OpenGL/entrypoints/GL1.1/gl_shade_model.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1f.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1i.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1s.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_1sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2f.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2i.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2s.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_2sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3d.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3f.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3i.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3s.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_3sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4d.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4f.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4i.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4s.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_4sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_coord_pointer.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_env_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_env_fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_env_i.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_env_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_gen_d.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_gen_dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_gen_i.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_gen_iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_sub_image_1d.h"
#include "OpenGL/entrypoints/GL1.1/gl_tex_sub_image_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_translate_d.h"
#include "OpenGL/entrypoints/GL1.1/gl_translate_f.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2d.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2f.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2i.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2s.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_2sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3d.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3f.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3i.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3s.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_3sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4d.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4dv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4f.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4fv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4i.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4iv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4s.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_4sv.h"
#include "OpenGL/entrypoints/GL1.1/gl_vertex_pointer.h"

#include "OpenGL/entrypoints/GL1.2/gl_copy_tex_sub_image_3d.h"
#include "OpenGL/entrypoints/GL1.2/gl_draw_range_elements.h"
#include "OpenGL/entrypoints/GL1.2/gl_tex_image_3d.h"
#include "OpenGL/entrypoints/GL1.2/gl_tex_sub_image_3d.h"

#include "OpenGL/entrypoints/GL1.3/gl_active_texture.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_1d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_2d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_3d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_1d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_2d.h"
#include "OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_3d.h"
#include "OpenGL/entrypoints/GL1.3/gl_get_compressed_tex_image.h"
#include "OpenGL/entrypoints/GL1.3/gl_sample_coverage.h"

#include "OpenGL/entrypoints/GL1.4/gl_blend_color.h"
#include "OpenGL/entrypoints/GL1.4/gl_blend_equation.h"
#include "OpenGL/entrypoints/GL1.4/gl_blend_func_separate.h"
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_arrays.h"
#include "OpenGL/entrypoints/GL1.4/gl_multi_draw_elements.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameterf.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameterfv.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameteri.h"
#include "OpenGL/entrypoints/GL1.4/gl_point_parameteriv.h"

#include "OpenGL/entrypoints/GL1.5/gl_begin_query.h"
#include "OpenGL/entrypoints/GL1.5/gl_bind_buffer.h"
#include "OpenGL/entrypoints/GL1.5/gl_buffer_data.h"
#include "OpenGL/entrypoints/GL1.5/gl_buffer_sub_data.h"
#include "OpenGL/entrypoints/GL1.5/gl_delete_buffers.h"
#include "OpenGL/entrypoints/GL1.5/gl_delete_queries.h"
#include "OpenGL/entrypoints/GL1.5/gl_end_query.h"
#include "OpenGL/entrypoints/GL1.5/gl_gen_buffers.h"
#include "OpenGL/entrypoints/GL1.5/gl_gen_queries.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_parameteriv.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_pointerv.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_buffer_sub_data.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_queryiv.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_query_objectiv.h"
#include "OpenGL/entrypoints/GL1.5/gl_get_query_objectuiv.h"
#include "OpenGL/entrypoints/GL1.5/gl_is_buffer.h"
#include "OpenGL/entrypoints/GL1.5/gl_is_query.h"
#include "OpenGL/entrypoints/GL1.5/gl_map_buffer.h"
#include "OpenGL/entrypoints/GL1.5/gl_unmap_buffer.h"

#include "OpenGL/entrypoints/GL2.0/gl_attach_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_bind_attrib_location.h"
#include "OpenGL/entrypoints/GL2.0/gl_blend_equation_separate.h"
#include "OpenGL/entrypoints/GL2.0/gl_compile_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_create_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_create_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_delete_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_delete_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_detach_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_disable_vertex_attrib_array.h"
#include "OpenGL/entrypoints/GL2.0/gl_draw_buffers.h"
#include "OpenGL/entrypoints/GL2.0/gl_enable_vertex_attrib_array.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_active_attrib.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_active_uniform.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_attached_shaders.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_attrib_location.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_programiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_program_info_log.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_shaderiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_shader_info_log.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_shader_source.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_uniformfv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_uniformiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_uniform_location.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attribdv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attribfv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attribiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_get_vertex_attrib_pointerv.h"
#include "OpenGL/entrypoints/GL2.0/gl_is_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_is_shader.h"
#include "OpenGL/entrypoints/GL2.0/gl_link_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_shader_source.h"
#include "OpenGL/entrypoints/GL2.0/gl_stencil_func_separate.h"
#include "OpenGL/entrypoints/GL2.0/gl_stencil_mask_separate.h"
#include "OpenGL/entrypoints/GL2.0/gl_stencil_op_separate.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_1f.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_1fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_1i.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_1iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2f.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2i.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_2iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3f.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3i.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_3iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4f.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4i.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_4iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_matrix_2fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_matrix_3fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_uniform_matrix_4fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_use_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_validate_program.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1d.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1dv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1f.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1s.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1sv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2d.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2dv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2f.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2s.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2sv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3d.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3dv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3f.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3s.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3sv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4bv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4d.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4dv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4f.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4fv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4iv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nbv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Niv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nsv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nub.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nubv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nuiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nusv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4s.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4sv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4ubv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4uiv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4usv.h"
#include "OpenGL/entrypoints/GL2.0/gl_vertex_attrib_pointer.h"

#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_2x3_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_2x4_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_3x2_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_3x4_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_4x2_fv.h"
#include "OpenGL/entrypoints/GL2.1/gl_uniform_matrix_4x3_fv.h"

#include "OpenGL/entrypoints/GL3.0/gl_begin_conditional_render.h"
#include "OpenGL/entrypoints/GL3.0/gl_begin_transform_feedback.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_buffer_base.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_buffer_range.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_frag_data_location.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_framebuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_renderbuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_bind_vertex_array.h"
#include "OpenGL/entrypoints/GL3.0/gl_blit_framebuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_check_framebuffer_status.h"
#include "OpenGL/entrypoints/GL3.0/gl_clamp_color.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_fi.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_fv.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_clear_buffer_uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_color_maski.h"
#include "OpenGL/entrypoints/GL3.0/gl_delete_framebuffers.h"
#include "OpenGL/entrypoints/GL3.0/gl_delete_renderbuffers.h"
#include "OpenGL/entrypoints/GL3.0/gl_delete_vertex_arrays.h"
#include "OpenGL/entrypoints/GL3.0/gl_disablei.h"
#include "OpenGL/entrypoints/GL3.0/gl_enablei.h"
#include "OpenGL/entrypoints/GL3.0/gl_end_conditional_render.h"
#include "OpenGL/entrypoints/GL3.0/gl_end_transform_feedback.h"
#include "OpenGL/entrypoints/GL3.0/gl_flush_mapped_buffer_range.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_renderbuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_1d.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_2d.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_3d.h"
#include "OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_layer.h"
#include "OpenGL/entrypoints/GL3.0/gl_generate_mipmap.h"
#include "OpenGL/entrypoints/GL3.0/gl_gen_framebuffers.h"
#include "OpenGL/entrypoints/GL3.0/gl_gen_renderbuffers.h"
#include "OpenGL/entrypoints/GL3.0/gl_gen_vertex_arrays.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_booleani_v.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_frag_data_location.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_framebuffer_attachment_parameteriv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_integeri_v.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_renderbuffer_parameteriv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_stringi.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_tex_parameter_i_iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_tex_parameter_i_uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_transform_feedback_varying.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_uniformuiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_vertex_attrib_i_iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_get_vertex_attrib_i_uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_enabledi.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_framebuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_renderbuffer.h"
#include "OpenGL/entrypoints/GL3.0/gl_is_vertex_array.h"
#include "OpenGL/entrypoints/GL3.0/gl_map_buffer_range.h"
#include "OpenGL/entrypoints/GL3.0/gl_renderbuffer_storage.h"
#include "OpenGL/entrypoints/GL3.0/gl_renderbuffer_storage_multisample.h"
#include "OpenGL/entrypoints/GL3.0/gl_tex_parameter_i_iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_tex_parameter_i_uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_transform_feedback_varyings.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_1ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_1uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_2ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_2uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_3ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_3uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_4ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_uniform_4uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1i.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2i.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3i.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4bv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4i.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4iv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4sv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ubv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ui.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4uiv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4usv.h"
#include "OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_pointer.h"

#include "OpenGL/entrypoints/GL3.1/gl_copy_buffer_sub_data.h"
#include "OpenGL/entrypoints/GL3.1/gl_draw_arrays_instanced.h"
#include "OpenGL/entrypoints/GL3.1/gl_draw_elements_instanced.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniformsiv.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_blockiv.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_block_name.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_active_uniform_name.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_uniform_block_index.h"
#include "OpenGL/entrypoints/GL3.1/gl_get_uniform_indices.h"
#include "OpenGL/entrypoints/GL3.1/gl_primitive_restart_index.h"
#include "OpenGL/entrypoints/GL3.1/gl_tex_buffer.h"
#include "OpenGL/entrypoints/GL3.1/gl_uniform_block_binding.h"

#include "OpenGL/entrypoints/GL3.2/gl_client_wait_sync.h"
#include "OpenGL/entrypoints/GL3.2/gl_delete_sync.h"
#include "OpenGL/entrypoints/GL3.2/gl_draw_elements_base_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_draw_elements_instanced_base_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_draw_range_elements_base_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_fence_sync.h"
#include "OpenGL/entrypoints/GL3.2/gl_framebuffer_texture.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_buffer_parameteri64v.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_integer64i_v.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_integer64v.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_multisamplefv.h"
#include "OpenGL/entrypoints/GL3.2/gl_get_synciv.h"
#include "OpenGL/entrypoints/GL3.2/gl_is_sync.h"
#include "OpenGL/entrypoints/GL3.2/gl_multi_draw_elements_base_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_provoking_vertex.h"
#include "OpenGL/entrypoints/GL3.2/gl_sample_maski.h"
#include "OpenGL/entrypoints/GL3.2/gl_tex_image_2d_multisample.h"
#include "OpenGL/entrypoints/GL3.2/gl_tex_image_3d_multisample.h"
#include "OpenGL/entrypoints/GL3.2/gl_wait_sync.h"

#include "OpenGL/entrypoints/GL_ARB_color_buffer_float/gl_clamp_color_arb.h"

#include "OpenGL/entrypoints/GL_ARB_draw_buffers/gl_draw_buffers_arb.h"

#include "OpenGL/entrypoints/GL_ARB_draw_instanced/gl_draw_arrays_instanced_arb.h"
#include "OpenGL/entrypoints/GL_ARB_draw_instanced/gl_draw_elements_instanced_arb.h"

#include "OpenGL/entrypoints/GL_ARB_multisample/gl_sample_coverage_arb.h"

#include "OpenGL/entrypoints/GL_ARB_multitexture/gl_active_texture_arb.h"

#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_begin_query_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_delete_queries_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_end_query_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_gen_queries_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_get_queryiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_get_query_objectiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_get_query_objectuiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_occlusion_query/gl_is_query_arb.h"

#include "OpenGL/entrypoints/GL_ARB_point_parameters/gl_point_parameterf_arb.h"
#include "OpenGL/entrypoints/GL_ARB_point_parameters/gl_point_parameterfv_arb.h"

#include "OpenGL/entrypoints/GL_ARB_texture_buffer_object/gl_tex_buffer_arb.h"

#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_image_1d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_image_2d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_image_3d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_sub_image_1d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_sub_image_2d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_sub_image_3d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_texture_compression/gl_get_compressed_tex_image_arb.h"

#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_bind_buffer_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_buffer_data_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_buffer_sub_data_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_delete_buffers_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_gen_buffers_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_get_buffer_parameteriv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_get_buffer_pointerv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_get_buffer_sub_data_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_is_buffer_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_map_buffer_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_unmap_buffer_arb.h"

#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_disable_vertex_attrib_array_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_enable_vertex_attrib_array_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attribdv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attribfv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attribiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attrib_pointerv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1dv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1fv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1f_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1sv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1s_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2dv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2fv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2f_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2sv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2s_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3dv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3fv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3f_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3sv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3s_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4bv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4dv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4d_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4fv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4f_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4iv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nbv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Niv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nsv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nubv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nub_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nuiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4sv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4s_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4ubv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4uiv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4usv_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_pointer_arb.h"

#include "OpenGL/entrypoints/GL_ARB_vertex_shader/gl_bind_attrib_location_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_shader/gl_get_active_attrib_arb.h"
#include "OpenGL/entrypoints/GL_ARB_vertex_shader/gl_get_attrib_location_arb.h"

#include "OpenGL/entrypoints/GL_EXT_texture_object/gl_are_textures_resident_ext.h"
#include "OpenGL/entrypoints/GL_EXT_texture_object/gl_bind_texture_ext.h"
#include "OpenGL/entrypoints/GL_EXT_texture_object/gl_delete_textures_ext.h"
#include "OpenGL/entrypoints/GL_EXT_texture_object/gl_gen_textures_ext.h"
#include "OpenGL/entrypoints/GL_EXT_texture_object/gl_is_texture_ext.h"
#include "OpenGL/entrypoints/GL_EXT_texture_object/gl_prioritize_textures_ext.h"

#include "OpenGL/globals.h"
#include "OpenGL/interceptors.h"

std::unordered_map<std::string, void*> OpenGL::get_func_name_to_func_ptr_map()
{
    /* NOTE: If you add any new entrypoints to this function, make sure to also update OpenGL::Context::init_dispatch_table() */

    std::unordered_map<std::string, void*> result;

    result["glCopyTexSubImage3D"] = OpenGL::aiCopyTexSubImage3D;
    result["glDrawRangeElements"] = OpenGL::aiDrawRangeElements;
    result["glTexImage3D"]        = OpenGL::aiTexImage3D;
    result["glTexSubImage3D"]     = OpenGL::aiTexSubImage3D;

    result["glActiveTexture"]           = OpenGL::aiActiveTexture;
    result["glCompressedTexImage1D"]    = OpenGL::aiCompressedTexImage1D;
    result["glCompressedTexImage2D"]    = OpenGL::aiCompressedTexImage2D;
    result["glCompressedTexImage3D"]    = OpenGL::aiCompressedTexImage3D;
    result["glCompressedTexSubImage1D"] = OpenGL::aiCompressedTexSubImage1D;
    result["glCompressedTexSubImage2D"] = OpenGL::aiCompressedTexSubImage2D;
    result["glCompressedTexSubImage3D"] = OpenGL::aiCompressedTexSubImage3D;
    result["glGetCompressedTexImage"]   = OpenGL::aiGetCompressedTexImage;
    result["glSampleCoverage"]          = OpenGL::aiSampleCoverage;

    result["glBlendColor"]        = OpenGL::aiBlendColor;
    result["glBlendEquation"]     = OpenGL::aiBlendEquation;
    result["glBlendFuncSeparate"] = OpenGL::aiBlendFuncSeparate;
    result["glMultiDrawArrays"]   = OpenGL::aiMultiDrawArrays;
    result["glMultiDrawElements"] = OpenGL::aiMultiDrawElements;
    result["glPointParameterf"]   = OpenGL::aiPointParameterf;
    result["glPointParameterfv"]  = OpenGL::aiPointParameterfv;
    result["glPointParameteri"]   = OpenGL::aiPointParameteri;
    result["glPointParameteriv"]  = OpenGL::aiPointParameteriv;

    result["glBeginQuery"]           = OpenGL::aiBeginQuery;
    result["glBindBuffer"]           = OpenGL::aiBindBuffer;
    result["glBufferData"]           = OpenGL::aiBufferData;
    result["glBufferSubData"]        = OpenGL::aiBufferSubData;
    result["glDeleteBuffers"]        = OpenGL::aiDeleteBuffers;
    result["glDeleteQueries"]        = OpenGL::aiDeleteQueries;
    result["glEndQuery"]             = OpenGL::aiEndQuery;
    result["glGenBuffers"]           = OpenGL::aiGenBuffers;
    result["glGenQueries"]           = OpenGL::aiGenQueries;
    result["glGetBufferParameteriv"] = OpenGL::aiGetBufferParameteriv;
    result["glGetBufferPointerv"]    = OpenGL::aiGetBufferPointerv;
    result["glGetBufferSubData"]     = OpenGL::aiGetBufferSubData;
    result["glGetQueryiv"]           = OpenGL::aiGetQueryiv;
    result["glGetQueryObjectiv"]     = OpenGL::aiGetQueryObjectiv;
    result["glGetQueryObjectuiv"]    = OpenGL::aiGetQueryObjectuiv;
    result["glIsBuffer"]             = OpenGL::aiIsBuffer;
    result["glIsQuery"]              = OpenGL::aiIsQuery;
    result["glMapBuffer"]            = OpenGL::aiMapBuffer;
    result["glUnmapBuffer"]          = OpenGL::aiUnmapBuffer;

    result["glAttachShader"]             = OpenGL::aiAttachShader;
    result["glBindAttribLocation"]       = OpenGL::aiBindAttribLocation;
    result["glBlendEquationSeparate"]    = OpenGL::aiBlendEquationSeparate;
    result["glCompileShader"]            = OpenGL::aiCompileShader;
    result["glCreateProgram"]            = OpenGL::aiCreateProgram;
    result["glCreateShader"]             = OpenGL::aiCreateShader;
    result["glDeleteProgram"]            = OpenGL::aiDeleteProgram;
    result["glDeleteShader"]             = OpenGL::aiDeleteShader;
    result["glDetachShader"]             = OpenGL::aiDetachShader;
    result["glDisableVertexAttribArray"] = OpenGL::aiDisableVertexAttribArray;
    result["glDrawBuffers"]              = OpenGL::aiDrawBuffers;
    result["glEnableVertexAttribArray"]  = OpenGL::aiEnableVertexAttribArray;
    result["glGetActiveAttrib"]          = OpenGL::aiGetActiveAttrib;
    result["glGetActiveUniform"]         = OpenGL::aiGetActiveUniform;
    result["glGetAttachedShaders"]       = OpenGL::aiGetAttachedShaders;
    result["glGetAttribLocation"]        = OpenGL::aiGetAttribLocation;
    result["glGetProgramiv"]             = OpenGL::aiGetProgramiv;
    result["glGetProgramInfoLog"]        = OpenGL::aiGetProgramInfoLog;
    result["glGetShaderiv"]              = OpenGL::aiGetShaderiv;
    result["glGetShaderInfoLog"]         = OpenGL::aiGetShaderInfoLog;
    result["glGetShaderSource"]          = OpenGL::aiGetShaderSource;
    result["glGetUniformfv"]             = OpenGL::aiGetUniformfv;
    result["glGetUniformiv"]             = OpenGL::aiGetUniformiv;
    result["glGetUniformLocation"]       = OpenGL::aiGetUniformLocation;
    result["glGetVertexAttribdv"]        = OpenGL::aiGetVertexAttribdv;
    result["glGetVertexAttribfv"]        = OpenGL::aiGetVertexAttribfv;
    result["glGetVertexAttribiv"]        = OpenGL::aiGetVertexAttribiv;
    result["glGetVertexAttribPointerv"]  = OpenGL::aiGetVertexAttribPointerv;
    result["glIsProgram"]                = OpenGL::aiIsProgram;
    result["glIsShader"]                 = OpenGL::aiIsShader;
    result["glLinkProgram"]              = OpenGL::aiLinkProgram;
    result["glShaderSource"]             = OpenGL::aiShaderSource;
    result["glStencilFuncSeparate"]      = OpenGL::aiStencilFuncSeparate;
    result["glStencilMaskSeparate"]      = OpenGL::aiStencilMaskSeparate;
    result["glStencilOpSeparate"]        = OpenGL::aiStencilOpSeparate;
    result["glUniform1f"]                = OpenGL::aiUniform1f;
    result["glUniform1fv"]               = OpenGL::aiUniform1fv;
    result["glUniform1i"]                = OpenGL::aiUniform1i;
    result["glUniform1iv"]               = OpenGL::aiUniform1iv;
    result["glUniform2f"]                = OpenGL::aiUniform2f;
    result["glUniform2fv"]               = OpenGL::aiUniform2fv;
    result["glUniform2i"]                = OpenGL::aiUniform2i;
    result["glUniform2iv"]               = OpenGL::aiUniform2iv;
    result["glUniform3f"]                = OpenGL::aiUniform3f;
    result["glUniform3fv"]               = OpenGL::aiUniform3fv;
    result["glUniform3i"]                = OpenGL::aiUniform3i;
    result["glUniform3iv"]               = OpenGL::aiUniform3iv;
    result["glUniform4f"]                = OpenGL::aiUniform4f;
    result["glUniform4fv"]               = OpenGL::aiUniform4fv;
    result["glUniform4i"]                = OpenGL::aiUniform4i;
    result["glUniform4iv"]               = OpenGL::aiUniform4iv;
    result["glUniformMatrix2fv"]         = OpenGL::aiUniformMatrix2fv;
    result["glUniformMatrix3fv"]         = OpenGL::aiUniformMatrix3fv;
    result["glUniformMatrix4fv"]         = OpenGL::aiUniformMatrix4fv;
    result["glUseProgram"]               = OpenGL::aiUseProgram;
    result["glValidateProgram"]          = OpenGL::aiValidateProgram;
    result["glVertexAttrib1d"]           = OpenGL::aiVertexAttrib1d;
    result["glVertexAttrib1dv"]          = OpenGL::aiVertexAttrib1dv;
    result["glVertexAttrib1f"]           = OpenGL::aiVertexAttrib1f;
    result["glVertexAttrib1fv"]          = OpenGL::aiVertexAttrib1fv;
    result["glVertexAttrib1s"]           = OpenGL::aiVertexAttrib1s;
    result["glVertexAttrib1sv"]          = OpenGL::aiVertexAttrib1sv;
    result["glVertexAttrib2d"]           = OpenGL::aiVertexAttrib2d;
    result["glVertexAttrib2dv"]          = OpenGL::aiVertexAttrib2dv;
    result["glVertexAttrib2f"]           = OpenGL::aiVertexAttrib2f;
    result["glVertexAttrib2fv"]          = OpenGL::aiVertexAttrib2fv;
    result["glVertexAttrib2s"]           = OpenGL::aiVertexAttrib2s;
    result["glVertexAttrib2sv"]          = OpenGL::aiVertexAttrib2sv;
    result["glVertexAttrib3d"]           = OpenGL::aiVertexAttrib3d;
    result["glVertexAttrib3dv"]          = OpenGL::aiVertexAttrib3dv;
    result["glVertexAttrib3f"]           = OpenGL::aiVertexAttrib3f;
    result["glVertexAttrib3fv"]          = OpenGL::aiVertexAttrib3fv;
    result["glVertexAttrib3s"]           = OpenGL::aiVertexAttrib3s;
    result["glVertexAttrib3sv"]          = OpenGL::aiVertexAttrib3sv;
    result["glVertexAttrib4bv"]          = OpenGL::aiVertexAttrib4bv;
    result["glVertexAttrib4d"]           = OpenGL::aiVertexAttrib4d;
    result["glVertexAttrib4dv"]          = OpenGL::aiVertexAttrib4dv;
    result["glVertexAttrib4f"]           = OpenGL::aiVertexAttrib4f;
    result["glVertexAttrib4fv"]          = OpenGL::aiVertexAttrib4fv;
    result["glVertexAttrib4iv"]          = OpenGL::aiVertexAttrib4iv;
    result["glVertexAttrib4Nbv"]         = OpenGL::aiVertexAttrib4Nbv;
    result["glVertexAttrib4Niv"]         = OpenGL::aiVertexAttrib4Niv;
    result["glVertexAttrib4Nsv"]         = OpenGL::aiVertexAttrib4Nsv;
    result["glVertexAttrib4Nub"]         = OpenGL::aiVertexAttrib4Nub;
    result["glVertexAttrib4Nubv"]        = OpenGL::aiVertexAttrib4Nubv;
    result["glVertexAttrib4Nuiv"]        = OpenGL::aiVertexAttrib4Nuiv;
    result["glVertexAttrib4Nusv"]        = OpenGL::aiVertexAttrib4Nusv;
    result["glVertexAttrib4s"]           = OpenGL::aiVertexAttrib4s;
    result["glVertexAttrib4sv"]          = OpenGL::aiVertexAttrib4sv;
    result["glVertexAttrib4ubv"]         = OpenGL::aiVertexAttrib4ubv;
    result["glVertexAttrib4uiv"]         = OpenGL::aiVertexAttrib4uiv;
    result["glVertexAttrib4usv"]         = OpenGL::aiVertexAttrib4usv;
    result["glVertexAttribPointer"]      = OpenGL::aiVertexAttribPointer;

    result["glUniformMatrix2x3fv"] = OpenGL::aiUniformMatrix2x3fv;
    result["glUniformMatrix2x4fv"] = OpenGL::aiUniformMatrix2x4fv;
    result["glUniformMatrix3x2fv"] = OpenGL::aiUniformMatrix3x2fv;
    result["glUniformMatrix3x4fv"] = OpenGL::aiUniformMatrix3x4fv;
    result["glUniformMatrix4x2fv"] = OpenGL::aiUniformMatrix4x2fv;
    result["glUniformMatrix4x3fv"] = OpenGL::aiUniformMatrix4x3fv;

    result["glBeginConditionalRender"]              = OpenGL::aiBeginConditionalRender;
    result["glBeginTransformFeedback"]              = OpenGL::aiBeginTransformFeedback;
    result["glBindBufferBase"]                      = OpenGL::aiBindBufferBase;
    result["glBindBufferRange"]                     = OpenGL::aiBindBufferRange;
    result["glBindFragDataLocation"]                = OpenGL::aiBindFragDataLocation;
    result["glBindFramebuffer"]                     = OpenGL::aiBindFramebuffer;
    result["glBindRenderbuffer"]                    = OpenGL::aiBindRenderbuffer;
    result["glBindVertexArray"]                     = OpenGL::aiBindVertexArray;
    result["glBlitFramebuffer"]                     = OpenGL::aiBlitFramebuffer;
    result["glCheckFramebufferStatus"]              = OpenGL::aiCheckFramebufferStatus;
    result["glClampColor"]                          = OpenGL::aiClampColor;
    result["glClearBufferfi"]                       = OpenGL::aiClearBufferfi;
    result["glClearBufferfv"]                       = OpenGL::aiClearBufferfv;
    result["glClearBufferiv"]                       = OpenGL::aiClearBufferiv;
    result["glClearBufferuiv"]                      = OpenGL::aiClearBufferuiv;
    result["glColorMaski"]                          = OpenGL::aiColorMaski;
    result["glDeleteFramebuffers"]                  = OpenGL::aiDeleteFramebuffers;
    result["glDeleteRenderbuffers"]                 = OpenGL::aiDeleteRenderbuffers;
    result["glDeleteVertexArrays"]                  = OpenGL::aiDeleteVertexArrays;
    result["glDisablei"]                            = OpenGL::aiDisablei;
    result["glEnablei"]                             = OpenGL::aiEnablei;
    result["glEndConditionalRender"]                = OpenGL::aiEndConditionalRender;
    result["glEndTransformFeedback"]                = OpenGL::aiEndTransformFeedback;
    result["glFlushMappedBufferRange"]              = OpenGL::aiFlushMappedBufferRange;
    result["glFramebufferRenderbuffer"]             = OpenGL::aiFramebufferRenderbuffer;
    result["glFramebufferTexture1D"]                = OpenGL::aiFramebufferTexture1D;
    result["glFramebufferTexture2D"]                = OpenGL::aiFramebufferTexture2D;
    result["glFramebufferTexture3D"]                = OpenGL::aiFramebufferTexture3D;
    result["glFramebufferTextureLayer"]             = OpenGL::aiFramebufferTextureLayer;
    result["glGenerateMipmap"]                      = OpenGL::aiGenerateMipmap;
    result["glGenFramebuffers"]                     = OpenGL::aiGenFramebuffers;
    result["glGenRenderbuffers"]                    = OpenGL::aiGenRenderbuffers;
    result["glGenVertexArrays"]                     = OpenGL::aiGenVertexArrays;
    result["glGetBooleani_v"]                       = OpenGL::aiGetBooleani_v;
    result["glGetFragDataLocation"]                 = OpenGL::aiGetFragDataLocation;
    result["glGetFramebufferAttachmentParameteriv"] = OpenGL::aiGetFramebufferAttachmentParameteriv;
    result["glGetIntegeri_v"]                       = OpenGL::aiGetIntegeri_v;
    result["glGetRenderbufferParameteriv"]          = OpenGL::aiGetRenderbufferParameteriv;
    result["glGetStringi"]                          = OpenGL::aiGetStringi;
    result["glGetTexParameterIiv"]                  = OpenGL::aiGetTexParameterIiv;
    result["glGetTexParameterIuiv"]                 = OpenGL::aiGetTexParameterIuiv;
    result["glGetTransformFeedbackVarying"]         = OpenGL::aiGetTransformFeedbackVarying;
    result["glGetUniformuiv"]                       = OpenGL::aiGetUniformuiv;
    result["glGetVertexAttribIiv"]                  = OpenGL::aiGetVertexAttribIiv;
    result["glGetVertexAttribIuiv"]                 = OpenGL::aiGetVertexAttribIuiv;
    result["glIsEnabledi"]                          = OpenGL::aiIsEnabledi;
    result["glIsFramebuffer"]                       = OpenGL::aiIsFramebuffer;
    result["glIsRenderbuffer"]                      = OpenGL::aiIsRenderbuffer;
    result["glIsVertexArray"]                       = OpenGL::aiIsVertexArray;
    result["glMapBufferRange"]                      = OpenGL::aiMapBufferRange;
    result["glRenderbufferStorage"]                 = OpenGL::aiRenderbufferStorage;
    result["glRenderbufferStorageMultisample"]      = OpenGL::aiRenderbufferStorageMultisample;
    result["glTexParameterIiv"]                     = OpenGL::aiTexParameterIiv;
    result["glTexParameterIuiv"]                    = OpenGL::aiTexParameterIuiv;
    result["glTransformFeedbackVaryings"]           = OpenGL::aiTransformFeedbackVaryings;
    result["glUniform1ui"]                          = OpenGL::aiUniform1ui;
    result["glUniform1uiv"]                         = OpenGL::aiUniform1uiv;
    result["glUniform2ui"]                          = OpenGL::aiUniform2ui;
    result["glUniform2uiv"]                         = OpenGL::aiUniform2uiv;
    result["glUniform3ui"]                          = OpenGL::aiUniform3ui;
    result["glUniform3uiv"]                         = OpenGL::aiUniform3uiv;
    result["glUniform4ui"]                          = OpenGL::aiUniform4ui;
    result["glUniform4uiv"]                         = OpenGL::aiUniform4uiv;
    result["glVertexAttribI1i"]                     = OpenGL::aiVertexAttribI1i;
    result["glVertexAttribI1iv"]                    = OpenGL::aiVertexAttribI1iv;
    result["glVertexAttribI1ui"]                    = OpenGL::aiVertexAttribI1ui;
    result["glVertexAttribI1uiv"]                   = OpenGL::aiVertexAttribI1uiv;
    result["glVertexAttribI2i"]                     = OpenGL::aiVertexAttribI2i;
    result["glVertexAttribI2iv"]                    = OpenGL::aiVertexAttribI2iv;
    result["glVertexAttribI2ui"]                    = OpenGL::aiVertexAttribI2ui;
    result["glVertexAttribI2uiv"]                   = OpenGL::aiVertexAttribI2uiv;
    result["glVertexAttribI3i"]                     = OpenGL::aiVertexAttribI3i;
    result["glVertexAttribI3iv"]                    = OpenGL::aiVertexAttribI3iv;
    result["glVertexAttribI3ui"]                    = OpenGL::aiVertexAttribI3ui;
    result["glVertexAttribI3uiv"]                   = OpenGL::aiVertexAttribI3uiv;
    result["glVertexAttribI4bv"]                    = OpenGL::aiVertexAttribI4bv;
    result["glVertexAttribI4i"]                     = OpenGL::aiVertexAttribI4i;
    result["glVertexAttribI4iv"]                    = OpenGL::aiVertexAttribI4iv;
    result["glVertexAttribI4sv"]                    = OpenGL::aiVertexAttribI4sv;
    result["glVertexAttribI4ubv"]                   = OpenGL::aiVertexAttribI4ubv;
    result["glVertexAttribI4ui"]                    = OpenGL::aiVertexAttribI4ui;
    result["glVertexAttribI4uiv"]                   = OpenGL::aiVertexAttribI4uiv;
    result["glVertexAttribI4usv"]                   = OpenGL::aiVertexAttribI4usv;
    result["glVertexAttribIPointer"]                = OpenGL::aiVertexAttribIPointer;
    result["glViewport"]                            = OpenGL::aiViewport;

    result["glCopyBufferSubData"]         = OpenGL::aiCopyBufferSubData;
    result["glDrawArraysInstanced"]       = OpenGL::aiDrawArraysInstanced;
    result["glDrawElementsInstanced"]     = OpenGL::aiDrawElementsInstanced;
    result["glGetActiveUniformsiv"]       = OpenGL::aiGetActiveUniformsiv;
    result["glGetActiveUniformBlockiv"]   = OpenGL::aiGetActiveUniformBlockiv;
    result["glGetActiveUniformBlockName"] = OpenGL::aiGetActiveUniformBlockName;
    result["glGetActiveUniformName"]      = OpenGL::aiGetActiveUniformName;
    result["glGetUniformBlockIndex"]      = OpenGL::aiGetUniformBlockIndex;
    result["glGetUniformIndices"]         = OpenGL::aiGetUniformIndices;
    result["glPrimitiveRestartIndex"]     = OpenGL::aiPrimitiveRestartIndex;
    result["glTexBuffer"]                 = OpenGL::aiTexBuffer;
    result["glUniformBlockBinding"]       = OpenGL::aiUniformBlockBinding;

    result["glClientWaitSync"]                  = OpenGL::aiClientWaitSync;
    result["glDeleteSync"]                      = OpenGL::aiDeleteSync;
    result["glDrawElementsBaseVertex"]          = OpenGL::aiDrawElementsBaseVertex;
    result["glDrawElementsInstancedBaseVertex"] = OpenGL::aiDrawElementsInstancedBaseVertex;
    result["glDrawRangeElementsBaseVertex"]     = OpenGL::aiDrawRangeElementsBaseVertex;
    result["glFenceSync"]                       = OpenGL::aiFenceSync;
    result["glFramebufferTexture"]              = OpenGL::aiFramebufferTexture;
    result["glGetBufferParameteri64v"]          = OpenGL::aiGetBufferParameteri64v;
    result["glGetInteger64i_v"]                 = OpenGL::aiGetInteger64i_v;
    result["glGetInteger64v"]                   = OpenGL::aiGetInteger64v;
    result["glGetMultisamplefv"]                = OpenGL::aiGetMultisamplefv;
    result["glGetSynciv"]                       = OpenGL::aiGetSynciv;
    result["glIsSync"]                          = OpenGL::aiIsSync;
    result["glMultiDrawElementsBaseVertex"]     = OpenGL::aiMultiDrawElementsBaseVertex;
    result["glProvokingVertex"]                 = OpenGL::aiProvokingVertex;
    result["glSampleMaski"]                     = OpenGL::aiSampleMaski;
    result["glTexImage2DMultisample"]           = OpenGL::aiTexImage2DMultisample;
    result["glTexImage3DMultisample"]           = OpenGL::aiTexImage3DMultisample;
    result["glWaitSync"]                        = OpenGL::aiWaitSync;

    result["glClampColorARB"] = OpenGL::aiClampColorARB;

    result["glDrawBuffersARB"] = OpenGL::aiDrawBuffersARB;

    result["glDrawArraysInstancedARB"]   = OpenGL::aiDrawArraysInstancedARB;
    result["glDrawElementsInstancedARB"] = OpenGL::aiDrawElementsInstancedARB;

    result["glSampleCoverageARB"] = OpenGL::aiSampleCoverageARB;

    result["glActiveTextureARB"] = OpenGL::aiActiveTextureARB;

    result["glBeginQueryARB"]        = OpenGL::aiBeginQueryARB;
    result["glDeleteQueriesARB"]     = OpenGL::aiDeleteQueriesARB;
    result["glEndQueryARB"]          = OpenGL::aiEndQueryARB;
    result["glGenQueriesARB"]        = OpenGL::aiGenQueriesARB;
    result["glGetQueryivARB"]        = OpenGL::aiGetQueryivARB;
    result["glGetQueryObjectivARB"]  = OpenGL::aiGetQueryObjectivARB;
    result["glGetQueryObjectuivARB"] = OpenGL::aiGetQueryObjectuivARB;
    result["glIsQueryARB"]           = OpenGL::aiIsQueryARB;

    result["glPointParameterfARB"]  = OpenGL::aiPointParameterfARB;
    result["glPointParameterfvARB"] = OpenGL::aiPointParameterfvARB;

    result["glTexBufferARB"] = OpenGL::aiTexBufferARB;

    result["glCompressedTexImage1DARB"]    = OpenGL::aiCompressedTexImage1DARB;
    result["glCompressedTexImage2DARB"]    = OpenGL::aiCompressedTexImage2DARB;
    result["glCompressedTexImage3DARB"]    = OpenGL::aiCompressedTexImage3DARB;
    result["glCompressedTexSubImage1DARB"] = OpenGL::aiCompressedTexSubImage1DARB;
    result["glCompressedTexSubImage2DARB"] = OpenGL::aiCompressedTexSubImage2DARB;
    result["glCompressedTexSubImage3DARB"] = OpenGL::aiCompressedTexSubImage3DARB;
    result["glGetCompressedTexImageARB"]   = OpenGL::aiGetCompressedTexImageARB;

    result["glBindBufferARB"]           = OpenGL::aiBindBufferARB;
    result["glBufferDataARB"]           = OpenGL::aiBufferDataARB;
    result["glBufferSubDataARB"]        = OpenGL::aiBufferSubDataARB;
    result["glDeleteBuffersARB"]        = OpenGL::aiDeleteBuffersARB;
    result["glGenBuffersARB"]           = OpenGL::aiGenBuffersARB;
    result["glGetBufferParameterivARB"] = OpenGL::aiGetBufferParameterivARB;
    result["glGetBufferPointervARB"]    = OpenGL::aiGetBufferPointervARB;
    result["glGetBufferSubDataARB"]     = OpenGL::aiGetBufferSubDataARB;
    result["glIsBufferARB"]             = OpenGL::aiIsBufferARB;
    result["glMapBufferARB"]            = OpenGL::aiMapBufferARB;
    result["glUnmapBufferARB"]          = OpenGL::aiUnmapBufferARB;

    result["glDisableVertexAttribArrayARB"] = OpenGL::aiDisableVertexAttribArrayARB;
    result["glEnableVertexAttribArrayARB"]  = OpenGL::aiEnableVertexAttribArrayARB;
    result["glGetVertexAttribdvARB"]        = OpenGL::aiGetVertexAttribdvARB;
    result["glGetVertexAttribfvARB"]        = OpenGL::aiGetVertexAttribfvARB;
    result["glGetVertexAttribivARB"]        = OpenGL::aiGetVertexAttribivARB;
    result["glGetVertexAttribPointervARB"]  = OpenGL::aiGetVertexAttribPointervARB;
    result["glVertexAttrib1dvARB"]          = OpenGL::aiVertexAttrib1dvARB;
    result["glVertexAttrib1dARB"]           = OpenGL::aiVertexAttrib1dARB;
    result["glVertexAttrib1fvARB"]          = OpenGL::aiVertexAttrib1fvARB;
    result["glVertexAttrib1fARB"]           = OpenGL::aiVertexAttrib1fARB;
    result["glVertexAttrib1svARB"]          = OpenGL::aiVertexAttrib1svARB;
    result["glVertexAttrib1sARB"]           = OpenGL::aiVertexAttrib1sARB;
    result["glVertexAttrib2dvARB"]          = OpenGL::aiVertexAttrib2dvARB;
    result["glVertexAttrib2dARB"]           = OpenGL::aiVertexAttrib2dARB;
    result["glVertexAttrib2fvARB"]          = OpenGL::aiVertexAttrib2fvARB;
    result["glVertexAttrib2fARB"]           = OpenGL::aiVertexAttrib2fARB;
    result["glVertexAttrib2svARB"]          = OpenGL::aiVertexAttrib2svARB;
    result["glVertexAttrib2sARB"]           = OpenGL::aiVertexAttrib2sARB;
    result["glVertexAttrib3dvARB"]          = OpenGL::aiVertexAttrib3dvARB;
    result["glVertexAttrib3dARB"]           = OpenGL::aiVertexAttrib3dARB;
    result["glVertexAttrib3fvARB"]          = OpenGL::aiVertexAttrib3fvARB;
    result["glVertexAttrib3fARB"]           = OpenGL::aiVertexAttrib3fARB;
    result["glVertexAttrib3svARB"]          = OpenGL::aiVertexAttrib3svARB;
    result["glVertexAttrib3sARB"]           = OpenGL::aiVertexAttrib3sARB;
    result["glVertexAttrib4bvARB"]          = OpenGL::aiVertexAttrib4bvARB;
    result["glVertexAttrib4dvARB"]          = OpenGL::aiVertexAttrib4dvARB;
    result["glVertexAttrib4dARB"]           = OpenGL::aiVertexAttrib4dARB;
    result["glVertexAttrib4fvARB"]          = OpenGL::aiVertexAttrib4fvARB;
    result["glVertexAttrib4fARB"]           = OpenGL::aiVertexAttrib4fARB;
    result["glVertexAttrib4ivARB"]          = OpenGL::aiVertexAttrib4ivARB;
    result["glVertexAttrib4NbvARB"]         = OpenGL::aiVertexAttrib4NbvARB;
    result["glVertexAttrib4NivARB"]         = OpenGL::aiVertexAttrib4NivARB;
    result["glVertexAttrib4NsvARB"]         = OpenGL::aiVertexAttrib4NsvARB;
    result["glVertexAttrib4NubvARB"]        = OpenGL::aiVertexAttrib4NubvARB;
    result["glVertexAttrib4NubARB"]         = OpenGL::aiVertexAttrib4NubARB;
    result["glVertexAttrib4NuivARB"]        = OpenGL::aiVertexAttrib4NuivARB;
    result["glVertexAttrib4svARB"]          = OpenGL::aiVertexAttrib4svARB;
    result["glVertexAttrib4sARB"]           = OpenGL::aiVertexAttrib4sARB;
    result["glVertexAttrib4ubvARB"]         = OpenGL::aiVertexAttrib4ubvARB;
    result["glVertexAttrib4uivARB"]         = OpenGL::aiVertexAttrib4uivARB;
    result["glVertexAttrib4usvARB"]         = OpenGL::aiVertexAttrib4usvARB;
    result["glVertexAttribPointerARB"]      = OpenGL::aiVertexAttribPointerARB;

    result["glBindAttribLocationARB"] = OpenGL::aiBindAttribLocationARB;
    result["glGetActiveAttribARB"]    = OpenGL::aiGetActiveAttribARB;
    result["glGetAttribLocationARB"]  = OpenGL::aiGetAttribLocationARB;

    /* GL_EXT_texture_object */
    result["glAreTexturesResidentEXT"] = OpenGL::aiAreTexturesResidentEXT;
    result["glBindTextureEXT"]         = OpenGL::aiBindTextureEXT;
    result["glDeleteTexturesEXT"]      = OpenGL::aiDeleteTexturesEXT;
    result["glGenTexturesEXT"]         = OpenGL::aiGenTexturesEXT;
    result["glIsTextureEXT"]           = OpenGL::aiIsTextureEXT;
    result["glPrioritizeTexturesEXT"]  = OpenGL::aiPrioritizeTexturesEXT;

    /* Compatibility profile (<= GL 1.1) */
    result["glAccum"]               = OpenGL::aiAccum;
    result["glAlphaFunc"]           = OpenGL::aiAlphaFunc;
    result["glAreTexturesResident"] = OpenGL::aiAreTexturesResident;
    result["glArrayElement"]        = OpenGL::aiArrayElement;
    result["glBegin"]               = OpenGL::aiBegin;
    result["glBitmap"]              = OpenGL::aiBitmap;
    result["glCallList"]            = OpenGL::aiCallList;
    result["glCallLists"]           = OpenGL::aiCallLists;
    result["glClearAccum"]          = OpenGL::aiClearAccum;
    result["glClearIndex"]          = OpenGL::aiClearIndex;
    result["glClipPlane"]           = OpenGL::aiClipPlane;
    result["glColor3b"]             = OpenGL::aiColor3b;
    result["glColor3bv"]            = OpenGL::aiColor3bv;
    result["glColor3d"]             = OpenGL::aiColor3d;
    result["glColor3dv"]            = OpenGL::aiColor3dv;
    result["glColor3f"]             = OpenGL::aiColor3f;
    result["glColor3fv"]            = OpenGL::aiColor3fv;
    result["glColor3i"]             = OpenGL::aiColor3i;
    result["glColor3iv"]            = OpenGL::aiColor3iv;
    result["glColor3s"]             = OpenGL::aiColor3s;
    result["glColor3sv"]            = OpenGL::aiColor3sv;
    result["glColor3ub"]            = OpenGL::aiColor3ub;
    result["glColor3ubv"]           = OpenGL::aiColor3ubv;
    result["glColor3ui"]            = OpenGL::aiColor3ui;
    result["glColor3uiv"]           = OpenGL::aiColor3uiv;
    result["glColor3us"]            = OpenGL::aiColor3us;
    result["glColor3usv"]           = OpenGL::aiColor3usv;
    result["glColor4b"]             = OpenGL::aiColor4b;
    result["glColor4bv"]            = OpenGL::aiColor4bv;
    result["glColor4d"]             = OpenGL::aiColor4d;
    result["glColor4dv"]            = OpenGL::aiColor4dv;
    result["glColor4f"]             = OpenGL::aiColor4f;
    result["glColor4fv"]            = OpenGL::aiColor4fv;
    result["glColor4i"]             = OpenGL::aiColor4i;
    result["glColor4iv"]            = OpenGL::aiColor4iv;
    result["glColor4s"]             = OpenGL::aiColor4s;
    result["glColor4sv"]            = OpenGL::aiColor4sv;
    result["glColor4ub"]            = OpenGL::aiColor4ub;
    result["glColor4ubv"]           = OpenGL::aiColor4ubv;
    result["glColor4ui"]            = OpenGL::aiColor4ui;
    result["glColor4uiv"]           = OpenGL::aiColor4uiv;
    result["glColor4us"]            = OpenGL::aiColor4us;
    result["glColor4usv"]           = OpenGL::aiColor4usv;
    result["glColorMaterial"]       = OpenGL::aiColorMaterial;
    result["glColorPointer"]        = OpenGL::aiColorPointer;
    result["glCopyPixels"]          = OpenGL::aiCopyPixels;
    result["glDeleteLists"]         = OpenGL::aiDeleteLists;
    result["glDisableClientState"]  = OpenGL::aiDisableClientState;
    result["glDrawPixels"]          = OpenGL::aiDrawPixels;
    result["glEdgeFlag"]            = OpenGL::aiEdgeFlag;
    result["glEdgeFlagv"]           = OpenGL::aiEdgeFlagv;
    result["glEdgeFlagPointer"]     = OpenGL::aiEdgeFlagPointer;
    result["glEnableClientState"]   = OpenGL::aiEnableClientState;
    result["glEndList"]             = OpenGL::aiEndList;
    result["glEvalCoord1d"]         = OpenGL::aiEvalCoord1d;
    result["glEvalCoord1dv"]        = OpenGL::aiEvalCoord1dv;
    result["glEvalCoord1f"]         = OpenGL::aiEvalCoord1f;
    result["glEvalCoord1fv"]        = OpenGL::aiEvalCoord1fv;
    result["glEvalCoord2d"]         = OpenGL::aiEvalCoord2d;
    result["glEvalCoord2dv"]        = OpenGL::aiEvalCoord2dv;
    result["glEvalCoord2f"]         = OpenGL::aiEvalCoord2f;
    result["glEvalCoord2fv"]        = OpenGL::aiEvalCoord2fv;
    result["glEvalMesh1"]           = OpenGL::aiEvalMesh1;
    result["glEvalMesh2"]           = OpenGL::aiEvalMesh2;
    result["glEvalPoint1"]          = OpenGL::aiEvalPoint1;
    result["glEvalPoint2"]          = OpenGL::aiEvalPoint2;
    result["glFeedbackBuffer"]      = OpenGL::aiFeedbackBuffer;
    result["glFogf"]                = OpenGL::aiFogf;
    result["glFogfv"]               = OpenGL::aiFogfv;
    result["glFogi"]                = OpenGL::aiFogi;
    result["glFogiv"]               = OpenGL::aiFogiv;
    result["glFrustum"]             = OpenGL::aiFrustum;
    result["glGenLists"]            = OpenGL::aiGenLists;
    result["glGetClipPlane"]        = OpenGL::aiGetClipPlane;
    result["glGetLightfv"]          = OpenGL::aiGetLightfv;
    result["glGetLightiv"]          = OpenGL::aiGetLightiv;
    result["glGetMapdv"]            = OpenGL::aiGetMapdv;
    result["glGetMapfv"]            = OpenGL::aiGetMapfv;
    result["glGetMapiv"]            = OpenGL::aiGetMapiv;
    result["glGetMaterialfv"]       = OpenGL::aiGetMaterialfv;
    result["glGetMaterialiv"]       = OpenGL::aiGetMaterialiv;
    result["glGetPixelMapfv"]       = OpenGL::aiGetPixelMapfv;
    result["glGetPixelMapuiv"]      = OpenGL::aiGetPixelMapuiv;
    result["glGetPixelMapusv"]      = OpenGL::aiGetPixelMapusv;
    result["glGetPointerv"]         = OpenGL::aiGetPointerv;
    result["glGetPolygonStipple"]   = OpenGL::aiGetPolygonStipple;
    result["glGetTexEnvfv"]         = OpenGL::aiGetTexEnvfv;
    result["glGetTexEnviv"]         = OpenGL::aiGetTexEnviv;
    result["glGetTexGendv"]         = OpenGL::aiGetTexGendv;
    result["glGetTexGeniv"]         = OpenGL::aiGetTexGeniv;
    result["glIndexd"]              = OpenGL::aiIndexd;
    result["glIndexdv"]             = OpenGL::aiIndexdv;
    result["glIndexf"]              = OpenGL::aiIndexf;
    result["glIndexfv"]             = OpenGL::aiIndexfv;
    result["glIndexi"]              = OpenGL::aiIndexi;
    result["glIndexiv"]             = OpenGL::aiIndexiv;
    result["glIndexMask"]           = OpenGL::aiIndexMask;
    result["glIndexPointer"]        = OpenGL::aiIndexPointer;
    result["glIndexs"]              = OpenGL::aiIndexs;
    result["glIndexsv"]             = OpenGL::aiIndexsv;
    result["glIndexub"]             = OpenGL::aiIndexub;
    result["glIndexubv"]            = OpenGL::aiIndexubv;
    result["glInitNames"]           = OpenGL::aiInitNames;
    result["glInterleavedArrays"]   = OpenGL::aiInterleavedArrays;
    result["glIsList"]              = OpenGL::aiIsList;
    result["glLightf"]              = OpenGL::aiLightf;
    result["glLightfv"]             = OpenGL::aiLightfv;
    result["glLighti"]              = OpenGL::aiLighti;
    result["glLightiv"]             = OpenGL::aiLightiv;
    result["glLightModelf"]         = OpenGL::aiLightModelf;
    result["glLightModelfv"]        = OpenGL::aiLightModelfv;
    result["glLightModeli"]         = OpenGL::aiLightModeli;
    result["glLightModeliv"]        = OpenGL::aiLightModeliv;
    result["glLineStipple"]         = OpenGL::aiLineStipple;
    result["glListBase"]            = OpenGL::aiListBase;
    result["glLoadIdentity"]        = OpenGL::aiLoadIdentity;
    result["glLoadMatrixd"]         = OpenGL::aiLoadMatrixd;
    result["glLoadMatrixf"]         = OpenGL::aiLoadMatrixf;
    result["glLoadName"]            = OpenGL::aiLoadName;
    result["glMap1d"]               = OpenGL::aiMap1d;
    result["glMap1f"]               = OpenGL::aiMap1f;
    result["glMap2d"]               = OpenGL::aiMap2d;
    result["glMap2f"]               = OpenGL::aiMap2f;
    result["glMapGrid1d"]           = OpenGL::aiMapGrid1d;
    result["glMapGrid1f"]           = OpenGL::aiMapGrid1f;
    result["glMapGrid2d"]           = OpenGL::aiMapGrid2d;
    result["glMapGrid2f"]           = OpenGL::aiMapGrid2f;
    result["glMaterialf"]           = OpenGL::aiMaterialf;
    result["glMaterialfv"]          = OpenGL::aiMaterialfv;
    result["glMateriali"]           = OpenGL::aiMateriali;
    result["glMaterialiv"]          = OpenGL::aiMaterialiv;
    result["glMatrixMode"]          = OpenGL::aiMatrixMode;
    result["glMultMatrixd"]         = OpenGL::aiMultMatrixd;
    result["glMultMatrixf"]         = OpenGL::aiMultMatrixf;
    result["glNewList"]             = OpenGL::aiNewList;
    result["glNormal3b"]            = OpenGL::aiNormal3b;
    result["glNormal3bv"]           = OpenGL::aiNormal3bv;
    result["glNormal3d"]            = OpenGL::aiNormal3d;
    result["glNormal3dv"]           = OpenGL::aiNormal3dv;
    result["glNormal3f"]            = OpenGL::aiNormal3f;
    result["glNormal3fv"]           = OpenGL::aiNormal3fv;
    result["glNormal3i"]            = OpenGL::aiNormal3i;
    result["glNormal3iv"]           = OpenGL::aiNormal3iv;
    result["glNormal3s"]            = OpenGL::aiNormal3s;
    result["glNormal3sv"]           = OpenGL::aiNormal3sv;
    result["glNormalPointer"]       = OpenGL::aiNormalPointer;
    result["glOrtho"]               = OpenGL::aiOrtho;
    result["glPassthrough"]         = OpenGL::aiPassthrough;
    result["glPixelMapfv"]          = OpenGL::aiPixelMapfv;
    result["glPixelMapuiv"]         = OpenGL::aiPixelMapuiv;
    result["glPixelMapusv"]         = OpenGL::aiPixelMapusv;
    result["glPixelStoref"]         = OpenGL::aiPixelStoref;
    result["glPixelStorei"]         = OpenGL::aiPixelStorei;
    result["glPixelTransferf"]      = OpenGL::aiPixelTransferf;
    result["glPixelTransferi"]      = OpenGL::aiPixelTransferi;
    result["glPixelZoom"]           = OpenGL::aiPixelZoom;
    result["glPolygonStipple"]      = OpenGL::aiPolygonStipple;
    result["glPopAttrib"]           = OpenGL::aiPopAttrib;
    result["glPopClientAttrib"]     = OpenGL::aiPopClientAttrib;
    result["glPopMatrix"]           = OpenGL::aiPopMatrix;
    result["glPopName"]             = OpenGL::aiPopName;
    result["glPrioritizeTextures"]  = OpenGL::aiPrioritizeTextures;
    result["glPushAttrib"]          = OpenGL::aiPushAttrib;
    result["glPushClientAttrib"]    = OpenGL::aiPushClientAttrib;
    result["glPushMatrix"]          = OpenGL::aiPushMatrix;
    result["glPushName"]            = OpenGL::aiPushName;
    result["glRasterPos2d"]         = OpenGL::aiRasterPos2d;
    result["glRasterPos2dv"]        = OpenGL::aiRasterPos2dv;
    result["glRasterPos2f"]         = OpenGL::aiRasterPos2f;
    result["glRasterPos2fv"]        = OpenGL::aiRasterPos2fv;
    result["glRasterPos2i"]         = OpenGL::aiRasterPos2i;
    result["glRasterPos2iv"]        = OpenGL::aiRasterPos2iv;
    result["glRasterPos2s"]         = OpenGL::aiRasterPos2s;
    result["glRasterPos2sv"]        = OpenGL::aiRasterPos2sv;
    result["glRasterPos3d"]         = OpenGL::aiRasterPos3d;
    result["glRasterPos3dv"]        = OpenGL::aiRasterPos3dv;
    result["glRasterPos3f"]         = OpenGL::aiRasterPos3f;
    result["glRasterPos3fv"]        = OpenGL::aiRasterPos3fv;
    result["glRasterPos3i"]         = OpenGL::aiRasterPos3i;
    result["glRasterPos3iv"]        = OpenGL::aiRasterPos3iv;
    result["glRasterPos3s"]         = OpenGL::aiRasterPos3s;
    result["glRasterPos3sv"]        = OpenGL::aiRasterPos3sv;
    result["glRasterPos4d"]         = OpenGL::aiRasterPos4d;
    result["glRasterPos4dv"]        = OpenGL::aiRasterPos4dv;
    result["glRasterPos4f"]         = OpenGL::aiRasterPos4f;
    result["glRasterPos4fv"]        = OpenGL::aiRasterPos4fv;
    result["glRasterPos4i"]         = OpenGL::aiRasterPos4i;
    result["glRasterPos4iv"]        = OpenGL::aiRasterPos4iv;
    result["glRasterPos4s"]         = OpenGL::aiRasterPos4s;
    result["glRasterPos4sv"]        = OpenGL::aiRasterPos4sv;
    result["glRectd"]               = OpenGL::aiRectd;
    result["glRectdv"]              = OpenGL::aiRectdv;
    result["glRectf"]               = OpenGL::aiRectf;
    result["glRectfv"]              = OpenGL::aiRectfv;
    result["glRecti"]               = OpenGL::aiRecti;
    result["glRectiv"]              = OpenGL::aiRectiv;
    result["glRects"]               = OpenGL::aiRects;
    result["glRectsv"]              = OpenGL::aiRectsv;
    result["glRenderMode"]          = OpenGL::aiRenderMode;
    result["glRotated"]             = OpenGL::aiRotated;
    result["glRotatef"]             = OpenGL::aiRotatef;
    result["glScaled"]              = OpenGL::aiScaled;
    result["glScalef"]              = OpenGL::aiScalef;
    result["glSelectBuffer"]        = OpenGL::aiSelectBuffer;
    result["glShadeModel"]          = OpenGL::aiShadeModel;
    result["glTexCoord1d"]          = OpenGL::aiTexCoord1d;
    result["glTexCoord1dv"]         = OpenGL::aiTexCoord1dv;
    result["glTexCoord1f"]          = OpenGL::aiTexCoord1f;
    result["glTexCoord1fv"]         = OpenGL::aiTexCoord1fv;
    result["glTexCoord1i"]          = OpenGL::aiTexCoord1i;
    result["glTexCoord1iv"]         = OpenGL::aiTexCoord1iv;
    result["glTexCoord1s"]          = OpenGL::aiTexCoord1s;
    result["glTexCoord1sv"]         = OpenGL::aiTexCoord1sv;
    result["glTexCoord2d"]          = OpenGL::aiTexCoord2d;
    result["glTexCoord2dv"]         = OpenGL::aiTexCoord2dv;
    result["glTexCoord2f"]          = OpenGL::aiTexCoord2f;
    result["glTexCoord2fv"]         = OpenGL::aiTexCoord2fv;
    result["glTexCoord2i"]          = OpenGL::aiTexCoord2i;
    result["glTexCoord2iv"]         = OpenGL::aiTexCoord2iv;
    result["glTexCoord2s"]          = OpenGL::aiTexCoord2s;
    result["glTexCoord2sv"]         = OpenGL::aiTexCoord2sv;
    result["glTexCoord3d"]          = OpenGL::aiTexCoord3d;
    result["glTexCoord3dv"]         = OpenGL::aiTexCoord3dv;
    result["glTexCoord3f"]          = OpenGL::aiTexCoord3f;
    result["glTexCoord3fv"]         = OpenGL::aiTexCoord3fv;
    result["glTexCoord3i"]          = OpenGL::aiTexCoord3i;
    result["glTexCoord3iv"]         = OpenGL::aiTexCoord3iv;
    result["glTexCoord3s"]          = OpenGL::aiTexCoord3s;
    result["glTexCoord3sv"]         = OpenGL::aiTexCoord3sv;
    result["glTexCoord4d"]          = OpenGL::aiTexCoord4d;
    result["glTexCoord4dv"]         = OpenGL::aiTexCoord4dv;
    result["glTexCoord4f"]          = OpenGL::aiTexCoord4f;
    result["glTexCoord4fv"]         = OpenGL::aiTexCoord4fv;
    result["glTexCoord4i"]          = OpenGL::aiTexCoord4i;
    result["glTexCoord4iv"]         = OpenGL::aiTexCoord4iv;
    result["glTexCoord4s"]          = OpenGL::aiTexCoord4s;
    result["glTexCoord4sv"]         = OpenGL::aiTexCoord4sv;
    result["glTexCoordPointer"]     = OpenGL::aiTexCoordPointer;
    result["glTexEnvf"]             = OpenGL::aiTexEnvf;
    result["glTexEnvfv"]            = OpenGL::aiTexEnvfv;
    result["glTexEnvi"]             = OpenGL::aiTexEnvi;
    result["glTexEnviv"]            = OpenGL::aiTexEnviv;
    result["glTexGend"]             = OpenGL::aiTexGend;
    result["glTexGendv"]            = OpenGL::aiTexGendv;
    result["glTexGeni"]             = OpenGL::aiTexGeni;
    result["glTexGeniv"]            = OpenGL::aiTexGeniv;
    result["glTranslated"]          = OpenGL::aiTranslated;
    result["glTranslatef"]          = OpenGL::aiTranslatef;
    result["glVertex2d"]            = OpenGL::aiVertex2d;
    result["glVertex2dv"]           = OpenGL::aiVertex2dv;
    result["glVertex2f"]            = OpenGL::aiVertex2f;
    result["glVertex2fv"]           = OpenGL::aiVertex2fv;
    result["glVertex2i"]            = OpenGL::aiVertex2i;
    result["glVertex2iv"]           = OpenGL::aiVertex2iv;
    result["glVertex2s"]            = OpenGL::aiVertex2s;
    result["glVertex2sv"]           = OpenGL::aiVertex2sv;
    result["glVertex3d"]            = OpenGL::aiVertex3d;
    result["glVertex3dv"]           = OpenGL::aiVertex3dv;
    result["glVertex3f"]            = OpenGL::aiVertex3f;
    result["glVertex3fv"]           = OpenGL::aiVertex3fv;
    result["glVertex3i"]            = OpenGL::aiVertex3i;
    result["glVertex3iv"]           = OpenGL::aiVertex3iv;
    result["glVertex3s"]            = OpenGL::aiVertex3s;
    result["glVertex3sv"]           = OpenGL::aiVertex3sv;
    result["glVertex4d"]            = OpenGL::aiVertex4d;
    result["glVertex4dv"]           = OpenGL::aiVertex4dv;
    result["glVertex4f"]            = OpenGL::aiVertex4f;
    result["glVertex4fv"]           = OpenGL::aiVertex4fv;
    result["glVertex4i"]            = OpenGL::aiVertex4i;
    result["glVertex4iv"]           = OpenGL::aiVertex4iv;
    result["glVertex4s"]            = OpenGL::aiVertex4s;
    result["glVertex4sv"]           = OpenGL::aiVertex4sv;
    result["glVertexPointer"]       = OpenGL::aiVertexPointer;

    return result;
}

std::vector<APIInterceptor::FunctionInterceptor> OpenGL::get_function_interceptors()
{
    /* NOTE: If you add any new entrypoints to this function, make sure to also update OpenGL::Context::init_dispatch_table() */

    /* <= GL 1.1 */
    return std::vector<APIInterceptor::FunctionInterceptor>
    {
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_bind_texture,              OpenGL::aiBindTexture),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_blend_func,                OpenGL::aiBlendFunc),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_clear,                     OpenGL::aiClear),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_clear_color,               OpenGL::aiClearColor),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_clear_depth,               OpenGL::aiClearDepth),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_clear_stencil,             OpenGL::aiClearStencil),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_mask,                OpenGL::aiColorMask),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_copy_tex_image_1d,         OpenGL::aiCopyTexImage1D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_copy_tex_image_2d,         OpenGL::aiCopyTexImage2D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_copy_tex_sub_image_1d,     OpenGL::aiCopyTexSubImage1D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_copy_tex_sub_image_2d,     OpenGL::aiCopyTexSubImage2D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_cull_face,                 OpenGL::aiCullFace),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_delete_textures,           OpenGL::aiDeleteTextures),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_depth_func,                OpenGL::aiDepthFunc),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_depth_mask,                OpenGL::aiDepthMask),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_depth_range,               OpenGL::aiDepthRange),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_disable,                   OpenGL::aiDisable),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_draw_arrays,               OpenGL::aiDrawArrays),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_draw_buffer,               OpenGL::aiDrawBuffer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_draw_elements,             OpenGL::aiDrawElements),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_enable,                    OpenGL::aiEnable),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_finish,                    OpenGL::aiFinish),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_flush,                     OpenGL::aiFlush),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_front_face,                OpenGL::aiFrontFace),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_gen_textures,              OpenGL::aiGenTextures),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_booleanv,              OpenGL::aiGetBooleanv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_doublev,               OpenGL::aiGetDoublev),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_error,                 OpenGL::aiGetError),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_floatv,                OpenGL::aiGetFloatv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_integerv,              OpenGL::aiGetIntegerv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_string,                OpenGL::aiGetString),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_tex_image,             OpenGL::aiGetTexImage),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_tex_level_parameterfv, OpenGL::aiGetTexLevelParameterfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_tex_level_parameteriv, OpenGL::aiGetTexLevelParameteriv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_tex_parameterfv,       OpenGL::aiGetTexParameterfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_tex_parameteriv,       OpenGL::aiGetTexParameteriv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_hint,                      OpenGL::aiHint),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_is_enabled,                OpenGL::aiIsEnabled),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_is_texture,                OpenGL::aiIsTexture),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_line_width,                OpenGL::aiLineWidth),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_logic_op,                  OpenGL::aiLogicOp),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_storef,              OpenGL::aiPixelStoref),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_storei,              OpenGL::aiPixelStorei),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_point_size,                OpenGL::aiPointSize),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_polygon_mode,              OpenGL::aiPolygonMode),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_polygon_offset,            OpenGL::aiPolygonOffset),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_read_buffer,               OpenGL::aiReadBuffer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_read_pixels,               OpenGL::aiReadPixels),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_scissor,                   OpenGL::aiScissor),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_stencil_func,              OpenGL::aiStencilFunc),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_stencil_mask,              OpenGL::aiStencilMask),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_stencil_op,                OpenGL::aiStencilOp),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_image_1d,              OpenGL::aiTexImage1D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_image_2d,              OpenGL::aiTexImage2D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_parameterf,            OpenGL::aiTexParameterf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_parameterfv,           OpenGL::aiTexParameterfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_parameteri,            OpenGL::aiTexParameteri),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_parameteriv,           OpenGL::aiTexParameteriv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_sub_image_1d,          OpenGL::aiTexSubImage1D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_sub_image_2d,          OpenGL::aiTexSubImage2D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_viewport_func_ptr,         OpenGL::aiViewport),

        /* Compat profile */
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_accum,                  OpenGL::aiAccum),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_alpha_func,             OpenGL::aiAlphaFunc),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_are_textures_resident,  OpenGL::aiAreTexturesResident),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_array_element,          OpenGL::aiArrayElement),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_begin,                  OpenGL::aiBegin),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_bitmap,                 OpenGL::aiBitmap),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_call_list,              OpenGL::aiCallList),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_call_lists,             OpenGL::aiCallLists),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_clear_accum,            OpenGL::aiClearAccum),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_clear_index,            OpenGL::aiClearIndex),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_clip_plane,             OpenGL::aiClipPlane),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3b,               OpenGL::aiColor3b),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3bv,              OpenGL::aiColor3bv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3d,               OpenGL::aiColor3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3dv,              OpenGL::aiColor3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3f,               OpenGL::aiColor3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3fv,              OpenGL::aiColor3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3i,               OpenGL::aiColor3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3iv,              OpenGL::aiColor3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3s,               OpenGL::aiColor3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3sv,              OpenGL::aiColor3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3ub,              OpenGL::aiColor3ub),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3ubv,             OpenGL::aiColor3ubv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3ui,              OpenGL::aiColor3ui),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3uiv,             OpenGL::aiColor3uiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3us,              OpenGL::aiColor3us),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_3usv,             OpenGL::aiColor3usv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4b,               OpenGL::aiColor4b),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4bv,              OpenGL::aiColor4bv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4d,               OpenGL::aiColor4d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4dv,              OpenGL::aiColor4dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4f,               OpenGL::aiColor4f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4fv,              OpenGL::aiColor4fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4i,               OpenGL::aiColor4i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4iv,              OpenGL::aiColor4iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4s,               OpenGL::aiColor4s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4sv,              OpenGL::aiColor4sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4ub,              OpenGL::aiColor4ub),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4ubv,             OpenGL::aiColor4ubv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4ui,              OpenGL::aiColor4ui),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4uiv,             OpenGL::aiColor4uiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4us,              OpenGL::aiColor4us),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_4usv,             OpenGL::aiColor4usv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_material,         OpenGL::aiColorMaterial),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_color_pointer,          OpenGL::aiColorPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_copy_pixels,            OpenGL::aiCopyPixels),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_delete_lists,           OpenGL::aiDeleteLists),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_disable_client_state,   OpenGL::aiDisableClientState),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_draw_pixels,            OpenGL::aiDrawPixels),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_edge_flag,              OpenGL::aiEdgeFlag),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_edge_flagv,             OpenGL::aiEdgeFlagv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_edge_flag_pointer,      OpenGL::aiEdgeFlagPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_enable_client_state,    OpenGL::aiEnableClientState),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_end,                    OpenGL::aiEnd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_end_list,               OpenGL::aiEndList),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_coord_1d,          OpenGL::aiEvalCoord1d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_coord_1dv,         OpenGL::aiEvalCoord1dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_coord_1f,          OpenGL::aiEvalCoord1f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_coord_1fv,         OpenGL::aiEvalCoord1fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_coord_2d,          OpenGL::aiEvalCoord2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_coord_2dv,         OpenGL::aiEvalCoord2dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_coord_2f,          OpenGL::aiEvalCoord2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_coord_2fv,         OpenGL::aiEvalCoord2fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_mesh1,             OpenGL::aiEvalMesh1),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_mesh2,             OpenGL::aiEvalMesh2),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_point1,            OpenGL::aiEvalPoint1),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_eval_point2,            OpenGL::aiEvalPoint2),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_feedback_buffer,        OpenGL::aiFeedbackBuffer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_fogf,                   OpenGL::aiFogf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_fogfv,                  OpenGL::aiFogfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_fogi,                   OpenGL::aiFogi),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_fogiv,                  OpenGL::aiFogiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_frustum,                OpenGL::aiFrustum),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_gen_lists,              OpenGL::aiGenLists),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_clip_plane,         OpenGL::aiGetClipPlane),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_light_fv,           OpenGL::aiGetLightfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_light_iv,           OpenGL::aiGetLightiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_map_dv,             OpenGL::aiGetMapdv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_map_fv,             OpenGL::aiGetMapfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_map_iv,             OpenGL::aiGetMapiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_material_fv,        OpenGL::aiGetMaterialfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_material_iv,        OpenGL::aiGetMaterialiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_pixel_map_fv,       OpenGL::aiGetPixelMapfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_pixel_map_uiv,      OpenGL::aiGetPixelMapuiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_pixel_map_usv,      OpenGL::aiGetPixelMapusv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_pointerv,           OpenGL::aiGetPointerv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_polygon_stipple,    OpenGL::aiGetPolygonStipple),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_tex_env_fv,         OpenGL::aiGetTexEnvfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_tex_env_iv,         OpenGL::aiGetTexEnviv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_tex_gen_dv,         OpenGL::aiGetTexGendv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_get_tex_gen_iv,         OpenGL::aiGetTexGeniv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_d,                OpenGL::aiIndexd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_dv,               OpenGL::aiIndexdv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_f,                OpenGL::aiIndexf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_fv,               OpenGL::aiIndexfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_i,                OpenGL::aiIndexi),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_iv,               OpenGL::aiIndexiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_mask,             OpenGL::aiIndexMask),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_pointer,          OpenGL::aiIndexPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_s,                OpenGL::aiIndexs),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_sv,               OpenGL::aiIndexsv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_ub,               OpenGL::aiIndexub),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_index_ubv,              OpenGL::aiIndexubv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_init_names,             OpenGL::aiInitNames),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_interleaved_arrays,     OpenGL::aiInterleavedArrays),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_is_list,                OpenGL::aiIsList),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_light_f,                OpenGL::aiLightf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_light_fv,               OpenGL::aiLightfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_light_i,                OpenGL::aiLighti),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_light_iv,               OpenGL::aiLightiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_light_model_f,          OpenGL::aiLightModelf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_light_model_fv,         OpenGL::aiLightModelfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_light_model_i,          OpenGL::aiLightModeli),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_light_model_iv,         OpenGL::aiLightModeliv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_line_stipple,           OpenGL::aiLineStipple),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_list_base,              OpenGL::aiListBase),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_load_identity,          OpenGL::aiLoadIdentity),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_load_matrix_d,          OpenGL::aiLoadMatrixd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_load_matrix_f,          OpenGL::aiLoadMatrixf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_load_name,              OpenGL::aiLoadName),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_map_1d,                 OpenGL::aiMap1d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_map_1f,                 OpenGL::aiMap1f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_map_2d,                 OpenGL::aiMap2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_map_2f,                 OpenGL::aiMap2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_map_grid_1d,            OpenGL::aiMapGrid1d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_map_grid_1f,            OpenGL::aiMapGrid1f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_map_grid_2d,            OpenGL::aiMapGrid2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_map_grid_2f,            OpenGL::aiMapGrid2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_material_f,             OpenGL::aiMaterialf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_material_fv,            OpenGL::aiMaterialfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_material_i,             OpenGL::aiMateriali),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_material_iv,            OpenGL::aiMaterialiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_matrix_mode,            OpenGL::aiMatrixMode),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_mult_matrix_d,          OpenGL::aiMultMatrixd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_mult_matrix_f,          OpenGL::aiMultMatrixf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_new_list,               OpenGL::aiNewList),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3b,              OpenGL::aiNormal3b),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3bv,             OpenGL::aiNormal3bv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3d,              OpenGL::aiNormal3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3dv,             OpenGL::aiNormal3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3f,              OpenGL::aiNormal3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3fv,             OpenGL::aiNormal3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3i,              OpenGL::aiNormal3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3iv,             OpenGL::aiNormal3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3s,              OpenGL::aiNormal3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_3sv,             OpenGL::aiNormal3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_normal_pointer,         OpenGL::aiNormalPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_ortho,                  OpenGL::aiOrtho),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_passthrough,            OpenGL::aiPassthrough),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_map_fv,           OpenGL::aiPixelMapfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_map_uiv,          OpenGL::aiPixelMapuiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_map_usv,          OpenGL::aiPixelMapusv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_store_f,          OpenGL::aiPixelStoref),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_store_i,          OpenGL::aiPixelStorei),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_transfer_f,       OpenGL::aiPixelTransferf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_transfer_i,       OpenGL::aiPixelTransferi),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pixel_zoom,             OpenGL::aiPixelZoom),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_polygon_stipple,        OpenGL::aiPolygonStipple),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pop_attrib,             OpenGL::aiPopAttrib),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pop_client_attrib,      OpenGL::aiPopClientAttrib),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pop_matrix,             OpenGL::aiPopMatrix),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_pop_name,               OpenGL::aiPopName),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_prioritize_textures,    OpenGL::aiPrioritizeTextures),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_push_attrib,            OpenGL::aiPushAttrib),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_push_client_attrib,     OpenGL::aiPushClientAttrib),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_push_matrix,            OpenGL::aiPushMatrix),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_push_name,              OpenGL::aiPushName),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_2d,          OpenGL::aiRasterPos2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_2dv,         OpenGL::aiRasterPos2dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_2f,          OpenGL::aiRasterPos2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_2fv,         OpenGL::aiRasterPos2fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_2i,          OpenGL::aiRasterPos2i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_2iv,         OpenGL::aiRasterPos2iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_2s,          OpenGL::aiRasterPos2s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_2sv,         OpenGL::aiRasterPos2sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_3d,          OpenGL::aiRasterPos3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_3dv,         OpenGL::aiRasterPos3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_3f,          OpenGL::aiRasterPos3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_3fv,         OpenGL::aiRasterPos3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_3i,          OpenGL::aiRasterPos3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_3iv,         OpenGL::aiRasterPos3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_3s,          OpenGL::aiRasterPos3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_3sv,         OpenGL::aiRasterPos3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_4d,          OpenGL::aiRasterPos4d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_4dv,         OpenGL::aiRasterPos4dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_4f,          OpenGL::aiRasterPos4f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_4fv,         OpenGL::aiRasterPos4fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_4i,          OpenGL::aiRasterPos4i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_4iv,         OpenGL::aiRasterPos4iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_4s,          OpenGL::aiRasterPos4s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_raster_pos_4sv,         OpenGL::aiRasterPos4sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rect_d,                 OpenGL::aiRectd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rect_dv,                OpenGL::aiRectdv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rect_f,                 OpenGL::aiRectf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rect_fv,                OpenGL::aiRectfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rect_i,                 OpenGL::aiRecti),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rect_iv,                OpenGL::aiRectiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rect_s,                 OpenGL::aiRects),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rect_sv,                OpenGL::aiRectsv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_render_mode,            OpenGL::aiRenderMode),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rotate_d,               OpenGL::aiRotated),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_rotate_f,               OpenGL::aiRotatef),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_scale_d,                OpenGL::aiScaled),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_scale_f,                OpenGL::aiScalef),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_select_buffer,          OpenGL::aiSelectBuffer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_shade_model,            OpenGL::aiShadeModel),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_1d,           OpenGL::aiTexCoord1d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_1dv,          OpenGL::aiTexCoord1dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_1f,           OpenGL::aiTexCoord1f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_1fv,          OpenGL::aiTexCoord1fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_1i,           OpenGL::aiTexCoord1i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_1iv,          OpenGL::aiTexCoord1iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_1s,           OpenGL::aiTexCoord1s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_1sv,          OpenGL::aiTexCoord1sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_2d,           OpenGL::aiTexCoord2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_2dv,          OpenGL::aiTexCoord2dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_2f,           OpenGL::aiTexCoord2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_2fv,          OpenGL::aiTexCoord2fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_2i,           OpenGL::aiTexCoord2i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_2iv,          OpenGL::aiTexCoord2iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_2s,           OpenGL::aiTexCoord2s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_2sv,          OpenGL::aiTexCoord2sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_3d,           OpenGL::aiTexCoord3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_3dv,          OpenGL::aiTexCoord3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_3f,           OpenGL::aiTexCoord3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_3fv,          OpenGL::aiTexCoord3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_3i,           OpenGL::aiTexCoord3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_3iv,          OpenGL::aiTexCoord3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_3s,           OpenGL::aiTexCoord3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_3sv,          OpenGL::aiTexCoord3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_4d,           OpenGL::aiTexCoord4d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_4dv,          OpenGL::aiTexCoord4dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_4f,           OpenGL::aiTexCoord4f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_4fv,          OpenGL::aiTexCoord4fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_4i,           OpenGL::aiTexCoord4i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_4iv,          OpenGL::aiTexCoord4iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_4s,           OpenGL::aiTexCoord4s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_4sv,          OpenGL::aiTexCoord4sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_coord_pointer,      OpenGL::aiTexCoordPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_env_f,              OpenGL::aiTexEnvf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_env_fv,             OpenGL::aiTexEnvfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_env_i,              OpenGL::aiTexEnvi),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_env_iv,             OpenGL::aiTexEnviv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_gen_d,              OpenGL::aiTexGend),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_gen_dv,             OpenGL::aiTexGendv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_gen_i,              OpenGL::aiTexGeni),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_tex_gen_iv,             OpenGL::aiTexGeniv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_translate_d,            OpenGL::aiTranslated),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_translate_f,            OpenGL::aiTranslatef),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_2d,              OpenGL::aiVertex2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_2dv,             OpenGL::aiVertex2dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_2f,              OpenGL::aiVertex2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_2fv,             OpenGL::aiVertex2fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_2i,              OpenGL::aiVertex2i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_2iv,             OpenGL::aiVertex2iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_2s,              OpenGL::aiVertex2s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_2sv,             OpenGL::aiVertex2sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_3d,              OpenGL::aiVertex3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_3dv,             OpenGL::aiVertex3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_3f,              OpenGL::aiVertex3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_3fv,             OpenGL::aiVertex3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_3i,              OpenGL::aiVertex3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_3iv,             OpenGL::aiVertex3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_3s,              OpenGL::aiVertex3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_3sv,             OpenGL::aiVertex3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_4d,              OpenGL::aiVertex4d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_4dv,             OpenGL::aiVertex4dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_4f,              OpenGL::aiVertex4f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_4fv,             OpenGL::aiVertex4fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_4i,              OpenGL::aiVertex4i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_4iv,             OpenGL::aiVertex4iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_4s,              OpenGL::aiVertex4s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_4sv,             OpenGL::aiVertex4sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) OpenGL::g_cached_gl_vertex_pointer,         OpenGL::aiVertexPointer),
   };
}