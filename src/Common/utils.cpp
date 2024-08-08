/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/utils.h"
#include "OpenGL/utils_enum.h"
#include <cassert>

void APIInterceptor::convert_api_command_to_string(const APICommand& in_api_command,
                                                   std::string*      out_string_ptr)
{
    std::stringstream sstream;

    switch (in_api_command.api_func)
    {
        case APIInterceptor::APIFUNCTION_GL_GLALPHAFUNC:
        {
            const auto arg_func = in_api_command.api_arg_vec.at(0).get_u32 ();
            const auto arg_ref  = in_api_command.api_arg_vec.at(1).get_fp32();

            sstream << "glAlphaFunc("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_func)
                    << ", "
                    << arg_ref
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLBEGIN:
        {
            const auto arg_mode = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glBegin("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_mode)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLBINDTEXTURE:
        {
            const auto arg_target  = in_api_command.api_arg_vec.at(0).get_u32();
            const auto arg_texture = in_api_command.api_arg_vec.at(1).get_u32();

            sstream << "glBindTexture("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_target)
                    << ", "
                    << arg_texture
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLBLENDFUNC:
        {
            const auto arg_sfactor = in_api_command.api_arg_vec.at(0).get_u32();
            const auto arg_dfactor = in_api_command.api_arg_vec.at(1).get_u32();

            sstream << "glBlendFunc("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_sfactor)
                    << ", "
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_dfactor)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLCLEAR:
        {
            const auto arg_mask = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glClear("
                    << OpenGL::Utils::get_raw_string_for_gl_bitfield(OpenGL::BitfieldType::Clear_Buffer_Mask,
                                                                     arg_mask)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLCLEARCOLOR:
        {
            const auto arg_red   = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_green = in_api_command.api_arg_vec.at(1).get_fp32();
            const auto arg_blue  = in_api_command.api_arg_vec.at(2).get_fp32();
            const auto arg_alpha = in_api_command.api_arg_vec.at(3).get_fp32();

            sstream << "glClearColor("
                    << arg_red
                    << ", "
                    << arg_green
                    << ", "
                    << arg_blue
                    << ", "
                    << arg_alpha
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLCLEARDEPTH:
        {
            const auto arg_depth = in_api_command.api_arg_vec.at(0).get_fp64();

            sstream << "glClearDepth("
                    << arg_depth
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLCOLOR3F:
        {
            const auto arg_x = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_y = in_api_command.api_arg_vec.at(1).get_fp32();
            const auto arg_z = in_api_command.api_arg_vec.at(2).get_fp32();

            sstream << "glColor3f("
                    << arg_x
                    << ", "
                    << arg_y
                    << ", "
                    << arg_z
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLCOLOR3UB:
        {
            const auto arg_x = in_api_command.api_arg_vec.at(0).get_u8();
            const auto arg_y = in_api_command.api_arg_vec.at(1).get_u8();
            const auto arg_z = in_api_command.api_arg_vec.at(2).get_u8();

            sstream << "glColor3ub("
                    << static_cast<uint32_t>(arg_x)
                    << ", "
                    << static_cast<uint32_t>(arg_y)
                    << ", "
                    << static_cast<uint32_t>(arg_z)
                    << ")\n";
            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLCOLOR4F:
        {
            const auto arg_x = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_y = in_api_command.api_arg_vec.at(1).get_fp32();
            const auto arg_z = in_api_command.api_arg_vec.at(2).get_fp32();
            const auto arg_w = in_api_command.api_arg_vec.at(3).get_fp32();

            sstream << "glColor4f("
                    << arg_x
                    << ", "
                    << arg_y
                    << ", "
                    << arg_z
                    << ", "
                    << arg_w
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLCULLFACE:
        {
            const auto arg_mode = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glCullFace("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_mode)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLDEPTHFUNC:
        {
            const auto arg_func = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glDepthFunc("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_func)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLDEPTHMASK:
        {
            const auto arg_flag = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glDepthMask("
                    << arg_flag
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLDEPTHRANGE:
        {
            const auto arg_n = in_api_command.api_arg_vec.at(0).get_fp64();
            const auto arg_f = in_api_command.api_arg_vec.at(1).get_fp64();

            sstream << "glDepthRange("
                    << arg_n
                    << ", "
                    << arg_f
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLDISABLE:
        {
            const auto arg_cap = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glDisable("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_cap)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLDRAWBUFFER:
        {
            const auto arg_mode = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glDrawBuffer("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_mode)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLENABLE:
        {
            const auto arg_cap = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glEnable("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_cap)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLEND:
        {
            sstream << "glEnd()\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLFINISH:
        {
            sstream << "glFinish()\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLFLUSH:
        {
            sstream << "glFlush()\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLFRONTFACE:
        {
            const auto arg_mode = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glFrontFace("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_mode)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLFRUSTUM:
        {
            const auto arg_left     = in_api_command.api_arg_vec.at(0).get_fp64();
            const auto arg_right    = in_api_command.api_arg_vec.at(1).get_fp64();
            const auto arg_bottom   = in_api_command.api_arg_vec.at(2).get_fp64();
            const auto arg_top      = in_api_command.api_arg_vec.at(3).get_fp64();
            const auto arg_near_val = in_api_command.api_arg_vec.at(4).get_fp64();
            const auto arg_far_val  = in_api_command.api_arg_vec.at(5).get_fp64();

            sstream << "glFrustum("
                    << arg_left
                    << ", "
                    << arg_right
                    << ", "
                    << arg_bottom
                    << ", "
                    << arg_top
                    << ", "
                    << arg_near_val
                    << ", "
                    << arg_far_val
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLLOADIDENTITY:
        {
            sstream << "glLoadIdentity()\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLMATRIXMODE:
        {
            const auto arg_mode = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glMatrixMode("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_mode)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLORTHO:
        {
            const auto arg_left     = in_api_command.api_arg_vec.at(0).get_fp64();
            const auto arg_right    = in_api_command.api_arg_vec.at(1).get_fp64();
            const auto arg_bottom   = in_api_command.api_arg_vec.at(2).get_fp64();
            const auto arg_top      = in_api_command.api_arg_vec.at(3).get_fp64();
            const auto arg_near_val = in_api_command.api_arg_vec.at(4).get_fp64();
            const auto arg_far_val  = in_api_command.api_arg_vec.at(5).get_fp64();

            sstream << "glOrtho("
                    << arg_left
                    << ", "
                    << arg_right
                    << ", "
                    << arg_bottom
                    << ", "
                    << arg_top
                    << ", "
                    << arg_near_val
                    << ", "
                    << arg_far_val
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLPOPMATRIX:
        {
            sstream << "glPopMatrix()\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLPUSHMATRIX:
        {
            sstream << "glPushMatrix()\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLROTATEF:
        {
            const auto arg_angle = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_x     = in_api_command.api_arg_vec.at(1).get_fp32();
            const auto arg_y     = in_api_command.api_arg_vec.at(2).get_fp32();
            const auto arg_z     = in_api_command.api_arg_vec.at(3).get_fp32();

            sstream << "glRotatef("
                    << arg_angle
                    << ", "
                    << arg_x
                    << ", "
                    << arg_y
                    << ", "
                    << arg_z
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLSCALEF:
        {
            const auto arg_x = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_y = in_api_command.api_arg_vec.at(1).get_fp32();
            const auto arg_z = in_api_command.api_arg_vec.at(2).get_fp32();

            sstream << "glScalef("
                    << arg_x
                    << ", "
                    << arg_y
                    << ", "
                    << arg_z
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLSHADEMODEL:
        {
            const auto arg_mode = in_api_command.api_arg_vec.at(0).get_u32();

            sstream << "glShaderModel("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_mode)
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLTEXCOORD2F:
        {
            const auto arg_s = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_t = in_api_command.api_arg_vec.at(1).get_fp32();

            sstream << "glTexCoord2f("
                    << arg_s
                    << ", "
                    << arg_t
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLTEXENVF:
        {
            const auto arg_target = in_api_command.api_arg_vec.at(0).get_u32 ();
            const auto arg_pname  = in_api_command.api_arg_vec.at(1).get_u32 ();
            const auto arg_param  = in_api_command.api_arg_vec.at(2).get_fp32();

            sstream << "glTexEnvf("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_target)
                    << ", "
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_pname)
                    << ", "
                    << OpenGL::Utils::get_raw_string_for_gl_enum(static_cast<uint32_t>(arg_param) )
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE2D:
        {
            const auto arg_target          = in_api_command.api_arg_vec.at(0).get_u32();
            const auto arg_level           = in_api_command.api_arg_vec.at(1).get_i32();
            const auto arg_internal_format = in_api_command.api_arg_vec.at(2).get_i32();
            const auto arg_width           = in_api_command.api_arg_vec.at(3).get_i32();
            const auto arg_height          = in_api_command.api_arg_vec.at(4).get_i32();
            const auto arg_border          = in_api_command.api_arg_vec.at(5).get_i32();
            const auto arg_format          = in_api_command.api_arg_vec.at(6).get_u32();
            const auto arg_type            = in_api_command.api_arg_vec.at(7).get_u32();
            const auto arg_data            = in_api_command.api_arg_vec.at(8).get_ptr();

            sstream << "glTexImage2D("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_target)
                    << ", "
                    << arg_level
                    << ", "
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_internal_format)
                    << ", "
                    << arg_width
                    << ", "
                    << arg_height
                    << ", "
                    << arg_border
                    << ", "
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_format)
                    << ", "
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_type)
                    << ", "
                    << arg_data
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLTEXPARAMETERF:
        {
            const auto arg_target = in_api_command.api_arg_vec.at(0).get_u32 ();
            const auto arg_pname  = in_api_command.api_arg_vec.at(1).get_u32 ();
            const auto arg_param  = in_api_command.api_arg_vec.at(2).get_fp32();

            sstream << "glTexParameterf("
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_target)
                    << ", "
                    << OpenGL::Utils::get_raw_string_for_gl_enum(arg_pname)
                    << ", "
                    << arg_param
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLTRANSLATEF:
        {
            const auto arg_x = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_y = in_api_command.api_arg_vec.at(1).get_fp32();
            const auto arg_z = in_api_command.api_arg_vec.at(2).get_fp32();

            sstream << "glTranslatef("
                    << arg_x
                    << ", "
                    << arg_y
                    << ", "
                    << arg_z
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLVERTEX2F:
        {
            const auto arg_x = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_y = in_api_command.api_arg_vec.at(1).get_fp32();

            sstream << "glVertex2f("
                    << arg_x
                    << ", "
                    << arg_y
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLVERTEX3F:
        {
            const auto arg_x = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_y = in_api_command.api_arg_vec.at(1).get_fp32();
            const auto arg_z = in_api_command.api_arg_vec.at(2).get_fp32();

            sstream << "glVertex3f("
                    << arg_x
                    << ", "
                    << arg_y
                    << ", "
                    << arg_z
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLVERTEX4F:
        {
            const auto arg_x = in_api_command.api_arg_vec.at(0).get_fp32();
            const auto arg_y = in_api_command.api_arg_vec.at(1).get_fp32();
            const auto arg_z = in_api_command.api_arg_vec.at(2).get_fp32();
            const auto arg_w = in_api_command.api_arg_vec.at(3).get_fp32();

            sstream << "glVertex3f("
                    << arg_x
                    << ", "
                    << arg_y
                    << ", "
                    << arg_z
                    << ", "
                    << arg_w
                    << ")\n";

            break;
        }

        case APIInterceptor::APIFUNCTION_GL_GLVIEWPORT:
        {
            const auto arg_x      = in_api_command.api_arg_vec.at(0).get_i32();
            const auto arg_y      = in_api_command.api_arg_vec.at(1).get_i32();
            const auto arg_width  = in_api_command.api_arg_vec.at(2).get_i32();
            const auto arg_height = in_api_command.api_arg_vec.at(3).get_i32();

            sstream << "glViewport("
                    << arg_x
                    << ", "
                    << arg_y
                    << ", "
                    << arg_width
                    << ", "
                    << arg_height
                    << ")\n";

            break;
        }

        default:
        {
            assert(false);
        }
    }

    *out_string_ptr = sstream.str();
}