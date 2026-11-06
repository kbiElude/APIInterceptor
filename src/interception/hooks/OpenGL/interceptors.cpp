/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_blend_func.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_clear.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_clear_color.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_clear_depth.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_clear_stencil.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_color_mask.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_cull_face.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_depth_func.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_depth_mask.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_depth_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_disable.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_draw_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_enable.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_finish.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_flush.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_front_face.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_booleanv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_doublev.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_error.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_floatv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_integerv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_string.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_tex_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_tex_level_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_tex_level_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_tex_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_get_tex_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_hint.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_is_enabled.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_line_width.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_logic_op.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_pixel_storef.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_pixel_storei.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_point_size.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_polygon_mode.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_read_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_read_pixels.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_scissor.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_stencil_func.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_stencil_mask.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_stencil_op.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_tex_image_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_tex_image_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_tex_parameterf.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_tex_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_tex_parameteri.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_tex_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.0/gl_viewport.h"

#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_accum.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_alpha_func.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_are_textures_resident.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_array_element.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_begin.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_bind_texture.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_bitmap.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_call_list.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_call_lists.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_clear_accum.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_clear_index.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_clip_plane.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3b.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3bv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3ub.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3ubv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3us.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_3usv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4b.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4bv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4ub.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4ubv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4us.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_4usv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_material.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_color_pointer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_copy_pixels.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_copy_tex_image_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_copy_tex_image_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_copy_tex_sub_image_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_copy_tex_sub_image_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_delete_lists.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_delete_textures.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_disable_client_state.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_draw_arrays.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_draw_elements.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_draw_pixels.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_edge_flag.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_edge_flagv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_edge_flag_pointer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_enable_client_state.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_end.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_end_list.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_coord_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_coord_1dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_coord_1f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_coord_1fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_coord_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_coord_2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_coord_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_coord_2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_mesh1.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_mesh2.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_point1.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_eval_point2.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_feedback_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_fogf.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_fogfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_fogi.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_fogiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_frustum.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_gen_lists.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_gen_textures.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_clip_plane.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_light_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_light_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_map_dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_map_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_map_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_material_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_material_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_pixel_map_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_pixel_map_uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_pixel_map_usv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_pointerv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_polygon_stipple.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_tex_env_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_tex_env_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_tex_gen_dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_get_tex_gen_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_mask.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_pointer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_ub.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_index_ubv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_init_names.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_interleaved_arrays.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_is_list.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_is_texture.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_light_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_light_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_light_i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_light_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_light_model_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_light_model_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_light_model_i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_light_model_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_line_stipple.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_list_base.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_load_identity.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_load_matrix_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_load_matrix_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_load_name.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_map_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_map_1f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_map_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_map_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_map_grid_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_map_grid_1f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_map_grid_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_map_grid_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_material_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_material_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_material_i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_material_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_matrix_mode.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_mult_matrix_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_mult_matrix_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_new_list.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3b.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3bv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_3sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_normal_pointer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_ortho.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_passthrough.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pixel_map_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pixel_map_uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pixel_map_usv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pixel_transfer_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pixel_transfer_i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pixel_zoom.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_polygon_offset.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_polygon_stipple.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pop_attrib.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pop_client_attrib.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pop_matrix.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_pop_name.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_prioritize_textures.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_push_attrib.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_push_client_attrib.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_push_matrix.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_push_name.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_2i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_2iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_2s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_2sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_3s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_3sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_4d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_4f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_4i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_4iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_4s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_raster_pos_4sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rect_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rect_dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rect_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rect_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rect_i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rect_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rect_s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rect_sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_render_mode.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rotate_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_rotate_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_scale_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_scale_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_select_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_shade_model.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_1dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_1f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_1fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_1i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_1iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_1s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_1sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_2i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_2iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_2s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_2sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_3s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_3sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_4d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_4f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_4i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_4iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_4s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_4sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_coord_pointer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_env_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_env_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_env_i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_env_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_gen_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_gen_dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_gen_i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_gen_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_sub_image_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_tex_sub_image_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_translate_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_translate_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_2i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_2iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_2s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_2sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_3s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_3sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_4d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_4f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_4i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_4iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_4s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_4sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.1/gl_vertex_pointer.h"

#include "interception/hooks/OpenGL/entrypoints/GL1.2/gl_copy_tex_sub_image_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.2/gl_draw_range_elements.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.2/gl_tex_image_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.2/gl_tex_sub_image_3d.h"

#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_active_texture.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_client_active_texture.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_compressed_tex_image_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_compressed_tex_sub_image_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_get_compressed_tex_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_load_transpose_matrix_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_load_transpose_matrix_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_mult_transpose_matrix_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_mult_transpose_matrix_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_1dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_1f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_1fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_1i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_1iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_1s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_1sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_2i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_2iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_2s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_2sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_3s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_3sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_4d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_4f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_4i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_4iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_4s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_multi_tex_coord_4sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.3/gl_sample_coverage.h"

#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_blend_color.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_blend_equation.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_blend_func_separate.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_fog_coord_d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_fog_coord_dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_fog_coord_f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_fog_coord_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_fog_coord_pointer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_multi_draw_arrays.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_multi_draw_elements.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_point_parameterf.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_point_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_point_parameteri.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_point_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3b.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3bv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3ub.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3ubv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3us.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_3usv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_secondary_color_pointer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_2i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_2iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_2s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_2sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_3s.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.4/gl_window_pos_3sv.h"

#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_begin_query.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_bind_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_buffer_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_buffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_delete_buffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_delete_queries.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_end_query.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_gen_buffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_gen_queries.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_get_buffer_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_get_buffer_pointerv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_get_buffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_get_queryiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_get_query_objectiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_get_query_objectuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_is_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_is_query.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_map_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL1.5/gl_unmap_buffer.h"

#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_attach_shader.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_bind_attrib_location.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_blend_equation_separate.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_compile_shader.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_create_program.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_create_shader.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_delete_program.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_delete_shader.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_detach_shader.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_disable_vertex_attrib_array.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_draw_buffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_enable_vertex_attrib_array.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_active_attrib.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_active_uniform.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_attached_shaders.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_attrib_location.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_programiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_program_info_log.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_shaderiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_shader_info_log.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_shader_source.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_uniformfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_uniformiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_uniform_location.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_vertex_attribdv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_vertex_attribfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_vertex_attribiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_get_vertex_attrib_pointerv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_is_program.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_is_shader.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_link_program.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_shader_source.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_stencil_func_separate.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_stencil_mask_separate.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_stencil_op_separate.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_1f.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_1fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_1i.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_1iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_2i.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_2iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_4f.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_4i.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_4iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_matrix_2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_matrix_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_uniform_matrix_4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_use_program.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_validate_program.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1f.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1s.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_1sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2s.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_2sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3s.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_3sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4bv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4d.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4f.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nbv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Niv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nsv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nub.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nubv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4Nusv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4s.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4ubv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_4usv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.0/gl_vertex_attrib_pointer.h"

#include "interception/hooks/OpenGL/entrypoints/GL2.1/gl_uniform_matrix_2x3_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.1/gl_uniform_matrix_2x4_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.1/gl_uniform_matrix_3x2_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.1/gl_uniform_matrix_3x4_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.1/gl_uniform_matrix_4x2_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL2.1/gl_uniform_matrix_4x3_fv.h"

#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_begin_conditional_render.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_begin_transform_feedback.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_bind_buffer_base.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_bind_buffer_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_bind_frag_data_location.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_bind_framebuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_bind_renderbuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_bind_vertex_array.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_blit_framebuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_check_framebuffer_status.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_clamp_color.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_clear_buffer_fi.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_clear_buffer_fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_clear_buffer_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_clear_buffer_uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_color_maski.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_delete_framebuffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_delete_renderbuffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_delete_vertex_arrays.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_disablei.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_enablei.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_end_conditional_render.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_end_transform_feedback.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_flush_mapped_buffer_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_framebuffer_renderbuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_framebuffer_texture_layer.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_generate_mipmap.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_gen_framebuffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_gen_renderbuffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_gen_vertex_arrays.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_booleani_v.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_frag_data_location.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_framebuffer_attachment_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_integeri_v.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_renderbuffer_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_stringi.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_tex_parameter_i_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_tex_parameter_i_uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_transform_feedback_varying.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_uniformuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_vertex_attrib_i_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_get_vertex_attrib_i_uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_is_enabledi.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_is_framebuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_is_renderbuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_is_vertex_array.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_map_buffer_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_renderbuffer_storage.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_renderbuffer_storage_multisample.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_tex_parameter_i_iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_tex_parameter_i_uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_transform_feedback_varyings.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_uniform_1ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_uniform_1uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_uniform_2ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_uniform_2uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_uniform_3ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_uniform_3uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_uniform_4ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_uniform_4uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1i.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_1uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2i.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_2uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_3uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4bv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4i.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4sv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ubv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_4usv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.0/gl_vertex_attrib_i_pointer.h"

#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_copy_buffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_draw_arrays_instanced.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_draw_elements_instanced.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_get_active_uniformsiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_get_active_uniform_blockiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_get_active_uniform_block_name.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_get_active_uniform_name.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_get_uniform_block_index.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_get_uniform_indices.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_primitive_restart_index.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_tex_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.1/gl_uniform_block_binding.h"

#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_client_wait_sync.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_delete_sync.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_draw_elements_base_vertex.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_draw_elements_instanced_base_vertex.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_draw_range_elements_base_vertex.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_fence_sync.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_framebuffer_texture.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_get_buffer_parameteri64v.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_get_integer64i_v.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_get_integer64v.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_get_multisamplefv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_get_synciv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_is_sync.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_multi_draw_elements_base_vertex.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_provoking_vertex.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_sample_maski.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_tex_image_2d_multisample.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_tex_image_3d_multisample.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.2/gl_wait_sync.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_bind_frag_data_location_indexed.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_bind_sampler.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_delete_samplers.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_gen_samplers.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_get_frag_data_index.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_get_query_objecti64v.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_get_query_objectui64v.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_get_sampler_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_get_sampler_parameter_iiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_get_sampler_parameter_iuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_get_sampler_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_is_sampler.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_query_counter.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_sampler_parameterf.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_sampler_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_sampler_parameteri.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_sampler_parameter_iiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_sampler_parameter_iuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_sampler_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_vertex_attrib_divisor.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_vertex_attrib_p1ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_vertex_attrib_p1uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_vertex_attrib_p2ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_vertex_attrib_p2uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_vertex_attrib_p3ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_vertex_attrib_p3uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_vertex_attrib_p4ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL3.3/gl_vertex_attrib_p4uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_begin_query_indexed.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_bind_transform_feedback.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_blend_equationi.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_blend_equation_separatei.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_blend_funci.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_blend_func_separatei.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_delete_transform_feedbacks.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_draw_arrays_indirect.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_draw_elements_indirect.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_draw_transform_feedback.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_draw_transform_feedback_stream.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_end_query_indexed.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_gen_transform_feedbacks.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_get_active_subroutine_name.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_get_active_subroutine_uniformiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_get_active_subroutine_uniform_name.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_get_program_stageiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_get_query_indexediv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_get_subroutine_index.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_get_subroutine_uniform_location.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_get_uniformdv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_get_uniform_subroutineuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_is_transform_feedback.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_min_sample_shading.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_patch_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_patch_parameteri.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_pause_transform_feedback.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_resume_transform_feedback.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform1dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform4d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_matrix2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_matrix2x3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_matrix2x4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_matrix3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_matrix3x2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_matrix3x4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_matrix4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_matrix4x2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_matrix4x3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.0/gl_uniform_subroutinesuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_active_shader_program.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_bind_program_pipeline.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_clear_depthf.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_create_shader_programv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_delete_program_pipelines.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_depth_range_arrayv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_depth_rangef.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_depth_range_indexed.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_gen_program_pipelines.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_get_doublei_v.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_get_floati_v.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_get_program_binary.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_get_program_pipeline_info_log.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_get_program_pipelineiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_get_shader_precision_format.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_get_vertex_attrib_ldv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_is_program_pipeline.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_binary.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_parameteri.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform1dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform1f.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform1fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform1i.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform1iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform1ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform1uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform2f.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform2i.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform2iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform2ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform2uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform3f.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform3i.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform3iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform3ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform3uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform4d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform4f.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform4i.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform4iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform4ui.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform4uiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix2x3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix2x3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix2x4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix2x4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix3x2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix3x2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix3x4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix3x4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix4fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix4x2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix4x2fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix4x3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_program_uniform_matrix4x3fv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_release_shader_compiler.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_scissor_arrayv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_scissor_indexed.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_scissor_indexedv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_shader_binary.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_use_program_stages.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_validate_program_pipeline.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_vertex_attrib_l1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_vertex_attrib_l1dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_vertex_attrib_l2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_vertex_attrib_l2dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_vertex_attrib_l3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_vertex_attrib_l3dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_vertex_attrib_l4d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_vertex_attrib_l4dv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_vertex_attrib_l_pointer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_viewport_arrayv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_viewport_indexedf.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.1/gl_viewport_indexedfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_bind_image_texture.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_draw_arrays_instanced_base_instance.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_draw_elements_instanced_base_instance.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_draw_elements_instanced_base_vertex_base_instance.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_draw_transform_feedback_instanced.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_draw_transform_feedback_stream_instanced.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_get_active_atomic_counter_bufferiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_get_internalformativ.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_memory_barrier.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_tex_storage1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_tex_storage2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.2/gl_tex_storage3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_bind_vertex_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_clear_buffer_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_clear_buffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_copy_image_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_debug_message_callback.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_debug_message_control.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_debug_message_insert.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_dispatch_compute.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_dispatch_compute_indirect.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_framebuffer_parameteri.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_debug_message_log.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_framebuffer_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_internalformati64v.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_object_label.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_object_ptr_label.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_program_interfaceiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_program_resource_index.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_program_resourceiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_program_resource_location.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_program_resource_location_index.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_get_program_resource_name.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_invalidate_buffer_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_invalidate_buffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_invalidate_framebuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_invalidate_sub_framebuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_invalidate_tex_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_invalidate_tex_sub_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_multi_draw_arrays_indirect.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_multi_draw_elements_indirect.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_object_label.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_object_ptr_label.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_pop_debug_group.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_push_debug_group.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_shader_storage_block_binding.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_tex_buffer_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_tex_storage2d_multisample.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_tex_storage3d_multisample.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_texture_view.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_vertex_attrib_binding.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_vertex_attrib_format.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_vertex_attrib_iformat.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_vertex_attrib_lformat.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.3/gl_vertex_binding_divisor.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_bind_buffers_base.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_bind_buffers_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_bind_image_textures.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_bind_samplers.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_bind_textures.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_bind_vertex_buffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_buffer_storage.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_clear_tex_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.4/gl_clear_tex_sub_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_bind_texture_unit.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_blit_named_framebuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_check_named_framebuffer_status.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_clear_named_buffer_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_clear_named_buffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_clear_named_framebufferfi.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_clear_named_framebufferfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_clear_named_framebufferiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_clear_named_framebufferuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_clip_control.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_compressed_texture_sub_image1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_compressed_texture_sub_image2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_compressed_texture_sub_image3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_copy_named_buffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_copy_texture_sub_image1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_copy_texture_sub_image2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_copy_texture_sub_image3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_create_buffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_create_framebuffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_create_program_pipelines.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_create_queries.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_create_renderbuffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_create_samplers.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_create_textures.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_create_transform_feedbacks.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_create_vertex_arrays.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_disable_vertex_array_attrib.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_enable_vertex_array_attrib.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_flush_mapped_named_buffer_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_generate_texture_mipmap.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_compressed_texture_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_compressed_texture_sub_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_graphics_reset_status.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_named_buffer_parameteri64v.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_named_buffer_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_named_buffer_pointerv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_named_buffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_named_framebuffer_attachment_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_named_framebuffer_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_named_renderbuffer_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_getn_compressed_tex_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_getn_tex_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_getn_uniformdv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_getn_uniformfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_getn_uniformiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_getn_uniformuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_query_buffer_objecti64v.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_query_buffer_objectiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_query_buffer_objectui64v.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_query_buffer_objectuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_texture_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_texture_level_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_texture_level_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_texture_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_texture_parameteriiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_texture_parameteriuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_texture_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_texture_sub_image.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_transform_feedbacki64_v.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_transform_feedbacki_v.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_transform_feedbackiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_vertex_array_indexed64iv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_vertex_array_indexediv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_get_vertex_arrayiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_invalidate_named_framebuffer_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_invalidate_named_framebuffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_map_named_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_map_named_buffer_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_memory_barrier_by_region.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_buffer_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_buffer_storage.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_buffer_sub_data.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_framebuffer_draw_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_framebuffer_draw_buffers.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_framebuffer_parameteri.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_framebuffer_read_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_framebuffer_renderbuffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_framebuffer_texture.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_framebuffer_texture_layer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_renderbuffer_storage.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_named_renderbuffer_storage_multisample.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_readn_pixels.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_barrier.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_buffer_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_parameterf.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_parameterfv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_parameteri.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_parameteriiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_parameteriuiv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_parameteriv.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_storage1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_storage2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_storage2d_multisample.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_storage3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_storage3d_multisample.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_sub_image1d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_sub_image2d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_texture_sub_image3d.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_transform_feedback_buffer_base.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_transform_feedback_buffer_range.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_unmap_named_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_vertex_array_attrib_binding.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_vertex_array_attrib_format.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_vertex_array_attrib_iformat.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_vertex_array_attrib_lformat.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_vertex_array_binding_divisor.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_vertex_array_element_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_vertex_array_vertex_buffer.h"
#include "interception/hooks/OpenGL/entrypoints/GL4.5/gl_vertex_array_vertex_buffers.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_color_buffer_float/gl_clamp_color_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_draw_buffers/gl_draw_buffers_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_draw_buffers_blend/gl_blend_equationi_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_draw_buffers_blend/gl_blend_equation_separatei_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_draw_buffers_blend/gl_blend_funci_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_draw_buffers_blend/gl_blend_func_separatei_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_draw_instanced/gl_draw_arrays_instanced_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_draw_instanced/gl_draw_elements_instanced_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_instanced_arrays/gl_draw_arrays_instanced_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_instanced_arrays/gl_draw_elements_instanced_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_instanced_arrays/gl_vertex_attrib_divisor_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multisample/gl_sample_coverage_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_active_texture_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_occlusion_query/gl_begin_query_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_occlusion_query/gl_delete_queries_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_occlusion_query/gl_end_query_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_occlusion_query/gl_gen_queries_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_occlusion_query/gl_get_queryiv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_occlusion_query/gl_get_query_objectiv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_occlusion_query/gl_get_query_objectuiv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_occlusion_query/gl_is_query_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_point_parameters/gl_point_parameterf_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_point_parameters/gl_point_parameterfv_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_sample_shading/gl_min_sample_shading_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_texture_buffer_object/gl_tex_buffer_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_image_1d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_image_2d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_image_3d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_sub_image_1d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_sub_image_2d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_texture_compression/gl_compressed_tex_sub_image_3d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_texture_compression/gl_get_compressed_tex_image_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_bind_buffer_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_buffer_data_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_buffer_sub_data_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_delete_buffers_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_gen_buffers_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_get_buffer_parameteriv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_get_buffer_pointerv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_get_buffer_sub_data_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_is_buffer_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_map_buffer_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_buffer_object/gl_unmap_buffer_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_disable_vertex_attrib_array_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_enable_vertex_attrib_array_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attribdv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attribfv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attribiv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_get_vertex_attrib_pointerv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1sv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_1s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2sv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_2s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3sv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_3s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4bv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4iv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nbv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Niv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nsv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nubv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nub_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nuiv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4Nusv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4sv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4ubv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4uiv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_4usv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_program/gl_vertex_attrib_pointer_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_shader/gl_bind_attrib_location_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_shader/gl_get_active_attrib_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_shader/gl_get_attrib_location_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_EXT_texture_object/gl_are_textures_resident_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_texture_object/gl_bind_texture_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_texture_object/gl_delete_textures_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_texture_object/gl_gen_textures_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_texture_object/gl_is_texture_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_texture_object/gl_prioritize_textures_ext.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_transpose_matrix/gl_load_transpose_matrixd_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_transpose_matrix/gl_load_transpose_matrixf_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_transpose_matrix/gl_mult_transpose_matrixd_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_transpose_matrix/gl_mult_transpose_matrixf_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_client_active_texture_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_1d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_1dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_1f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_1fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_1i_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_1iv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_1s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_1sv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_2d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_2dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_2f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_2fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_2i_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_2iv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_2s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_2sv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_3d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_3dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_3f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_3fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_3i_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_3iv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_3s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_3sv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_4d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_4dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_4f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_4fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_4i_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_4iv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_4s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_multitexture/gl_multi_tex_coord_4sv_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_array_object/gl_bind_vertex_array_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_array_object/gl_delete_vertex_arrays_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_array_object/gl_gen_vertex_arrays_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_vertex_array_object/gl_is_vertex_array_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_2d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_2dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_2f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_2fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_2i_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_2iv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_2s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_2sv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_3d_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_3dv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_3f_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_3fv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_3i_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_3iv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_3s_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_window_pos/gl_window_pos_3sv_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_EXT_blend_func_separate/gl_blend_func_separate_ext.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_debug_output/gl_debug_message_callback_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_debug_output/gl_debug_message_control_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_debug_output/gl_debug_message_insert_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_debug_output/gl_get_debug_message_log_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_ARB_robustness/gl_get_graphics_reset_status_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_robustness/gl_getn_compressed_tex_image_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_robustness/gl_getn_tex_image_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_robustness/gl_getn_uniformdv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_robustness/gl_getn_uniformfv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_robustness/gl_getn_uniformiv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_robustness/gl_getn_uniformuiv_arb.h"
#include "interception/hooks/OpenGL/entrypoints/GL_ARB_robustness/gl_readn_pixels_arb.h"

#include "interception/hooks/OpenGL/entrypoints/GL_EXT_draw_buffers2/gl_color_maski_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_draw_buffers2/gl_disablei_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_draw_buffers2/gl_enablei_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_draw_buffers2/gl_get_booleani_v_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_draw_buffers2/gl_get_integeri_v_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_draw_buffers2/gl_is_enabledi_ext.h"

#include "interception/hooks/OpenGL/entrypoints/GL_EXT_fog_coord/gl_fog_coordd_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_fog_coord/gl_fog_coorddv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_fog_coord/gl_fog_coordf_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_fog_coord/gl_fog_coordfv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_fog_coord/gl_fog_coord_pointer_ext.h"

#include "interception/hooks/OpenGL/entrypoints/GL_EXT_multi_draw_arrays/gl_multi_draw_arrays_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_multi_draw_arrays/gl_multi_draw_elements_ext.h"

#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3b_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3bv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3d_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3dv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3f_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3fv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3i_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3iv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3s_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3sv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3ub_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3ubv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3ui_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3uiv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3us_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_3usv_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_secondary_color/gl_secondary_color_pointer_ext.h"

#include "interception/hooks/OpenGL/entrypoints/GL_EXT_transform_feedback/gl_begin_transform_feedback_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_transform_feedback/gl_bind_buffer_base_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_transform_feedback/gl_bind_buffer_range_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_transform_feedback/gl_end_transform_feedback_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_transform_feedback/gl_get_transform_feedback_varying_ext.h"
#include "interception/hooks/OpenGL/entrypoints/GL_EXT_transform_feedback/gl_transform_feedback_varyings_ext.h"

#include "interception/hooks/OpenGL/entrypoints/GL_NV_conditional_render/gl_begin_conditional_render_nv.h"
#include "interception/hooks/OpenGL/entrypoints/GL_NV_conditional_render/gl_end_conditional_render_nv.h"

#include "interception/hooks/OpenGL/entrypoints/GL_NV_primitive_restart/gl_primitive_restart_index_nv.h"

#include "interception/hooks/OpenGL/globals.h"
#include "interception/hooks/OpenGL/interceptors.h"

std::unordered_map<std::string, void*> Interception::Hooks::OpenGL::get_func_name_to_func_ptr_map()
{
    /* NOTE: If you add any new entrypoints to this function, make sure to also update Interception::Hooks::OpenGL::Context::init_dispatch_table() */

    std::unordered_map<std::string, void*> result;

    result["glCopyTexSubImage3D"] = Interception::Hooks::OpenGL::aiCopyTexSubImage3D;
    result["glDrawRangeElements"] = Interception::Hooks::OpenGL::aiDrawRangeElements;
    result["glTexImage3D"]        = Interception::Hooks::OpenGL::aiTexImage3D;
    result["glTexSubImage3D"]     = Interception::Hooks::OpenGL::aiTexSubImage3D;

    result["glActiveTexture"]           = Interception::Hooks::OpenGL::aiActiveTexture;
    result["glClientActiveTexture"]     = Interception::Hooks::OpenGL::aiClientActiveTexture;
    result["glCompressedTexImage1D"]    = Interception::Hooks::OpenGL::aiCompressedTexImage1D;
    result["glCompressedTexImage2D"]    = Interception::Hooks::OpenGL::aiCompressedTexImage2D;
    result["glCompressedTexImage3D"]    = Interception::Hooks::OpenGL::aiCompressedTexImage3D;
    result["glCompressedTexSubImage1D"] = Interception::Hooks::OpenGL::aiCompressedTexSubImage1D;
    result["glCompressedTexSubImage2D"] = Interception::Hooks::OpenGL::aiCompressedTexSubImage2D;
    result["glCompressedTexSubImage3D"] = Interception::Hooks::OpenGL::aiCompressedTexSubImage3D;
    result["glGetCompressedTexImage"]   = Interception::Hooks::OpenGL::aiGetCompressedTexImage;
    result["glLoadTransposeMatrixd"]    = Interception::Hooks::OpenGL::aiLoadTransposeMatrixd;
    result["glLoadTransposeMatrixf"]    = Interception::Hooks::OpenGL::aiLoadTransposeMatrixf;
    result["glMultTransposeMatrixd"]    = Interception::Hooks::OpenGL::aiMultTransposeMatrixd;
    result["glMultTransposeMatrixf"]    = Interception::Hooks::OpenGL::aiMultTransposeMatrixf;
    result["glMultiTexCoord1d"]         = Interception::Hooks::OpenGL::aiMultiTexCoord1d;
    result["glMultiTexCoord1dv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord1dv;
    result["glMultiTexCoord1f"]         = Interception::Hooks::OpenGL::aiMultiTexCoord1f;
    result["glMultiTexCoord1fv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord1fv;
    result["glMultiTexCoord1i"]         = Interception::Hooks::OpenGL::aiMultiTexCoord1i;
    result["glMultiTexCoord1iv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord1iv;
    result["glMultiTexCoord1s"]         = Interception::Hooks::OpenGL::aiMultiTexCoord1s;
    result["glMultiTexCoord1sv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord1sv;
    result["glMultiTexCoord2d"]         = Interception::Hooks::OpenGL::aiMultiTexCoord2d;
    result["glMultiTexCoord2dv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord2dv;
    result["glMultiTexCoord2f"]         = Interception::Hooks::OpenGL::aiMultiTexCoord2f;
    result["glMultiTexCoord2fv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord2fv;
    result["glMultiTexCoord2i"]         = Interception::Hooks::OpenGL::aiMultiTexCoord2i;
    result["glMultiTexCoord2iv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord2iv;
    result["glMultiTexCoord2s"]         = Interception::Hooks::OpenGL::aiMultiTexCoord2s;
    result["glMultiTexCoord2sv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord2sv;
    result["glMultiTexCoord3d"]         = Interception::Hooks::OpenGL::aiMultiTexCoord3d;
    result["glMultiTexCoord3dv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord3dv;
    result["glMultiTexCoord3f"]         = Interception::Hooks::OpenGL::aiMultiTexCoord3f;
    result["glMultiTexCoord3fv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord3fv;
    result["glMultiTexCoord3i"]         = Interception::Hooks::OpenGL::aiMultiTexCoord3i;
    result["glMultiTexCoord3iv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord3iv;
    result["glMultiTexCoord3s"]         = Interception::Hooks::OpenGL::aiMultiTexCoord3s;
    result["glMultiTexCoord3sv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord3sv;
    result["glMultiTexCoord4d"]         = Interception::Hooks::OpenGL::aiMultiTexCoord4d;
    result["glMultiTexCoord4dv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord4dv;
    result["glMultiTexCoord4f"]         = Interception::Hooks::OpenGL::aiMultiTexCoord4f;
    result["glMultiTexCoord4fv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord4fv;
    result["glMultiTexCoord4i"]         = Interception::Hooks::OpenGL::aiMultiTexCoord4i;
    result["glMultiTexCoord4iv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord4iv;
    result["glMultiTexCoord4s"]         = Interception::Hooks::OpenGL::aiMultiTexCoord4s;
    result["glMultiTexCoord4sv"]        = Interception::Hooks::OpenGL::aiMultiTexCoord4sv;
    result["glSampleCoverage"]          = Interception::Hooks::OpenGL::aiSampleCoverage;

    result["glBlendColor"]        = Interception::Hooks::OpenGL::aiBlendColor;
    result["glBlendEquation"]     = Interception::Hooks::OpenGL::aiBlendEquation;
    result["glBlendFuncSeparate"] = Interception::Hooks::OpenGL::aiBlendFuncSeparate;
    result["glFogCoordd"]         = Interception::Hooks::OpenGL::aiFogCoordd;
    result["glFogCoorddv"]        = Interception::Hooks::OpenGL::aiFogCoorddv;
    result["glFogCoordf"]         = Interception::Hooks::OpenGL::aiFogCoordf;
    result["glFogCoordfv"]        = Interception::Hooks::OpenGL::aiFogCoordfv;
    result["glFogCoordPointer"]   = Interception::Hooks::OpenGL::aiFogCoordPointer;
    result["glMultiDrawArrays"]   = Interception::Hooks::OpenGL::aiMultiDrawArrays;
    result["glMultiDrawElements"] = Interception::Hooks::OpenGL::aiMultiDrawElements;
    result["glPointParameterf"]   = Interception::Hooks::OpenGL::aiPointParameterf;
    result["glPointParameterfv"]  = Interception::Hooks::OpenGL::aiPointParameterfv;
    result["glPointParameteri"]   = Interception::Hooks::OpenGL::aiPointParameteri;
    result["glPointParameteriv"]  = Interception::Hooks::OpenGL::aiPointParameteriv;
    result["glSecondaryColor3b"]  = Interception::Hooks::OpenGL::aiSecondaryColor3b;
    result["glSecondaryColor3bv"] = Interception::Hooks::OpenGL::aiSecondaryColor3bv;
    result["glSecondaryColor3d"]  = Interception::Hooks::OpenGL::aiSecondaryColor3d;
    result["glSecondaryColor3dv"] = Interception::Hooks::OpenGL::aiSecondaryColor3dv;
    result["glSecondaryColor3f"]  = Interception::Hooks::OpenGL::aiSecondaryColor3f;
    result["glSecondaryColor3fv"] = Interception::Hooks::OpenGL::aiSecondaryColor3fv;
    result["glSecondaryColor3i"]  = Interception::Hooks::OpenGL::aiSecondaryColor3i;
    result["glSecondaryColor3iv"] = Interception::Hooks::OpenGL::aiSecondaryColor3iv;
    result["glSecondaryColor3s"]  = Interception::Hooks::OpenGL::aiSecondaryColor3s;
    result["glSecondaryColor3sv"] = Interception::Hooks::OpenGL::aiSecondaryColor3sv;
    result["glSecondaryColor3ub"] = Interception::Hooks::OpenGL::aiSecondaryColor3ub;
    result["glSecondaryColor3ubv"]= Interception::Hooks::OpenGL::aiSecondaryColor3ubv;
    result["glSecondaryColor3ui"] = Interception::Hooks::OpenGL::aiSecondaryColor3ui;
    result["glSecondaryColor3uiv"]= Interception::Hooks::OpenGL::aiSecondaryColor3uiv;
    result["glSecondaryColor3us"] = Interception::Hooks::OpenGL::aiSecondaryColor3us;
    result["glSecondaryColor3usv"]= Interception::Hooks::OpenGL::aiSecondaryColor3usv;
    result["glSecondaryColorPointer"] = Interception::Hooks::OpenGL::aiSecondaryColorPointer;
    result["glWindowPos2d"]       = Interception::Hooks::OpenGL::aiWindowPos2d;
    result["glWindowPos2dv"]      = Interception::Hooks::OpenGL::aiWindowPos2dv;
    result["glWindowPos2f"]       = Interception::Hooks::OpenGL::aiWindowPos2f;
    result["glWindowPos2fv"]      = Interception::Hooks::OpenGL::aiWindowPos2fv;
    result["glWindowPos2i"]       = Interception::Hooks::OpenGL::aiWindowPos2i;
    result["glWindowPos2iv"]      = Interception::Hooks::OpenGL::aiWindowPos2iv;
    result["glWindowPos2s"]       = Interception::Hooks::OpenGL::aiWindowPos2s;
    result["glWindowPos2sv"]      = Interception::Hooks::OpenGL::aiWindowPos2sv;
    result["glWindowPos3d"]       = Interception::Hooks::OpenGL::aiWindowPos3d;
    result["glWindowPos3dv"]      = Interception::Hooks::OpenGL::aiWindowPos3dv;
    result["glWindowPos3f"]       = Interception::Hooks::OpenGL::aiWindowPos3f;
    result["glWindowPos3fv"]      = Interception::Hooks::OpenGL::aiWindowPos3fv;
    result["glWindowPos3i"]       = Interception::Hooks::OpenGL::aiWindowPos3i;
    result["glWindowPos3iv"]      = Interception::Hooks::OpenGL::aiWindowPos3iv;
    result["glWindowPos3s"]       = Interception::Hooks::OpenGL::aiWindowPos3s;
    result["glWindowPos3sv"]      = Interception::Hooks::OpenGL::aiWindowPos3sv;

    result["glBeginQuery"]           = Interception::Hooks::OpenGL::aiBeginQuery;
    result["glBindBuffer"]           = Interception::Hooks::OpenGL::aiBindBuffer;
    result["glBufferData"]           = Interception::Hooks::OpenGL::aiBufferData;
    result["glBufferSubData"]        = Interception::Hooks::OpenGL::aiBufferSubData;
    result["glDeleteBuffers"]        = Interception::Hooks::OpenGL::aiDeleteBuffers;
    result["glDeleteQueries"]        = Interception::Hooks::OpenGL::aiDeleteQueries;
    result["glEndQuery"]             = Interception::Hooks::OpenGL::aiEndQuery;
    result["glGenBuffers"]           = Interception::Hooks::OpenGL::aiGenBuffers;
    result["glGenQueries"]           = Interception::Hooks::OpenGL::aiGenQueries;
    result["glGetBufferParameteriv"] = Interception::Hooks::OpenGL::aiGetBufferParameteriv;
    result["glGetBufferPointerv"]    = Interception::Hooks::OpenGL::aiGetBufferPointerv;
    result["glGetBufferSubData"]     = Interception::Hooks::OpenGL::aiGetBufferSubData;
    result["glGetQueryiv"]           = Interception::Hooks::OpenGL::aiGetQueryiv;
    result["glGetQueryObjectiv"]     = Interception::Hooks::OpenGL::aiGetQueryObjectiv;
    result["glGetQueryObjectuiv"]    = Interception::Hooks::OpenGL::aiGetQueryObjectuiv;
    result["glIsBuffer"]             = Interception::Hooks::OpenGL::aiIsBuffer;
    result["glIsQuery"]              = Interception::Hooks::OpenGL::aiIsQuery;
    result["glMapBuffer"]            = Interception::Hooks::OpenGL::aiMapBuffer;
    result["glUnmapBuffer"]          = Interception::Hooks::OpenGL::aiUnmapBuffer;

    result["glAttachShader"]             = Interception::Hooks::OpenGL::aiAttachShader;
    result["glBindAttribLocation"]       = Interception::Hooks::OpenGL::aiBindAttribLocation;
    result["glBlendEquationSeparate"]    = Interception::Hooks::OpenGL::aiBlendEquationSeparate;
    result["glCompileShader"]            = Interception::Hooks::OpenGL::aiCompileShader;
    result["glCreateProgram"]            = Interception::Hooks::OpenGL::aiCreateProgram;
    result["glCreateShader"]             = Interception::Hooks::OpenGL::aiCreateShader;
    result["glDeleteProgram"]            = Interception::Hooks::OpenGL::aiDeleteProgram;
    result["glDeleteShader"]             = Interception::Hooks::OpenGL::aiDeleteShader;
    result["glDetachShader"]             = Interception::Hooks::OpenGL::aiDetachShader;
    result["glDisableVertexAttribArray"] = Interception::Hooks::OpenGL::aiDisableVertexAttribArray;
    result["glDrawBuffers"]              = Interception::Hooks::OpenGL::aiDrawBuffers;
    result["glEnableVertexAttribArray"]  = Interception::Hooks::OpenGL::aiEnableVertexAttribArray;
    result["glGetActiveAttrib"]          = Interception::Hooks::OpenGL::aiGetActiveAttrib;
    result["glGetActiveUniform"]         = Interception::Hooks::OpenGL::aiGetActiveUniform;
    result["glGetAttachedShaders"]       = Interception::Hooks::OpenGL::aiGetAttachedShaders;
    result["glGetAttribLocation"]        = Interception::Hooks::OpenGL::aiGetAttribLocation;
    result["glGetProgramiv"]             = Interception::Hooks::OpenGL::aiGetProgramiv;
    result["glGetProgramInfoLog"]        = Interception::Hooks::OpenGL::aiGetProgramInfoLog;
    result["glGetShaderiv"]              = Interception::Hooks::OpenGL::aiGetShaderiv;
    result["glGetShaderInfoLog"]         = Interception::Hooks::OpenGL::aiGetShaderInfoLog;
    result["glGetShaderSource"]          = Interception::Hooks::OpenGL::aiGetShaderSource;
    result["glGetUniformfv"]             = Interception::Hooks::OpenGL::aiGetUniformfv;
    result["glGetUniformiv"]             = Interception::Hooks::OpenGL::aiGetUniformiv;
    result["glGetUniformLocation"]       = Interception::Hooks::OpenGL::aiGetUniformLocation;
    result["glGetVertexAttribdv"]        = Interception::Hooks::OpenGL::aiGetVertexAttribdv;
    result["glGetVertexAttribfv"]        = Interception::Hooks::OpenGL::aiGetVertexAttribfv;
    result["glGetVertexAttribiv"]        = Interception::Hooks::OpenGL::aiGetVertexAttribiv;
    result["glGetVertexAttribPointerv"]  = Interception::Hooks::OpenGL::aiGetVertexAttribPointerv;
    result["glIsProgram"]                = Interception::Hooks::OpenGL::aiIsProgram;
    result["glIsShader"]                 = Interception::Hooks::OpenGL::aiIsShader;
    result["glLinkProgram"]              = Interception::Hooks::OpenGL::aiLinkProgram;
    result["glShaderSource"]             = Interception::Hooks::OpenGL::aiShaderSource;
    result["glStencilFuncSeparate"]      = Interception::Hooks::OpenGL::aiStencilFuncSeparate;
    result["glStencilMaskSeparate"]      = Interception::Hooks::OpenGL::aiStencilMaskSeparate;
    result["glStencilOpSeparate"]        = Interception::Hooks::OpenGL::aiStencilOpSeparate;
    result["glUniform1f"]                = Interception::Hooks::OpenGL::aiUniform1f;
    result["glUniform1fv"]               = Interception::Hooks::OpenGL::aiUniform1fv;
    result["glUniform1i"]                = Interception::Hooks::OpenGL::aiUniform1i;
    result["glUniform1iv"]               = Interception::Hooks::OpenGL::aiUniform1iv;
    result["glUniform2f"]                = Interception::Hooks::OpenGL::aiUniform2f;
    result["glUniform2fv"]               = Interception::Hooks::OpenGL::aiUniform2fv;
    result["glUniform2i"]                = Interception::Hooks::OpenGL::aiUniform2i;
    result["glUniform2iv"]               = Interception::Hooks::OpenGL::aiUniform2iv;
    result["glUniform3f"]                = Interception::Hooks::OpenGL::aiUniform3f;
    result["glUniform3fv"]               = Interception::Hooks::OpenGL::aiUniform3fv;
    result["glUniform3i"]                = Interception::Hooks::OpenGL::aiUniform3i;
    result["glUniform3iv"]               = Interception::Hooks::OpenGL::aiUniform3iv;
    result["glUniform4f"]                = Interception::Hooks::OpenGL::aiUniform4f;
    result["glUniform4fv"]               = Interception::Hooks::OpenGL::aiUniform4fv;
    result["glUniform4i"]                = Interception::Hooks::OpenGL::aiUniform4i;
    result["glUniform4iv"]               = Interception::Hooks::OpenGL::aiUniform4iv;
    result["glUniformMatrix2fv"]         = Interception::Hooks::OpenGL::aiUniformMatrix2fv;
    result["glUniformMatrix3fv"]         = Interception::Hooks::OpenGL::aiUniformMatrix3fv;
    result["glUniformMatrix4fv"]         = Interception::Hooks::OpenGL::aiUniformMatrix4fv;
    result["glUseProgram"]               = Interception::Hooks::OpenGL::aiUseProgram;
    result["glValidateProgram"]          = Interception::Hooks::OpenGL::aiValidateProgram;
    result["glVertexAttrib1d"]           = Interception::Hooks::OpenGL::aiVertexAttrib1d;
    result["glVertexAttrib1dv"]          = Interception::Hooks::OpenGL::aiVertexAttrib1dv;
    result["glVertexAttrib1f"]           = Interception::Hooks::OpenGL::aiVertexAttrib1f;
    result["glVertexAttrib1fv"]          = Interception::Hooks::OpenGL::aiVertexAttrib1fv;
    result["glVertexAttrib1s"]           = Interception::Hooks::OpenGL::aiVertexAttrib1s;
    result["glVertexAttrib1sv"]          = Interception::Hooks::OpenGL::aiVertexAttrib1sv;
    result["glVertexAttrib2d"]           = Interception::Hooks::OpenGL::aiVertexAttrib2d;
    result["glVertexAttrib2dv"]          = Interception::Hooks::OpenGL::aiVertexAttrib2dv;
    result["glVertexAttrib2f"]           = Interception::Hooks::OpenGL::aiVertexAttrib2f;
    result["glVertexAttrib2fv"]          = Interception::Hooks::OpenGL::aiVertexAttrib2fv;
    result["glVertexAttrib2s"]           = Interception::Hooks::OpenGL::aiVertexAttrib2s;
    result["glVertexAttrib2sv"]          = Interception::Hooks::OpenGL::aiVertexAttrib2sv;
    result["glVertexAttrib3d"]           = Interception::Hooks::OpenGL::aiVertexAttrib3d;
    result["glVertexAttrib3dv"]          = Interception::Hooks::OpenGL::aiVertexAttrib3dv;
    result["glVertexAttrib3f"]           = Interception::Hooks::OpenGL::aiVertexAttrib3f;
    result["glVertexAttrib3fv"]          = Interception::Hooks::OpenGL::aiVertexAttrib3fv;
    result["glVertexAttrib3s"]           = Interception::Hooks::OpenGL::aiVertexAttrib3s;
    result["glVertexAttrib3sv"]          = Interception::Hooks::OpenGL::aiVertexAttrib3sv;
    result["glVertexAttrib4bv"]          = Interception::Hooks::OpenGL::aiVertexAttrib4bv;
    result["glVertexAttrib4d"]           = Interception::Hooks::OpenGL::aiVertexAttrib4d;
    result["glVertexAttrib4dv"]          = Interception::Hooks::OpenGL::aiVertexAttrib4dv;
    result["glVertexAttrib4f"]           = Interception::Hooks::OpenGL::aiVertexAttrib4f;
    result["glVertexAttrib4fv"]          = Interception::Hooks::OpenGL::aiVertexAttrib4fv;
    result["glVertexAttrib4iv"]          = Interception::Hooks::OpenGL::aiVertexAttrib4iv;
    result["glVertexAttrib4Nbv"]         = Interception::Hooks::OpenGL::aiVertexAttrib4Nbv;
    result["glVertexAttrib4Niv"]         = Interception::Hooks::OpenGL::aiVertexAttrib4Niv;
    result["glVertexAttrib4Nsv"]         = Interception::Hooks::OpenGL::aiVertexAttrib4Nsv;
    result["glVertexAttrib4Nub"]         = Interception::Hooks::OpenGL::aiVertexAttrib4Nub;
    result["glVertexAttrib4Nubv"]        = Interception::Hooks::OpenGL::aiVertexAttrib4Nubv;
    result["glVertexAttrib4Nuiv"]        = Interception::Hooks::OpenGL::aiVertexAttrib4Nuiv;
    result["glVertexAttrib4Nusv"]        = Interception::Hooks::OpenGL::aiVertexAttrib4Nusv;
    result["glVertexAttrib4s"]           = Interception::Hooks::OpenGL::aiVertexAttrib4s;
    result["glVertexAttrib4sv"]          = Interception::Hooks::OpenGL::aiVertexAttrib4sv;
    result["glVertexAttrib4ubv"]         = Interception::Hooks::OpenGL::aiVertexAttrib4ubv;
    result["glVertexAttrib4uiv"]         = Interception::Hooks::OpenGL::aiVertexAttrib4uiv;
    result["glVertexAttrib4usv"]         = Interception::Hooks::OpenGL::aiVertexAttrib4usv;
    result["glVertexAttribPointer"]      = Interception::Hooks::OpenGL::aiVertexAttribPointer;

    result["glUniformMatrix2x3fv"] = Interception::Hooks::OpenGL::aiUniformMatrix2x3fv;
    result["glUniformMatrix2x4fv"] = Interception::Hooks::OpenGL::aiUniformMatrix2x4fv;
    result["glUniformMatrix3x2fv"] = Interception::Hooks::OpenGL::aiUniformMatrix3x2fv;
    result["glUniformMatrix3x4fv"] = Interception::Hooks::OpenGL::aiUniformMatrix3x4fv;
    result["glUniformMatrix4x2fv"] = Interception::Hooks::OpenGL::aiUniformMatrix4x2fv;
    result["glUniformMatrix4x3fv"] = Interception::Hooks::OpenGL::aiUniformMatrix4x3fv;

    result["glBeginConditionalRender"]              = Interception::Hooks::OpenGL::aiBeginConditionalRender;
    result["glBeginTransformFeedback"]              = Interception::Hooks::OpenGL::aiBeginTransformFeedback;
    result["glBindBufferBase"]                      = Interception::Hooks::OpenGL::aiBindBufferBase;
    result["glBindBufferRange"]                     = Interception::Hooks::OpenGL::aiBindBufferRange;
    result["glBindFragDataLocation"]                = Interception::Hooks::OpenGL::aiBindFragDataLocation;
    result["glBindFramebuffer"]                     = Interception::Hooks::OpenGL::aiBindFramebuffer;
    result["glBindRenderbuffer"]                    = Interception::Hooks::OpenGL::aiBindRenderbuffer;
    result["glBindVertexArray"]                     = Interception::Hooks::OpenGL::aiBindVertexArray;
    result["glBlitFramebuffer"]                     = Interception::Hooks::OpenGL::aiBlitFramebuffer;
    result["glCheckFramebufferStatus"]              = Interception::Hooks::OpenGL::aiCheckFramebufferStatus;
    result["glClampColor"]                          = Interception::Hooks::OpenGL::aiClampColor;
    result["glClearBufferfi"]                       = Interception::Hooks::OpenGL::aiClearBufferfi;
    result["glClearBufferfv"]                       = Interception::Hooks::OpenGL::aiClearBufferfv;
    result["glClearBufferiv"]                       = Interception::Hooks::OpenGL::aiClearBufferiv;
    result["glClearBufferuiv"]                      = Interception::Hooks::OpenGL::aiClearBufferuiv;
    result["glColorMaski"]                          = Interception::Hooks::OpenGL::aiColorMaski;
    result["glDeleteFramebuffers"]                  = Interception::Hooks::OpenGL::aiDeleteFramebuffers;
    result["glDeleteRenderbuffers"]                 = Interception::Hooks::OpenGL::aiDeleteRenderbuffers;
    result["glDeleteVertexArrays"]                  = Interception::Hooks::OpenGL::aiDeleteVertexArrays;
    result["glDisablei"]                            = Interception::Hooks::OpenGL::aiDisablei;
    result["glEnablei"]                             = Interception::Hooks::OpenGL::aiEnablei;
    result["glEndConditionalRender"]                = Interception::Hooks::OpenGL::aiEndConditionalRender;
    result["glEndTransformFeedback"]                = Interception::Hooks::OpenGL::aiEndTransformFeedback;
    result["glFlushMappedBufferRange"]              = Interception::Hooks::OpenGL::aiFlushMappedBufferRange;
    result["glFramebufferRenderbuffer"]             = Interception::Hooks::OpenGL::aiFramebufferRenderbuffer;
    result["glFramebufferTexture1D"]                = Interception::Hooks::OpenGL::aiFramebufferTexture1D;
    result["glFramebufferTexture2D"]                = Interception::Hooks::OpenGL::aiFramebufferTexture2D;
    result["glFramebufferTexture3D"]                = Interception::Hooks::OpenGL::aiFramebufferTexture3D;
    result["glFramebufferTextureLayer"]             = Interception::Hooks::OpenGL::aiFramebufferTextureLayer;
    result["glGenerateMipmap"]                      = Interception::Hooks::OpenGL::aiGenerateMipmap;
    result["glGenFramebuffers"]                     = Interception::Hooks::OpenGL::aiGenFramebuffers;
    result["glGenRenderbuffers"]                    = Interception::Hooks::OpenGL::aiGenRenderbuffers;
    result["glGenVertexArrays"]                     = Interception::Hooks::OpenGL::aiGenVertexArrays;
    result["glGetBooleani_v"]                       = Interception::Hooks::OpenGL::aiGetBooleani_v;
    result["glGetFragDataLocation"]                 = Interception::Hooks::OpenGL::aiGetFragDataLocation;
    result["glGetFramebufferAttachmentParameteriv"] = Interception::Hooks::OpenGL::aiGetFramebufferAttachmentParameteriv;
    result["glGetIntegeri_v"]                       = Interception::Hooks::OpenGL::aiGetIntegeri_v;
    result["glGetRenderbufferParameteriv"]          = Interception::Hooks::OpenGL::aiGetRenderbufferParameteriv;
    result["glGetStringi"]                          = Interception::Hooks::OpenGL::aiGetStringi;
    result["glGetTexParameterIiv"]                  = Interception::Hooks::OpenGL::aiGetTexParameterIiv;
    result["glGetTexParameterIuiv"]                 = Interception::Hooks::OpenGL::aiGetTexParameterIuiv;
    result["glGetTransformFeedbackVarying"]         = Interception::Hooks::OpenGL::aiGetTransformFeedbackVarying;
    result["glGetUniformuiv"]                       = Interception::Hooks::OpenGL::aiGetUniformuiv;
    result["glGetVertexAttribIiv"]                  = Interception::Hooks::OpenGL::aiGetVertexAttribIiv;
    result["glGetVertexAttribIuiv"]                 = Interception::Hooks::OpenGL::aiGetVertexAttribIuiv;
    result["glIsEnabledi"]                          = Interception::Hooks::OpenGL::aiIsEnabledi;
    result["glIsFramebuffer"]                       = Interception::Hooks::OpenGL::aiIsFramebuffer;
    result["glIsRenderbuffer"]                      = Interception::Hooks::OpenGL::aiIsRenderbuffer;
    result["glIsVertexArray"]                       = Interception::Hooks::OpenGL::aiIsVertexArray;
    result["glMapBufferRange"]                      = Interception::Hooks::OpenGL::aiMapBufferRange;
    result["glRenderbufferStorage"]                 = Interception::Hooks::OpenGL::aiRenderbufferStorage;
    result["glRenderbufferStorageMultisample"]      = Interception::Hooks::OpenGL::aiRenderbufferStorageMultisample;
    result["glTexParameterIiv"]                     = Interception::Hooks::OpenGL::aiTexParameterIiv;
    result["glTexParameterIuiv"]                    = Interception::Hooks::OpenGL::aiTexParameterIuiv;
    result["glTransformFeedbackVaryings"]           = Interception::Hooks::OpenGL::aiTransformFeedbackVaryings;
    result["glUniform1ui"]                          = Interception::Hooks::OpenGL::aiUniform1ui;
    result["glUniform1uiv"]                         = Interception::Hooks::OpenGL::aiUniform1uiv;
    result["glUniform2ui"]                          = Interception::Hooks::OpenGL::aiUniform2ui;
    result["glUniform2uiv"]                         = Interception::Hooks::OpenGL::aiUniform2uiv;
    result["glUniform3ui"]                          = Interception::Hooks::OpenGL::aiUniform3ui;
    result["glUniform3uiv"]                         = Interception::Hooks::OpenGL::aiUniform3uiv;
    result["glUniform4ui"]                          = Interception::Hooks::OpenGL::aiUniform4ui;
    result["glUniform4uiv"]                         = Interception::Hooks::OpenGL::aiUniform4uiv;
    result["glVertexAttribI1i"]                     = Interception::Hooks::OpenGL::aiVertexAttribI1i;
    result["glVertexAttribI1iv"]                    = Interception::Hooks::OpenGL::aiVertexAttribI1iv;
    result["glVertexAttribI1ui"]                    = Interception::Hooks::OpenGL::aiVertexAttribI1ui;
    result["glVertexAttribI1uiv"]                   = Interception::Hooks::OpenGL::aiVertexAttribI1uiv;
    result["glVertexAttribI2i"]                     = Interception::Hooks::OpenGL::aiVertexAttribI2i;
    result["glVertexAttribI2iv"]                    = Interception::Hooks::OpenGL::aiVertexAttribI2iv;
    result["glVertexAttribI2ui"]                    = Interception::Hooks::OpenGL::aiVertexAttribI2ui;
    result["glVertexAttribI2uiv"]                   = Interception::Hooks::OpenGL::aiVertexAttribI2uiv;
    result["glVertexAttribI3i"]                     = Interception::Hooks::OpenGL::aiVertexAttribI3i;
    result["glVertexAttribI3iv"]                    = Interception::Hooks::OpenGL::aiVertexAttribI3iv;
    result["glVertexAttribI3ui"]                    = Interception::Hooks::OpenGL::aiVertexAttribI3ui;
    result["glVertexAttribI3uiv"]                   = Interception::Hooks::OpenGL::aiVertexAttribI3uiv;
    result["glVertexAttribI4bv"]                    = Interception::Hooks::OpenGL::aiVertexAttribI4bv;
    result["glVertexAttribI4i"]                     = Interception::Hooks::OpenGL::aiVertexAttribI4i;
    result["glVertexAttribI4iv"]                    = Interception::Hooks::OpenGL::aiVertexAttribI4iv;
    result["glVertexAttribI4sv"]                    = Interception::Hooks::OpenGL::aiVertexAttribI4sv;
    result["glVertexAttribI4ubv"]                   = Interception::Hooks::OpenGL::aiVertexAttribI4ubv;
    result["glVertexAttribI4ui"]                    = Interception::Hooks::OpenGL::aiVertexAttribI4ui;
    result["glVertexAttribI4uiv"]                   = Interception::Hooks::OpenGL::aiVertexAttribI4uiv;
    result["glVertexAttribI4usv"]                   = Interception::Hooks::OpenGL::aiVertexAttribI4usv;
    result["glVertexAttribIPointer"]                = Interception::Hooks::OpenGL::aiVertexAttribIPointer;
    result["glViewport"]                            = Interception::Hooks::OpenGL::aiViewport;

    result["glCopyBufferSubData"]         = Interception::Hooks::OpenGL::aiCopyBufferSubData;
    result["glDrawArraysInstanced"]       = Interception::Hooks::OpenGL::aiDrawArraysInstanced;
    result["glDrawElementsInstanced"]     = Interception::Hooks::OpenGL::aiDrawElementsInstanced;
    result["glGetActiveUniformsiv"]       = Interception::Hooks::OpenGL::aiGetActiveUniformsiv;
    result["glGetActiveUniformBlockiv"]   = Interception::Hooks::OpenGL::aiGetActiveUniformBlockiv;
    result["glGetActiveUniformBlockName"] = Interception::Hooks::OpenGL::aiGetActiveUniformBlockName;
    result["glGetActiveUniformName"]      = Interception::Hooks::OpenGL::aiGetActiveUniformName;
    result["glGetUniformBlockIndex"]      = Interception::Hooks::OpenGL::aiGetUniformBlockIndex;
    result["glGetUniformIndices"]         = Interception::Hooks::OpenGL::aiGetUniformIndices;
    result["glPrimitiveRestartIndex"]     = Interception::Hooks::OpenGL::aiPrimitiveRestartIndex;
    result["glTexBuffer"]                 = Interception::Hooks::OpenGL::aiTexBuffer;
    result["glUniformBlockBinding"]       = Interception::Hooks::OpenGL::aiUniformBlockBinding;

    result["glClientWaitSync"]                  = Interception::Hooks::OpenGL::aiClientWaitSync;
    result["glDeleteSync"]                      = Interception::Hooks::OpenGL::aiDeleteSync;
    result["glDrawElementsBaseVertex"]          = Interception::Hooks::OpenGL::aiDrawElementsBaseVertex;
    result["glDrawElementsInstancedBaseVertex"] = Interception::Hooks::OpenGL::aiDrawElementsInstancedBaseVertex;
    result["glDrawRangeElementsBaseVertex"]     = Interception::Hooks::OpenGL::aiDrawRangeElementsBaseVertex;
    result["glFenceSync"]                       = Interception::Hooks::OpenGL::aiFenceSync;
    result["glFramebufferTexture"]              = Interception::Hooks::OpenGL::aiFramebufferTexture;
    result["glGetBufferParameteri64v"]          = Interception::Hooks::OpenGL::aiGetBufferParameteri64v;
    result["glGetInteger64i_v"]                 = Interception::Hooks::OpenGL::aiGetInteger64i_v;
    result["glGetInteger64v"]                   = Interception::Hooks::OpenGL::aiGetInteger64v;
    result["glGetMultisamplefv"]                = Interception::Hooks::OpenGL::aiGetMultisamplefv;
    result["glGetSynciv"]                       = Interception::Hooks::OpenGL::aiGetSynciv;
    result["glIsSync"]                          = Interception::Hooks::OpenGL::aiIsSync;
    result["glMultiDrawElementsBaseVertex"]     = Interception::Hooks::OpenGL::aiMultiDrawElementsBaseVertex;
    result["glProvokingVertex"]                 = Interception::Hooks::OpenGL::aiProvokingVertex;
    result["glSampleMaski"]                     = Interception::Hooks::OpenGL::aiSampleMaski;
    result["glTexImage2DMultisample"]           = Interception::Hooks::OpenGL::aiTexImage2DMultisample;
    result["glTexImage3DMultisample"]           = Interception::Hooks::OpenGL::aiTexImage3DMultisample;
    result["glWaitSync"]                        = Interception::Hooks::OpenGL::aiWaitSync;

    result["glBindFragDataLocationIndexed"] = Interception::Hooks::OpenGL::aiBindFragDataLocationIndexed;
    result["glBindSampler"]                 = Interception::Hooks::OpenGL::aiBindSampler;
    result["glDeleteSamplers"]              = Interception::Hooks::OpenGL::aiDeleteSamplers;
    result["glGenSamplers"]                 = Interception::Hooks::OpenGL::aiGenSamplers;
    result["glGetFragDataIndex"]            = Interception::Hooks::OpenGL::aiGetFragDataIndex;
    result["glGetQueryObjecti64v"]          = Interception::Hooks::OpenGL::aiGetQueryObjecti64v;
    result["glGetQueryObjectui64v"]         = Interception::Hooks::OpenGL::aiGetQueryObjectui64v;
    result["glGetSamplerParameterfv"]       = Interception::Hooks::OpenGL::aiGetSamplerParameterfv;
    result["glGetSamplerParameterIiv"]      = Interception::Hooks::OpenGL::aiGetSamplerParameterIiv;
    result["glGetSamplerParameterIuiv"]     = Interception::Hooks::OpenGL::aiGetSamplerParameterIuiv;
    result["glGetSamplerParameteriv"]       = Interception::Hooks::OpenGL::aiGetSamplerParameteriv;
    result["glIsSampler"]                   = Interception::Hooks::OpenGL::aiIsSampler;
    result["glQueryCounter"]                = Interception::Hooks::OpenGL::aiQueryCounter;
    result["glSamplerParameterf"]           = Interception::Hooks::OpenGL::aiSamplerParameterf;
    result["glSamplerParameterfv"]          = Interception::Hooks::OpenGL::aiSamplerParameterfv;
    result["glSamplerParameteri"]           = Interception::Hooks::OpenGL::aiSamplerParameteri;
    result["glSamplerParameterIiv"]         = Interception::Hooks::OpenGL::aiSamplerParameterIiv;
    result["glSamplerParameterIuiv"]        = Interception::Hooks::OpenGL::aiSamplerParameterIuiv;
    result["glSamplerParameteriv"]          = Interception::Hooks::OpenGL::aiSamplerParameteriv;
    result["glVertexAttribDivisor"]         = Interception::Hooks::OpenGL::aiVertexAttribDivisor;
    result["glVertexAttribDivisorARB"]      = Interception::Hooks::OpenGL::aiVertexAttribDivisorARB;
    result["glVertexAttribP1ui"]            = Interception::Hooks::OpenGL::aiVertexAttribP1ui;
    result["glVertexAttribP1uiv"]           = Interception::Hooks::OpenGL::aiVertexAttribP1uiv;
    result["glVertexAttribP2ui"]            = Interception::Hooks::OpenGL::aiVertexAttribP2ui;
    result["glVertexAttribP2uiv"]           = Interception::Hooks::OpenGL::aiVertexAttribP2uiv;
    result["glVertexAttribP3ui"]            = Interception::Hooks::OpenGL::aiVertexAttribP3ui;
    result["glVertexAttribP3uiv"]           = Interception::Hooks::OpenGL::aiVertexAttribP3uiv;
    result["glVertexAttribP4ui"]            = Interception::Hooks::OpenGL::aiVertexAttribP4ui;
    result["glVertexAttribP4uiv"]           = Interception::Hooks::OpenGL::aiVertexAttribP4uiv;

    result["glBeginQueryIndexed"]              = Interception::Hooks::OpenGL::aiBeginQueryIndexed;
    result["glBindTransformFeedback"]          = Interception::Hooks::OpenGL::aiBindTransformFeedback;
    result["glBlendEquationi"]                 = Interception::Hooks::OpenGL::aiBlendEquationi;
    result["glBlendEquationiARB"]              = Interception::Hooks::OpenGL::aiBlendEquationiARB;
    result["glBlendEquationSeparatei"]         = Interception::Hooks::OpenGL::aiBlendEquationSeparatei;
    result["glBlendEquationSeparateiARB"]      = Interception::Hooks::OpenGL::aiBlendEquationSeparateiARB;
    result["glBlendFunci"]                     = Interception::Hooks::OpenGL::aiBlendFunci;
    result["glBlendFunciARB"]                  = Interception::Hooks::OpenGL::aiBlendFunciARB;
    result["glBlendFuncSeparatei"]             = Interception::Hooks::OpenGL::aiBlendFuncSeparatei;
    result["glBlendFuncSeparateiARB"]          = Interception::Hooks::OpenGL::aiBlendFuncSeparateiARB;
    result["glDeleteTransformFeedbacks"]       = Interception::Hooks::OpenGL::aiDeleteTransformFeedbacks;
    result["glDrawArraysIndirect"]             = Interception::Hooks::OpenGL::aiDrawArraysIndirect;
    result["glDrawElementsIndirect"]           = Interception::Hooks::OpenGL::aiDrawElementsIndirect;
    result["glDrawTransformFeedback"]          = Interception::Hooks::OpenGL::aiDrawTransformFeedback;
    result["glDrawTransformFeedbackStream"]    = Interception::Hooks::OpenGL::aiDrawTransformFeedbackStream;
    result["glEndQueryIndexed"]                = Interception::Hooks::OpenGL::aiEndQueryIndexed;
    result["glGenTransformFeedbacks"]          = Interception::Hooks::OpenGL::aiGenTransformFeedbacks;
    result["glGetActiveSubroutineName"]        = Interception::Hooks::OpenGL::aiGetActiveSubroutineName;
    result["glGetActiveSubroutineUniformiv"]   = Interception::Hooks::OpenGL::aiGetActiveSubroutineUniformiv;
    result["glGetActiveSubroutineUniformName"] = Interception::Hooks::OpenGL::aiGetActiveSubroutineUniformName;
    result["glGetProgramStageiv"]              = Interception::Hooks::OpenGL::aiGetProgramStageiv;
    result["glGetQueryIndexediv"]              = Interception::Hooks::OpenGL::aiGetQueryIndexediv;
    result["glGetSubroutineIndex"]             = Interception::Hooks::OpenGL::aiGetSubroutineIndex;
    result["glGetSubroutineUniformLocation"]   = Interception::Hooks::OpenGL::aiGetSubroutineUniformLocation;
    result["glGetUniformdv"]                   = Interception::Hooks::OpenGL::aiGetUniformdv;
    result["glGetUniformSubroutineuiv"]        = Interception::Hooks::OpenGL::aiGetUniformSubroutineuiv;
    result["glIsTransformFeedback"]            = Interception::Hooks::OpenGL::aiIsTransformFeedback;
    result["glMinSampleShading"]               = Interception::Hooks::OpenGL::aiMinSampleShading;
    result["glMinSampleShadingARB"]            = Interception::Hooks::OpenGL::aiMinSampleShadingARB;
    result["glPatchParameterfv"]               = Interception::Hooks::OpenGL::aiPatchParameterfv;
    result["glPatchParameteri"]                = Interception::Hooks::OpenGL::aiPatchParameteri;
    result["glPauseTransformFeedback"]         = Interception::Hooks::OpenGL::aiPauseTransformFeedback;
    result["glResumeTransformFeedback"]        = Interception::Hooks::OpenGL::aiResumeTransformFeedback;
    result["glUniform1d"]                      = Interception::Hooks::OpenGL::aiUniform1d;
    result["glUniform1dv"]                     = Interception::Hooks::OpenGL::aiUniform1dv;
    result["glUniform2d"]                      = Interception::Hooks::OpenGL::aiUniform2d;
    result["glUniform2dv"]                     = Interception::Hooks::OpenGL::aiUniform2dv;
    result["glUniform3d"]                      = Interception::Hooks::OpenGL::aiUniform3d;
    result["glUniform3dv"]                     = Interception::Hooks::OpenGL::aiUniform3dv;
    result["glUniform4d"]                      = Interception::Hooks::OpenGL::aiUniform4d;
    result["glUniform4dv"]                     = Interception::Hooks::OpenGL::aiUniform4dv;
    result["glUniformMatrix2dv"]               = Interception::Hooks::OpenGL::aiUniformMatrix2dv;
    result["glUniformMatrix2x3dv"]             = Interception::Hooks::OpenGL::aiUniformMatrix2x3dv;
    result["glUniformMatrix2x4dv"]             = Interception::Hooks::OpenGL::aiUniformMatrix2x4dv;
    result["glUniformMatrix3dv"]               = Interception::Hooks::OpenGL::aiUniformMatrix3dv;
    result["glUniformMatrix3x2dv"]             = Interception::Hooks::OpenGL::aiUniformMatrix3x2dv;
    result["glUniformMatrix3x4dv"]             = Interception::Hooks::OpenGL::aiUniformMatrix3x4dv;
    result["glUniformMatrix4dv"]               = Interception::Hooks::OpenGL::aiUniformMatrix4dv;
    result["glUniformMatrix4x2dv"]             = Interception::Hooks::OpenGL::aiUniformMatrix4x2dv;
    result["glUniformMatrix4x3dv"]             = Interception::Hooks::OpenGL::aiUniformMatrix4x3dv;
    result["glUniformSubroutinesuiv"]          = Interception::Hooks::OpenGL::aiUniformSubroutinesuiv;

    result["glActiveShaderProgram"]           = Interception::Hooks::OpenGL::aiActiveShaderProgram;
    result["glBindProgramPipeline"]           = Interception::Hooks::OpenGL::aiBindProgramPipeline;
    result["glClearDepthf"]                   = Interception::Hooks::OpenGL::aiClearDepthf;
    result["glCreateShaderProgramv"]          = Interception::Hooks::OpenGL::aiCreateShaderProgramv;
    result["glDeleteProgramPipelines"]        = Interception::Hooks::OpenGL::aiDeleteProgramPipelines;
    result["glDepthRangeArrayv"]              = Interception::Hooks::OpenGL::aiDepthRangeArrayv;
    result["glDepthRangef"]                   = Interception::Hooks::OpenGL::aiDepthRangef;
    result["glDepthRangeIndexed"]             = Interception::Hooks::OpenGL::aiDepthRangeIndexed;
    result["glGenProgramPipelines"]           = Interception::Hooks::OpenGL::aiGenProgramPipelines;
    result["glGetDoublei_v"]                  = Interception::Hooks::OpenGL::aiGetDoublei_v;
    result["glGetFloati_v"]                   = Interception::Hooks::OpenGL::aiGetFloati_v;
    result["glGetProgramBinary"]              = Interception::Hooks::OpenGL::aiGetProgramBinary;
    result["glGetProgramPipelineInfoLog"]     = Interception::Hooks::OpenGL::aiGetProgramPipelineInfoLog;
    result["glGetProgramPipelineiv"]          = Interception::Hooks::OpenGL::aiGetProgramPipelineiv;
    result["glGetShaderPrecisionFormat"]      = Interception::Hooks::OpenGL::aiGetShaderPrecisionFormat;
    result["glGetVertexAttribLdv"]            = Interception::Hooks::OpenGL::aiGetVertexAttribLdv;
    result["glIsProgramPipeline"]             = Interception::Hooks::OpenGL::aiIsProgramPipeline;
    result["glProgramBinary"]                 = Interception::Hooks::OpenGL::aiProgramBinary;
    result["glProgramParameteri"]             = Interception::Hooks::OpenGL::aiProgramParameteri;
    result["glProgramUniform1d"]              = Interception::Hooks::OpenGL::aiProgramUniform1d;
    result["glProgramUniform1dv"]             = Interception::Hooks::OpenGL::aiProgramUniform1dv;
    result["glProgramUniform1f"]              = Interception::Hooks::OpenGL::aiProgramUniform1f;
    result["glProgramUniform1fv"]             = Interception::Hooks::OpenGL::aiProgramUniform1fv;
    result["glProgramUniform1i"]              = Interception::Hooks::OpenGL::aiProgramUniform1i;
    result["glProgramUniform1iv"]             = Interception::Hooks::OpenGL::aiProgramUniform1iv;
    result["glProgramUniform1ui"]             = Interception::Hooks::OpenGL::aiProgramUniform1ui;
    result["glProgramUniform1uiv"]            = Interception::Hooks::OpenGL::aiProgramUniform1uiv;
    result["glProgramUniform2d"]              = Interception::Hooks::OpenGL::aiProgramUniform2d;
    result["glProgramUniform2dv"]             = Interception::Hooks::OpenGL::aiProgramUniform2dv;
    result["glProgramUniform2f"]              = Interception::Hooks::OpenGL::aiProgramUniform2f;
    result["glProgramUniform2fv"]             = Interception::Hooks::OpenGL::aiProgramUniform2fv;
    result["glProgramUniform2i"]              = Interception::Hooks::OpenGL::aiProgramUniform2i;
    result["glProgramUniform2iv"]             = Interception::Hooks::OpenGL::aiProgramUniform2iv;
    result["glProgramUniform2ui"]             = Interception::Hooks::OpenGL::aiProgramUniform2ui;
    result["glProgramUniform2uiv"]            = Interception::Hooks::OpenGL::aiProgramUniform2uiv;
    result["glProgramUniform3d"]              = Interception::Hooks::OpenGL::aiProgramUniform3d;
    result["glProgramUniform3dv"]             = Interception::Hooks::OpenGL::aiProgramUniform3dv;
    result["glProgramUniform3f"]              = Interception::Hooks::OpenGL::aiProgramUniform3f;
    result["glProgramUniform3fv"]             = Interception::Hooks::OpenGL::aiProgramUniform3fv;
    result["glProgramUniform3i"]              = Interception::Hooks::OpenGL::aiProgramUniform3i;
    result["glProgramUniform3iv"]             = Interception::Hooks::OpenGL::aiProgramUniform3iv;
    result["glProgramUniform3ui"]             = Interception::Hooks::OpenGL::aiProgramUniform3ui;
    result["glProgramUniform3uiv"]            = Interception::Hooks::OpenGL::aiProgramUniform3uiv;
    result["glProgramUniform4d"]              = Interception::Hooks::OpenGL::aiProgramUniform4d;
    result["glProgramUniform4dv"]             = Interception::Hooks::OpenGL::aiProgramUniform4dv;
    result["glProgramUniform4f"]              = Interception::Hooks::OpenGL::aiProgramUniform4f;
    result["glProgramUniform4fv"]             = Interception::Hooks::OpenGL::aiProgramUniform4fv;
    result["glProgramUniform4i"]              = Interception::Hooks::OpenGL::aiProgramUniform4i;
    result["glProgramUniform4iv"]             = Interception::Hooks::OpenGL::aiProgramUniform4iv;
    result["glProgramUniform4ui"]             = Interception::Hooks::OpenGL::aiProgramUniform4ui;
    result["glProgramUniform4uiv"]            = Interception::Hooks::OpenGL::aiProgramUniform4uiv;
    result["glProgramUniformMatrix2dv"]       = Interception::Hooks::OpenGL::aiProgramUniformMatrix2dv;
    result["glProgramUniformMatrix2fv"]       = Interception::Hooks::OpenGL::aiProgramUniformMatrix2fv;
    result["glProgramUniformMatrix2x3dv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix2x3dv;
    result["glProgramUniformMatrix2x3fv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix2x3fv;
    result["glProgramUniformMatrix2x4dv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix2x4dv;
    result["glProgramUniformMatrix2x4fv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix2x4fv;
    result["glProgramUniformMatrix3dv"]       = Interception::Hooks::OpenGL::aiProgramUniformMatrix3dv;
    result["glProgramUniformMatrix3fv"]       = Interception::Hooks::OpenGL::aiProgramUniformMatrix3fv;
    result["glProgramUniformMatrix3x2dv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix3x2dv;
    result["glProgramUniformMatrix3x2fv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix3x2fv;
    result["glProgramUniformMatrix3x4dv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix3x4dv;
    result["glProgramUniformMatrix3x4fv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix3x4fv;
    result["glProgramUniformMatrix4dv"]       = Interception::Hooks::OpenGL::aiProgramUniformMatrix4dv;
    result["glProgramUniformMatrix4fv"]       = Interception::Hooks::OpenGL::aiProgramUniformMatrix4fv;
    result["glProgramUniformMatrix4x2dv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix4x2dv;
    result["glProgramUniformMatrix4x2fv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix4x2fv;
    result["glProgramUniformMatrix4x3dv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix4x3dv;
    result["glProgramUniformMatrix4x3fv"]     = Interception::Hooks::OpenGL::aiProgramUniformMatrix4x3fv;
    result["glReleaseShaderCompiler"]         = Interception::Hooks::OpenGL::aiReleaseShaderCompiler;
    result["glScissorArrayv"]                 = Interception::Hooks::OpenGL::aiScissorArrayv;
    result["glScissorIndexed"]                = Interception::Hooks::OpenGL::aiScissorIndexed;
    result["glScissorIndexedv"]               = Interception::Hooks::OpenGL::aiScissorIndexedv;
    result["glShaderBinary"]                  = Interception::Hooks::OpenGL::aiShaderBinary;
    result["glUseProgramStages"]              = Interception::Hooks::OpenGL::aiUseProgramStages;
    result["glValidateProgramPipeline"]       = Interception::Hooks::OpenGL::aiValidateProgramPipeline;
    result["glVertexAttribL1d"]               = Interception::Hooks::OpenGL::aiVertexAttribL1d;
    result["glVertexAttribL1dv"]              = Interception::Hooks::OpenGL::aiVertexAttribL1dv;
    result["glVertexAttribL2d"]               = Interception::Hooks::OpenGL::aiVertexAttribL2d;
    result["glVertexAttribL2dv"]              = Interception::Hooks::OpenGL::aiVertexAttribL2dv;
    result["glVertexAttribL3d"]               = Interception::Hooks::OpenGL::aiVertexAttribL3d;
    result["glVertexAttribL3dv"]              = Interception::Hooks::OpenGL::aiVertexAttribL3dv;
    result["glVertexAttribL4d"]               = Interception::Hooks::OpenGL::aiVertexAttribL4d;
    result["glVertexAttribL4dv"]              = Interception::Hooks::OpenGL::aiVertexAttribL4dv;
    result["glVertexAttribLPointer"]          = Interception::Hooks::OpenGL::aiVertexAttribLPointer;
    result["glViewportArrayv"]                = Interception::Hooks::OpenGL::aiViewportArrayv;
    result["glViewportIndexedf"]              = Interception::Hooks::OpenGL::aiViewportIndexedf;
    result["glViewportIndexedfv"]             = Interception::Hooks::OpenGL::aiViewportIndexedfv;

    result["glBindImageTexture"]                                 = Interception::Hooks::OpenGL::aiBindImageTexture;
    result["glDrawArraysInstancedBaseInstance"]                  = Interception::Hooks::OpenGL::aiDrawArraysInstancedBaseInstance;
    result["glDrawElementsInstancedBaseInstance"]                = Interception::Hooks::OpenGL::aiDrawElementsInstancedBaseInstance;
    result["glDrawElementsInstancedBaseVertexBaseInstance"]      = Interception::Hooks::OpenGL::aiDrawElementsInstancedBaseVertexBaseInstance;
    result["glDrawTransformFeedbackInstanced"]                   = Interception::Hooks::OpenGL::aiDrawTransformFeedbackInstanced;
    result["glDrawTransformFeedbackStreamInstanced"]             = Interception::Hooks::OpenGL::aiDrawTransformFeedbackStreamInstanced;
    result["glGetActiveAtomicCounterBufferiv"]                   = Interception::Hooks::OpenGL::aiGetActiveAtomicCounterBufferiv;
    result["glGetInternalformativ"]                              = Interception::Hooks::OpenGL::aiGetInternalformativ;
    result["glMemoryBarrier"]                                    = Interception::Hooks::OpenGL::aiMemoryBarrier;
    result["glTexStorage1D"]                                     = Interception::Hooks::OpenGL::aiTexStorage1D;
    result["glTexStorage2D"]                                     = Interception::Hooks::OpenGL::aiTexStorage2D;
    result["glTexStorage3D"]                                     = Interception::Hooks::OpenGL::aiTexStorage3D;

    result["glBindVertexBuffer"]                 = Interception::Hooks::OpenGL::aiBindVertexBuffer;
    result["glClearBufferData"]                  = Interception::Hooks::OpenGL::aiClearBufferData;
    result["glClearBufferSubData"]               = Interception::Hooks::OpenGL::aiClearBufferSubData;
    result["glCopyImageSubData"]                 = Interception::Hooks::OpenGL::aiCopyImageSubData;
    result["glDebugMessageCallback"]             = Interception::Hooks::OpenGL::aiDebugMessageCallback;
    result["glDebugMessageCallbackARB"]          = Interception::Hooks::OpenGL::aiDebugMessageCallbackARB;
    result["glDebugMessageControl"]              = Interception::Hooks::OpenGL::aiDebugMessageControl;
    result["glDebugMessageControlARB"]           = Interception::Hooks::OpenGL::aiDebugMessageControlARB;
    result["glDebugMessageInsert"]               = Interception::Hooks::OpenGL::aiDebugMessageInsert;
    result["glDebugMessageInsertARB"]            = Interception::Hooks::OpenGL::aiDebugMessageInsertARB;
    result["glDispatchCompute"]                  = Interception::Hooks::OpenGL::aiDispatchCompute;
    result["glDispatchComputeIndirect"]          = Interception::Hooks::OpenGL::aiDispatchComputeIndirect;
    result["glFramebufferParameteri"]            = Interception::Hooks::OpenGL::aiFramebufferParameteri;
    result["glGetDebugMessageLog"]               = Interception::Hooks::OpenGL::aiGetDebugMessageLog;
    result["glGetDebugMessageLogARB"]            = Interception::Hooks::OpenGL::aiGetDebugMessageLogARB;
    result["glGetFramebufferParameteriv"]        = Interception::Hooks::OpenGL::aiGetFramebufferParameteriv;
    result["glGetInternalformati64v"]            = Interception::Hooks::OpenGL::aiGetInternalformati64v;
    result["glGetObjectLabel"]                   = Interception::Hooks::OpenGL::aiGetObjectLabel;
    result["glGetObjectPtrLabel"]                = Interception::Hooks::OpenGL::aiGetObjectPtrLabel;
    result["glGetProgramInterfaceiv"]            = Interception::Hooks::OpenGL::aiGetProgramInterfaceiv;
    result["glGetProgramResourceIndex"]          = Interception::Hooks::OpenGL::aiGetProgramResourceIndex;
    result["glGetProgramResourceiv"]             = Interception::Hooks::OpenGL::aiGetProgramResourceiv;
    result["glGetProgramResourceLocation"]       = Interception::Hooks::OpenGL::aiGetProgramResourceLocation;
    result["glGetProgramResourceLocationIndex"]  = Interception::Hooks::OpenGL::aiGetProgramResourceLocationIndex;
    result["glGetProgramResourceName"]           = Interception::Hooks::OpenGL::aiGetProgramResourceName;
    result["glInvalidateBufferData"]             = Interception::Hooks::OpenGL::aiInvalidateBufferData;
    result["glInvalidateBufferSubData"]          = Interception::Hooks::OpenGL::aiInvalidateBufferSubData;
    result["glInvalidateFramebuffer"]            = Interception::Hooks::OpenGL::aiInvalidateFramebuffer;
    result["glInvalidateSubFramebuffer"]         = Interception::Hooks::OpenGL::aiInvalidateSubFramebuffer;
    result["glInvalidateTexImage"]               = Interception::Hooks::OpenGL::aiInvalidateTexImage;
    result["glInvalidateTexSubImage"]            = Interception::Hooks::OpenGL::aiInvalidateTexSubImage;
    result["glMultiDrawArraysIndirect"]          = Interception::Hooks::OpenGL::aiMultiDrawArraysIndirect;
    result["glMultiDrawElementsIndirect"]        = Interception::Hooks::OpenGL::aiMultiDrawElementsIndirect;
    result["glObjectLabel"]                      = Interception::Hooks::OpenGL::aiObjectLabel;
    result["glObjectPtrLabel"]                   = Interception::Hooks::OpenGL::aiObjectPtrLabel;
    result["glPopDebugGroup"]                    = Interception::Hooks::OpenGL::aiPopDebugGroup;
    result["glPushDebugGroup"]                   = Interception::Hooks::OpenGL::aiPushDebugGroup;
    result["glShaderStorageBlockBinding"]        = Interception::Hooks::OpenGL::aiShaderStorageBlockBinding;
    result["glTexBufferRange"]                   = Interception::Hooks::OpenGL::aiTexBufferRange;
    result["glTexStorage2DMultisample"]          = Interception::Hooks::OpenGL::aiTexStorage2DMultisample;
    result["glTexStorage3DMultisample"]          = Interception::Hooks::OpenGL::aiTexStorage3DMultisample;
    result["glTextureView"]                      = Interception::Hooks::OpenGL::aiTextureView;
    result["glVertexAttribBinding"]              = Interception::Hooks::OpenGL::aiVertexAttribBinding;
    result["glVertexAttribFormat"]               = Interception::Hooks::OpenGL::aiVertexAttribFormat;
    result["glVertexAttribIFormat"]              = Interception::Hooks::OpenGL::aiVertexAttribIFormat;
    result["glVertexAttribLFormat"]              = Interception::Hooks::OpenGL::aiVertexAttribLFormat;
    result["glVertexBindingDivisor"]             = Interception::Hooks::OpenGL::aiVertexBindingDivisor;

    result["glBindBuffersBase"]    = Interception::Hooks::OpenGL::aiBindBuffersBase;
    result["glBindBuffersRange"]   = Interception::Hooks::OpenGL::aiBindBuffersRange;
    result["glBindImageTextures"]  = Interception::Hooks::OpenGL::aiBindImageTextures;
    result["glBindSamplers"]       = Interception::Hooks::OpenGL::aiBindSamplers;
    result["glBindTextures"]       = Interception::Hooks::OpenGL::aiBindTextures;
    result["glBindVertexBuffers"]  = Interception::Hooks::OpenGL::aiBindVertexBuffers;
    result["glBufferStorage"]      = Interception::Hooks::OpenGL::aiBufferStorage;
    result["glClearTexImage"]      = Interception::Hooks::OpenGL::aiClearTexImage;
    result["glClearTexSubImage"]   = Interception::Hooks::OpenGL::aiClearTexSubImage;

    result["glBindTextureUnit"]                               = Interception::Hooks::OpenGL::aiBindTextureUnit;
    result["glBlitNamedFramebuffer"]                          = Interception::Hooks::OpenGL::aiBlitNamedFramebuffer;
    result["glCheckNamedFramebufferStatus"]                   = Interception::Hooks::OpenGL::aiCheckNamedFramebufferStatus;
    result["glClearNamedBufferData"]                          = Interception::Hooks::OpenGL::aiClearNamedBufferData;
    result["glClearNamedBufferSubData"]                       = Interception::Hooks::OpenGL::aiClearNamedBufferSubData;
    result["glClearNamedFramebufferfi"]                       = Interception::Hooks::OpenGL::aiClearNamedFramebufferfi;
    result["glClearNamedFramebufferfv"]                       = Interception::Hooks::OpenGL::aiClearNamedFramebufferfv;
    result["glClearNamedFramebufferiv"]                       = Interception::Hooks::OpenGL::aiClearNamedFramebufferiv;
    result["glClearNamedFramebufferuiv"]                      = Interception::Hooks::OpenGL::aiClearNamedFramebufferuiv;
    result["glClipControl"]                                   = Interception::Hooks::OpenGL::aiClipControl;
    result["glCompressedTextureSubImage1D"]                   = Interception::Hooks::OpenGL::aiCompressedTextureSubImage1D;
    result["glCompressedTextureSubImage2D"]                   = Interception::Hooks::OpenGL::aiCompressedTextureSubImage2D;
    result["glCompressedTextureSubImage3D"]                   = Interception::Hooks::OpenGL::aiCompressedTextureSubImage3D;
    result["glCopyNamedBufferSubData"]                        = Interception::Hooks::OpenGL::aiCopyNamedBufferSubData;
    result["glCopyTextureSubImage1D"]                         = Interception::Hooks::OpenGL::aiCopyTextureSubImage1D;
    result["glCopyTextureSubImage2D"]                         = Interception::Hooks::OpenGL::aiCopyTextureSubImage2D;
    result["glCopyTextureSubImage3D"]                         = Interception::Hooks::OpenGL::aiCopyTextureSubImage3D;
    result["glCreateBuffers"]                                 = Interception::Hooks::OpenGL::aiCreateBuffers;
    result["glCreateFramebuffers"]                            = Interception::Hooks::OpenGL::aiCreateFramebuffers;
    result["glCreateProgramPipelines"]                        = Interception::Hooks::OpenGL::aiCreateProgramPipelines;
    result["glCreateQueries"]                                 = Interception::Hooks::OpenGL::aiCreateQueries;
    result["glCreateRenderbuffers"]                           = Interception::Hooks::OpenGL::aiCreateRenderbuffers;
    result["glCreateSamplers"]                                = Interception::Hooks::OpenGL::aiCreateSamplers;
    result["glCreateTextures"]                                = Interception::Hooks::OpenGL::aiCreateTextures;
    result["glCreateTransformFeedbacks"]                      = Interception::Hooks::OpenGL::aiCreateTransformFeedbacks;
    result["glCreateVertexArrays"]                            = Interception::Hooks::OpenGL::aiCreateVertexArrays;
    result["glDisableVertexArrayAttrib"]                      = Interception::Hooks::OpenGL::aiDisableVertexArrayAttrib;
    result["glEnableVertexArrayAttrib"]                       = Interception::Hooks::OpenGL::aiEnableVertexArrayAttrib;
    result["glFlushMappedNamedBufferRange"]                   = Interception::Hooks::OpenGL::aiFlushMappedNamedBufferRange;
    result["glGenerateTextureMipmap"]                         = Interception::Hooks::OpenGL::aiGenerateTextureMipmap;
    result["glGetCompressedTextureImage"]                     = Interception::Hooks::OpenGL::aiGetCompressedTextureImage;
    result["glGetCompressedTextureSubImage"]                  = Interception::Hooks::OpenGL::aiGetCompressedTextureSubImage;
    result["glGetGraphicsResetStatus"]                        = Interception::Hooks::OpenGL::aiGetGraphicsResetStatus;
    result["glGetGraphicsResetStatusARB"]                     = Interception::Hooks::OpenGL::aiGetGraphicsResetStatusARB;
    result["glGetNamedBufferParameteri64v"]                   = Interception::Hooks::OpenGL::aiGetNamedBufferParameteri64v;
    result["glGetNamedBufferParameteriv"]                     = Interception::Hooks::OpenGL::aiGetNamedBufferParameteriv;
    result["glGetNamedBufferPointerv"]                        = Interception::Hooks::OpenGL::aiGetNamedBufferPointerv;
    result["glGetNamedBufferSubData"]                         = Interception::Hooks::OpenGL::aiGetNamedBufferSubData;
    result["glGetNamedFramebufferAttachmentParameteriv"]      = Interception::Hooks::OpenGL::aiGetNamedFramebufferAttachmentParameteriv;
    result["glGetNamedFramebufferParameteriv"]                = Interception::Hooks::OpenGL::aiGetNamedFramebufferParameteriv;
    result["glGetNamedRenderbufferParameteriv"]               = Interception::Hooks::OpenGL::aiGetNamedRenderbufferParameteriv;
    result["glGetnCompressedTexImage"]                        = Interception::Hooks::OpenGL::aiGetnCompressedTexImage;
    result["glGetnCompressedTexImageARB"]                     = Interception::Hooks::OpenGL::aiGetnCompressedTexImageARB;
    result["glGetnTexImage"]                                  = Interception::Hooks::OpenGL::aiGetnTexImage;
    result["glGetnTexImageARB"]                               = Interception::Hooks::OpenGL::aiGetnTexImageARB;
    result["glGetnUniformdv"]                                 = Interception::Hooks::OpenGL::aiGetnUniformdv;
    result["glGetnUniformdvARB"]                              = Interception::Hooks::OpenGL::aiGetnUniformdvARB;
    result["glGetnUniformfv"]                                 = Interception::Hooks::OpenGL::aiGetnUniformfv;
    result["glGetnUniformfvARB"]                              = Interception::Hooks::OpenGL::aiGetnUniformfvARB;
    result["glGetnUniformiv"]                                 = Interception::Hooks::OpenGL::aiGetnUniformiv;
    result["glGetnUniformivARB"]                              = Interception::Hooks::OpenGL::aiGetnUniformivARB;
    result["glGetnUniformuiv"]                                = Interception::Hooks::OpenGL::aiGetnUniformuiv;
    result["glGetnUniformuivARB"]                             = Interception::Hooks::OpenGL::aiGetnUniformuivARB;
    result["glGetQueryBufferObjecti64v"]                      = Interception::Hooks::OpenGL::aiGetQueryBufferObjecti64v;
    result["glGetQueryBufferObjectiv"]                        = Interception::Hooks::OpenGL::aiGetQueryBufferObjectiv;
    result["glGetQueryBufferObjectui64v"]                     = Interception::Hooks::OpenGL::aiGetQueryBufferObjectui64v;
    result["glGetQueryBufferObjectuiv"]                       = Interception::Hooks::OpenGL::aiGetQueryBufferObjectuiv;
    result["glGetTextureImage"]                               = Interception::Hooks::OpenGL::aiGetTextureImage;
    result["glGetTextureLevelParameterfv"]                    = Interception::Hooks::OpenGL::aiGetTextureLevelParameterfv;
    result["glGetTextureLevelParameteriv"]                    = Interception::Hooks::OpenGL::aiGetTextureLevelParameteriv;
    result["glGetTextureParameterfv"]                         = Interception::Hooks::OpenGL::aiGetTextureParameterfv;
    result["glGetTextureParameterIiv"]                        = Interception::Hooks::OpenGL::aiGetTextureParameterIiv;
    result["glGetTextureParameterIuiv"]                       = Interception::Hooks::OpenGL::aiGetTextureParameterIuiv;
    result["glGetTextureParameteriv"]                         = Interception::Hooks::OpenGL::aiGetTextureParameteriv;
    result["glGetTextureSubImage"]                            = Interception::Hooks::OpenGL::aiGetTextureSubImage;
    result["glGetTransformFeedbacki64_v"]                     = Interception::Hooks::OpenGL::aiGetTransformFeedbacki64_v;
    result["glGetTransformFeedbacki_v"]                       = Interception::Hooks::OpenGL::aiGetTransformFeedbacki_v;
    result["glGetTransformFeedbackiv"]                        = Interception::Hooks::OpenGL::aiGetTransformFeedbackiv;
    result["glGetVertexArrayIndexed64iv"]                     = Interception::Hooks::OpenGL::aiGetVertexArrayIndexed64iv;
    result["glGetVertexArrayIndexediv"]                       = Interception::Hooks::OpenGL::aiGetVertexArrayIndexediv;
    result["glGetVertexArrayiv"]                              = Interception::Hooks::OpenGL::aiGetVertexArrayiv;
    result["glInvalidateNamedFramebufferData"]                = Interception::Hooks::OpenGL::aiInvalidateNamedFramebufferData;
    result["glInvalidateNamedFramebufferSubData"]             = Interception::Hooks::OpenGL::aiInvalidateNamedFramebufferSubData;
    result["glMapNamedBuffer"]                                = Interception::Hooks::OpenGL::aiMapNamedBuffer;
    result["glMapNamedBufferRange"]                           = Interception::Hooks::OpenGL::aiMapNamedBufferRange;
    result["glMemoryBarrierByRegion"]                         = Interception::Hooks::OpenGL::aiMemoryBarrierByRegion;
    result["glNamedBufferData"]                               = Interception::Hooks::OpenGL::aiNamedBufferData;
    result["glNamedBufferStorage"]                            = Interception::Hooks::OpenGL::aiNamedBufferStorage;
    result["glNamedBufferSubData"]                            = Interception::Hooks::OpenGL::aiNamedBufferSubData;
    result["glNamedFramebufferDrawBuffer"]                    = Interception::Hooks::OpenGL::aiNamedFramebufferDrawBuffer;
    result["glNamedFramebufferDrawBuffers"]                   = Interception::Hooks::OpenGL::aiNamedFramebufferDrawBuffers;
    result["glNamedFramebufferParameteri"]                    = Interception::Hooks::OpenGL::aiNamedFramebufferParameteri;
    result["glNamedFramebufferReadBuffer"]                    = Interception::Hooks::OpenGL::aiNamedFramebufferReadBuffer;
    result["glNamedFramebufferRenderbuffer"]                  = Interception::Hooks::OpenGL::aiNamedFramebufferRenderbuffer;
    result["glNamedFramebufferTexture"]                       = Interception::Hooks::OpenGL::aiNamedFramebufferTexture;
    result["glNamedFramebufferTextureLayer"]                  = Interception::Hooks::OpenGL::aiNamedFramebufferTextureLayer;
    result["glNamedRenderbufferStorage"]                      = Interception::Hooks::OpenGL::aiNamedRenderbufferStorage;
    result["glNamedRenderbufferStorageMultisample"]           = Interception::Hooks::OpenGL::aiNamedRenderbufferStorageMultisample;
    result["glReadnPixels"]                                   = Interception::Hooks::OpenGL::aiReadnPixels;
    result["glReadnPixelsARB"]                                = Interception::Hooks::OpenGL::aiReadnPixelsARB;
    result["glTextureBarrier"]                                = Interception::Hooks::OpenGL::aiTextureBarrier;
    result["glTextureBuffer"]                                 = Interception::Hooks::OpenGL::aiTextureBuffer;
    result["glTextureBufferRange"]                            = Interception::Hooks::OpenGL::aiTextureBufferRange;
    result["glTextureParameterf"]                             = Interception::Hooks::OpenGL::aiTextureParameterf;
    result["glTextureParameterfv"]                            = Interception::Hooks::OpenGL::aiTextureParameterfv;
    result["glTextureParameteri"]                             = Interception::Hooks::OpenGL::aiTextureParameteri;
    result["glTextureParameterIiv"]                           = Interception::Hooks::OpenGL::aiTextureParameterIiv;
    result["glTextureParameterIuiv"]                          = Interception::Hooks::OpenGL::aiTextureParameterIuiv;
    result["glTextureParameteriv"]                            = Interception::Hooks::OpenGL::aiTextureParameteriv;
    result["glTextureStorage1D"]                              = Interception::Hooks::OpenGL::aiTextureStorage1D;
    result["glTextureStorage2D"]                              = Interception::Hooks::OpenGL::aiTextureStorage2D;
    result["glTextureStorage2DMultisample"]                   = Interception::Hooks::OpenGL::aiTextureStorage2DMultisample;
    result["glTextureStorage3D"]                              = Interception::Hooks::OpenGL::aiTextureStorage3D;
    result["glTextureStorage3DMultisample"]                   = Interception::Hooks::OpenGL::aiTextureStorage3DMultisample;
    result["glTextureSubImage1D"]                             = Interception::Hooks::OpenGL::aiTextureSubImage1D;
    result["glTextureSubImage2D"]                             = Interception::Hooks::OpenGL::aiTextureSubImage2D;
    result["glTextureSubImage3D"]                             = Interception::Hooks::OpenGL::aiTextureSubImage3D;
    result["glTransformFeedbackBufferBase"]                   = Interception::Hooks::OpenGL::aiTransformFeedbackBufferBase;
    result["glTransformFeedbackBufferRange"]                  = Interception::Hooks::OpenGL::aiTransformFeedbackBufferRange;
    result["glUnmapNamedBuffer"]                              = Interception::Hooks::OpenGL::aiUnmapNamedBuffer;
    result["glVertexArrayAttribBinding"]                      = Interception::Hooks::OpenGL::aiVertexArrayAttribBinding;
    result["glVertexArrayAttribFormat"]                       = Interception::Hooks::OpenGL::aiVertexArrayAttribFormat;
    result["glVertexArrayAttribIFormat"]                      = Interception::Hooks::OpenGL::aiVertexArrayAttribIFormat;
    result["glVertexArrayAttribLFormat"]                      = Interception::Hooks::OpenGL::aiVertexArrayAttribLFormat;
    result["glVertexArrayBindingDivisor"]                     = Interception::Hooks::OpenGL::aiVertexArrayBindingDivisor;
    result["glVertexArrayElementBuffer"]                      = Interception::Hooks::OpenGL::aiVertexArrayElementBuffer;
    result["glVertexArrayVertexBuffer"]                       = Interception::Hooks::OpenGL::aiVertexArrayVertexBuffer;
    result["glVertexArrayVertexBuffers"]                      = Interception::Hooks::OpenGL::aiVertexArrayVertexBuffers;

    result["glClampColorARB"] = Interception::Hooks::OpenGL::aiClampColorARB;

    result["glDrawBuffersARB"] = Interception::Hooks::OpenGL::aiDrawBuffersARB;

    result["glDrawArraysInstancedARB"]   = Interception::Hooks::OpenGL::aiDrawArraysInstancedARB;
    result["glDrawElementsInstancedARB"] = Interception::Hooks::OpenGL::aiDrawElementsInstancedARB;

    result["glSampleCoverageARB"] = Interception::Hooks::OpenGL::aiSampleCoverageARB;

    result["glActiveTextureARB"] = Interception::Hooks::OpenGL::aiActiveTextureARB;

    result["glBeginQueryARB"]        = Interception::Hooks::OpenGL::aiBeginQueryARB;
    result["glDeleteQueriesARB"]     = Interception::Hooks::OpenGL::aiDeleteQueriesARB;
    result["glEndQueryARB"]          = Interception::Hooks::OpenGL::aiEndQueryARB;
    result["glGenQueriesARB"]        = Interception::Hooks::OpenGL::aiGenQueriesARB;
    result["glGetQueryivARB"]        = Interception::Hooks::OpenGL::aiGetQueryivARB;
    result["glGetQueryObjectivARB"]  = Interception::Hooks::OpenGL::aiGetQueryObjectivARB;
    result["glGetQueryObjectuivARB"] = Interception::Hooks::OpenGL::aiGetQueryObjectuivARB;
    result["glIsQueryARB"]           = Interception::Hooks::OpenGL::aiIsQueryARB;

    result["glPointParameterfARB"]  = Interception::Hooks::OpenGL::aiPointParameterfARB;
    result["glPointParameterfvARB"] = Interception::Hooks::OpenGL::aiPointParameterfvARB;

    result["glTexBufferARB"] = Interception::Hooks::OpenGL::aiTexBufferARB;

    result["glCompressedTexImage1DARB"]    = Interception::Hooks::OpenGL::aiCompressedTexImage1DARB;
    result["glCompressedTexImage2DARB"]    = Interception::Hooks::OpenGL::aiCompressedTexImage2DARB;
    result["glCompressedTexImage3DARB"]    = Interception::Hooks::OpenGL::aiCompressedTexImage3DARB;
    result["glCompressedTexSubImage1DARB"] = Interception::Hooks::OpenGL::aiCompressedTexSubImage1DARB;
    result["glCompressedTexSubImage2DARB"] = Interception::Hooks::OpenGL::aiCompressedTexSubImage2DARB;
    result["glCompressedTexSubImage3DARB"] = Interception::Hooks::OpenGL::aiCompressedTexSubImage3DARB;
    result["glGetCompressedTexImageARB"]   = Interception::Hooks::OpenGL::aiGetCompressedTexImageARB;

    result["glBindBufferARB"]           = Interception::Hooks::OpenGL::aiBindBufferARB;
    result["glBufferDataARB"]           = Interception::Hooks::OpenGL::aiBufferDataARB;
    result["glBufferSubDataARB"]        = Interception::Hooks::OpenGL::aiBufferSubDataARB;
    result["glDeleteBuffersARB"]        = Interception::Hooks::OpenGL::aiDeleteBuffersARB;
    result["glGenBuffersARB"]           = Interception::Hooks::OpenGL::aiGenBuffersARB;
    result["glGetBufferParameterivARB"] = Interception::Hooks::OpenGL::aiGetBufferParameterivARB;
    result["glGetBufferPointervARB"]    = Interception::Hooks::OpenGL::aiGetBufferPointervARB;
    result["glGetBufferSubDataARB"]     = Interception::Hooks::OpenGL::aiGetBufferSubDataARB;
    result["glIsBufferARB"]             = Interception::Hooks::OpenGL::aiIsBufferARB;
    result["glMapBufferARB"]            = Interception::Hooks::OpenGL::aiMapBufferARB;
    result["glUnmapBufferARB"]          = Interception::Hooks::OpenGL::aiUnmapBufferARB;

    result["glDisableVertexAttribArrayARB"] = Interception::Hooks::OpenGL::aiDisableVertexAttribArrayARB;
    result["glEnableVertexAttribArrayARB"]  = Interception::Hooks::OpenGL::aiEnableVertexAttribArrayARB;
    result["glGetVertexAttribdvARB"]        = Interception::Hooks::OpenGL::aiGetVertexAttribdvARB;
    result["glGetVertexAttribfvARB"]        = Interception::Hooks::OpenGL::aiGetVertexAttribfvARB;
    result["glGetVertexAttribivARB"]        = Interception::Hooks::OpenGL::aiGetVertexAttribivARB;
    result["glGetVertexAttribPointervARB"]  = Interception::Hooks::OpenGL::aiGetVertexAttribPointervARB;
    result["glVertexAttrib1dvARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib1dvARB;
    result["glVertexAttrib1dARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib1dARB;
    result["glVertexAttrib1fvARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib1fvARB;
    result["glVertexAttrib1fARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib1fARB;
    result["glVertexAttrib1svARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib1svARB;
    result["glVertexAttrib1sARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib1sARB;
    result["glVertexAttrib2dvARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib2dvARB;
    result["glVertexAttrib2dARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib2dARB;
    result["glVertexAttrib2fvARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib2fvARB;
    result["glVertexAttrib2fARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib2fARB;
    result["glVertexAttrib2svARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib2svARB;
    result["glVertexAttrib2sARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib2sARB;
    result["glVertexAttrib3dvARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib3dvARB;
    result["glVertexAttrib3dARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib3dARB;
    result["glVertexAttrib3fvARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib3fvARB;
    result["glVertexAttrib3fARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib3fARB;
    result["glVertexAttrib3svARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib3svARB;
    result["glVertexAttrib3sARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib3sARB;
    result["glVertexAttrib4bvARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib4bvARB;
    result["glVertexAttrib4dvARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib4dvARB;
    result["glVertexAttrib4dARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib4dARB;
    result["glVertexAttrib4fvARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib4fvARB;
    result["glVertexAttrib4fARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib4fARB;
    result["glVertexAttrib4ivARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib4ivARB;
    result["glVertexAttrib4NbvARB"]         = Interception::Hooks::OpenGL::aiVertexAttrib4NbvARB;
    result["glVertexAttrib4NivARB"]         = Interception::Hooks::OpenGL::aiVertexAttrib4NivARB;
    result["glVertexAttrib4NsvARB"]         = Interception::Hooks::OpenGL::aiVertexAttrib4NsvARB;
    result["glVertexAttrib4NubvARB"]        = Interception::Hooks::OpenGL::aiVertexAttrib4NubvARB;
    result["glVertexAttrib4NubARB"]         = Interception::Hooks::OpenGL::aiVertexAttrib4NubARB;
    result["glVertexAttrib4NuivARB"]        = Interception::Hooks::OpenGL::aiVertexAttrib4NuivARB;
    result["glVertexAttrib4NusvARB"]        = Interception::Hooks::OpenGL::aiVertexAttrib4NusvARB;
    result["glVertexAttrib4svARB"]          = Interception::Hooks::OpenGL::aiVertexAttrib4svARB;
    result["glVertexAttrib4sARB"]           = Interception::Hooks::OpenGL::aiVertexAttrib4sARB;
    result["glVertexAttrib4ubvARB"]         = Interception::Hooks::OpenGL::aiVertexAttrib4ubvARB;
    result["glVertexAttrib4uivARB"]         = Interception::Hooks::OpenGL::aiVertexAttrib4uivARB;
    result["glVertexAttrib4usvARB"]         = Interception::Hooks::OpenGL::aiVertexAttrib4usvARB;
    result["glVertexAttribPointerARB"]      = Interception::Hooks::OpenGL::aiVertexAttribPointerARB;

    result["glBindAttribLocationARB"] = Interception::Hooks::OpenGL::aiBindAttribLocationARB;
    result["glGetActiveAttribARB"]    = Interception::Hooks::OpenGL::aiGetActiveAttribARB;
    result["glGetAttribLocationARB"]  = Interception::Hooks::OpenGL::aiGetAttribLocationARB;

    /* GL_EXT_texture_object */
    result["glAreTexturesResidentEXT"] = Interception::Hooks::OpenGL::aiAreTexturesResidentEXT;
    result["glBindTextureEXT"]         = Interception::Hooks::OpenGL::aiBindTextureEXT;
    result["glDeleteTexturesEXT"]      = Interception::Hooks::OpenGL::aiDeleteTexturesEXT;
    result["glGenTexturesEXT"]         = Interception::Hooks::OpenGL::aiGenTexturesEXT;
    result["glIsTextureEXT"]           = Interception::Hooks::OpenGL::aiIsTextureEXT;
    result["glPrioritizeTexturesEXT"]  = Interception::Hooks::OpenGL::aiPrioritizeTexturesEXT;

    /* GL_ARB_transpose_matrix */
    result["glLoadTransposeMatrixdARB"] = Interception::Hooks::OpenGL::aiLoadTransposeMatrixdARB;
    result["glLoadTransposeMatrixfARB"] = Interception::Hooks::OpenGL::aiLoadTransposeMatrixfARB;
    result["glMultTransposeMatrixdARB"] = Interception::Hooks::OpenGL::aiMultTransposeMatrixdARB;
    result["glMultTransposeMatrixfARB"] = Interception::Hooks::OpenGL::aiMultTransposeMatrixfARB;

    /* GL_ARB_multitexture (missing entries) */
    result["glClientActiveTextureARB"] = Interception::Hooks::OpenGL::aiClientActiveTextureARB;
    result["glMultiTexCoord1dARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord1dARB;
    result["glMultiTexCoord1dvARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord1dvARB;
    result["glMultiTexCoord1fARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord1fARB;
    result["glMultiTexCoord1fvARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord1fvARB;
    result["glMultiTexCoord1iARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord1iARB;
    result["glMultiTexCoord1ivARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord1ivARB;
    result["glMultiTexCoord1sARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord1sARB;
    result["glMultiTexCoord1svARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord1svARB;
    result["glMultiTexCoord2dARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord2dARB;
    result["glMultiTexCoord2dvARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord2dvARB;
    result["glMultiTexCoord2fARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord2fARB;
    result["glMultiTexCoord2fvARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord2fvARB;
    result["glMultiTexCoord2iARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord2iARB;
    result["glMultiTexCoord2ivARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord2ivARB;
    result["glMultiTexCoord2sARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord2sARB;
    result["glMultiTexCoord2svARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord2svARB;
    result["glMultiTexCoord3dARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord3dARB;
    result["glMultiTexCoord3dvARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord3dvARB;
    result["glMultiTexCoord3fARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord3fARB;
    result["glMultiTexCoord3fvARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord3fvARB;
    result["glMultiTexCoord3iARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord3iARB;
    result["glMultiTexCoord3ivARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord3ivARB;
    result["glMultiTexCoord3sARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord3sARB;
    result["glMultiTexCoord3svARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord3svARB;
    result["glMultiTexCoord4dARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord4dARB;
    result["glMultiTexCoord4dvARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord4dvARB;
    result["glMultiTexCoord4fARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord4fARB;
    result["glMultiTexCoord4fvARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord4fvARB;
    result["glMultiTexCoord4iARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord4iARB;
    result["glMultiTexCoord4ivARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord4ivARB;
    result["glMultiTexCoord4sARB"]     = Interception::Hooks::OpenGL::aiMultiTexCoord4sARB;
    result["glMultiTexCoord4svARB"]    = Interception::Hooks::OpenGL::aiMultiTexCoord4svARB;

    /* GL_ARB_vertex_array_object */
    result["glBindVertexArrayARB"]    = Interception::Hooks::OpenGL::aiBindVertexArrayARB;
    result["glDeleteVertexArraysARB"] = Interception::Hooks::OpenGL::aiDeleteVertexArraysARB;
    result["glGenVertexArraysARB"]    = Interception::Hooks::OpenGL::aiGenVertexArraysARB;
    result["glIsVertexArrayARB"]      = Interception::Hooks::OpenGL::aiIsVertexArrayARB;

    /* GL_ARB_window_pos */
    result["glWindowPos2dARB"]  = Interception::Hooks::OpenGL::aiWindowPos2dARB;
    result["glWindowPos2dvARB"] = Interception::Hooks::OpenGL::aiWindowPos2dvARB;
    result["glWindowPos2fARB"]  = Interception::Hooks::OpenGL::aiWindowPos2fARB;
    result["glWindowPos2fvARB"] = Interception::Hooks::OpenGL::aiWindowPos2fvARB;
    result["glWindowPos2iARB"]  = Interception::Hooks::OpenGL::aiWindowPos2iARB;
    result["glWindowPos2ivARB"] = Interception::Hooks::OpenGL::aiWindowPos2ivARB;
    result["glWindowPos2sARB"]  = Interception::Hooks::OpenGL::aiWindowPos2sARB;
    result["glWindowPos2svARB"] = Interception::Hooks::OpenGL::aiWindowPos2svARB;
    result["glWindowPos3dARB"]  = Interception::Hooks::OpenGL::aiWindowPos3dARB;
    result["glWindowPos3dvARB"] = Interception::Hooks::OpenGL::aiWindowPos3dvARB;
    result["glWindowPos3fARB"]  = Interception::Hooks::OpenGL::aiWindowPos3fARB;
    result["glWindowPos3fvARB"] = Interception::Hooks::OpenGL::aiWindowPos3fvARB;
    result["glWindowPos3iARB"]  = Interception::Hooks::OpenGL::aiWindowPos3iARB;
    result["glWindowPos3ivARB"] = Interception::Hooks::OpenGL::aiWindowPos3ivARB;
    result["glWindowPos3sARB"]  = Interception::Hooks::OpenGL::aiWindowPos3sARB;
    result["glWindowPos3svARB"] = Interception::Hooks::OpenGL::aiWindowPos3svARB;

    /* GL_EXT_blend_func_separate */
    result["glBlendFuncSeparateEXT"] = Interception::Hooks::OpenGL::aiBlendFuncSeparateEXT;

    /* GL_EXT_draw_buffers2 */
    result["glColorMaskIndexedEXT"] = Interception::Hooks::OpenGL::aiColorMaskiEXT;
    result["glColorMaskiEXT"]       = Interception::Hooks::OpenGL::aiColorMaskiEXT;
    result["glDisableiEXT"]      = Interception::Hooks::OpenGL::aiDisableiEXT;
    result["glEnableiEXT"]       = Interception::Hooks::OpenGL::aiEnableiEXT;
    result["glGetBooleani_vEXT"] = Interception::Hooks::OpenGL::aiGetBooleani_vEXT;
    result["glGetIntegeri_vEXT"] = Interception::Hooks::OpenGL::aiGetIntegeri_vEXT;
    result["glIsEnablediEXT"]    = Interception::Hooks::OpenGL::aiIsEnablediEXT;

    /* GL_EXT_fog_coord */
    result["glFogCoorddEXT"]       = Interception::Hooks::OpenGL::aiFogCoorddEXT;
    result["glFogCoorddvEXT"]      = Interception::Hooks::OpenGL::aiFogCoorddvEXT;
    result["glFogCoordfEXT"]       = Interception::Hooks::OpenGL::aiFogCoordfEXT;
    result["glFogCoordfvEXT"]      = Interception::Hooks::OpenGL::aiFogCoordfvEXT;
    result["glFogCoordPointerEXT"] = Interception::Hooks::OpenGL::aiFogCoordPointerEXT;

    /* GL_EXT_multi_draw_arrays */
    result["glMultiDrawArraysEXT"]   = Interception::Hooks::OpenGL::aiMultiDrawArraysEXT;
    result["glMultiDrawElementsEXT"] = Interception::Hooks::OpenGL::aiMultiDrawElementsEXT;

    /* GL_EXT_secondary_color */
    result["glSecondaryColor3bEXT"]       = Interception::Hooks::OpenGL::aiSecondaryColor3bEXT;
    result["glSecondaryColor3bvEXT"]      = Interception::Hooks::OpenGL::aiSecondaryColor3bvEXT;
    result["glSecondaryColor3dEXT"]       = Interception::Hooks::OpenGL::aiSecondaryColor3dEXT;
    result["glSecondaryColor3dvEXT"]      = Interception::Hooks::OpenGL::aiSecondaryColor3dvEXT;
    result["glSecondaryColor3fEXT"]       = Interception::Hooks::OpenGL::aiSecondaryColor3fEXT;
    result["glSecondaryColor3fvEXT"]      = Interception::Hooks::OpenGL::aiSecondaryColor3fvEXT;
    result["glSecondaryColor3iEXT"]       = Interception::Hooks::OpenGL::aiSecondaryColor3iEXT;
    result["glSecondaryColor3ivEXT"]      = Interception::Hooks::OpenGL::aiSecondaryColor3ivEXT;
    result["glSecondaryColor3sEXT"]       = Interception::Hooks::OpenGL::aiSecondaryColor3sEXT;
    result["glSecondaryColor3svEXT"]      = Interception::Hooks::OpenGL::aiSecondaryColor3svEXT;
    result["glSecondaryColor3ubEXT"]      = Interception::Hooks::OpenGL::aiSecondaryColor3ubEXT;
    result["glSecondaryColor3ubvEXT"]     = Interception::Hooks::OpenGL::aiSecondaryColor3ubvEXT;
    result["glSecondaryColor3uiEXT"]      = Interception::Hooks::OpenGL::aiSecondaryColor3uiEXT;
    result["glSecondaryColor3uivEXT"]     = Interception::Hooks::OpenGL::aiSecondaryColor3uivEXT;
    result["glSecondaryColor3usEXT"]      = Interception::Hooks::OpenGL::aiSecondaryColor3usEXT;
    result["glSecondaryColor3usvEXT"]     = Interception::Hooks::OpenGL::aiSecondaryColor3usvEXT;
    result["glSecondaryColorPointerEXT"]  = Interception::Hooks::OpenGL::aiSecondaryColorPointerEXT;

    /* GL_EXT_transform_feedback */
    result["glBeginTransformFeedbackEXT"]      = Interception::Hooks::OpenGL::aiBeginTransformFeedbackEXT;
    result["glBindBufferBaseEXT"]              = Interception::Hooks::OpenGL::aiBindBufferBaseEXT;
    result["glBindBufferRangeEXT"]             = Interception::Hooks::OpenGL::aiBindBufferRangeEXT;
    result["glEndTransformFeedbackEXT"]        = Interception::Hooks::OpenGL::aiEndTransformFeedbackEXT;
    result["glGetTransformFeedbackVaryingEXT"] = Interception::Hooks::OpenGL::aiGetTransformFeedbackVaryingEXT;
    result["glTransformFeedbackVaryingsEXT"]   = Interception::Hooks::OpenGL::aiTransformFeedbackVaryingsEXT;

    /* GL_NV_conditional_render */
    result["glBeginConditionalRenderNV"] = Interception::Hooks::OpenGL::aiBeginConditionalRenderNV;
    result["glEndConditionalRenderNV"]   = Interception::Hooks::OpenGL::aiEndConditionalRenderNV;

    /* GL_NV_primitive_restart */
    result["glPrimitiveRestartIndexNV"] = Interception::Hooks::OpenGL::aiPrimitiveRestartIndexNV;

    /* Compatibility profile (<= GL 1.1) */
    result["glAccum"]               = Interception::Hooks::OpenGL::aiAccum;
    result["glAlphaFunc"]           = Interception::Hooks::OpenGL::aiAlphaFunc;
    result["glAreTexturesResident"] = Interception::Hooks::OpenGL::aiAreTexturesResident;
    result["glArrayElement"]        = Interception::Hooks::OpenGL::aiArrayElement;
    result["glBegin"]               = Interception::Hooks::OpenGL::aiBegin;
    result["glBitmap"]              = Interception::Hooks::OpenGL::aiBitmap;
    result["glCallList"]            = Interception::Hooks::OpenGL::aiCallList;
    result["glCallLists"]           = Interception::Hooks::OpenGL::aiCallLists;
    result["glClearAccum"]          = Interception::Hooks::OpenGL::aiClearAccum;
    result["glClearIndex"]          = Interception::Hooks::OpenGL::aiClearIndex;
    result["glClipPlane"]           = Interception::Hooks::OpenGL::aiClipPlane;
    result["glColor3b"]             = Interception::Hooks::OpenGL::aiColor3b;
    result["glColor3bv"]            = Interception::Hooks::OpenGL::aiColor3bv;
    result["glColor3d"]             = Interception::Hooks::OpenGL::aiColor3d;
    result["glColor3dv"]            = Interception::Hooks::OpenGL::aiColor3dv;
    result["glColor3f"]             = Interception::Hooks::OpenGL::aiColor3f;
    result["glColor3fv"]            = Interception::Hooks::OpenGL::aiColor3fv;
    result["glColor3i"]             = Interception::Hooks::OpenGL::aiColor3i;
    result["glColor3iv"]            = Interception::Hooks::OpenGL::aiColor3iv;
    result["glColor3s"]             = Interception::Hooks::OpenGL::aiColor3s;
    result["glColor3sv"]            = Interception::Hooks::OpenGL::aiColor3sv;
    result["glColor3ub"]            = Interception::Hooks::OpenGL::aiColor3ub;
    result["glColor3ubv"]           = Interception::Hooks::OpenGL::aiColor3ubv;
    result["glColor3ui"]            = Interception::Hooks::OpenGL::aiColor3ui;
    result["glColor3uiv"]           = Interception::Hooks::OpenGL::aiColor3uiv;
    result["glColor3us"]            = Interception::Hooks::OpenGL::aiColor3us;
    result["glColor3usv"]           = Interception::Hooks::OpenGL::aiColor3usv;
    result["glColor4b"]             = Interception::Hooks::OpenGL::aiColor4b;
    result["glColor4bv"]            = Interception::Hooks::OpenGL::aiColor4bv;
    result["glColor4d"]             = Interception::Hooks::OpenGL::aiColor4d;
    result["glColor4dv"]            = Interception::Hooks::OpenGL::aiColor4dv;
    result["glColor4f"]             = Interception::Hooks::OpenGL::aiColor4f;
    result["glColor4fv"]            = Interception::Hooks::OpenGL::aiColor4fv;
    result["glColor4i"]             = Interception::Hooks::OpenGL::aiColor4i;
    result["glColor4iv"]            = Interception::Hooks::OpenGL::aiColor4iv;
    result["glColor4s"]             = Interception::Hooks::OpenGL::aiColor4s;
    result["glColor4sv"]            = Interception::Hooks::OpenGL::aiColor4sv;
    result["glColor4ub"]            = Interception::Hooks::OpenGL::aiColor4ub;
    result["glColor4ubv"]           = Interception::Hooks::OpenGL::aiColor4ubv;
    result["glColor4ui"]            = Interception::Hooks::OpenGL::aiColor4ui;
    result["glColor4uiv"]           = Interception::Hooks::OpenGL::aiColor4uiv;
    result["glColor4us"]            = Interception::Hooks::OpenGL::aiColor4us;
    result["glColor4usv"]           = Interception::Hooks::OpenGL::aiColor4usv;
    result["glColorMaterial"]       = Interception::Hooks::OpenGL::aiColorMaterial;
    result["glColorPointer"]        = Interception::Hooks::OpenGL::aiColorPointer;
    result["glCopyPixels"]          = Interception::Hooks::OpenGL::aiCopyPixels;
    result["glDeleteLists"]         = Interception::Hooks::OpenGL::aiDeleteLists;
    result["glDisableClientState"]  = Interception::Hooks::OpenGL::aiDisableClientState;
    result["glDrawPixels"]          = Interception::Hooks::OpenGL::aiDrawPixels;
    result["glEdgeFlag"]            = Interception::Hooks::OpenGL::aiEdgeFlag;
    result["glEdgeFlagv"]           = Interception::Hooks::OpenGL::aiEdgeFlagv;
    result["glEdgeFlagPointer"]     = Interception::Hooks::OpenGL::aiEdgeFlagPointer;
    result["glEnableClientState"]   = Interception::Hooks::OpenGL::aiEnableClientState;
    result["glEndList"]             = Interception::Hooks::OpenGL::aiEndList;
    result["glEvalCoord1d"]         = Interception::Hooks::OpenGL::aiEvalCoord1d;
    result["glEvalCoord1dv"]        = Interception::Hooks::OpenGL::aiEvalCoord1dv;
    result["glEvalCoord1f"]         = Interception::Hooks::OpenGL::aiEvalCoord1f;
    result["glEvalCoord1fv"]        = Interception::Hooks::OpenGL::aiEvalCoord1fv;
    result["glEvalCoord2d"]         = Interception::Hooks::OpenGL::aiEvalCoord2d;
    result["glEvalCoord2dv"]        = Interception::Hooks::OpenGL::aiEvalCoord2dv;
    result["glEvalCoord2f"]         = Interception::Hooks::OpenGL::aiEvalCoord2f;
    result["glEvalCoord2fv"]        = Interception::Hooks::OpenGL::aiEvalCoord2fv;
    result["glEvalMesh1"]           = Interception::Hooks::OpenGL::aiEvalMesh1;
    result["glEvalMesh2"]           = Interception::Hooks::OpenGL::aiEvalMesh2;
    result["glEvalPoint1"]          = Interception::Hooks::OpenGL::aiEvalPoint1;
    result["glEvalPoint2"]          = Interception::Hooks::OpenGL::aiEvalPoint2;
    result["glFeedbackBuffer"]      = Interception::Hooks::OpenGL::aiFeedbackBuffer;
    result["glFogf"]                = Interception::Hooks::OpenGL::aiFogf;
    result["glFogfv"]               = Interception::Hooks::OpenGL::aiFogfv;
    result["glFogi"]                = Interception::Hooks::OpenGL::aiFogi;
    result["glFogiv"]               = Interception::Hooks::OpenGL::aiFogiv;
    result["glFrustum"]             = Interception::Hooks::OpenGL::aiFrustum;
    result["glGenLists"]            = Interception::Hooks::OpenGL::aiGenLists;
    result["glGetClipPlane"]        = Interception::Hooks::OpenGL::aiGetClipPlane;
    result["glGetLightfv"]          = Interception::Hooks::OpenGL::aiGetLightfv;
    result["glGetLightiv"]          = Interception::Hooks::OpenGL::aiGetLightiv;
    result["glGetMapdv"]            = Interception::Hooks::OpenGL::aiGetMapdv;
    result["glGetMapfv"]            = Interception::Hooks::OpenGL::aiGetMapfv;
    result["glGetMapiv"]            = Interception::Hooks::OpenGL::aiGetMapiv;
    result["glGetMaterialfv"]       = Interception::Hooks::OpenGL::aiGetMaterialfv;
    result["glGetMaterialiv"]       = Interception::Hooks::OpenGL::aiGetMaterialiv;
    result["glGetPixelMapfv"]       = Interception::Hooks::OpenGL::aiGetPixelMapfv;
    result["glGetPixelMapuiv"]      = Interception::Hooks::OpenGL::aiGetPixelMapuiv;
    result["glGetPixelMapusv"]      = Interception::Hooks::OpenGL::aiGetPixelMapusv;
    result["glGetPointerv"]         = Interception::Hooks::OpenGL::aiGetPointerv;
    result["glGetPolygonStipple"]   = Interception::Hooks::OpenGL::aiGetPolygonStipple;
    result["glGetTexEnvfv"]         = Interception::Hooks::OpenGL::aiGetTexEnvfv;
    result["glGetTexEnviv"]         = Interception::Hooks::OpenGL::aiGetTexEnviv;
    result["glGetTexGendv"]         = Interception::Hooks::OpenGL::aiGetTexGendv;
    result["glGetTexGeniv"]         = Interception::Hooks::OpenGL::aiGetTexGeniv;
    result["glIndexd"]              = Interception::Hooks::OpenGL::aiIndexd;
    result["glIndexdv"]             = Interception::Hooks::OpenGL::aiIndexdv;
    result["glIndexf"]              = Interception::Hooks::OpenGL::aiIndexf;
    result["glIndexfv"]             = Interception::Hooks::OpenGL::aiIndexfv;
    result["glIndexi"]              = Interception::Hooks::OpenGL::aiIndexi;
    result["glIndexiv"]             = Interception::Hooks::OpenGL::aiIndexiv;
    result["glIndexMask"]           = Interception::Hooks::OpenGL::aiIndexMask;
    result["glIndexPointer"]        = Interception::Hooks::OpenGL::aiIndexPointer;
    result["glIndexs"]              = Interception::Hooks::OpenGL::aiIndexs;
    result["glIndexsv"]             = Interception::Hooks::OpenGL::aiIndexsv;
    result["glIndexub"]             = Interception::Hooks::OpenGL::aiIndexub;
    result["glIndexubv"]            = Interception::Hooks::OpenGL::aiIndexubv;
    result["glInitNames"]           = Interception::Hooks::OpenGL::aiInitNames;
    result["glInterleavedArrays"]   = Interception::Hooks::OpenGL::aiInterleavedArrays;
    result["glIsList"]              = Interception::Hooks::OpenGL::aiIsList;
    result["glLightf"]              = Interception::Hooks::OpenGL::aiLightf;
    result["glLightfv"]             = Interception::Hooks::OpenGL::aiLightfv;
    result["glLighti"]              = Interception::Hooks::OpenGL::aiLighti;
    result["glLightiv"]             = Interception::Hooks::OpenGL::aiLightiv;
    result["glLightModelf"]         = Interception::Hooks::OpenGL::aiLightModelf;
    result["glLightModelfv"]        = Interception::Hooks::OpenGL::aiLightModelfv;
    result["glLightModeli"]         = Interception::Hooks::OpenGL::aiLightModeli;
    result["glLightModeliv"]        = Interception::Hooks::OpenGL::aiLightModeliv;
    result["glLineStipple"]         = Interception::Hooks::OpenGL::aiLineStipple;
    result["glListBase"]            = Interception::Hooks::OpenGL::aiListBase;
    result["glLoadIdentity"]        = Interception::Hooks::OpenGL::aiLoadIdentity;
    result["glLoadMatrixd"]         = Interception::Hooks::OpenGL::aiLoadMatrixd;
    result["glLoadMatrixf"]         = Interception::Hooks::OpenGL::aiLoadMatrixf;
    result["glLoadName"]            = Interception::Hooks::OpenGL::aiLoadName;
    result["glMap1d"]               = Interception::Hooks::OpenGL::aiMap1d;
    result["glMap1f"]               = Interception::Hooks::OpenGL::aiMap1f;
    result["glMap2d"]               = Interception::Hooks::OpenGL::aiMap2d;
    result["glMap2f"]               = Interception::Hooks::OpenGL::aiMap2f;
    result["glMapGrid1d"]           = Interception::Hooks::OpenGL::aiMapGrid1d;
    result["glMapGrid1f"]           = Interception::Hooks::OpenGL::aiMapGrid1f;
    result["glMapGrid2d"]           = Interception::Hooks::OpenGL::aiMapGrid2d;
    result["glMapGrid2f"]           = Interception::Hooks::OpenGL::aiMapGrid2f;
    result["glMaterialf"]           = Interception::Hooks::OpenGL::aiMaterialf;
    result["glMaterialfv"]          = Interception::Hooks::OpenGL::aiMaterialfv;
    result["glMateriali"]           = Interception::Hooks::OpenGL::aiMateriali;
    result["glMaterialiv"]          = Interception::Hooks::OpenGL::aiMaterialiv;
    result["glMatrixMode"]          = Interception::Hooks::OpenGL::aiMatrixMode;
    result["glMultMatrixd"]         = Interception::Hooks::OpenGL::aiMultMatrixd;
    result["glMultMatrixf"]         = Interception::Hooks::OpenGL::aiMultMatrixf;
    result["glNewList"]             = Interception::Hooks::OpenGL::aiNewList;
    result["glNormal3b"]            = Interception::Hooks::OpenGL::aiNormal3b;
    result["glNormal3bv"]           = Interception::Hooks::OpenGL::aiNormal3bv;
    result["glNormal3d"]            = Interception::Hooks::OpenGL::aiNormal3d;
    result["glNormal3dv"]           = Interception::Hooks::OpenGL::aiNormal3dv;
    result["glNormal3f"]            = Interception::Hooks::OpenGL::aiNormal3f;
    result["glNormal3fv"]           = Interception::Hooks::OpenGL::aiNormal3fv;
    result["glNormal3i"]            = Interception::Hooks::OpenGL::aiNormal3i;
    result["glNormal3iv"]           = Interception::Hooks::OpenGL::aiNormal3iv;
    result["glNormal3s"]            = Interception::Hooks::OpenGL::aiNormal3s;
    result["glNormal3sv"]           = Interception::Hooks::OpenGL::aiNormal3sv;
    result["glNormalPointer"]       = Interception::Hooks::OpenGL::aiNormalPointer;
    result["glOrtho"]               = Interception::Hooks::OpenGL::aiOrtho;
    result["glPassthrough"]         = Interception::Hooks::OpenGL::aiPassthrough;
    result["glPixelMapfv"]          = Interception::Hooks::OpenGL::aiPixelMapfv;
    result["glPixelMapuiv"]         = Interception::Hooks::OpenGL::aiPixelMapuiv;
    result["glPixelMapusv"]         = Interception::Hooks::OpenGL::aiPixelMapusv;
    result["glPixelStoref"]         = Interception::Hooks::OpenGL::aiPixelStoref;
    result["glPixelStorei"]         = Interception::Hooks::OpenGL::aiPixelStorei;
    result["glPixelTransferf"]      = Interception::Hooks::OpenGL::aiPixelTransferf;
    result["glPixelTransferi"]      = Interception::Hooks::OpenGL::aiPixelTransferi;
    result["glPixelZoom"]           = Interception::Hooks::OpenGL::aiPixelZoom;
    result["glPolygonStipple"]      = Interception::Hooks::OpenGL::aiPolygonStipple;
    result["glPopAttrib"]           = Interception::Hooks::OpenGL::aiPopAttrib;
    result["glPopClientAttrib"]     = Interception::Hooks::OpenGL::aiPopClientAttrib;
    result["glPopMatrix"]           = Interception::Hooks::OpenGL::aiPopMatrix;
    result["glPopName"]             = Interception::Hooks::OpenGL::aiPopName;
    result["glPrioritizeTextures"]  = Interception::Hooks::OpenGL::aiPrioritizeTextures;
    result["glPushAttrib"]          = Interception::Hooks::OpenGL::aiPushAttrib;
    result["glPushClientAttrib"]    = Interception::Hooks::OpenGL::aiPushClientAttrib;
    result["glPushMatrix"]          = Interception::Hooks::OpenGL::aiPushMatrix;
    result["glPushName"]            = Interception::Hooks::OpenGL::aiPushName;
    result["glRasterPos2d"]         = Interception::Hooks::OpenGL::aiRasterPos2d;
    result["glRasterPos2dv"]        = Interception::Hooks::OpenGL::aiRasterPos2dv;
    result["glRasterPos2f"]         = Interception::Hooks::OpenGL::aiRasterPos2f;
    result["glRasterPos2fv"]        = Interception::Hooks::OpenGL::aiRasterPos2fv;
    result["glRasterPos2i"]         = Interception::Hooks::OpenGL::aiRasterPos2i;
    result["glRasterPos2iv"]        = Interception::Hooks::OpenGL::aiRasterPos2iv;
    result["glRasterPos2s"]         = Interception::Hooks::OpenGL::aiRasterPos2s;
    result["glRasterPos2sv"]        = Interception::Hooks::OpenGL::aiRasterPos2sv;
    result["glRasterPos3d"]         = Interception::Hooks::OpenGL::aiRasterPos3d;
    result["glRasterPos3dv"]        = Interception::Hooks::OpenGL::aiRasterPos3dv;
    result["glRasterPos3f"]         = Interception::Hooks::OpenGL::aiRasterPos3f;
    result["glRasterPos3fv"]        = Interception::Hooks::OpenGL::aiRasterPos3fv;
    result["glRasterPos3i"]         = Interception::Hooks::OpenGL::aiRasterPos3i;
    result["glRasterPos3iv"]        = Interception::Hooks::OpenGL::aiRasterPos3iv;
    result["glRasterPos3s"]         = Interception::Hooks::OpenGL::aiRasterPos3s;
    result["glRasterPos3sv"]        = Interception::Hooks::OpenGL::aiRasterPos3sv;
    result["glRasterPos4d"]         = Interception::Hooks::OpenGL::aiRasterPos4d;
    result["glRasterPos4dv"]        = Interception::Hooks::OpenGL::aiRasterPos4dv;
    result["glRasterPos4f"]         = Interception::Hooks::OpenGL::aiRasterPos4f;
    result["glRasterPos4fv"]        = Interception::Hooks::OpenGL::aiRasterPos4fv;
    result["glRasterPos4i"]         = Interception::Hooks::OpenGL::aiRasterPos4i;
    result["glRasterPos4iv"]        = Interception::Hooks::OpenGL::aiRasterPos4iv;
    result["glRasterPos4s"]         = Interception::Hooks::OpenGL::aiRasterPos4s;
    result["glRasterPos4sv"]        = Interception::Hooks::OpenGL::aiRasterPos4sv;
    result["glRectd"]               = Interception::Hooks::OpenGL::aiRectd;
    result["glRectdv"]              = Interception::Hooks::OpenGL::aiRectdv;
    result["glRectf"]               = Interception::Hooks::OpenGL::aiRectf;
    result["glRectfv"]              = Interception::Hooks::OpenGL::aiRectfv;
    result["glRecti"]               = Interception::Hooks::OpenGL::aiRecti;
    result["glRectiv"]              = Interception::Hooks::OpenGL::aiRectiv;
    result["glRects"]               = Interception::Hooks::OpenGL::aiRects;
    result["glRectsv"]              = Interception::Hooks::OpenGL::aiRectsv;
    result["glRenderMode"]          = Interception::Hooks::OpenGL::aiRenderMode;
    result["glRotated"]             = Interception::Hooks::OpenGL::aiRotated;
    result["glRotatef"]             = Interception::Hooks::OpenGL::aiRotatef;
    result["glScaled"]              = Interception::Hooks::OpenGL::aiScaled;
    result["glScalef"]              = Interception::Hooks::OpenGL::aiScalef;
    result["glSelectBuffer"]        = Interception::Hooks::OpenGL::aiSelectBuffer;
    result["glShadeModel"]          = Interception::Hooks::OpenGL::aiShadeModel;
    result["glTexCoord1d"]          = Interception::Hooks::OpenGL::aiTexCoord1d;
    result["glTexCoord1dv"]         = Interception::Hooks::OpenGL::aiTexCoord1dv;
    result["glTexCoord1f"]          = Interception::Hooks::OpenGL::aiTexCoord1f;
    result["glTexCoord1fv"]         = Interception::Hooks::OpenGL::aiTexCoord1fv;
    result["glTexCoord1i"]          = Interception::Hooks::OpenGL::aiTexCoord1i;
    result["glTexCoord1iv"]         = Interception::Hooks::OpenGL::aiTexCoord1iv;
    result["glTexCoord1s"]          = Interception::Hooks::OpenGL::aiTexCoord1s;
    result["glTexCoord1sv"]         = Interception::Hooks::OpenGL::aiTexCoord1sv;
    result["glTexCoord2d"]          = Interception::Hooks::OpenGL::aiTexCoord2d;
    result["glTexCoord2dv"]         = Interception::Hooks::OpenGL::aiTexCoord2dv;
    result["glTexCoord2f"]          = Interception::Hooks::OpenGL::aiTexCoord2f;
    result["glTexCoord2fv"]         = Interception::Hooks::OpenGL::aiTexCoord2fv;
    result["glTexCoord2i"]          = Interception::Hooks::OpenGL::aiTexCoord2i;
    result["glTexCoord2iv"]         = Interception::Hooks::OpenGL::aiTexCoord2iv;
    result["glTexCoord2s"]          = Interception::Hooks::OpenGL::aiTexCoord2s;
    result["glTexCoord2sv"]         = Interception::Hooks::OpenGL::aiTexCoord2sv;
    result["glTexCoord3d"]          = Interception::Hooks::OpenGL::aiTexCoord3d;
    result["glTexCoord3dv"]         = Interception::Hooks::OpenGL::aiTexCoord3dv;
    result["glTexCoord3f"]          = Interception::Hooks::OpenGL::aiTexCoord3f;
    result["glTexCoord3fv"]         = Interception::Hooks::OpenGL::aiTexCoord3fv;
    result["glTexCoord3i"]          = Interception::Hooks::OpenGL::aiTexCoord3i;
    result["glTexCoord3iv"]         = Interception::Hooks::OpenGL::aiTexCoord3iv;
    result["glTexCoord3s"]          = Interception::Hooks::OpenGL::aiTexCoord3s;
    result["glTexCoord3sv"]         = Interception::Hooks::OpenGL::aiTexCoord3sv;
    result["glTexCoord4d"]          = Interception::Hooks::OpenGL::aiTexCoord4d;
    result["glTexCoord4dv"]         = Interception::Hooks::OpenGL::aiTexCoord4dv;
    result["glTexCoord4f"]          = Interception::Hooks::OpenGL::aiTexCoord4f;
    result["glTexCoord4fv"]         = Interception::Hooks::OpenGL::aiTexCoord4fv;
    result["glTexCoord4i"]          = Interception::Hooks::OpenGL::aiTexCoord4i;
    result["glTexCoord4iv"]         = Interception::Hooks::OpenGL::aiTexCoord4iv;
    result["glTexCoord4s"]          = Interception::Hooks::OpenGL::aiTexCoord4s;
    result["glTexCoord4sv"]         = Interception::Hooks::OpenGL::aiTexCoord4sv;
    result["glTexCoordPointer"]     = Interception::Hooks::OpenGL::aiTexCoordPointer;
    result["glTexEnvf"]             = Interception::Hooks::OpenGL::aiTexEnvf;
    result["glTexEnvfv"]            = Interception::Hooks::OpenGL::aiTexEnvfv;
    result["glTexEnvi"]             = Interception::Hooks::OpenGL::aiTexEnvi;
    result["glTexEnviv"]            = Interception::Hooks::OpenGL::aiTexEnviv;
    result["glTexGend"]             = Interception::Hooks::OpenGL::aiTexGend;
    result["glTexGendv"]            = Interception::Hooks::OpenGL::aiTexGendv;
    result["glTexGeni"]             = Interception::Hooks::OpenGL::aiTexGeni;
    result["glTexGeniv"]            = Interception::Hooks::OpenGL::aiTexGeniv;
    result["glTranslated"]          = Interception::Hooks::OpenGL::aiTranslated;
    result["glTranslatef"]          = Interception::Hooks::OpenGL::aiTranslatef;
    result["glVertex2d"]            = Interception::Hooks::OpenGL::aiVertex2d;
    result["glVertex2dv"]           = Interception::Hooks::OpenGL::aiVertex2dv;
    result["glVertex2f"]            = Interception::Hooks::OpenGL::aiVertex2f;
    result["glVertex2fv"]           = Interception::Hooks::OpenGL::aiVertex2fv;
    result["glVertex2i"]            = Interception::Hooks::OpenGL::aiVertex2i;
    result["glVertex2iv"]           = Interception::Hooks::OpenGL::aiVertex2iv;
    result["glVertex2s"]            = Interception::Hooks::OpenGL::aiVertex2s;
    result["glVertex2sv"]           = Interception::Hooks::OpenGL::aiVertex2sv;
    result["glVertex3d"]            = Interception::Hooks::OpenGL::aiVertex3d;
    result["glVertex3dv"]           = Interception::Hooks::OpenGL::aiVertex3dv;
    result["glVertex3f"]            = Interception::Hooks::OpenGL::aiVertex3f;
    result["glVertex3fv"]           = Interception::Hooks::OpenGL::aiVertex3fv;
    result["glVertex3i"]            = Interception::Hooks::OpenGL::aiVertex3i;
    result["glVertex3iv"]           = Interception::Hooks::OpenGL::aiVertex3iv;
    result["glVertex3s"]            = Interception::Hooks::OpenGL::aiVertex3s;
    result["glVertex3sv"]           = Interception::Hooks::OpenGL::aiVertex3sv;
    result["glVertex4d"]            = Interception::Hooks::OpenGL::aiVertex4d;
    result["glVertex4dv"]           = Interception::Hooks::OpenGL::aiVertex4dv;
    result["glVertex4f"]            = Interception::Hooks::OpenGL::aiVertex4f;
    result["glVertex4fv"]           = Interception::Hooks::OpenGL::aiVertex4fv;
    result["glVertex4i"]            = Interception::Hooks::OpenGL::aiVertex4i;
    result["glVertex4iv"]           = Interception::Hooks::OpenGL::aiVertex4iv;
    result["glVertex4s"]            = Interception::Hooks::OpenGL::aiVertex4s;
    result["glVertex4sv"]           = Interception::Hooks::OpenGL::aiVertex4sv;
    result["glVertexPointer"]       = Interception::Hooks::OpenGL::aiVertexPointer;

    return result;
}

std::vector<APIInterceptor::FunctionInterceptor> Interception::Hooks::OpenGL::get_function_interceptors()
{
    /* NOTE: If you add any new entrypoints to this function, make sure to also update Interception::Hooks::OpenGL::Context::init_dispatch_table() */

    /* <= GL 1.1 */
    return std::vector<APIInterceptor::FunctionInterceptor>
    {
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_bind_texture,              Interception::Hooks::OpenGL::aiBindTexture),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_blend_func,                Interception::Hooks::OpenGL::aiBlendFunc),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_clear,                     Interception::Hooks::OpenGL::aiClear),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_clear_color,               Interception::Hooks::OpenGL::aiClearColor),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_clear_depth,               Interception::Hooks::OpenGL::aiClearDepth),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_clear_stencil,             Interception::Hooks::OpenGL::aiClearStencil),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_mask,                Interception::Hooks::OpenGL::aiColorMask),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_copy_tex_image_1d,         Interception::Hooks::OpenGL::aiCopyTexImage1D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_copy_tex_image_2d,         Interception::Hooks::OpenGL::aiCopyTexImage2D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_copy_tex_sub_image_1d,     Interception::Hooks::OpenGL::aiCopyTexSubImage1D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_copy_tex_sub_image_2d,     Interception::Hooks::OpenGL::aiCopyTexSubImage2D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_cull_face,                 Interception::Hooks::OpenGL::aiCullFace),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_delete_textures,           Interception::Hooks::OpenGL::aiDeleteTextures),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_depth_func,                Interception::Hooks::OpenGL::aiDepthFunc),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_depth_mask,                Interception::Hooks::OpenGL::aiDepthMask),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_depth_range,               Interception::Hooks::OpenGL::aiDepthRange),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_disable,                   Interception::Hooks::OpenGL::aiDisable),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_draw_arrays,               Interception::Hooks::OpenGL::aiDrawArrays),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_draw_buffer,               Interception::Hooks::OpenGL::aiDrawBuffer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_draw_elements,             Interception::Hooks::OpenGL::aiDrawElements),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_enable,                    Interception::Hooks::OpenGL::aiEnable),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_finish,                    Interception::Hooks::OpenGL::aiFinish),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_flush,                     Interception::Hooks::OpenGL::aiFlush),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_front_face,                Interception::Hooks::OpenGL::aiFrontFace),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_gen_textures,              Interception::Hooks::OpenGL::aiGenTextures),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_booleanv,              Interception::Hooks::OpenGL::aiGetBooleanv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_doublev,               Interception::Hooks::OpenGL::aiGetDoublev),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_error,                 Interception::Hooks::OpenGL::aiGetError),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_floatv,                Interception::Hooks::OpenGL::aiGetFloatv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_integerv,              Interception::Hooks::OpenGL::aiGetIntegerv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_string,                Interception::Hooks::OpenGL::aiGetString),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_tex_image,             Interception::Hooks::OpenGL::aiGetTexImage),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_tex_level_parameterfv, Interception::Hooks::OpenGL::aiGetTexLevelParameterfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_tex_level_parameteriv, Interception::Hooks::OpenGL::aiGetTexLevelParameteriv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_tex_parameterfv,       Interception::Hooks::OpenGL::aiGetTexParameterfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_tex_parameteriv,       Interception::Hooks::OpenGL::aiGetTexParameteriv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_hint,                      Interception::Hooks::OpenGL::aiHint),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_is_enabled,                Interception::Hooks::OpenGL::aiIsEnabled),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_is_texture,                Interception::Hooks::OpenGL::aiIsTexture),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_line_width,                Interception::Hooks::OpenGL::aiLineWidth),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_logic_op,                  Interception::Hooks::OpenGL::aiLogicOp),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_storef,              Interception::Hooks::OpenGL::aiPixelStoref),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_storei,              Interception::Hooks::OpenGL::aiPixelStorei),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_point_size,                Interception::Hooks::OpenGL::aiPointSize),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_polygon_mode,              Interception::Hooks::OpenGL::aiPolygonMode),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_polygon_offset,            Interception::Hooks::OpenGL::aiPolygonOffset),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_read_buffer,               Interception::Hooks::OpenGL::aiReadBuffer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_read_pixels,               Interception::Hooks::OpenGL::aiReadPixels),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_scissor,                   Interception::Hooks::OpenGL::aiScissor),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_stencil_func,              Interception::Hooks::OpenGL::aiStencilFunc),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_stencil_mask,              Interception::Hooks::OpenGL::aiStencilMask),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_stencil_op,                Interception::Hooks::OpenGL::aiStencilOp),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_image_1D,              Interception::Hooks::OpenGL::aiTexImage1D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_image_2D,              Interception::Hooks::OpenGL::aiTexImage2D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_parameterf,            Interception::Hooks::OpenGL::aiTexParameterf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_parameterfv,           Interception::Hooks::OpenGL::aiTexParameterfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_parameteri,            Interception::Hooks::OpenGL::aiTexParameteri),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_parameteriv,           Interception::Hooks::OpenGL::aiTexParameteriv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_sub_image_1d,          Interception::Hooks::OpenGL::aiTexSubImage1D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_sub_image_2d,          Interception::Hooks::OpenGL::aiTexSubImage2D),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_viewport,                  Interception::Hooks::OpenGL::aiViewport),

        /* Compat profile */
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_accum,                  Interception::Hooks::OpenGL::aiAccum),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_alpha_func,             Interception::Hooks::OpenGL::aiAlphaFunc),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_are_textures_resident,  Interception::Hooks::OpenGL::aiAreTexturesResident),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_array_element,          Interception::Hooks::OpenGL::aiArrayElement),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_begin,                  Interception::Hooks::OpenGL::aiBegin),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_bitmap,                 Interception::Hooks::OpenGL::aiBitmap),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_call_list,              Interception::Hooks::OpenGL::aiCallList),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_call_lists,             Interception::Hooks::OpenGL::aiCallLists),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_clear_accum,            Interception::Hooks::OpenGL::aiClearAccum),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_clear_index,            Interception::Hooks::OpenGL::aiClearIndex),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_clip_plane,             Interception::Hooks::OpenGL::aiClipPlane),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3b,               Interception::Hooks::OpenGL::aiColor3b),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3bv,              Interception::Hooks::OpenGL::aiColor3bv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3d,               Interception::Hooks::OpenGL::aiColor3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3dv,              Interception::Hooks::OpenGL::aiColor3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3f,               Interception::Hooks::OpenGL::aiColor3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3fv,              Interception::Hooks::OpenGL::aiColor3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3i,               Interception::Hooks::OpenGL::aiColor3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3iv,              Interception::Hooks::OpenGL::aiColor3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3s,               Interception::Hooks::OpenGL::aiColor3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3sv,              Interception::Hooks::OpenGL::aiColor3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3ub,              Interception::Hooks::OpenGL::aiColor3ub),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3ubv,             Interception::Hooks::OpenGL::aiColor3ubv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3ui,              Interception::Hooks::OpenGL::aiColor3ui),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3uiv,             Interception::Hooks::OpenGL::aiColor3uiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3us,              Interception::Hooks::OpenGL::aiColor3us),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_3usv,             Interception::Hooks::OpenGL::aiColor3usv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4b,               Interception::Hooks::OpenGL::aiColor4b),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4bv,              Interception::Hooks::OpenGL::aiColor4bv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4d,               Interception::Hooks::OpenGL::aiColor4d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4dv,              Interception::Hooks::OpenGL::aiColor4dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4f,               Interception::Hooks::OpenGL::aiColor4f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4fv,              Interception::Hooks::OpenGL::aiColor4fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4i,               Interception::Hooks::OpenGL::aiColor4i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4iv,              Interception::Hooks::OpenGL::aiColor4iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4s,               Interception::Hooks::OpenGL::aiColor4s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4sv,              Interception::Hooks::OpenGL::aiColor4sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4ub,              Interception::Hooks::OpenGL::aiColor4ub),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4ubv,             Interception::Hooks::OpenGL::aiColor4ubv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4ui,              Interception::Hooks::OpenGL::aiColor4ui),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4uiv,             Interception::Hooks::OpenGL::aiColor4uiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4us,              Interception::Hooks::OpenGL::aiColor4us),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_4usv,             Interception::Hooks::OpenGL::aiColor4usv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_material,         Interception::Hooks::OpenGL::aiColorMaterial),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_color_pointer,          Interception::Hooks::OpenGL::aiColorPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_copy_pixels,            Interception::Hooks::OpenGL::aiCopyPixels),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_delete_lists,           Interception::Hooks::OpenGL::aiDeleteLists),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_disable_client_state,   Interception::Hooks::OpenGL::aiDisableClientState),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_draw_pixels,            Interception::Hooks::OpenGL::aiDrawPixels),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_edge_flag,              Interception::Hooks::OpenGL::aiEdgeFlag),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_edge_flagv,             Interception::Hooks::OpenGL::aiEdgeFlagv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_edge_flag_pointer,      Interception::Hooks::OpenGL::aiEdgeFlagPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_enable_client_state,    Interception::Hooks::OpenGL::aiEnableClientState),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_end,                    Interception::Hooks::OpenGL::aiEnd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_end_list,               Interception::Hooks::OpenGL::aiEndList),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_coord_1d,          Interception::Hooks::OpenGL::aiEvalCoord1d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_coord_1dv,         Interception::Hooks::OpenGL::aiEvalCoord1dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_coord_1f,          Interception::Hooks::OpenGL::aiEvalCoord1f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_coord_1fv,         Interception::Hooks::OpenGL::aiEvalCoord1fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_coord_2d,          Interception::Hooks::OpenGL::aiEvalCoord2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_coord_2dv,         Interception::Hooks::OpenGL::aiEvalCoord2dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_coord_2f,          Interception::Hooks::OpenGL::aiEvalCoord2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_coord_2fv,         Interception::Hooks::OpenGL::aiEvalCoord2fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_mesh1,             Interception::Hooks::OpenGL::aiEvalMesh1),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_mesh2,             Interception::Hooks::OpenGL::aiEvalMesh2),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_point1,            Interception::Hooks::OpenGL::aiEvalPoint1),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_eval_point2,            Interception::Hooks::OpenGL::aiEvalPoint2),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_feedback_buffer,        Interception::Hooks::OpenGL::aiFeedbackBuffer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_fogf,                   Interception::Hooks::OpenGL::aiFogf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_fogfv,                  Interception::Hooks::OpenGL::aiFogfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_fogi,                   Interception::Hooks::OpenGL::aiFogi),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_fogiv,                  Interception::Hooks::OpenGL::aiFogiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_frustum,                Interception::Hooks::OpenGL::aiFrustum),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_gen_lists,              Interception::Hooks::OpenGL::aiGenLists),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_clip_plane,         Interception::Hooks::OpenGL::aiGetClipPlane),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_light_fv,           Interception::Hooks::OpenGL::aiGetLightfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_light_iv,           Interception::Hooks::OpenGL::aiGetLightiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_map_dv,             Interception::Hooks::OpenGL::aiGetMapdv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_map_fv,             Interception::Hooks::OpenGL::aiGetMapfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_map_iv,             Interception::Hooks::OpenGL::aiGetMapiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_material_fv,        Interception::Hooks::OpenGL::aiGetMaterialfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_material_iv,        Interception::Hooks::OpenGL::aiGetMaterialiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_pixel_map_fv,       Interception::Hooks::OpenGL::aiGetPixelMapfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_pixel_map_uiv,      Interception::Hooks::OpenGL::aiGetPixelMapuiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_pixel_map_usv,      Interception::Hooks::OpenGL::aiGetPixelMapusv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_pointerv,           Interception::Hooks::OpenGL::aiGetPointerv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_polygon_stipple,    Interception::Hooks::OpenGL::aiGetPolygonStipple),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_tex_env_fv,         Interception::Hooks::OpenGL::aiGetTexEnvfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_tex_env_iv,         Interception::Hooks::OpenGL::aiGetTexEnviv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_tex_gen_dv,         Interception::Hooks::OpenGL::aiGetTexGendv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_get_tex_gen_iv,         Interception::Hooks::OpenGL::aiGetTexGeniv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_d,                Interception::Hooks::OpenGL::aiIndexd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_dv,               Interception::Hooks::OpenGL::aiIndexdv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_f,                Interception::Hooks::OpenGL::aiIndexf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_fv,               Interception::Hooks::OpenGL::aiIndexfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_i,                Interception::Hooks::OpenGL::aiIndexi),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_iv,               Interception::Hooks::OpenGL::aiIndexiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_mask,             Interception::Hooks::OpenGL::aiIndexMask),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_pointer,          Interception::Hooks::OpenGL::aiIndexPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_s,                Interception::Hooks::OpenGL::aiIndexs),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_sv,               Interception::Hooks::OpenGL::aiIndexsv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_ub,               Interception::Hooks::OpenGL::aiIndexub),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_index_ubv,              Interception::Hooks::OpenGL::aiIndexubv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_init_names,             Interception::Hooks::OpenGL::aiInitNames),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_interleaved_arrays,     Interception::Hooks::OpenGL::aiInterleavedArrays),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_is_list,                Interception::Hooks::OpenGL::aiIsList),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_light_f,                Interception::Hooks::OpenGL::aiLightf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_light_fv,               Interception::Hooks::OpenGL::aiLightfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_light_i,                Interception::Hooks::OpenGL::aiLighti),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_light_iv,               Interception::Hooks::OpenGL::aiLightiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_light_model_f,          Interception::Hooks::OpenGL::aiLightModelf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_light_model_fv,         Interception::Hooks::OpenGL::aiLightModelfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_light_model_i,          Interception::Hooks::OpenGL::aiLightModeli),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_light_model_iv,         Interception::Hooks::OpenGL::aiLightModeliv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_line_stipple,           Interception::Hooks::OpenGL::aiLineStipple),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_list_base,              Interception::Hooks::OpenGL::aiListBase),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_load_identity,          Interception::Hooks::OpenGL::aiLoadIdentity),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_load_matrix_d,          Interception::Hooks::OpenGL::aiLoadMatrixd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_load_matrix_f,          Interception::Hooks::OpenGL::aiLoadMatrixf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_load_name,              Interception::Hooks::OpenGL::aiLoadName),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_map_1d,                 Interception::Hooks::OpenGL::aiMap1d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_map_1f,                 Interception::Hooks::OpenGL::aiMap1f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_map_2d,                 Interception::Hooks::OpenGL::aiMap2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_map_2f,                 Interception::Hooks::OpenGL::aiMap2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_map_grid_1d,            Interception::Hooks::OpenGL::aiMapGrid1d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_map_grid_1f,            Interception::Hooks::OpenGL::aiMapGrid1f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_map_grid_2d,            Interception::Hooks::OpenGL::aiMapGrid2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_map_grid_2f,            Interception::Hooks::OpenGL::aiMapGrid2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_material_f,             Interception::Hooks::OpenGL::aiMaterialf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_material_fv,            Interception::Hooks::OpenGL::aiMaterialfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_material_i,             Interception::Hooks::OpenGL::aiMateriali),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_material_iv,            Interception::Hooks::OpenGL::aiMaterialiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_matrix_mode,            Interception::Hooks::OpenGL::aiMatrixMode),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_mult_matrix_d,          Interception::Hooks::OpenGL::aiMultMatrixd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_mult_matrix_f,          Interception::Hooks::OpenGL::aiMultMatrixf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_new_list,               Interception::Hooks::OpenGL::aiNewList),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3b,              Interception::Hooks::OpenGL::aiNormal3b),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3bv,             Interception::Hooks::OpenGL::aiNormal3bv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3d,              Interception::Hooks::OpenGL::aiNormal3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3dv,             Interception::Hooks::OpenGL::aiNormal3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3f,              Interception::Hooks::OpenGL::aiNormal3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3fv,             Interception::Hooks::OpenGL::aiNormal3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3i,              Interception::Hooks::OpenGL::aiNormal3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3iv,             Interception::Hooks::OpenGL::aiNormal3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3s,              Interception::Hooks::OpenGL::aiNormal3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_3sv,             Interception::Hooks::OpenGL::aiNormal3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_normal_pointer,         Interception::Hooks::OpenGL::aiNormalPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_ortho,                  Interception::Hooks::OpenGL::aiOrtho),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_passthrough,            Interception::Hooks::OpenGL::aiPassthrough),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_map_fv,           Interception::Hooks::OpenGL::aiPixelMapfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_map_uiv,          Interception::Hooks::OpenGL::aiPixelMapuiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_map_usv,          Interception::Hooks::OpenGL::aiPixelMapusv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_store_f,          Interception::Hooks::OpenGL::aiPixelStoref),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_store_i,          Interception::Hooks::OpenGL::aiPixelStorei),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_transfer_f,       Interception::Hooks::OpenGL::aiPixelTransferf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_transfer_i,       Interception::Hooks::OpenGL::aiPixelTransferi),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pixel_zoom,             Interception::Hooks::OpenGL::aiPixelZoom),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_polygon_stipple,        Interception::Hooks::OpenGL::aiPolygonStipple),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pop_attrib,             Interception::Hooks::OpenGL::aiPopAttrib),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pop_client_attrib,      Interception::Hooks::OpenGL::aiPopClientAttrib),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pop_matrix,             Interception::Hooks::OpenGL::aiPopMatrix),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_pop_name,               Interception::Hooks::OpenGL::aiPopName),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_prioritize_textures,    Interception::Hooks::OpenGL::aiPrioritizeTextures),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_push_attrib,            Interception::Hooks::OpenGL::aiPushAttrib),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_push_client_attrib,     Interception::Hooks::OpenGL::aiPushClientAttrib),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_push_matrix,            Interception::Hooks::OpenGL::aiPushMatrix),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_push_name,              Interception::Hooks::OpenGL::aiPushName),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_2d,          Interception::Hooks::OpenGL::aiRasterPos2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_2dv,         Interception::Hooks::OpenGL::aiRasterPos2dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_2f,          Interception::Hooks::OpenGL::aiRasterPos2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_2fv,         Interception::Hooks::OpenGL::aiRasterPos2fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_2i,          Interception::Hooks::OpenGL::aiRasterPos2i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_2iv,         Interception::Hooks::OpenGL::aiRasterPos2iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_2s,          Interception::Hooks::OpenGL::aiRasterPos2s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_2sv,         Interception::Hooks::OpenGL::aiRasterPos2sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_3d,          Interception::Hooks::OpenGL::aiRasterPos3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_3dv,         Interception::Hooks::OpenGL::aiRasterPos3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_3f,          Interception::Hooks::OpenGL::aiRasterPos3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_3fv,         Interception::Hooks::OpenGL::aiRasterPos3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_3i,          Interception::Hooks::OpenGL::aiRasterPos3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_3iv,         Interception::Hooks::OpenGL::aiRasterPos3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_3s,          Interception::Hooks::OpenGL::aiRasterPos3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_3sv,         Interception::Hooks::OpenGL::aiRasterPos3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_4d,          Interception::Hooks::OpenGL::aiRasterPos4d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_4dv,         Interception::Hooks::OpenGL::aiRasterPos4dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_4f,          Interception::Hooks::OpenGL::aiRasterPos4f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_4fv,         Interception::Hooks::OpenGL::aiRasterPos4fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_4i,          Interception::Hooks::OpenGL::aiRasterPos4i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_4iv,         Interception::Hooks::OpenGL::aiRasterPos4iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_4s,          Interception::Hooks::OpenGL::aiRasterPos4s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_raster_pos_4sv,         Interception::Hooks::OpenGL::aiRasterPos4sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rect_d,                 Interception::Hooks::OpenGL::aiRectd),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rect_dv,                Interception::Hooks::OpenGL::aiRectdv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rect_f,                 Interception::Hooks::OpenGL::aiRectf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rect_fv,                Interception::Hooks::OpenGL::aiRectfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rect_i,                 Interception::Hooks::OpenGL::aiRecti),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rect_iv,                Interception::Hooks::OpenGL::aiRectiv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rect_s,                 Interception::Hooks::OpenGL::aiRects),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rect_sv,                Interception::Hooks::OpenGL::aiRectsv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_render_mode,            Interception::Hooks::OpenGL::aiRenderMode),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rotate_d,               Interception::Hooks::OpenGL::aiRotated),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_rotate_f,               Interception::Hooks::OpenGL::aiRotatef),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_scale_d,                Interception::Hooks::OpenGL::aiScaled),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_scale_f,                Interception::Hooks::OpenGL::aiScalef),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_select_buffer,          Interception::Hooks::OpenGL::aiSelectBuffer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_shade_model,            Interception::Hooks::OpenGL::aiShadeModel),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_1d,           Interception::Hooks::OpenGL::aiTexCoord1d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_1dv,          Interception::Hooks::OpenGL::aiTexCoord1dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_1f,           Interception::Hooks::OpenGL::aiTexCoord1f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_1fv,          Interception::Hooks::OpenGL::aiTexCoord1fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_1i,           Interception::Hooks::OpenGL::aiTexCoord1i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_1iv,          Interception::Hooks::OpenGL::aiTexCoord1iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_1s,           Interception::Hooks::OpenGL::aiTexCoord1s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_1sv,          Interception::Hooks::OpenGL::aiTexCoord1sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_2d,           Interception::Hooks::OpenGL::aiTexCoord2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_2dv,          Interception::Hooks::OpenGL::aiTexCoord2dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_2f,           Interception::Hooks::OpenGL::aiTexCoord2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_2fv,          Interception::Hooks::OpenGL::aiTexCoord2fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_2i,           Interception::Hooks::OpenGL::aiTexCoord2i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_2iv,          Interception::Hooks::OpenGL::aiTexCoord2iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_2s,           Interception::Hooks::OpenGL::aiTexCoord2s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_2sv,          Interception::Hooks::OpenGL::aiTexCoord2sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_3d,           Interception::Hooks::OpenGL::aiTexCoord3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_3dv,          Interception::Hooks::OpenGL::aiTexCoord3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_3f,           Interception::Hooks::OpenGL::aiTexCoord3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_3fv,          Interception::Hooks::OpenGL::aiTexCoord3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_3i,           Interception::Hooks::OpenGL::aiTexCoord3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_3iv,          Interception::Hooks::OpenGL::aiTexCoord3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_3s,           Interception::Hooks::OpenGL::aiTexCoord3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_3sv,          Interception::Hooks::OpenGL::aiTexCoord3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_4d,           Interception::Hooks::OpenGL::aiTexCoord4d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_4dv,          Interception::Hooks::OpenGL::aiTexCoord4dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_4f,           Interception::Hooks::OpenGL::aiTexCoord4f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_4fv,          Interception::Hooks::OpenGL::aiTexCoord4fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_4i,           Interception::Hooks::OpenGL::aiTexCoord4i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_4iv,          Interception::Hooks::OpenGL::aiTexCoord4iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_4s,           Interception::Hooks::OpenGL::aiTexCoord4s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_4sv,          Interception::Hooks::OpenGL::aiTexCoord4sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_coord_pointer,      Interception::Hooks::OpenGL::aiTexCoordPointer),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_env_f,              Interception::Hooks::OpenGL::aiTexEnvf),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_env_fv,             Interception::Hooks::OpenGL::aiTexEnvfv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_env_i,              Interception::Hooks::OpenGL::aiTexEnvi),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_env_iv,             Interception::Hooks::OpenGL::aiTexEnviv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_gen_d,              Interception::Hooks::OpenGL::aiTexGend),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_gen_dv,             Interception::Hooks::OpenGL::aiTexGendv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_gen_i,              Interception::Hooks::OpenGL::aiTexGeni),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_tex_gen_iv,             Interception::Hooks::OpenGL::aiTexGeniv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_translate_d,            Interception::Hooks::OpenGL::aiTranslated),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_translate_f,            Interception::Hooks::OpenGL::aiTranslatef),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_2d,              Interception::Hooks::OpenGL::aiVertex2d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_2dv,             Interception::Hooks::OpenGL::aiVertex2dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_2f,              Interception::Hooks::OpenGL::aiVertex2f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_2fv,             Interception::Hooks::OpenGL::aiVertex2fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_2i,              Interception::Hooks::OpenGL::aiVertex2i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_2iv,             Interception::Hooks::OpenGL::aiVertex2iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_2s,              Interception::Hooks::OpenGL::aiVertex2s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_2sv,             Interception::Hooks::OpenGL::aiVertex2sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_3d,              Interception::Hooks::OpenGL::aiVertex3d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_3dv,             Interception::Hooks::OpenGL::aiVertex3dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_3f,              Interception::Hooks::OpenGL::aiVertex3f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_3fv,             Interception::Hooks::OpenGL::aiVertex3fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_3i,              Interception::Hooks::OpenGL::aiVertex3i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_3iv,             Interception::Hooks::OpenGL::aiVertex3iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_3s,              Interception::Hooks::OpenGL::aiVertex3s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_3sv,             Interception::Hooks::OpenGL::aiVertex3sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_4d,              Interception::Hooks::OpenGL::aiVertex4d),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_4dv,             Interception::Hooks::OpenGL::aiVertex4dv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_4f,              Interception::Hooks::OpenGL::aiVertex4f),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_4fv,             Interception::Hooks::OpenGL::aiVertex4fv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_4i,              Interception::Hooks::OpenGL::aiVertex4i),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_4iv,             Interception::Hooks::OpenGL::aiVertex4iv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_4s,              Interception::Hooks::OpenGL::aiVertex4s),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_4sv,             Interception::Hooks::OpenGL::aiVertex4sv),
        APIInterceptor::FunctionInterceptor(&(PVOID&) Interception::Hooks::OpenGL::g_cached_gl_vertex_pointer,         Interception::Hooks::OpenGL::aiVertexPointer),
   };
}