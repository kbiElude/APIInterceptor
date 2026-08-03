/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/globals.h"
#include "Common/logger.h"
#include "Common/tracker.h"
#include "OpenGL/globals.h"
#include "WGL/globals.h"
#include "WGL/entrypoints/wgl_make_current.h"

bool update_non10_entrypoints()
{
    bool result = true;

    static const struct
    {
        const char* name;
        void**      ptr_ptr;
    } non10_entrypoints[] =
    {
        {"glBlendFunc",            &OpenGL::g_cached_gl_blend_func},
        {"glClear",                &OpenGL::g_cached_gl_clear},
        {"glClearColor",           &OpenGL::g_cached_gl_clear_color},
        {"glClearDepth",           &OpenGL::g_cached_gl_clear_depth},
        {"glClearStencil",         &OpenGL::g_cached_gl_clear_stencil},
        {"glColorMask",            &OpenGL::g_cached_gl_color_mask},
        {"glCullFace",             &OpenGL::g_cached_gl_cull_face},
        {"glDepthFunc",            &OpenGL::g_cached_gl_depth_func},
        {"glDepthMask",            &OpenGL::g_cached_gl_depth_mask},
        {"glDepthRange",           &OpenGL::g_cached_gl_depth_range},
        {"glDisable",              &OpenGL::g_cached_gl_disable},
        {"glDrawBuffer",           &OpenGL::g_cached_gl_draw_buffer},
        {"glEnable",               &OpenGL::g_cached_gl_enable},
        {"glEndTransformFeedback", &OpenGL::g_cached_gl_end_transform_feedback},
        {"glFinish",               &OpenGL::g_cached_gl_finish},
        {"glFlush",                &OpenGL::g_cached_gl_flush},
        {"glFrontFace",            &OpenGL::g_cached_gl_front_face},
        {"glGetBooleanv",          &OpenGL::g_cached_gl_get_booleanv},
        {"glGetTexImage",          &OpenGL::g_cached_gl_get_tex_image},
        {"glGetTexParameterfv",    &OpenGL::g_cached_gl_get_tex_parameterfv},
        {"glGetTexParameteriv",    &OpenGL::g_cached_gl_get_tex_parameteriv},
        {"glHint",                 &OpenGL::g_cached_gl_hint},
        {"glIsEnabled",            &OpenGL::g_cached_gl_is_enabled},
        {"glLineWidth",            &OpenGL::g_cached_gl_line_width},
        {"glLogicOp",              &OpenGL::g_cached_gl_logic_op},
        {"glPixelStoref",          &OpenGL::g_cached_gl_pixel_storef},
        {"glPixelStorei",          &OpenGL::g_cached_gl_pixel_storei},
        {"glPointSize",            &OpenGL::g_cached_gl_point_size}, 
        {"glPolygonMode",          &OpenGL::g_cached_gl_polygon_mode},
        {"glReadBuffer",           &OpenGL::g_cached_gl_read_buffer},
        {"glReadPixels",           &OpenGL::g_cached_gl_read_pixels},
        {"glScissor",              &OpenGL::g_cached_gl_scissor},
        {"glStencilFunc",          &OpenGL::g_cached_gl_stencil_func},
        {"glStencilMask",          &OpenGL::g_cached_gl_stencil_mask},
        {"glStencilOp",            &OpenGL::g_cached_gl_stencil_op},
        {"glTexImage1D",           &OpenGL::g_cached_gl_tex_image_1D},
        {"glTexImage2D",           &OpenGL::g_cached_gl_tex_image_2D},
        {"glTexParameterf",        &OpenGL::g_cached_gl_tex_parameterf},
        {"glTexParameterfv",       &OpenGL::g_cached_gl_tex_parameterfv},
        {"glTexParameteri",        &OpenGL::g_cached_gl_tex_parameteri},
        {"glTexParameteriv",       &OpenGL::g_cached_gl_tex_parameteriv},
        {"glViewport",             &OpenGL::g_cached_gl_viewport},

        /* 1.1 */
        {"glAreTexturesResidentEXT", &OpenGL::g_cached_are_textures_resident_ext},
        {"glBindTexture",            &OpenGL::g_cached_gl_bind_texture},
        {"glCopyTexImage1D",         &OpenGL::g_cached_gl_copy_tex_image_1D},
        {"glCopyTexImage2D",         &OpenGL::g_cached_gl_copy_tex_image_2D},
        {"glCopyTexSubImage1D",      &OpenGL::g_cached_gl_copy_tex_sub_image_1D},
        {"glCopyTexSubImage2D",      &OpenGL::g_cached_gl_copy_tex_sub_image_2D},
        {"glDeleteTextures",         &OpenGL::g_cached_gl_delete_textures},
        {"glDeleteFramebuffers",     &OpenGL::g_cached_gl_delete_framebuffers},
        {"glGenTextures",            &OpenGL::g_cached_gl_gen_textures},
        {"glIsTexture",              &OpenGL::g_cached_gl_is_texture},
        {"glPolygonOffset",          &OpenGL::g_cached_gl_polygon_offset},
        {"glPrioritizeTexturesEXT",  &OpenGL::g_cached_prioritize_textures_ext},
        {"glShadeModel",             &OpenGL::g_cached_gl_shade_model},
        {"glTexSubImage1D",          &OpenGL::g_cached_gl_tex_sub_image_1D},
        {"glTexSubImage2D",          &OpenGL::g_cached_gl_tex_sub_image_2D},

        /* 1.2 */
        {"glCopyTexSubImage3D", &OpenGL::g_cached_gl_copy_tex_sub_image_3D},
        {"glDrawRangeElements", &OpenGL::g_cached_gl_draw_range_elements},
        {"glTexImage3D",        &OpenGL::g_cached_gl_tex_image_3D},
        {"glTexSubImage3D",     &OpenGL::g_cached_gl_tex_sub_image_3D},

        /* 1.3 */
        {"glActiveTexture",           &OpenGL::g_cached_gl_active_texture},
        {"glClientActiveTexture",     &OpenGL::g_cached_gl_client_active_texture},
        {"glCompressedTexImage1D",    &OpenGL::g_cached_gl_compressed_tex_image_1D},
        {"glCompressedTexImage2D",    &OpenGL::g_cached_gl_compressed_tex_image_2D},
        {"glCompressedTexImage3D",    &OpenGL::g_cached_gl_compressed_tex_image_3D},
        {"glCompressedTexSubImage1D", &OpenGL::g_cached_gl_compressed_tex_sub_image_1D},
        {"glCompressedTexSubImage2D", &OpenGL::g_cached_gl_compressed_tex_sub_image_2D},
        {"glCompressedTexSubImage3D", &OpenGL::g_cached_gl_compressed_tex_sub_image_3D},
        {"glEndTransformFeedback",    &OpenGL::g_cached_gl_end_transform_feedback},
        {"glLoadTransposeMatrixd",    &OpenGL::g_cached_gl_load_transpose_matrix_d},
        {"glLoadTransposeMatrixf",    &OpenGL::g_cached_gl_load_transpose_matrix_f},
        {"glMultTransposeMatrixd",    &OpenGL::g_cached_gl_mult_transpose_matrix_d},
        {"glMultTransposeMatrixf",    &OpenGL::g_cached_gl_mult_transpose_matrix_f},
        {"glMultiTexCoord1d",         &OpenGL::g_cached_gl_multi_tex_coord_1d},
        {"glMultiTexCoord1dv",        &OpenGL::g_cached_gl_multi_tex_coord_1dv},
        {"glMultiTexCoord1f",         &OpenGL::g_cached_gl_multi_tex_coord_1f},
        {"glMultiTexCoord1fv",        &OpenGL::g_cached_gl_multi_tex_coord_1fv},
        {"glMultiTexCoord1i",         &OpenGL::g_cached_gl_multi_tex_coord_1i},
        {"glMultiTexCoord1iv",        &OpenGL::g_cached_gl_multi_tex_coord_1iv},
        {"glMultiTexCoord1s",         &OpenGL::g_cached_gl_multi_tex_coord_1s},
        {"glMultiTexCoord1sv",        &OpenGL::g_cached_gl_multi_tex_coord_1sv},
        {"glMultiTexCoord2d",         &OpenGL::g_cached_gl_multi_tex_coord_2d},
        {"glMultiTexCoord2dv",        &OpenGL::g_cached_gl_multi_tex_coord_2dv},
        {"glMultiTexCoord2f",         &OpenGL::g_cached_gl_multi_tex_coord_2f},
        {"glMultiTexCoord2fv",        &OpenGL::g_cached_gl_multi_tex_coord_2fv},
        {"glMultiTexCoord2i",         &OpenGL::g_cached_gl_multi_tex_coord_2i},
        {"glMultiTexCoord2iv",        &OpenGL::g_cached_gl_multi_tex_coord_2iv},
        {"glMultiTexCoord2s",         &OpenGL::g_cached_gl_multi_tex_coord_2s},
        {"glMultiTexCoord2sv",        &OpenGL::g_cached_gl_multi_tex_coord_2sv},
        {"glMultiTexCoord3d",         &OpenGL::g_cached_gl_multi_tex_coord_3d},
        {"glMultiTexCoord3dv",        &OpenGL::g_cached_gl_multi_tex_coord_3dv},
        {"glMultiTexCoord3f",         &OpenGL::g_cached_gl_multi_tex_coord_3f},
        {"glMultiTexCoord3fv",        &OpenGL::g_cached_gl_multi_tex_coord_3fv},
        {"glMultiTexCoord3i",         &OpenGL::g_cached_gl_multi_tex_coord_3i},
        {"glMultiTexCoord3iv",        &OpenGL::g_cached_gl_multi_tex_coord_3iv},
        {"glMultiTexCoord3s",         &OpenGL::g_cached_gl_multi_tex_coord_3s},
        {"glMultiTexCoord3sv",        &OpenGL::g_cached_gl_multi_tex_coord_3sv},
        {"glMultiTexCoord4d",         &OpenGL::g_cached_gl_multi_tex_coord_4d},
        {"glMultiTexCoord4dv",        &OpenGL::g_cached_gl_multi_tex_coord_4dv},
        {"glMultiTexCoord4f",         &OpenGL::g_cached_gl_multi_tex_coord_4f},
        {"glMultiTexCoord4fv",        &OpenGL::g_cached_gl_multi_tex_coord_4fv},
        {"glMultiTexCoord4i",         &OpenGL::g_cached_gl_multi_tex_coord_4i},
        {"glMultiTexCoord4iv",        &OpenGL::g_cached_gl_multi_tex_coord_4iv},
        {"glMultiTexCoord4s",         &OpenGL::g_cached_gl_multi_tex_coord_4s},
        {"glMultiTexCoord4sv",        &OpenGL::g_cached_gl_multi_tex_coord_4sv},
        {"glSampleCoverage",          &OpenGL::g_cached_gl_sample_coverage},

        /* 1.4 */
        {"glBlendColor",        &OpenGL::g_cached_gl_blend_color},
        {"glBlendEquation",     &OpenGL::g_cached_gl_blend_equation},
        {"glBlendFuncSeparate", &OpenGL::g_cached_gl_blend_func_separate},
        {"glMultiDrawArrays",   &OpenGL::g_cached_gl_multi_draw_arrays},
        {"glMultiDrawElements", &OpenGL::g_cached_gl_multi_draw_elements},
        {"glPointParameterf",   &OpenGL::g_cached_gl_point_parameterf},
        {"glPointParameterfv",  &OpenGL::g_cached_gl_point_parameterfv},
        {"glPointParameteri",   &OpenGL::g_cached_gl_point_parameteri},
        {"glPointParameteriv",  &OpenGL::g_cached_gl_point_parameteriv},
        {"glFogCoordd",         &OpenGL::g_cached_gl_fog_coord_d},
        {"glFogCoorddv",        &OpenGL::g_cached_gl_fog_coord_dv},
        {"glFogCoordf",         &OpenGL::g_cached_gl_fog_coord_f},
        {"glFogCoordfv",        &OpenGL::g_cached_gl_fog_coord_fv},
        {"glFogCoordPointer",   &OpenGL::g_cached_gl_fog_coord_pointer},
        {"glSecondaryColor3b",  &OpenGL::g_cached_gl_secondary_color_3b},
        {"glSecondaryColor3bv", &OpenGL::g_cached_gl_secondary_color_3bv},
        {"glSecondaryColor3d",  &OpenGL::g_cached_gl_secondary_color_3d},
        {"glSecondaryColor3dv", &OpenGL::g_cached_gl_secondary_color_3dv},
        {"glSecondaryColor3f",  &OpenGL::g_cached_gl_secondary_color_3f},
        {"glSecondaryColor3fv", &OpenGL::g_cached_gl_secondary_color_3fv},
        {"glSecondaryColor3i",  &OpenGL::g_cached_gl_secondary_color_3i},
        {"glSecondaryColor3iv", &OpenGL::g_cached_gl_secondary_color_3iv},
        {"glSecondaryColor3s",  &OpenGL::g_cached_gl_secondary_color_3s},
        {"glSecondaryColor3sv", &OpenGL::g_cached_gl_secondary_color_3sv},
        {"glSecondaryColor3ub", &OpenGL::g_cached_gl_secondary_color_3ub},
        {"glSecondaryColor3ubv",&OpenGL::g_cached_gl_secondary_color_3ubv},
        {"glSecondaryColor3ui", &OpenGL::g_cached_gl_secondary_color_3ui},
        {"glSecondaryColor3uiv",&OpenGL::g_cached_gl_secondary_color_3uiv},
        {"glSecondaryColor3us", &OpenGL::g_cached_gl_secondary_color_3us},
        {"glSecondaryColor3usv",&OpenGL::g_cached_gl_secondary_color_3usv},
        {"glSecondaryColorPointer",&OpenGL::g_cached_gl_secondary_color_pointer},
        {"glWindowPos2d",       &OpenGL::g_cached_gl_window_pos_2d},
        {"glWindowPos2dv",      &OpenGL::g_cached_gl_window_pos_2dv},
        {"glWindowPos2f",       &OpenGL::g_cached_gl_window_pos_2f},
        {"glWindowPos2fv",      &OpenGL::g_cached_gl_window_pos_2fv},
        {"glWindowPos2i",       &OpenGL::g_cached_gl_window_pos_2i},
        {"glWindowPos2iv",      &OpenGL::g_cached_gl_window_pos_2iv},
        {"glWindowPos2s",       &OpenGL::g_cached_gl_window_pos_2s},
        {"glWindowPos2sv",      &OpenGL::g_cached_gl_window_pos_2sv},
        {"glWindowPos3d",       &OpenGL::g_cached_gl_window_pos_3d},
        {"glWindowPos3dv",      &OpenGL::g_cached_gl_window_pos_3dv},
        {"glWindowPos3f",       &OpenGL::g_cached_gl_window_pos_3f},
        {"glWindowPos3fv",      &OpenGL::g_cached_gl_window_pos_3fv},
        {"glWindowPos3i",       &OpenGL::g_cached_gl_window_pos_3i},
        {"glWindowPos3iv",      &OpenGL::g_cached_gl_window_pos_3iv},
        {"glWindowPos3s",       &OpenGL::g_cached_gl_window_pos_3s},
        {"glWindowPos3sv",      &OpenGL::g_cached_gl_window_pos_3sv},

        /* 1.5 */
        {"glBeginQuery",           &OpenGL::g_cached_gl_begin_query},
        {"glBindBuffer",           &OpenGL::g_cached_gl_bind_buffer},
        {"glBufferData",           &OpenGL::g_cached_gl_buffer_data},
        {"glBufferSubData",        &OpenGL::g_cached_gl_buffer_sub_data},
        {"glDeleteBuffers",        &OpenGL::g_cached_gl_delete_buffers},
        {"glDeleteQueries",        &OpenGL::g_cached_gl_delete_queries},
        {"glEndQuery",             &OpenGL::g_cached_gl_end_query},
        {"glGenBuffers",           &OpenGL::g_cached_gl_gen_buffers},
        {"glGenQueries",           &OpenGL::g_cached_gl_gen_queries},
        {"glGetBufferParameteriv", &OpenGL::g_cached_gl_get_buffer_parameteriv},
        {"glGetBufferPointerv",    &OpenGL::g_cached_gl_get_buffer_pointerv},
        {"glGetBufferSubData",     &OpenGL::g_cached_gl_get_buffer_sub_data},
        {"glEndTransformFeedback", &OpenGL::g_cached_gl_end_transform_feedback},
        {"glGetQueryObjectiv",     &OpenGL::g_cached_gl_get_query_objectiv},
        {"glIsBuffer",             &OpenGL::g_cached_gl_is_buffer},
        {"glIsQuery",              &OpenGL::g_cached_gl_is_query},
        {"glMapBuffer",            &OpenGL::g_cached_gl_map_buffer},
        {"glUnmapBuffer",          &OpenGL::g_cached_gl_unmap_buffer},

        /* 2.0 */
        {"glAttachShader",             &OpenGL::g_cached_gl_attach_shader},
        {"glBindAttribLocation",       &OpenGL::g_cached_gl_bind_attrib_location},
        {"glBlendEquationSeparate",    &OpenGL::g_cached_gl_blend_equation_separate},
        {"glCompileShader",            &OpenGL::g_cached_gl_compile_shader},
        {"glCreateProgram",            &OpenGL::g_cached_gl_create_program},
        {"glCreateShader",             &OpenGL::g_cached_gl_create_shader},
        {"glDeleteProgram",            &OpenGL::g_cached_gl_delete_program},
        {"glDeleteShader",             &OpenGL::g_cached_gl_delete_shader},
        {"glDetachShader",             &OpenGL::g_cached_gl_detach_shader},
        {"glDisableVertexAttribArray", &OpenGL::g_cached_gl_disable_vertex_attrib_array},
        {"glDrawBuffers",              &OpenGL::g_cached_gl_draw_buffers},
        {"glEnableVertexAttribArray",  &OpenGL::g_cached_gl_enable_vertex_attrib_array},
        {"glGetActiveAttrib",          &OpenGL::g_cached_gl_get_active_attrib},
        {"glGetActiveUniform",         &OpenGL::g_cached_gl_get_active_uniform},
        {"glGetAttachedShaders",       &OpenGL::g_cached_gl_get_attached_shaders},
        {"glGetAttribLocation",        &OpenGL::g_cached_gl_get_attrib_location},
        {"glGetProgramiv",             &OpenGL::g_cached_gl_get_programiv},
        {"glGetProgramInfoLog",        &OpenGL::g_cached_gl_get_program_info_log},
        {"glGetShaderiv",              &OpenGL::g_cached_gl_get_shaderiv},
        {"glGetShaderInfoLog",         &OpenGL::g_cached_gl_get_shader_info_log},
        {"glGetUniformiv",             &OpenGL::g_cached_gl_get_uniformiv},
        {"glGetUniformLocation",       &OpenGL::g_cached_gl_get_uniform_location},
        {"glGetVertexAttribdv",        &OpenGL::g_cached_gl_get_vertex_attribdv},
        {"glGetVertexAttribfv",        &OpenGL::g_cached_gl_get_vertex_attribfv},
        {"glIsProgram",                &OpenGL::g_cached_gl_is_program},
        {"glIsShader",                 &OpenGL::g_cached_gl_is_shader},
        {"glLinkProgram",              &OpenGL::g_cached_gl_link_program},
        {"glShaderSource",             &OpenGL::g_cached_gl_shader_source},
        {"glStencilFuncSeparate",      &OpenGL::g_cached_gl_stencil_func_separate},
        {"glStencilMaskSeparate",      &OpenGL::g_cached_gl_stencil_mask_separate},
        {"glStencilOpSeparate",        &OpenGL::g_cached_gl_stencil_op_separate},
        {"glUniform1f",                &OpenGL::g_cached_gl_uniform_1f},
        {"glUniform1fv",               &OpenGL::g_cached_gl_uniform_1fv},
        {"glUniform1i",                &OpenGL::g_cached_gl_uniform_1i},
        {"glUniform1iv",               &OpenGL::g_cached_gl_uniform_1iv},
        {"glUniform2f",                &OpenGL::g_cached_gl_uniform_2f},
        {"glUniform2fv",               &OpenGL::g_cached_gl_uniform_2fv},
        {"glUniform2i",                &OpenGL::g_cached_gl_uniform_2i},
        {"glUniform2iv",               &OpenGL::g_cached_gl_uniform_2iv},
        {"glUniform3f",                &OpenGL::g_cached_gl_uniform_3f},
        {"glUniform3fv",               &OpenGL::g_cached_gl_uniform_3fv},
        {"glUniform3i",                &OpenGL::g_cached_gl_uniform_3i},
        {"glUniform3iv",               &OpenGL::g_cached_gl_uniform_3iv},
        {"glUniform4f",                &OpenGL::g_cached_gl_uniform_4f},
        {"glUniform4fv",               &OpenGL::g_cached_gl_uniform_4fv},
        {"glUniform4i",                &OpenGL::g_cached_gl_uniform_4i},
        {"glUniform4iv",               &OpenGL::g_cached_gl_uniform_4iv},
        {"glUniformMatrix2fv",         &OpenGL::g_cached_gl_uniform_matrix_2fv},
        {"glUniformMatrix3fv",         &OpenGL::g_cached_gl_uniform_matrix_3fv},
        {"glUniformMatrix4fv",         &OpenGL::g_cached_gl_uniform_matrix_4fv},
        {"glUseProgram",               &OpenGL::g_cached_gl_use_program},
        {"glValidateProgram",          &OpenGL::g_cached_gl_validate_program},
        {"glVertexAttrib1d",           &OpenGL::g_cached_gl_vertex_attrib_1d},
        {"glVertexAttrib1dv",          &OpenGL::g_cached_gl_vertex_attrib_1dv},
        {"glVertexAttrib1f",           &OpenGL::g_cached_gl_vertex_attrib_1f},
        {"glVertexAttrib1fv",          &OpenGL::g_cached_gl_vertex_attrib_1fv},
        {"glVertexAttrib1s",           &OpenGL::g_cached_gl_vertex_attrib_1s},
        {"glVertexAttrib1sv",          &OpenGL::g_cached_gl_vertex_attrib_1sv},
        {"glVertexAttrib2d",           &OpenGL::g_cached_gl_vertex_attrib_2d},
        {"glVertexAttrib2dv",          &OpenGL::g_cached_gl_vertex_attrib_2dv},
        {"glVertexAttrib2f",           &OpenGL::g_cached_gl_vertex_attrib_2f},
        {"glVertexAttrib2fv",          &OpenGL::g_cached_gl_vertex_attrib_2fv},
        {"glVertexAttrib2s",           &OpenGL::g_cached_gl_vertex_attrib_2s},
        {"glVertexAttrib2sv",          &OpenGL::g_cached_gl_vertex_attrib_2sv},
        {"glVertexAttrib3d",           &OpenGL::g_cached_gl_vertex_attrib_3d},
        {"glVertexAttrib3dv",          &OpenGL::g_cached_gl_vertex_attrib_3dv},
        {"glVertexAttrib3f",           &OpenGL::g_cached_gl_vertex_attrib_3f},
        {"glVertexAttrib3fv",          &OpenGL::g_cached_gl_vertex_attrib_3fv},
        {"glVertexAttrib3s",           &OpenGL::g_cached_gl_vertex_attrib_3s},
        {"glVertexAttrib3sv",          &OpenGL::g_cached_gl_vertex_attrib_3sv},
        {"glVertexAttrib4bv",          &OpenGL::g_cached_gl_vertex_attrib_4bv},
        {"glVertexAttrib4d",           &OpenGL::g_cached_gl_vertex_attrib_4d},
        {"glVertexAttrib4dv",          &OpenGL::g_cached_gl_vertex_attrib_4dv},
        {"glVertexAttrib4f",           &OpenGL::g_cached_gl_vertex_attrib_4f},
        {"glVertexAttrib4fv",          &OpenGL::g_cached_gl_vertex_attrib_4fv},
        {"glVertexAttrib4iv",          &OpenGL::g_cached_gl_vertex_attrib_4iv},
        {"glVertexAttrib4Nbv",         &OpenGL::g_cached_gl_vertex_attrib_4Nbv},
        {"glVertexAttrib4Niv",         &OpenGL::g_cached_gl_vertex_attrib_4Niv},
        {"glVertexAttrib4Nsv",         &OpenGL::g_cached_gl_vertex_attrib_4Nsv},
        {"glVertexAttrib4Nub",         &OpenGL::g_cached_gl_vertex_attrib_4Nub},
        {"glVertexAttrib4Nubv",        &OpenGL::g_cached_gl_vertex_attrib_4Nubv},
        {"glVertexAttrib4Nuiv",        &OpenGL::g_cached_gl_vertex_attrib_4Nuiv},
        {"glVertexAttrib4Nusv",        &OpenGL::g_cached_gl_vertex_attrib_4Nusv},
        {"glVertexAttrib4s",           &OpenGL::g_cached_gl_vertex_attrib_4s},
        {"glVertexAttrib4sv",          &OpenGL::g_cached_gl_vertex_attrib_4sv},
        {"glVertexAttrib4ubv",         &OpenGL::g_cached_gl_vertex_attrib_4ubv},
        {"glVertexAttrib4uiv",         &OpenGL::g_cached_gl_vertex_attrib_4uiv},
        {"glVertexAttrib4usv",         &OpenGL::g_cached_gl_vertex_attrib_4usv},
        {"glVertexAttribPointer",      &OpenGL::g_cached_gl_vertex_attrib_pointer},

        /* 2.1 */
        {"glUniformMatrix2x3fv", &OpenGL::g_cached_gl_uniform_matrix_2x3_fv},
        {"glUniformMatrix2x4fv", &OpenGL::g_cached_gl_uniform_matrix_2x4_fv},
        {"glUniformMatrix3x2fv", &OpenGL::g_cached_gl_uniform_matrix_3x2_fv},
        {"glUniformMatrix3x4fv", &OpenGL::g_cached_gl_uniform_matrix_3x4_fv},
        {"glUniformMatrix4x2fv", &OpenGL::g_cached_gl_uniform_matrix_4x2_fv},
        {"glUniformMatrix4x3fv", &OpenGL::g_cached_gl_uniform_matrix_4x3_fv},

        /* 3.0 */
        {"glBeginConditionalRender",              &OpenGL::g_cached_gl_begin_conditional_render},
        {"glBeginTransformFeedback",              &OpenGL::g_cached_gl_begin_transform_feedback},
        {"glBindBufferBase",                      &OpenGL::g_cached_gl_bind_buffer_base},
        {"glBindBufferRange",                     &OpenGL::g_cached_gl_bind_buffer_range},
        {"glBindFragDataLocation",                &OpenGL::g_cached_gl_bind_frag_data_location},
        {"glBindFramebuffer",                     &OpenGL::g_cached_gl_bind_framebuffer},
        {"glBindRenderbuffer",                    &OpenGL::g_cached_gl_bind_renderbuffer},
        {"glBindVertexArray",                     &OpenGL::g_cached_gl_bind_vertex_array},
        {"glBlitFramebuffer",                     &OpenGL::g_cached_gl_blit_framebuffer},
        {"glCheckFramebufferStatus",              &OpenGL::g_cached_gl_check_framebuffer_status},
        {"glClampColor",                          &OpenGL::g_cached_gl_clamp_color},
        {"glClearBufferfi",                       &OpenGL::g_cached_gl_clear_buffer_fi},
        {"glClearBufferfv",                       &OpenGL::g_cached_gl_clear_buffer_fv},
        {"glClearBufferfv",                       &OpenGL::g_cached_gl_clear_buffer_iv},
        {"glClearBufferuiv",                      &OpenGL::g_cached_gl_clear_buffer_uiv},
        {"glColorMaski",                          &OpenGL::g_cached_gl_color_maski},
        {"glDeleteVertexArrays",                  &OpenGL::g_cached_gl_delete_vertex_arrays},
        {"glDisablei",                            &OpenGL::g_cached_gl_disablei},
        {"glDeleteFramebuffers",                  &OpenGL::g_cached_gl_delete_framebuffers},
        {"glEndConditionalRender",                &OpenGL::g_cached_gl_end_conditional_render},
        {"glEndTransformFeedback",                &OpenGL::g_cached_gl_end_transform_feedback},
        {"glFlushMappedBufferRange",              &OpenGL::g_cached_gl_flush_mapped_buffer_range},
        {"glFramebufferRenderbuffer",             &OpenGL::g_cached_gl_framebuffer_renderbuffer},
        {"glFramebufferTexture1D",                &OpenGL::g_cached_gl_framebuffer_texture_1D},
        {"glFramebufferTexture2D",                &OpenGL::g_cached_gl_framebuffer_texture_2D},
        {"glFramebufferTexture3D",                &OpenGL::g_cached_gl_framebuffer_texture_3D},
        {"glFramebufferTextureLayer",             &OpenGL::g_cached_gl_framebuffer_texture_layer},
        {"glGenerateMipmap",                      &OpenGL::g_cached_gl_generate_mipmap},
        {"glGenFramebuffers",                     &OpenGL::g_cached_gl_gen_framebuffers},
        {"glGenRenderbuffers",                    &OpenGL::g_cached_gl_gen_renderbuffers},
        {"glGenVertexArrays",                     &OpenGL::g_cached_gl_gen_vertex_arrays},
        {"glGetBooleani_v",                       &OpenGL::g_cached_gl_get_booleani_v},
        {"glGetFragDataLocation",                 &OpenGL::g_cached_gl_get_frag_data_location},
        {"glGetFramebufferAttachmentParameteriv", &OpenGL::g_cached_gl_get_framebuffer_attachment_parameteriv},
        {"glGetIntegeri_v",                       &OpenGL::g_cached_gl_get_integeri_v},
        {"glGetRenderbufferParameteriv",          &OpenGL::g_cached_gl_get_renderbuffer_parameteriv},
        {"glGetStringi",                          &OpenGL::g_cached_gl_get_stringi},
        {"glGetTexParameterIuiv",                 &OpenGL::g_cached_gl_get_tex_parameter_i_uiv},
        {"glGetVertexAttribIiv",                  &OpenGL::g_cached_gl_get_vertex_attrib_i_iv},
        {"glGetVertexAttribIuiv",                 &OpenGL::g_cached_gl_get_vertex_attrib_i_uiv},
        {"glIsEnabledi",                          &OpenGL::g_cached_gl_is_enabledi},
        {"glIsFramebuffer",                       &OpenGL::g_cached_gl_is_framebuffer},
        {"glIsRenderbuffer",                      &OpenGL::g_cached_gl_is_renderbuffer},
        {"glIsVertexArray",                       &OpenGL::g_cached_gl_is_vertex_array},
        {"glMapBufferRange",                      &OpenGL::g_cached_gl_map_buffer_range},
        {"glRenderbufferStorage",                 &OpenGL::g_cached_gl_renderbuffer_storage},
        {"glRenderbufferStorageMultisample",      &OpenGL::g_cached_gl_renderbuffer_storage_multisample},
        {"glTexParameterIiv",                     &OpenGL::g_cached_gl_tex_parameter_i_iv},
        {"glTexParameterIuiv",                    &OpenGL::g_cached_gl_tex_parameter_i_uiv},
        {"glTransformFeedbackVaryings",           &OpenGL::g_cached_gl_transform_feedback_varyings},
        {"glUniform1ui",                          &OpenGL::g_cached_gl_uniform_1ui},
        {"glUniform1uiv",                         &OpenGL::g_cached_gl_uniform_1uiv},
        {"glUniform2ui",                          &OpenGL::g_cached_gl_uniform_2ui},
        {"glUniform2uiv",                         &OpenGL::g_cached_gl_uniform_2uiv},
        {"glUniform3ui",                          &OpenGL::g_cached_gl_uniform_3ui},
        {"glUniform3uiv",                         &OpenGL::g_cached_gl_uniform_3uiv},
        {"glUniform4ui",                          &OpenGL::g_cached_gl_uniform_4ui},
        {"glUniform4uiv",                         &OpenGL::g_cached_gl_uniform_4uiv},
        {"glVertexAttribI1i",                     &OpenGL::g_cached_gl_vertex_attrib_i_1i},
        {"glVertexAttribI1iv",                    &OpenGL::g_cached_gl_vertex_attrib_i_1iv},
        {"glVertexAttribI1ui",                    &OpenGL::g_cached_gl_vertex_attrib_i_1ui},
        {"glVertexAttribI1uiv",                   &OpenGL::g_cached_gl_vertex_attrib_i_1uiv},
        {"glVertexAttribI2i",                     &OpenGL::g_cached_gl_vertex_attrib_i_2i},
        {"glVertexAttribI2iv",                    &OpenGL::g_cached_gl_vertex_attrib_i_2iv},
        {"glVertexAttribI2ui",                    &OpenGL::g_cached_gl_vertex_attrib_i_2ui},
        {"glVertexAttribI2uiv",                   &OpenGL::g_cached_gl_vertex_attrib_i_2uiv},
        {"glVertexAttribI3i",                     &OpenGL::g_cached_gl_vertex_attrib_i_3i},
        {"glVertexAttribI3iv",                    &OpenGL::g_cached_gl_vertex_attrib_i_3iv},
        {"glVertexAttribI3ui",                    &OpenGL::g_cached_gl_vertex_attrib_i_3ui},
        {"glVertexAttribI3uiv",                   &OpenGL::g_cached_gl_vertex_attrib_i_3uiv},
        {"glVertexAttribI4bv",                    &OpenGL::g_cached_gl_vertex_attrib_i_4bv},
        {"glVertexAttribI4i",                     &OpenGL::g_cached_gl_vertex_attrib_i_4i},
        {"glVertexAttribI4iv",                    &OpenGL::g_cached_gl_vertex_attrib_i_4iv},
        {"glVertexAttribI4sv",                    &OpenGL::g_cached_gl_vertex_attrib_i_4sv},
        {"glVertexAttribI4ubv",                   &OpenGL::g_cached_gl_vertex_attrib_i_4ubv},
        {"glVertexAttribI4ui",                    &OpenGL::g_cached_gl_vertex_attrib_i_4ui},
        {"glVertexAttribI4uiv",                   &OpenGL::g_cached_gl_vertex_attrib_i_4uiv},
        {"glVertexAttribI4usv",                   &OpenGL::g_cached_gl_vertex_attrib_i_4usv},
        {"glVertexAttribIPointer",                &OpenGL::g_cached_gl_vertex_attrib_i_pointer},

        /* 3.1 */
        {"glCopyBufferSubData",         &OpenGL::g_cached_gl_copy_buffer_sub_data},
        {"glDrawArraysInstanced",       &OpenGL::g_cached_gl_draw_arrays_instanced},
        {"glDrawElementsInstanced",     &OpenGL::g_cached_gl_draw_elements_instanced},
        {"glGetActiveUniformsiv",       &OpenGL::g_cached_gl_get_active_uniformsiv},
        {"glGetActiveUniformBlockiv",   &OpenGL::g_cached_gl_get_active_uniform_blockiv},
        {"glGetActiveUniformBlockName", &OpenGL::g_cached_gl_get_active_uniform_block_name},
        {"glGetUniformIndices",         &OpenGL::g_cached_gl_get_uniform_indices},
        {"glPrimitiveRestartIndex",     &OpenGL::g_cached_gl_primitive_restart_index},
        {"glTexBuffer",                 &OpenGL::g_cached_gl_tex_buffer},
        {"glUniformBlockBinding",       &OpenGL::g_cached_gl_uniform_block_binding},

        /* 3.2 */
        {"glClientWaitSync",                  &OpenGL::g_cached_gl_client_wait_sync},
        {"glDeleteSync",                      &OpenGL::g_cached_gl_delete_sync},
        {"glDrawElementsBaseVertex",          &OpenGL::g_cached_gl_draw_elements_base_vertex},
        {"glDrawElementsInstancedBaseVertex", &OpenGL::g_cached_gl_draw_elements_instanced_base_vertex},
        {"glDrawRangeElementsBaseVertex",     &OpenGL::g_cached_gl_draw_range_elements_base_vertex},
        {"glFenceSync",                       &OpenGL::g_cached_gl_fence_sync},
        {"glFramebufferTexture",              &OpenGL::g_cached_gl_framebuffer_texture},
        {"glGetBufferParameteri64v",          &OpenGL::g_cached_gl_get_buffer_parameteri64v},
        {"glGetInteger64i_v",                 &OpenGL::g_cached_gl_get_integer64i_v},
        {"glGetInteger64v",                   &OpenGL::g_cached_gl_get_integer64v},
        {"glGetMultisamplefv",                &OpenGL::g_cached_gl_get_multisamplefv},
        {"glIsSync",                          &OpenGL::g_cached_gl_is_sync},
        {"glMultiDrawElementsBaseVertex",     &OpenGL::g_cached_gl_multi_draw_elements_base_vertex},
        {"glProvokingVertex",                 &OpenGL::g_cached_gl_provoking_vertex},
        {"glSampleMaski",                     &OpenGL::g_cached_gl_sample_maski},
        {"glTexImage2DMultisample",           &OpenGL::g_cached_gl_tex_image_2DMultisample},
        {"glTexImage3DMultisample",           &OpenGL::g_cached_gl_tex_image_3DMultisample},
        {"glWaitSync",                        &OpenGL::g_cached_gl_wait_sync}
    };

    for (const auto& current_entrypoint : non10_entrypoints)
    {
        if (*current_entrypoint.ptr_ptr == nullptr)
        {
            *current_entrypoint.ptr_ptr = reinterpret_cast<WGL::PFNWGLGETPROCADDRESSPROC>(WGL::g_cached_get_proc_address_func_ptr)(current_entrypoint.name);

            AI_ASSERT(*current_entrypoint.ptr_ptr != nullptr);

            result &= (*current_entrypoint.ptr_ptr != nullptr);
        }
    }

    return result;
}

BOOL WINAPI WGL::make_current(HDC   in_hdc,
                              HGLRC in_hglrc)
{
    static bool has_successfully_updated_non10_entrypoints = false;

    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    BOOL                                    result                 = TRUE;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("wglMakeCurrent(in_hdc=[%p] in_hglrc=[%p])",
                   in_hdc,
                   in_hglrc);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLMAKECURRENT,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hdc),
                APIInterceptor::APIFunctionArgument::create_void_ptr(in_hglrc),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLMAKECURRENT,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    // This function should always patch through down the driver stack!
    AI_ASSERT(should_pass_through);

    result = reinterpret_cast<PFNWGLMAKECURRENTPROC>(WGL::g_cached_make_current_func_ptr)(in_hdc,
                                                                                          in_hglrc);

    if (tracker.is_top_level_api_call() )
    {
        if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_WGL_WGLMAKECURRENT,
                                                          &post_callback_func_ptr,
                                                          &post_callback_func_arg) )
        {
            const auto result_arg = APIInterceptor::APIFunctionArgument::create_i32(result);

            post_callback_func_ptr(APIInterceptor::APIFUNCTION_WGL_WGLMAKECURRENT,
                                   post_callback_func_arg,
                                   0,       /* in_n_args_out   */
                                   nullptr, /* in_args_out_ptr */
                                  &result_arg);
        }
    }

    if (in_hglrc                                   != nullptr &&
        has_successfully_updated_non10_entrypoints == false)
    {
        has_successfully_updated_non10_entrypoints |= update_non10_entrypoints();
    }

    return result;
}
