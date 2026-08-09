#include <Windows.h>
#include <assert.h>
#include <stdio.h>
#include <string>
#include "APIDumpLoader/APIDumpLoader.h"
#include "OpenGLUtils/utils_enum.h"

const char* get_string(const APIInterceptor::APIFunction& in_func)
{
    const char* result_ptr = "?!";

    switch (in_func)
    {
        case APIInterceptor::APIFunction::APIFUNCTION_GDI32_CHOOSEPIXELFORMAT:   result_ptr = "ChoosePixelFormat";   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GDI32_DESCRIBEPIXELFORMAT: result_ptr = "DescribePixelFormat"; break;
        case APIInterceptor::APIFunction::APIFUNCTION_GDI32_GETPIXELFORMAT:      result_ptr = "GetPixelFormat";      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GDI32_SETPIXELFORMAT:      result_ptr = "SetPixelFormat";      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GDI32_SWAPBUFFERS:         result_ptr = "SwapBuffers";         break;

        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLACCUM:                                   result_ptr = "glAccum";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLACTIVETEXTURE:                           result_ptr = "glActiveTexture";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLALPHAFUNC:                               result_ptr = "glAlphaFunc";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLARETEXTURESRESIDENT:                     result_ptr = "glAreTexturesResident";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLARRAYELEMENT:                            result_ptr = "glArrayElement";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLATTACHSHADER:                            result_ptr = "glAttachShader";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBEGIN:                                   result_ptr = "glBegin";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBEGINCONDITIONALRENDER:                  result_ptr = "glBeginConditionalRender";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBEGINQUERY:                              result_ptr = "glBeginQuery";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBEGINTRANSFORMFEEDBACK:                  result_ptr = "glBeginTransformFeedback";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDATTRIBLOCATION:                      result_ptr = "glBindAttribLocation";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDBUFFER:                              result_ptr = "glBindBuffer";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDBUFFERBASE:                          result_ptr = "glBindBufferBase";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDBUFFERRANGE:                         result_ptr = "glBindBufferRange";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDFRAGDATALOCATION:                    result_ptr = "glBindFragDataLocation";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDFRAMEBUFFER:                         result_ptr = "glBindFramebuffer";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDRENDERBUFFER:                        result_ptr = "glBindRenderbuffer";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDTEXTURE:                             result_ptr = "glBindTexture";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDVERTEXARRAY:                         result_ptr = "glBindVertexArray";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBITMAP:                                  result_ptr = "glBitmap";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLENDCOLOR:                              result_ptr = "glBlendColor";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLENDEQUATION:                           result_ptr = "glBlendEquation";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLENDEQUATIONSEPARATE:                   result_ptr = "glBlendEquationSeparate";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLENDFUNC:                               result_ptr = "glBlendFunc";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLENDFUNCSEPARATE:                       result_ptr = "glBlendFuncSeparate";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLITFRAMEBUFFER:                         result_ptr = "glBlitFramebuffer";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBUFFERDATA:                              result_ptr = "glBufferData";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBUFFERSUBDATA:                           result_ptr = "glBufferSubData";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCALLLIST:                                result_ptr = "glCallList";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCALLLISTS:                               result_ptr = "glCallLists";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCHECKFRAMEBUFFERSTATUS:                  result_ptr = "glCheckFramebufferStatus";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLAMPCOLOR:                              result_ptr = "glClampColor";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEAR:                                   result_ptr = "glClear";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARACCUM:                              result_ptr = "glClearAccum";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARBUFFERFI:                           result_ptr = "glClearBufferfi";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARBUFFERFV:                           result_ptr = "glClearBufferfv";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARBUFFERUIV:                          result_ptr = "glClearBufferuiv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARCOLOR:                              result_ptr = "glClearColor";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARDEPTH:                              result_ptr = "glClearDepth";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARINDEX:                              result_ptr = "glClearIndex";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARSTENCIL:                            result_ptr = "glClearStencil";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLIENTACTIVETEXTURE:                     result_ptr = "glClientActiveTexture";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLIENTWAITSYNC:                          result_ptr = "glClientWaitSync";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLIPPLANE:                               result_ptr = "glClipPlane";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3B:                                 result_ptr = "glColor3b";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3BV:                                result_ptr = "glColor3bv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3D:                                 result_ptr = "glColor3d";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3DV:                                result_ptr = "glColor3dv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3F:                                 result_ptr = "glColor3f";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3FV:                                result_ptr = "glColor3fv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3I:                                 result_ptr = "glColor3i";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3IV:                                result_ptr = "glColor3iv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3S:                                 result_ptr = "glColor3s";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3SV:                                result_ptr = "glColor3sv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3UB:                                result_ptr = "glColor3ub";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3UBV:                               result_ptr = "glColor3ubv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3UI:                                result_ptr = "glColor3ui";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3UIV:                               result_ptr = "glColor3uiv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3US:                                result_ptr = "glColor3us";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR3USV:                               result_ptr = "glColor3usv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4B:                                 result_ptr = "glColor4b";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4BV:                                result_ptr = "glColor4bv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4D:                                 result_ptr = "glColor4d";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4DV:                                result_ptr = "glColor4dv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4F:                                 result_ptr = "glColor4f";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4FV:                                result_ptr = "glColor4fv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4I:                                 result_ptr = "glColor4i";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4IV:                                result_ptr = "glColor4iv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4S:                                 result_ptr = "glColor4s";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4SV:                                result_ptr = "glColor4sv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4UB:                                result_ptr = "glColor4ub";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4UBV:                               result_ptr = "glColor4ubv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4UI:                                result_ptr = "glColor4ui";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4UIV:                               result_ptr = "glColor4uiv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4US:                                result_ptr = "glColor4us";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLOR4USV:                               result_ptr = "glColor4usv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLORMASK:                               result_ptr = "glColorMask";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLORMASKI:                              result_ptr = "glColorMaski";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLORMATERIAL:                           result_ptr = "glColorMaterial";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOLORPOINTER:                            result_ptr = "glColorPointer";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPILESHADER:                           result_ptr = "glCompileShader";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE1D:                    result_ptr = "glCompressedTexImage1D";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE2D:                    result_ptr = "glCompressedTexImage2D";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPRESSEDTEXIMAGE3D:                    result_ptr = "glCompressedTexImage3D";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPRESSEDTEXSUBIMAGE1D:                 result_ptr = "glCompressedTexSubImage1D";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPRESSEDTEXSUBIMAGE2D:                 result_ptr = "glCompressedTexSubImage2D";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPRESSEDTEXSUBIMAGE3D:                 result_ptr = "glCompressedTexSubImage3D";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYBUFFERSUBDATA:                       result_ptr = "glCopyBufferSubData";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYPIXELS:                              result_ptr = "glCopyPixels";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYTEXIMAGE1D:                          result_ptr = "glCopyTexImage1D";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYTEXIMAGE2D:                          result_ptr = "glCopyTexImage2D";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYTEXSUBIMAGE1D:                       result_ptr = "glCopyTexSubImage1D";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYTEXSUBIMAGE2D:                       result_ptr = "glCopyTexSubImage2D";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYTEXSUBIMAGE3D:                       result_ptr = "glCopyTexSubImage3D";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATEPROGRAM:                           result_ptr = "glCreateProgram";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATESHADER:                            result_ptr = "glCreateShader";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCULLFACE:                                result_ptr = "glCullFace";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETEBUFFERS:                           result_ptr = "glDeleteBuffers";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETEFRAMEBUFFERS:                      result_ptr = "glDeleteFramebuffers";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETELISTS:                             result_ptr = "glDeleteLists";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETEPROGRAM:                           result_ptr = "glDeleteProgram";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETEQUERIES:                           result_ptr = "glDeleteQueries";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETERENDERBUFFERS:                     result_ptr = "glDeleteRenderbuffers";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETESHADER:                            result_ptr = "glDeleteShader";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETESYNC:                              result_ptr = "glDeleteSync";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETETEXTURES:                          result_ptr = "glDeleteTextures";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETEVERTEXARRAYS:                      result_ptr = "glDeleteVertexArrays";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDEPTHFUNC:                               result_ptr = "glDepthFunc";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDEPTHMASK:                               result_ptr = "glDepthMask";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDEPTHRANGE:                              result_ptr = "glDepthRange";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDETACHSHADER:                            result_ptr = "glDetachShader";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDISABLE:                                 result_ptr = "glDisable";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDISABLECLIENTSTATE:                      result_ptr = "glDisableClientState";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDISABLEVERTEXATTRIBARRAY:                result_ptr = "glDisableVertexAttribArray";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDISABLEI:                                result_ptr = "glDisablei";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWARRAYS:                              result_ptr = "glDrawArrays";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWARRAYSINSTANCED:                     result_ptr = "glDrawArraysInstanced";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWBUFFER:                              result_ptr = "glDrawBuffer";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWBUFFERS:                             result_ptr = "glDrawBuffers";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWELEMENTS:                            result_ptr = "glDrawElements";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWELEMENTSBASEVERTEX:                  result_ptr = "glDrawElementsBaseVertex";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCED:                   result_ptr = "glDrawElementsInstanced";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCEDBASEVERTEX:         result_ptr = "glDrawElementsInstancedBaseVertex";     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWPIXELS:                              result_ptr = "glDrawPixels";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWRANGEELEMENTS:                       result_ptr = "glDrawRangeElements";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWRANGEELEMENTSBASEVERTEX:             result_ptr = "glDrawRangeElementsBaseVertex";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEDGEFLAG:                                result_ptr = "glEdgeFlag";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEDGEFLAGPOINTER:                         result_ptr = "glEdgeFlagPointer";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEDGEFLAGV:                               result_ptr = "glEdgeFlagv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENABLE:                                  result_ptr = "glEnable";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENABLECLIENTSTATE:                       result_ptr = "glEnableClientState";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENABLEVERTEXATTRIBARRAY:                 result_ptr = "glEnableVertexAttribArray";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENABLEI:                                 result_ptr = "glEnablei";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEND:                                     result_ptr = "glEnd";                                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENDCONDITIONALRENDER:                    result_ptr = "glEndConditionalRender";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENDLIST:                                 result_ptr = "glEndList";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENDQUERY:                                result_ptr = "glEndQuery";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENDTRANSFORMFEEDBACK:                    result_ptr = "glEndTransformFeedback";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALCOORD1D:                             result_ptr = "glEvalCoord1d";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALCOORD1DV:                            result_ptr = "glEvalCoord1dv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALCOORD1F:                             result_ptr = "glEvalCoord1f";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALCOORD1FV:                            result_ptr = "glEvalCoord1fv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALCOORD2D:                             result_ptr = "glEvalCoord2d";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALCOORD2DV:                            result_ptr = "glEvalCoord2dv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALCOORD2F:                             result_ptr = "glEvalCoord2f";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALCOORD2FV:                            result_ptr = "glEvalCoord2fv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALMESH1:                               result_ptr = "glEvalMesh1";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALMESH2:                               result_ptr = "glEvalMesh2";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALPOINT1:                              result_ptr = "glEvalPoint1";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLEVALPOINT2:                              result_ptr = "glEvalPoint2";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFEEDBACKBUFFER:                          result_ptr = "glFeedbackBuffer";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFENCESYNC:                               result_ptr = "glFenceSync";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFINISH:                                  result_ptr = "glFinish";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFLUSH:                                   result_ptr = "glFlush";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFLUSHMAPPEDBUFFERRANGE:                  result_ptr = "glFlushMappedBufferRange";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFOGCOORDD:                               result_ptr = "glFogCoordd";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFOGCOORDDV:                              result_ptr = "glFogCoorddv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFOGCOORDF:                               result_ptr = "glFogCoordf";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFOGCOORDFV:                              result_ptr = "glFogCoordfv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFOGCOORDPOINTER:                         result_ptr = "glFogCoordPointer";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFOGF:                                    result_ptr = "glFogf";                                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFOGFV:                                   result_ptr = "glFogfv";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFOGI:                                    result_ptr = "glFogi";                                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFOGIV:                                   result_ptr = "glFogiv";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFRAMEBUFFERRENDERBUFFER:                 result_ptr = "glFramebufferRenderbuffer";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFRAMEBUFFERTEXTURE:                      result_ptr = "glFramebufferTexture";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFRAMEBUFFERTEXTURE1D:                    result_ptr = "glFramebufferTexture1D";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFRAMEBUFFERTEXTURE2D:                    result_ptr = "glFramebufferTexture2D";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFRAMEBUFFERTEXTURE3D:                    result_ptr = "glFramebufferTexture3D";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFRAMEBUFFERTEXTURELAYER:                 result_ptr = "glFramebufferTextureLayer";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFRONTFACE:                               result_ptr = "glFrontFace";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFRUSTUM:                                 result_ptr = "glFrustum";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENBUFFERS:                              result_ptr = "glGenBuffers";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENFRAMEBUFFERS:                         result_ptr = "glGenFramebuffers";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENLISTS:                                result_ptr = "glGenLists";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENQUERIES:                              result_ptr = "glGenQueries";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENRENDERBUFFERS:                        result_ptr = "glGenRenderbuffers";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENTEXTURES:                             result_ptr = "glGenTextures";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENVERTEXARRAYS:                         result_ptr = "glGenVertexArrays";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENERATEMIPMAP:                          result_ptr = "glGenerateMipmap";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVEATTRIB:                         result_ptr = "glGetActiveAttrib";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVEUNIFORM:                        result_ptr = "glGetActiveUniform";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVEUNIFORMBLOCKNAME:               result_ptr = "glGetActiveUniformBlockName";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVEUNIFORMBLOCKIV:                 result_ptr = "glGetActiveUniformBlockiv";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVEUNIFORMNAME:                    result_ptr = "glGetActiveUniformName";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVEUNIFORMSIV:                     result_ptr = "glGetActiveUniformsiv";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETATTACHEDSHADERS:                      result_ptr = "glGetAttachedShaders";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETATTRIBLOCATION:                       result_ptr = "glGetAttribLocation";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETBOOLEANI_V:                           result_ptr = "glGetBooleani_v";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETBOOLEANV:                             result_ptr = "glGetBooleanv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETBUFFERPARAMETERI64V:                  result_ptr = "glGetBufferParameteri64v";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETBUFFERPARAMETERIV:                    result_ptr = "glGetBufferParameteriv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETBUFFERPOINTERV:                       result_ptr = "glGetBufferPointerv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETBUFFERSUBDATA:                        result_ptr = "glGetBufferSubData";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETCLIPPLANE:                            result_ptr = "glGetClipPlane";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETCOMPRESSEDTEXIMAGE:                   result_ptr = "glGetCompressedTexImage";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETDOUBLEV:                              result_ptr = "glGetDoublev";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETERROR:                                result_ptr = "glGetError";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETFLOATV:                               result_ptr = "glGetFloatv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETFRAGDATALOCATION:                     result_ptr = "glGetFragDataLocation";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETFRAMEBUFFERATTACHMENTPARAMETERIV:     result_ptr = "glGetFramebufferAttachmentParameteriv"; break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETINTEGER64I_V:                         result_ptr = "glGetInteger64i_v";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETINTEGER64V:                           result_ptr = "glGetInteger64v";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETINTEGERI_V:                           result_ptr = "glGetIntegeri_v";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETINTEGERV:                             result_ptr = "glGetIntegerv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETLIGHTFV:                              result_ptr = "glGetLightfv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETLIGHTIV:                              result_ptr = "glGetLightiv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETMAPDV:                                result_ptr = "glGetMapdv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETMAPFV:                                result_ptr = "glGetMapfv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETMAPIV:                                result_ptr = "glGetMapiv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETMATERIALFV:                           result_ptr = "glGetMaterialfv";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETMATERIALIV:                           result_ptr = "glGetMaterialiv";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETMULTISAMPLEFV:                        result_ptr = "glGetMultisamplefv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPIXELMAPFV:                           result_ptr = "glGetPixelMapfv";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPIXELMAPUIV:                          result_ptr = "glGetPixelMapuiv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPIXELMAPUSV:                          result_ptr = "glGetPixelMapusv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPOINTERV:                             result_ptr = "glGetPointerv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPOLYGONSTIPPLE:                       result_ptr = "glGetPolygonStipple";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMINFOLOG:                       result_ptr = "glGetProgramInfoLog";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMIV:                            result_ptr = "glGetProgramiv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYOBJECTIV:                        result_ptr = "glGetQueryObjectiv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYOBJECTUIV:                       result_ptr = "glGetQueryObjectuiv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYIV:                              result_ptr = "glGetQueryiv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETRENDERBUFFERPARAMETERIV:              result_ptr = "glGetRenderBufferParameteriv";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSHADERINFOLOG:                        result_ptr = "glGetShaderInfoLog";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSHADERSOURCE:                         result_ptr = "glGetShaderSource";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSHADERIV:                             result_ptr = "glGetShaderiv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSTRING:                               result_ptr = "glGetString";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSTRINGI:                              result_ptr = "glGetStringi";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSYNCIV:                               result_ptr = "glGetSynciv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXENVFV:                             result_ptr = "glGetTexEnvfv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXENVIV:                             result_ptr = "glGetTexEnviv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXGENDV:                             result_ptr = "glGetTexGendv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXGENIV:                             result_ptr = "glGetTexGeniv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXIMAGE:                             result_ptr = "glGetTexImage";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXLEVELPARAMETERFV:                  result_ptr = "glGetTexLevelParameterfv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXLEVELPARAMETERIV:                  result_ptr = "glGetTexLevelParameteriv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXPARAMETERI_IV:                     result_ptr = "glGetTexParameteri_iv";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXPARAMETERI_UIV:                    result_ptr = "glGetTexParameteri_uiv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXPARAMETERFV:                       result_ptr = "glGetTexParameterfv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXPARAMETERIV:                       result_ptr = "glGetTexParameteriv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTRANSFORMFEEDBACKVARYING:             result_ptr = "glGetTransformFeedbackVarying";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETUNIFORMBLOCKINDEX:                    result_ptr = "glGetUniformBlockIndex";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETUNIFORMINDICES:                       result_ptr = "glGetUniformIndices";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETUNIFORMLOCATION:                      result_ptr = "glGetUniformLocation";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETUNIFORMFV:                            result_ptr = "glGetUniformfv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETUNIFORMIV:                            result_ptr = "glGetUniformiv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETUNIFORMUIV:                           result_ptr = "glGetUniformuiv";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXATTRIBI_IV:                     result_ptr = "glGetVertexAttribI_iv";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXATTRIBI_UIV:                    result_ptr = "glGetVertexAttribI_uiv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXATTRIBPOINTERV:                 result_ptr = "glGetVertexAttribPointerv";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXATTRIBDV:                       result_ptr = "glGetVertexAttribdv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXATTRIBFV:                       result_ptr = "glGetVertexAttribfv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXATTRIBIV:                       result_ptr = "glGetVertexAttribiv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLHINT:                                    result_ptr = "glHint";                                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXD:                                  result_ptr = "glIndexd";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXDV:                                 result_ptr = "glIndexdv";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXF:                                  result_ptr = "glIndexf";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXFV:                                 result_ptr = "glIndexfv";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXI:                                  result_ptr = "glIndexi";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXIV:                                 result_ptr = "glIndexiv";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXMASK:                               result_ptr = "glIndexMask";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXPOINTER:                            result_ptr = "glIndexPointer";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXS:                                  result_ptr = "glIndexs";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXSV:                                 result_ptr = "glIndexsv";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXUB:                                 result_ptr = "glIndexub";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINDEXUBV:                                result_ptr = "glIndexubv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINITNAMES:                               result_ptr = "glInitNames";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINTERLEAVEDARRRAYS:                      result_ptr = "glInterleavedArrays";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISBUFFER:                                result_ptr = "glIsBuffer";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISENABLED:                               result_ptr = "glIsEnabled";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISENABLEDI:                              result_ptr = "glIsEnabledi";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISFRAMEBUFFER:                           result_ptr = "glIsFramebuffer";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISLIST:                                  result_ptr = "glIsList";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISPROGRAM:                               result_ptr = "glIsProgram";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISQUERY:                                 result_ptr = "glIsQuery";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISRENDERBUFFER:                          result_ptr = "glIsRenderbuffer";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISSHADER:                                result_ptr = "glIsShader";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISSYNC:                                  result_ptr = "glIsSync";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISTEXTURE:                               result_ptr = "glIsTexture";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISVERTEXARRAY:                           result_ptr = "glIsVertexArray";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLIGHTF:                                  result_ptr = "glLightf";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLIGHTFV:                                 result_ptr = "glLightfv";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLIGHTI:                                  result_ptr = "glLighti";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLIGHTIV:                                 result_ptr = "glLightiv";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLIGHTMODELF:                             result_ptr = "glLightModelf";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLIGHTMODELFV:                            result_ptr = "glLightModelfv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLIGHTMODELI:                             result_ptr = "glLightModeli";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLIGHTMODELIV:                            result_ptr = "glLightModeliv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLINESTIPPLE:                             result_ptr = "glLineStipple";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLINEWIDTH:                               result_ptr = "glLineWidth";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLINKPROGRAM:                             result_ptr = "glLinkProgram";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLISTBASE:                                result_ptr = "glListBase";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLOADIDENTITY:                            result_ptr = "glLoadIdentity";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLOADMATRIXD:                             result_ptr = "glLoadMatrixd";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLOADMATRIXF:                             result_ptr = "glLoadMatrixf";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLOADNAME:                                result_ptr = "glLoadName";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLOADTRANSPOSEMATRIXD:                    result_ptr = "glLoadTransposeMatrixd";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLOADTRANSPOSEMATRIXF:                    result_ptr = "glLoadTransposeMatrixf";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLLOGICOP:                                 result_ptr = "glLogicOp";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAP1D:                                   result_ptr = "glMap1d";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAP1F:                                   result_ptr = "glMap1f";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAP2D:                                   result_ptr = "glMap2d";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAP2F:                                   result_ptr = "glMap2f";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAPGRID1D:                               result_ptr = "glMapGrid1d";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAPGRID1F:                               result_ptr = "glMapGrid1f";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAPGRID2D:                               result_ptr = "glMapGrid2d";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAPGRID2F:                               result_ptr = "glMapGrid2f";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMATERIALF:                               result_ptr = "glMaterialf";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMATERIALFV:                              result_ptr = "glMaterialfv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMATERIALI:                               result_ptr = "glMateriali";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMATERIALIV:                              result_ptr = "glMaterialiv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMATRIXMODE:                              result_ptr = "glMatrixMode";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTMATRIXD:                             result_ptr = "glMultMatrixd";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTMATRIXF:                             result_ptr = "glMultMatrixf";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTIDRAWARRAYS:                         result_ptr = "glMultiDrawArrays";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTIDRAWELEMENTS:                       result_ptr = "glMultIDrawElements";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTIDRAWELEMENTSBASEVERTEX:             result_ptr = "glMultIDrawElementsBaseVertex";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD1D:                         result_ptr = "glMultiTexCoord1d";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD1DV:                        result_ptr = "glMultiTexCoord1dv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD1F:                         result_ptr = "glMultiTexCoord1f";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD1FV:                        result_ptr = "glMultiTexCoord1fv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD1I:                         result_ptr = "glMultiTexCoord1i";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD1IV:                        result_ptr = "glMultiTexCoord1iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD1S:                         result_ptr = "glMultiTexCoord1s";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD1SV:                        result_ptr = "glMultiTexCoord1sv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD2D:                         result_ptr = "glMultiTexCoord2d";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD2DV:                        result_ptr = "glMultiTexCoord2dv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD2F:                         result_ptr = "glMultiTexCoord2f";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD2FV:                        result_ptr = "glMultiTexCoord2fv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD2I:                         result_ptr = "glMultiTexCoord2i";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD2IV:                        result_ptr = "glMultiTexCoord2iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD2S:                         result_ptr = "glMultiTexCoord2s";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD2SV:                        result_ptr = "glMultiTexCoord2sv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD3D:                         result_ptr = "glMultiTexCoord3d";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD3DV:                        result_ptr = "glMultiTexCoord3dv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD3F:                         result_ptr = "glMultiTexCoord3f";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD3FV:                        result_ptr = "glMultiTexCoord3fv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD3I:                         result_ptr = "glMultiTexCoord3i";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD3IV:                        result_ptr = "glMultiTexCoord3iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD3S:                         result_ptr = "glMultiTexCoord3s";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD3SV:                        result_ptr = "glMultiTexCoord3sv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD4D:                         result_ptr = "glMultiTexCoord4d";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD4DV:                        result_ptr = "glMultiTexCoord4dv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD4F:                         result_ptr = "glMultiTexCoord4f";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD4FV:                        result_ptr = "glMultiTexCoord4fv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD4I:                         result_ptr = "glMultiTexCoord4i";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD4IV:                        result_ptr = "glMultiTexCoord4iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD4S:                         result_ptr = "glMultiTexCoord4s";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTITEXCOORD4SV:                        result_ptr = "glMultiTexCoord4sv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTTRANSPOSEMATRIXD:                    result_ptr = "glMultTransposeMatrixd";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTTRANSPOSEMATRIXF:                    result_ptr = "glMultTransposeMatrixf";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNEWLIST:                                 result_ptr = "glNewList";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3B:                                result_ptr = "glNormal3b";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3BV:                               result_ptr = "glNormal3bv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3D:                                result_ptr = "glNormal3d";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3DV:                               result_ptr = "glNormal3dv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3F:                                result_ptr = "glNormal3f";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3FV:                               result_ptr = "glNormal3fv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3I:                                result_ptr = "glNormal3i";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3IV:                               result_ptr = "glNormal3iv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3S:                                result_ptr = "glNormal3s";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMAL3SV:                               result_ptr = "glNormal3sv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNORMALPOINTER:                           result_ptr = "glNormalPointer";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLORTHO:                                   result_ptr = "glOrtho";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPASSTHROUGH:                             result_ptr = "glPassThrough";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPIXELMAPFV:                              result_ptr = "glPixelMapfv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPIXELMAPUIV:                             result_ptr = "glPixelMapuiv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPIXELMAPUSV:                             result_ptr = "glPixelMapusv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPIXELSTOREF:                             result_ptr = "glPixelStoref";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPIXELSTOREI:                             result_ptr = "glPixelStorei";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPIXELTRANSFERF:                          result_ptr = "glPixelTransferf";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPIXELTRANSFERI:                          result_ptr = "glPixelTransferi";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPIXELZOOM:                               result_ptr = "glPixelZoom";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOINTPARAMETERF:                         result_ptr = "glPointParameterf";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOINTPARAMETERFV:                        result_ptr = "glPointParameterfv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOINTPARAMETERI:                         result_ptr = "glPointParameteri";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOINTPARAMETERIV:                        result_ptr = "glPointParameteriv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOINTSIZE:                               result_ptr = "glPointSize";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOLYGONMODE:                             result_ptr = "glPolygonMode";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOLYGONOFFSET:                           result_ptr = "glPolygonOffset";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOLYGONSTIPPLE:                          result_ptr = "glPolygonStipple";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOPATTRIB:                               result_ptr = "glPopAttrib";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOPCLIENTATTRIB:                         result_ptr = "glPopClientAttrib";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOPMATRIX:                               result_ptr = "glPopMatrix";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOPNAME:                                 result_ptr = "glPopName";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPRIMITIVERESTARTINDEX:                   result_ptr = "glPrimitiveRestartIndex";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPRIORITIZETEXTURES:                      result_ptr = "glPrioritizeTextures";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROVOKINGVERTEX:                         result_ptr = "glProvokingVertex";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPUSHATTRIB:                              result_ptr = "glPushAttrib";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPUSHCLIENTATTRIB:                        result_ptr = "glPushClientAttrib";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPUSHMATRIX:                              result_ptr = "glPushMatrix";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPUSHNAME:                                result_ptr = "glPushName";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS2D:                             result_ptr = "glRasterPos2d";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS2DV:                            result_ptr = "glRasterPos2dv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS2F:                             result_ptr = "glRasterPos2f";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS2FV:                            result_ptr = "glRasterPos2fv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS2I:                             result_ptr = "glRasterPos2i";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS2IV:                            result_ptr = "glRasterPos2iv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS2S:                             result_ptr = "glRasterPos2s";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS2SV:                            result_ptr = "glRasterPos2sv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS3D:                             result_ptr = "glRasterPos3d";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS3DV:                            result_ptr = "glRasterPos3dv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS3F:                             result_ptr = "glRasterPos3f";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS3FV:                            result_ptr = "glRasterPos3fv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS3I:                             result_ptr = "glRasterPos3i";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS3IV:                            result_ptr = "glRasterPos3iv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS3S:                             result_ptr = "glRasterPos3s";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS3SV:                            result_ptr = "glRasterPos3sv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS4D:                             result_ptr = "glRasterPos4d";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS4DV:                            result_ptr = "glRasterPos4dv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS4F:                             result_ptr = "glRasterPos4f";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS4FV:                            result_ptr = "glRasterPos4fv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS4I:                             result_ptr = "glRasterPos4i";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS4IV:                            result_ptr = "glRasterPos4iv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS4S:                             result_ptr = "glRasterPos4s";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRASTERPOS4SV:                            result_ptr = "glRasterPos4sv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLREADBUFFER:                              result_ptr = "glReadBuffer";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLREADPIXELS:                              result_ptr = "glReadPixels";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRECTD:                                   result_ptr = "glRectd";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRECTDV:                                  result_ptr = "glRectdv";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRECTF:                                   result_ptr = "glRectf";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRECTFV:                                  result_ptr = "glRectfv";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRECTI:                                   result_ptr = "glRecti";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRECTIV:                                  result_ptr = "glRectiv";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRECTS:                                   result_ptr = "glRects";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRECTSV:                                  result_ptr = "glRectsv";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRENDERMODE:                              result_ptr = "glRenderMode";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRENDERBUFFERSTORAGE:                     result_ptr = "glRenderbufferStorage";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRENDERBUFFERSTORAGEMULTISAMPLE:          result_ptr = "glRenderbufferStorageMultisample";      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLROTATED:                                 result_ptr = "glRotated";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLROTATEF:                                 result_ptr = "glRotatef";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSAMPLECOVERAGE:                          result_ptr = "glSampleCoverage";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSAMPLEMASKI:                             result_ptr = "glSampleMaski";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSCALED:                                  result_ptr = "glScaled";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSCALEF:                                  result_ptr = "glScalef";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSCISSOR:                                 result_ptr = "glScissor";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3B:                        result_ptr = "glSecondaryColor3b";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3BV:                       result_ptr = "glSecondaryColor3bv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3D:                        result_ptr = "glSecondaryColor3d";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3DV:                       result_ptr = "glSecondaryColor3dv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3F:                        result_ptr = "glSecondaryColor3f";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3FV:                       result_ptr = "glSecondaryColor3fv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3I:                        result_ptr = "glSecondaryColor3i";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3IV:                       result_ptr = "glSecondaryColor3iv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3S:                        result_ptr = "glSecondaryColor3s";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3SV:                       result_ptr = "glSecondaryColor3sv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3UB:                       result_ptr = "glSecondaryColor3ub";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3UBV:                      result_ptr = "glSecondaryColor3ubv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3UI:                       result_ptr = "glSecondaryColor3ui";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3UIV:                      result_ptr = "glSecondaryColor3uiv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3US:                       result_ptr = "glSecondaryColor3us";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLOR3USV:                      result_ptr = "glSecondaryColor3usv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSECONDARYCOLORPOINTER:                   result_ptr = "glSecondaryColorPointer";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSELECTBUFFER:                            result_ptr = "glSelectBuffer";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSHADEMODEL:                              result_ptr = "glShadeModel";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSHADERSOURCE:                            result_ptr = "glShaderSource";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSTENCILFUNC:                             result_ptr = "glStencilFunc";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSTENCILFUNCSEPARATE:                    result_ptr = "glStencilFuncSeparate";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSTENCILMASK:                             result_ptr = "glStencilMask";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSTENCILMASKSEPARATE:                     result_ptr = "glStencilMaskSeparate";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSTENCILOP:                               result_ptr = "glStencilOp";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSTENCILOPSEPARATE:                       result_ptr = "glStencilOpSeparate";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXBUFFER:                               result_ptr = "glTexBuffer";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD1D:                              result_ptr = "glTexCoord1d";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD1DV:                             result_ptr = "glTexCoord1dv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD1F:                              result_ptr = "glTexCoord1f";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD1FV:                             result_ptr = "glTexCoord1fv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD1I:                              result_ptr = "glTexCoord1i";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD1IV:                             result_ptr = "glTexCoord1iv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD1S:                              result_ptr = "glTexCoord1s";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD1SV:                             result_ptr = "glTexCoord1sv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD2D:                              result_ptr = "glTexCoord2d";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD2DV:                             result_ptr = "glTexCoord2dv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD2F:                              result_ptr = "glTexCoord2f";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD2FV:                             result_ptr = "glTexCoord2fv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD2I:                              result_ptr = "glTexCoord2i";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD2IV:                             result_ptr = "glTexCoord2iv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD2S:                              result_ptr = "glTexCoord2s";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD2SV:                             result_ptr = "glTexCoord2sv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD3D:                              result_ptr = "glTexCoord3d";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD3DV:                             result_ptr = "glTexCoord3dv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD3F:                              result_ptr = "glTexCoord3f";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD3FV:                             result_ptr = "glTexCoord3fv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD3I:                              result_ptr = "glTexCoord3i";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD3IV:                             result_ptr = "glTexCoord3iv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD3S:                              result_ptr = "glTexCoord3s";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD3SV:                             result_ptr = "glTexCoord3sv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD4D:                              result_ptr = "glTexCoord4d";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD4DV:                             result_ptr = "glTexCoord4dv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD4F:                              result_ptr = "glTexCoord4f";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD4FV:                             result_ptr = "glTexCoord4fv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD4I:                              result_ptr = "glTexCoord4i";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD4IV:                             result_ptr = "glTexCoord4iv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD4S:                              result_ptr = "glTexCoord4s";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORD4SV:                             result_ptr = "glTexCoord4sv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXCOORDPOINTER:                         result_ptr = "glTexCoordPointer";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXENVF:                                 result_ptr = "glTexEnvf";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXENVFV:                                result_ptr = "glTexEnvfv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXENVI:                                 result_ptr = "glTexEnvi";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXENVIV:                                result_ptr = "glTexEnviv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXGEND:                                 result_ptr = "glTexGend";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXGENDV:                                result_ptr = "glTexGendv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXGENI:                                 result_ptr = "glTexGeni";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXGENIV:                                result_ptr = "glTexGeniv";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXIMAGE1D:                              result_ptr = "glTexImage1D";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXIMAGE2D:                              result_ptr = "glTexImage2D";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXIMAGE2DMULTISMAPLE:                   result_ptr = "glTexImage2DMultisample";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXIMAGE3D:                              result_ptr = "glTexImage3D";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXIMAGE3DMULTISMAPLE:                   result_ptr = "glTexImage3DMultisample";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXPARAMETERI_IV:                        result_ptr = "glTexParameterI_iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXPARAMETERI_IUIV:                      result_ptr = "glTexParameterI_iuiv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXPARAMETERF:                           result_ptr = "glTexParameterf";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXPARAMETERFV:                          result_ptr = "glTexParameterfv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXPARAMETERI:                           result_ptr = "glTexParameteri";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXPARAMETERIV:                          result_ptr = "glTexParameteriv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXSUBIMAGE1D:                           result_ptr = "glTexSubImage1D";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXSUBIMAGE2D:                           result_ptr = "glTexSubImage2D";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXSUBIMAGE3D:                           result_ptr = "glTexSubImage3D";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTRANSFORMFEEDBACKVARYINGS:               result_ptr = "glTransformFeedbackVaryings";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTRANSLATED:                              result_ptr = "glTranslated";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTRANSLATEF:                              result_ptr = "glTranslatef";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM1F:                               result_ptr = "glUniform1f";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM1FV:                              result_ptr = "glUniform1fv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM1I:                               result_ptr = "glUniform1i";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM1IV:                              result_ptr = "glUniform1iv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM1UI:                              result_ptr = "glUniform1ui";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM1UIV:                             result_ptr = "glUniform1uiv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM2F:                               result_ptr = "glUniform2f";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM2FV:                              result_ptr = "glUniform2fv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM2I:                               result_ptr = "glUniform2i";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM2IV:                              result_ptr = "glUniform2iv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM2UI:                              result_ptr = "glUniform2ui";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM2UIV:                             result_ptr = "glUniform2uiv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM3F:                               result_ptr = "glUniform3f";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM3FV:                              result_ptr = "glUniform3fv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM3I:                               result_ptr = "glUniform3i";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM3IV:                              result_ptr = "glUniform3iv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM3UI:                              result_ptr = "glUniform3ui";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM3UIV:                             result_ptr = "glUniform3uiv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM4F:                               result_ptr = "glUniform4f";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM4FV:                              result_ptr = "glUniform4fv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM4I:                               result_ptr = "glUniform4i";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM4IV:                              result_ptr = "glUniform4iv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM4UI:                              result_ptr = "glUniform4ui";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM4UIV:                             result_ptr = "glUniform4uiv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMBLOCKBINDING:                     result_ptr = "glUniformBlockBinding";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX2FV:                        result_ptr = "glUniformMatrix2fv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX2X3FV:                      result_ptr = "glUniformMatrix2x3fv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX2X4FV:                      result_ptr = "glUniformMatrix2x4fv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX3FV:                        result_ptr = "glUniformMatrix3fv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX3X2FV:                      result_ptr = "glUniformMatrix3x2fv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX3X4FV:                      result_ptr = "glUniformMatrix3x4fv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX4FV:                        result_ptr = "glUniformMatrix4fv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX4X2FV:                      result_ptr = "glUniformMatrix4x2fv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX4X3FV:                      result_ptr = "glUniformMatrix4x3fv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAPBUFFER:                               result_ptr = "glMapBuffer";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNMAPBUFFER:                             result_ptr = "glUnmapBuffer";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUSEPROGRAM:                              result_ptr = "glUseProgram";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVALIDATEPROGRAM:                         result_ptr = "glValidateProgram";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX2D:                                result_ptr = "glVertex2d";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX2DV:                               result_ptr = "glVertex2dv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX2F:                                result_ptr = "glVertex2f";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX2FV:                               result_ptr = "glVertex2fv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX2I:                                result_ptr = "glVertex2i";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX2IV:                               result_ptr = "glVertex2iv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX2S:                                result_ptr = "glVertex2s";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX2SV:                               result_ptr = "glVertex2sv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX3D:                                result_ptr = "glVertex3d";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX3DV:                               result_ptr = "glVertex3dv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX3F:                                result_ptr = "glVertex3f";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX3FV:                               result_ptr = "glVertex3fv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX3I:                                result_ptr = "glVertex3i";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX3IV:                               result_ptr = "glVertex3iv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX3S:                                result_ptr = "glVertex3s";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX3SV:                               result_ptr = "glVertex3sv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX4D:                                result_ptr = "glVertex4d";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX4DV:                               result_ptr = "glVertex4dv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX4F:                                result_ptr = "glVertex4f";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX4FV:                               result_ptr = "glVertex4fv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX4I:                                result_ptr = "glVertex4i";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX4IV:                               result_ptr = "glVertex4iv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX4S:                                result_ptr = "glVertex4s";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEX4SV:                               result_ptr = "glVertex4sv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB1D:                          result_ptr = "glVertexAttrib1d";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB1DV:                         result_ptr = "glVertexAttrib1dv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB1F:                          result_ptr = "glVertexAttrib1f";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB1FV:                         result_ptr = "glVertexAttrib1fv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB1S:                          result_ptr = "glVertexAttrib1s";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB1SV:                         result_ptr = "glVertexAttrib1sv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB2D:                          result_ptr = "glVertexAttrib2d";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB2DV:                         result_ptr = "glVertexAttrib2dv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB2F:                          result_ptr = "glVertexAttrib2f";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB2FV:                         result_ptr = "glVertexAttrib2fv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB2S:                          result_ptr = "glVertexAttrib2s";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB2SV:                         result_ptr = "glVertexAttrib2sv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB3D:                          result_ptr = "glVertexAttrib3d";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB3DV:                         result_ptr = "glVertexAttrib3dv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB3F:                          result_ptr = "glVertexAttrib3f";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB3FV:                         result_ptr = "glVertexAttrib3fv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB3S:                          result_ptr = "glVertexAttrib3s";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB3SV:                         result_ptr = "glVertexAttrib3sv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4BV:                         result_ptr = "glVertexAttrib4bv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4D:                          result_ptr = "glVertexAttrib4d";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4DV:                         result_ptr = "glVertexAttrib4dv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4F:                          result_ptr = "glVertexAttrib4f";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4FV:                         result_ptr = "glVertexAttrib4fv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4S:                          result_ptr = "glVertexAttrib4s";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4SV:                         result_ptr = "glVertexAttrib4sv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4IV:                         result_ptr = "glVertexAttrib4iv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4UBV:                        result_ptr = "glVertexAttrib4ubv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4UIV:                        result_ptr = "glVertexAttrib4uiv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4USV:                        result_ptr = "glVertexAttrib4usv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4NBV:                        result_ptr = "glVertexAttrib4Nbv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4NIV:                        result_ptr = "glVertexAttrib4Niv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4NSV:                        result_ptr = "glVertexAttrib4Nsv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4NUB:                        result_ptr = "glVertexAttrib4Nub";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4NUBV:                       result_ptr = "glVertexAttrib4Nubv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4NUIV:                       result_ptr = "glVertexAttrib4Nuiv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB4NUSV:                       result_ptr = "glVertexAttrib4Nusv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I1I:                        result_ptr = "glVertexAttribI1i";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I1IV:                       result_ptr = "glVertexAttribI1iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I1UI:                       result_ptr = "glVertexAttribI1ui";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I1UIV:                      result_ptr = "glVertexAttribI1uiv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I2I:                        result_ptr = "glVertexAttribI2i";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I2IV:                       result_ptr = "glVertexAttribI2iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I2UI:                       result_ptr = "glVertexAttribI2ui";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I2UIV:                      result_ptr = "glVertexAttribI2uiv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I3I:                        result_ptr = "glVertexAttribI3i";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I3IV:                       result_ptr = "glVertexAttribI3iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I3UI:                       result_ptr = "glVertexAttribI3ui";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I3UIV:                      result_ptr = "glVertexAttribI3uiv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I4BV:                       result_ptr = "glVertexAttribI4bv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I4I:                        result_ptr = "glVertexAttribI4i";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I4IV:                       result_ptr = "glVertexAttribI4iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I4SV:                       result_ptr = "glVertexAttribI4sv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I4UBV:                      result_ptr = "glVertexAttribI4ubv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I4UI:                       result_ptr = "glVertexAttribI4ui";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I4UIV:                      result_ptr = "glVertexAttribI4uiv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_I4USV:                      result_ptr = "glVertexAttribI4usv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIB_IPOINTER:                   result_ptr = "glVertexAttribIPointer";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBPOINTER:                     result_ptr = "glVertexAttribPointer";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXPOINTER:                           result_ptr = "glVertexPointer";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVIEWPORT:                                result_ptr = "glViewport";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWAITSYNC:                                result_ptr = "glWaitSync";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS2D:                             result_ptr = "glWindowPos2d";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS2DV:                            result_ptr = "glWindowPos2dv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS2F:                             result_ptr = "glWindowPos2f";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS2FV:                            result_ptr = "glWindowPos2fv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS2I:                             result_ptr = "glWindowPos2i";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS2IV:                            result_ptr = "glWindowPos2iv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS2S:                             result_ptr = "glWindowPos2s";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS2SV:                            result_ptr = "glWindowPos2sv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS3D:                             result_ptr = "glWindowPos3d";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS3DV:                            result_ptr = "glWindowPos3dv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS3F:                             result_ptr = "glWindowPos3f";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS3FV:                            result_ptr = "glWindowPos3fv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS3I:                             result_ptr = "glWindowPos3i";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS3IV:                            result_ptr = "glWindowPos3iv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS3S:                             result_ptr = "glWindowPos3s";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLWINDOWPOS3SV:                            result_ptr = "glWindowPos3sv";                        break;

        /* GL 3.3 */
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDFRAGDATALOCATIONINDEXED: result_ptr = "glBindFragDataLocationIndexed"; break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDSAMPLER:                 result_ptr = "glBindSampler";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETESAMPLERS:              result_ptr = "glDeleteSamplers";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENSAMPLERS:                 result_ptr = "glGenSamplers";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETFRAGDATAINDEX:            result_ptr = "glGetFragDataIndex";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYOBJECTI64V:          result_ptr = "glGetQueryObjecti64v";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYOBJECTUI64V:         result_ptr = "glGetQueryObjectui64v";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSAMPLERPARAMETERFV:       result_ptr = "glGetSamplerParameterfv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSAMPLERPARAMETERIIV:      result_ptr = "glGetSamplerParameterIiv";      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSAMPLERPARAMETERIUIV:     result_ptr = "glGetSamplerParameterIuiv";     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSAMPLERPARAMETERIV:       result_ptr = "glGetSamplerParameteriv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISSAMPLER:                   result_ptr = "glIsSampler";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLQUERYCOUNTER:                result_ptr = "glQueryCounter";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSAMPLERPARAMETERF:           result_ptr = "glSamplerParameterf";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSAMPLERPARAMETERFV:          result_ptr = "glSamplerParameterfv";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSAMPLERPARAMETERI:           result_ptr = "glSamplerParameteri";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSAMPLERPARAMETERIIV:         result_ptr = "glSamplerParameterIiv";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSAMPLERPARAMETERIUIV:        result_ptr = "glSamplerParameterIuiv";        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSAMPLERPARAMETERIV:          result_ptr = "glSamplerParameteriv";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBDIVISOR:         result_ptr = "glVertexAttribDivisor";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBP1UI:            result_ptr = "glVertexAttribP1ui";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBP1UIV:           result_ptr = "glVertexAttribP1uiv";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBP2UI:            result_ptr = "glVertexAttribP2ui";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBP2UIV:           result_ptr = "glVertexAttribP2uiv";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBP3UI:            result_ptr = "glVertexAttribP3ui";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBP3UIV:           result_ptr = "glVertexAttribP3uiv";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBP4UI:            result_ptr = "glVertexAttribP4ui";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBP4UIV:           result_ptr = "glVertexAttribP4uiv";           break;

        /* GL 3.2 (missing entries) */
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXIMAGE2DMULTISAMPLE:       result_ptr = "glTexImage2DMultisample";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXIMAGE3DMULTISAMPLE:       result_ptr = "glTexImage3DMultisample";       break;

        /* GL 4.0 */
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBEGINQUERYINDEXED:               result_ptr = "glBeginQueryIndexed";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDTRANSFORMFEEDBACK:           result_ptr = "glBindTransformFeedback";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLENDEQUATIONI:                  result_ptr = "glBlendEquationi";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLENDEQUATIONSEPARATEI:          result_ptr = "glBlendEquationSeparatei";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLENDFUNCI:                      result_ptr = "glBlendFunci";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLENDFUNCSEPARATEI:              result_ptr = "glBlendFuncSeparatei";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETETRANSFORMFEEDBACKS:        result_ptr = "glDeleteTransformFeedbacks";        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWARRAYSINDIRECT:              result_ptr = "glDrawArraysIndirect";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWELEMENTSINDIRECT:            result_ptr = "glDrawElementsIndirect";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWTRANSFORMFEEDBACK:           result_ptr = "glDrawTransformFeedback";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWTRANSFORMFEEDBACKSTREAM:     result_ptr = "glDrawTransformFeedbackStream";     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENDQUERYINDEXED:                 result_ptr = "glEndQueryIndexed";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENTRANSFORMFEEDBACKS:           result_ptr = "glGenTransformFeedbacks";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVESUBROUTINENAME:         result_ptr = "glGetActiveSubroutineName";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVESUBROUTINEUNIFORMIV:    result_ptr = "glGetActiveSubroutineUniformiv";    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVESUBROUTINEUNIFORMNAME:  result_ptr = "glGetActiveSubroutineUniformName";  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMSTAGEIV:               result_ptr = "glGetProgramStageiv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYINDEXEDIV:               result_ptr = "glGetQueryIndexediv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSUBROUTINEINDEX:              result_ptr = "glGetSubroutineIndex";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSUBROUTINEUNIFORMLOCATION:    result_ptr = "glGetSubroutineUniformLocation";    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETUNIFORMDV:                    result_ptr = "glGetUniformdv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETUNIFORMSUBROUTINEUIV:         result_ptr = "glGetUniformSubroutineuiv";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISTRANSFORMFEEDBACK:             result_ptr = "glIsTransformFeedback";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMINSAMPLESHADING:                result_ptr = "glMinSampleShading";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPATCHPARAMETERFV:                result_ptr = "glPatchParameterfv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPATCHPARAMETERI:                 result_ptr = "glPatchParameteri";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPAUSETRANSFORMFEEDBACK:          result_ptr = "glPauseTransformFeedback";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRESUMETRANSFORMFEEDBACK:         result_ptr = "glResumeTransformFeedback";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM1D:                       result_ptr = "glUniform1d";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM1DV:                      result_ptr = "glUniform1dv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM2D:                       result_ptr = "glUniform2d";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM2DV:                      result_ptr = "glUniform2dv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM3D:                       result_ptr = "glUniform3d";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM3DV:                      result_ptr = "glUniform3dv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM4D:                       result_ptr = "glUniform4d";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORM4DV:                      result_ptr = "glUniform4dv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX2DV:                result_ptr = "glUniformMatrix2dv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX2X3DV:              result_ptr = "glUniformMatrix2x3dv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX2X4DV:              result_ptr = "glUniformMatrix2x4dv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX3DV:                result_ptr = "glUniformMatrix3dv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX3X2DV:              result_ptr = "glUniformMatrix3x2dv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX3X4DV:              result_ptr = "glUniformMatrix3x4dv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX4DV:                result_ptr = "glUniformMatrix4dv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX4X2DV:              result_ptr = "glUniformMatrix4x2dv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMMATRIX4X3DV:              result_ptr = "glUniformMatrix4x3dv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNIFORMSUBROUTINESUIV:           result_ptr = "glUniformSubroutinesuiv";           break;

        /* GL 4.1 */
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLACTIVESHADERPROGRAM:             result_ptr = "glActiveShaderProgram";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDPROGRAMPIPELINE:             result_ptr = "glBindProgramPipeline";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARDEPTHF:                     result_ptr = "glClearDepthf";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATESHADERPROGRAMV:            result_ptr = "glCreateShaderProgramv";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDELETEPROGRAMPIPELINES:          result_ptr = "glDeleteProgramPipelines";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDEPTHRANGEARRAYV:                result_ptr = "glDepthRangeArrayv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDEPTHRANGEF:                     result_ptr = "glDepthRangef";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDEPTHRANGEINDEXED:               result_ptr = "glDepthRangeIndexed";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENPROGRAMPIPELINES:             result_ptr = "glGenProgramPipelines";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETDOUBLEI_V:                    result_ptr = "glGetDoublei_v";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETFLOATI_V:                     result_ptr = "glGetFloati_v";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMBINARY:                result_ptr = "glGetProgramBinary";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMPIPELINEINFOLOG:       result_ptr = "glGetProgramPipelineInfoLog";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMPIPELINEIV:            result_ptr = "glGetProgramPipelineiv";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETSHADERPRECISIONFORMAT:        result_ptr = "glGetShaderPrecisionFormat";        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXATTRIBLDV:              result_ptr = "glGetVertexAttribLdv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLISPROGRAMPIPELINE:               result_ptr = "glIsProgramPipeline";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMBINARY:                   result_ptr = "glProgramBinary";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMPARAMETERI:               result_ptr = "glProgramParameteri";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM1D:                result_ptr = "glProgramUniform1d";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM1DV:               result_ptr = "glProgramUniform1dv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM1F:                result_ptr = "glProgramUniform1f";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM1FV:               result_ptr = "glProgramUniform1fv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM1I:                result_ptr = "glProgramUniform1i";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM1IV:               result_ptr = "glProgramUniform1iv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM1UI:               result_ptr = "glProgramUniform1ui";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM1UIV:              result_ptr = "glProgramUniform1uiv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM2D:                result_ptr = "glProgramUniform2d";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM2DV:               result_ptr = "glProgramUniform2dv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM2F:                result_ptr = "glProgramUniform2f";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM2FV:               result_ptr = "glProgramUniform2fv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM2I:                result_ptr = "glProgramUniform2i";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM2IV:               result_ptr = "glProgramUniform2iv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM2UI:               result_ptr = "glProgramUniform2ui";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM2UIV:              result_ptr = "glProgramUniform2uiv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM3D:                result_ptr = "glProgramUniform3d";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM3DV:               result_ptr = "glProgramUniform3dv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM3F:                result_ptr = "glProgramUniform3f";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM3FV:               result_ptr = "glProgramUniform3fv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM3I:                result_ptr = "glProgramUniform3i";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM3IV:               result_ptr = "glProgramUniform3iv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM3UI:               result_ptr = "glProgramUniform3ui";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM3UIV:              result_ptr = "glProgramUniform3uiv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM4D:                result_ptr = "glProgramUniform4d";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM4DV:               result_ptr = "glProgramUniform4dv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM4F:                result_ptr = "glProgramUniform4f";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM4FV:               result_ptr = "glProgramUniform4fv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM4I:                result_ptr = "glProgramUniform4i";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM4IV:               result_ptr = "glProgramUniform4iv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM4UI:               result_ptr = "glProgramUniform4ui";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORM4UIV:              result_ptr = "glProgramUniform4uiv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX2DV:         result_ptr = "glProgramUniformMatrix2dv";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX2FV:         result_ptr = "glProgramUniformMatrix2fv";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX2X3DV:       result_ptr = "glProgramUniformMatrix2x3dv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX2X3FV:       result_ptr = "glProgramUniformMatrix2x3fv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX2X4DV:       result_ptr = "glProgramUniformMatrix2x4dv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX2X4FV:       result_ptr = "glProgramUniformMatrix2x4fv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX3DV:         result_ptr = "glProgramUniformMatrix3dv";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX3FV:         result_ptr = "glProgramUniformMatrix3fv";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX3X2DV:       result_ptr = "glProgramUniformMatrix3x2dv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX3X2FV:       result_ptr = "glProgramUniformMatrix3x2fv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX3X4DV:       result_ptr = "glProgramUniformMatrix3x4dv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX3X4FV:       result_ptr = "glProgramUniformMatrix3x4fv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX4DV:         result_ptr = "glProgramUniformMatrix4dv";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX4FV:         result_ptr = "glProgramUniformMatrix4fv";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX4X2DV:       result_ptr = "glProgramUniformMatrix4x2dv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX4X2FV:       result_ptr = "glProgramUniformMatrix4x2fv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX4X3DV:       result_ptr = "glProgramUniformMatrix4x3dv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPROGRAMUNIFORMMATRIX4X3FV:       result_ptr = "glProgramUniformMatrix4x3fv";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLRELEASESHADERCOMPILER:           result_ptr = "glReleaseShaderCompiler";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSCISSORARRAYV:                   result_ptr = "glScissorArrayv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSCISSORINDEXED:                  result_ptr = "glScissorIndexed";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSCISSORINDEXEDV:                 result_ptr = "glScissorIndexedv";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSHADERBINARY:                    result_ptr = "glShaderBinary";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUSEPROGRAMSTAGES:                result_ptr = "glUseProgramStages";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVALIDATEPROGRAMPIPELINE:         result_ptr = "glValidateProgramPipeline";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBL1D:                 result_ptr = "glVertexAttribL1d";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBL1DV:                result_ptr = "glVertexAttribL1dv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBL2D:                 result_ptr = "glVertexAttribL2d";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBL2DV:                result_ptr = "glVertexAttribL2dv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBL3D:                 result_ptr = "glVertexAttribL3d";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBL3DV:                result_ptr = "glVertexAttribL3dv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBL4D:                 result_ptr = "glVertexAttribL4d";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBL4DV:                result_ptr = "glVertexAttribL4dv";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBLPOINTER:            result_ptr = "glVertexAttribLPointer";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVIEWPORTARRAYV:                  result_ptr = "glViewportArrayv";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVIEWPORTINDEXEDF:                result_ptr = "glViewportIndexedf";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVIEWPORTINDEXEDFV:               result_ptr = "glViewportIndexedfv";               break;

        /* GL 4.2 */
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDIMAGETEXTURE:                          result_ptr = "glBindImageTexture";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWARRAYSINSTANCEDBASEINSTANCE:           result_ptr = "glDrawArraysInstancedBaseInstance";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCEDBASEINSTANCE:         result_ptr = "glDrawElementsInstancedBaseInstance";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWELEMENTSINSTANCEDBASEVERTEXBASEINSTANCE: result_ptr = "glDrawElementsInstancedBaseVertexBaseInstance"; break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWTRANSFORMFEEDBACKINSTANCED:            result_ptr = "glDrawTransformFeedbackInstanced";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDRAWTRANSFORMFEEDBACKSTREAMINSTANCED:      result_ptr = "glDrawTransformFeedbackStreamInstanced";      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETACTIVEATOMICCOUNTERBUFFERIV:            result_ptr = "glGetActiveAtomicCounterBufferiv";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETINTERNALFORMATIV:                       result_ptr = "glGetInternalformativ";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMEMORYBARRIER:                             result_ptr = "glMemoryBarrier";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXSTORAGE1D:                              result_ptr = "glTexStorage1D";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXSTORAGE2D:                              result_ptr = "glTexStorage2D";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXSTORAGE3D:                              result_ptr = "glTexStorage3D";                              break;

        /* GL 4.3 */
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDVERTEXBUFFER:                 result_ptr = "glBindVertexBuffer";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARBUFFERDATA:                  result_ptr = "glClearBufferData";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARBUFFERSUBDATA:               result_ptr = "glClearBufferSubData";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYIMAGESUBDATA:                 result_ptr = "glCopyImageSubData";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDEBUGMESSAGECALLBACK:             result_ptr = "glDebugMessageCallback";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDEBUGMESSAGECONTROL:              result_ptr = "glDebugMessageControl";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDEBUGMESSAGEINSERT:               result_ptr = "glDebugMessageInsert";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDISPATCHCOMPUTE:                  result_ptr = "glDispatchCompute";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDISPATCHCOMPUTEINDIRECT:          result_ptr = "glDispatchComputeIndirect";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFRAMEBUFFERPARAMETERI:            result_ptr = "glFramebufferParameteri";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETDEBUGMESSAGELOG:               result_ptr = "glGetDebugMessageLog";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETFRAMEBUFFERPARAMETERIV:        result_ptr = "glGetFramebufferParameteriv";        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETINTERNALFORMATI64V:            result_ptr = "glGetInternalformati64v";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETOBJECTLABEL:                   result_ptr = "glGetObjectLabel";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETOBJECTPTRLABEL:                result_ptr = "glGetObjectPtrLabel";                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMINTERFACEIV:            result_ptr = "glGetProgramInterfaceiv";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMRESOURCEINDEX:          result_ptr = "glGetProgramResourceIndex";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMRESOURCEIV:             result_ptr = "glGetProgramResourceiv";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMRESOURCELOCATION:       result_ptr = "glGetProgramResourceLocation";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMRESOURCELOCATIONINDEX:  result_ptr = "glGetProgramResourceLocationIndex";  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETPROGRAMRESOURCENAME:           result_ptr = "glGetProgramResourceName";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINVALIDATEBUFFERDATA:             result_ptr = "glInvalidateBufferData";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINVALIDATEBUFFERSUBDATA:          result_ptr = "glInvalidateBufferSubData";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINVALIDATEFRAMEBUFFER:            result_ptr = "glInvalidateFramebuffer";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINVALIDATESUBFRAMEBUFFER:         result_ptr = "glInvalidateSubFramebuffer";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINVALIDATETEXIMAGEPROC:           result_ptr = "glInvalidateTexImage";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINVALIDATETEXSUBIMAGE:            result_ptr = "glInvalidateTexSubImage";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTIDRAWARRAYSINDIRECT:          result_ptr = "glMultiDrawArraysIndirect";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMULTIDRAWELEMENTSINDIRECT:        result_ptr = "glMultiDrawElementsIndirect";        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLOBJECTLABEL:                      result_ptr = "glObjectLabel";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLOBJECTPTRLABEL:                   result_ptr = "glObjectPtrLabel";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPOPDEBUGGROUPPROC:                result_ptr = "glPopDebugGroup";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLPUSHDEBUGGROUP:                   result_ptr = "glPushDebugGroup";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSHADERSTORAGEBLOCKBINDING:        result_ptr = "glShaderStorageBlockBinding";        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXBUFFERRANGE:                   result_ptr = "glTexBufferRange";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXSTORAGE2DMULTISAMPLE:          result_ptr = "glTexStorage2DMultisample";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXSTORAGE3DMULTISAMPLE:          result_ptr = "glTexStorage3DMultisample";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREVIEW:                      result_ptr = "glTextureView";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBBINDING:              result_ptr = "glVertexAttribBinding";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBFORMAT:               result_ptr = "glVertexAttribFormat";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBIFORMAT:              result_ptr = "glVertexAttribIFormat";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXATTRIBLFORMAT:              result_ptr = "glVertexAttribLFormat";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXBINDINGDIVISOR:             result_ptr = "glVertexBindingDivisor";             break;

        /* GL 4.4 */
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDBUFFERSBASE:    result_ptr = "glBindBuffersBase";    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDBUFFERSRANGE:   result_ptr = "glBindBuffersRange";   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDIMAGETEXTURES:  result_ptr = "glBindImageTextures";  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDSAMPLERS:       result_ptr = "glBindSamplers";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDTEXTURES:       result_ptr = "glBindTextures";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDVERTEXBUFFERS:  result_ptr = "glBindVertexBuffers";  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBUFFERSTORAGE:      result_ptr = "glBufferStorage";      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARTEXIMAGE:      result_ptr = "glClearTexImage";      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARTEXSUBIMAGE:   result_ptr = "glClearTexSubImage";   break;

        /* GL 4.5 */
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBINDTEXTUREUNIT:                              result_ptr = "glBindTextureUnit";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLBLITNAMEDFRAMEBUFFER:                         result_ptr = "glBlitNamedFramebuffer";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCHECKNAMEDFRAMEBUFFERSTATUS:                  result_ptr = "glCheckNamedFramebufferStatus";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARNAMEDBUFFERDATA:                         result_ptr = "glClearNamedBufferData";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARNAMEDBUFFERSUBDATA:                      result_ptr = "glClearNamedBufferSubData";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARNAMEDFRAMEBUFFERFI:                      result_ptr = "glClearNamedFramebufferfi";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARNAMEDFRAMEBUFFERFV:                      result_ptr = "glClearNamedFramebufferfv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARNAMEDFRAMEBUFFERIV:                      result_ptr = "glClearNamedFramebufferiv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLEARNAMEDFRAMEBUFFERUIV:                     result_ptr = "glClearNamedFramebufferuiv";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCLIPCONTROL:                                  result_ptr = "glClipControl";                                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPRESSEDTEXTURESUBIMAGE1D:                  result_ptr = "glCompressedTextureSubImage1D";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPRESSEDTEXTURESUBIMAGE2D:                  result_ptr = "glCompressedTextureSubImage2D";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOMPRESSEDTEXTURESUBIMAGE3D:                  result_ptr = "glCompressedTextureSubImage3D";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYNAMEDBUFFERSUBDATA:                       result_ptr = "glCopyNamedBufferSubData";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYTEXTURESUBIMAGE1D:                        result_ptr = "glCopyTextureSubImage1D";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYTEXTURESUBIMAGE2D:                        result_ptr = "glCopyTextureSubImage2D";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCOPYTEXTURESUBIMAGE3D:                        result_ptr = "glCopyTextureSubImage3D";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATEBUFFERS:                                result_ptr = "glCreateBuffers";                                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATEFRAMEBUFFERS:                           result_ptr = "glCreateFramebuffers";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATEPROGRAMPIPELINES:                       result_ptr = "glCreateProgramPipelines";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATEQUERIES:                                result_ptr = "glCreateQueries";                                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATERENDERBUFFERS:                          result_ptr = "glCreateRenderbuffers";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATESAMPLERS:                               result_ptr = "glCreateSamplers";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATETEXTURES:                               result_ptr = "glCreateTextures";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATETRANSFORMFEEDBACKS:                     result_ptr = "glCreateTransformFeedbacks";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLCREATEVERTEXARRAYS:                           result_ptr = "glCreateVertexArrays";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLDISABLEVERTEXARRAYATTRIB:                     result_ptr = "glDisableVertexArrayAttrib";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLENABLEVERTEXARRAYATTRIB:                      result_ptr = "glEnableVertexArrayAttrib";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLFLUSHMAPPEDNAMEDBUFFERRANGE:                  result_ptr = "glFlushMappedNamedBufferRange";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGENERATETEXTUREMIPMAP:                        result_ptr = "glGenerateTextureMipmap";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETCOMPRESSEDTEXTUREIMAGE:                    result_ptr = "glGetCompressedTextureImage";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETCOMPRESSEDTEXTURESUBIMAGE:                 result_ptr = "glGetCompressedTextureSubImage";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETGRAPHICSRESETSTATUS:                       result_ptr = "glGetGraphicsResetStatus";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNAMEDBUFFERPARAMETERI64V:                  result_ptr = "glGetNamedBufferParameteri64v";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNAMEDBUFFERPARAMETERIV:                    result_ptr = "glGetNamedBufferParameteriv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNAMEDBUFFERPOINTERV:                       result_ptr = "glGetNamedBufferPointerv";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNAMEDBUFFERSUBDATA:                        result_ptr = "glGetNamedBufferSubData";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNAMEDFRAMEBUFFERATTACHMENTPARAMETERIV:     result_ptr = "glGetNamedFramebufferAttachmentParameteriv";     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNAMEDFRAMEBUFFERPARAMETERIV:               result_ptr = "glGetNamedFramebufferParameteriv";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNAMEDRENDERBUFFERPARAMETERIV:              result_ptr = "glGetNamedRenderbufferParameteriv";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNCOMPRESSEDTEXIMAGE:                       result_ptr = "glGetnCompressedTexImage";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNTEXIMAGE:                                 result_ptr = "glGetnTexImage";                                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNUNIFORMDV:                                result_ptr = "glGetnUniformdv";                                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNUNIFORMFV:                                result_ptr = "glGetnUniformfv";                                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNUNIFORMIV:                                result_ptr = "glGetnUniformiv";                                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETNUNIFORMUIV:                               result_ptr = "glGetnUniformuiv";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYBUFFEROBJECTI64V:                     result_ptr = "glGetQueryBufferObjecti64v";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYBUFFEROBJECTIV:                       result_ptr = "glGetQueryBufferObjectiv";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYBUFFEROBJECTUI64V:                    result_ptr = "glGetQueryBufferObjectui64v";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETQUERYBUFFEROBJECTUIV:                      result_ptr = "glGetQueryBufferObjectuiv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXTUREIMAGE:                              result_ptr = "glGetTextureImage";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXTURELEVELPARAMETERFV:                   result_ptr = "glGetTextureLevelParameterfv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXTURELEVELPARAMETERIV:                   result_ptr = "glGetTextureLevelParameteriv";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXTUREPARAMETERFV:                        result_ptr = "glGetTextureParameterfv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXTUREPARAMETERIIV:                       result_ptr = "glGetTextureParameterIiv";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXTUREPARAMETERIUIV:                      result_ptr = "glGetTextureParameterIuiv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXTUREPARAMETERIV:                        result_ptr = "glGetTextureParameteriv";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTEXTURESUBIMAGE:                           result_ptr = "glGetTextureSubImage";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTRANSFORMFEEDBACKI64_V:                    result_ptr = "glGetTransformFeedbacki64_v";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTRANSFORMFEEDBACKI_V:                      result_ptr = "glGetTransformFeedbacki_v";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETTRANSFORMFEEDBACKIV:                       result_ptr = "glGetTransformFeedbackiv";                       break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXARRAYINDEXED64IV:                    result_ptr = "glGetVertexArrayIndexed64iv";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXARRAYINDEXEDIV:                      result_ptr = "glGetVertexArrayIndexediv";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLGETVERTEXARRAYIV:                             result_ptr = "glGetVertexArrayiv";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINVALIDATENAMEDFRAMEBUFFERDATA:               result_ptr = "glInvalidateNamedFramebufferData";               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLINVALIDATENAMEDFRAMEBUFFERSUBDATA:            result_ptr = "glInvalidateNamedFramebufferSubData";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAPNAMEDBUFFER:                               result_ptr = "glMapNamedBuffer";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMAPNAMEDBUFFERRANGE:                          result_ptr = "glMapNamedBufferRange";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLMEMORYBARRIERBYREGION:                        result_ptr = "glMemoryBarrierByRegion";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDBUFFERDATA:                              result_ptr = "glNamedBufferData";                              break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDBUFFERSTORAGE:                           result_ptr = "glNamedBufferStorage";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDBUFFERSUBDATA:                           result_ptr = "glNamedBufferSubData";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDFRAMEBUFFERDRAWBUFFER:                   result_ptr = "glNamedFramebufferDrawBuffer";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDFRAMEBUFFERDRAWBUFFERS:                  result_ptr = "glNamedFramebufferDrawBuffers";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDFRAMEBUFFERPARAMETERI:                   result_ptr = "glNamedFramebufferParameteri";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDFRAMEBUFFERREADBUFFER:                   result_ptr = "glNamedFramebufferReadBuffer";                   break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDFRAMEBUFFERRENDERBUFFER:                 result_ptr = "glNamedFramebufferRenderbuffer";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDFRAMEBUFFERTEXTURE:                      result_ptr = "glNamedFramebufferTexture";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDFRAMEBUFFERTEXTURELAYER:                 result_ptr = "glNamedFramebufferTextureLayer";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDRENDERBUFFERSTORAGE:                     result_ptr = "glNamedRenderbufferStorage";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLNAMEDRENDERBUFFERSTORAGEMULTISAMPLE:          result_ptr = "glNamedRenderbufferStorageMultisample";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLREADNPIXELS:                                  result_ptr = "glReadnPixels";                                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREBARRIER:                               result_ptr = "glTextureBarrier";                               break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREBUFFER:                                result_ptr = "glTextureBuffer";                                break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREBUFFERRANGE:                           result_ptr = "glTextureBufferRange";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREPARAMETERF:                            result_ptr = "glTextureParameterf";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREPARAMETERFV:                           result_ptr = "glTextureParameterfv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREPARAMETERI:                            result_ptr = "glTextureParameteri";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREPARAMETERIIV:                          result_ptr = "glTextureParameterIiv";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREPARAMETERIUIV:                         result_ptr = "glTextureParameterIuiv";                         break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTUREPARAMETERIV:                           result_ptr = "glTextureParameteriv";                           break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTURESTORAGE1D:                             result_ptr = "glTextureStorage1D";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTURESTORAGE2D:                             result_ptr = "glTextureStorage2D";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTURESTORAGE2DMULTISAMPLE:                  result_ptr = "glTextureStorage2DMultisample";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTURESTORAGE3D:                             result_ptr = "glTextureStorage3D";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTURESTORAGE3DMULTISAMPLE:                  result_ptr = "glTextureStorage3DMultisample";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTURESUBIMAGE1D:                            result_ptr = "glTextureSubImage1D";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTURESUBIMAGE2D:                            result_ptr = "glTextureSubImage2D";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTEXTURESUBIMAGE3D:                            result_ptr = "glTextureSubImage3D";                            break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTRANSFORMFEEDBACKBUFFERBASE:                  result_ptr = "glTransformFeedbackBufferBase";                  break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLTRANSFORMFEEDBACKBUFFERRANGE:                 result_ptr = "glTransformFeedbackBufferRange";                 break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLUNMAPNAMEDBUFFER:                             result_ptr = "glUnmapNamedBuffer";                             break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXARRAYATTRIBBINDING:                     result_ptr = "glVertexArrayAttribBinding";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXARRAYATTRIBFORMAT:                      result_ptr = "glVertexArrayAttribFormat";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXARRAYATTRIBIFORMAT:                     result_ptr = "glVertexArrayAttribIFormat";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXARRAYATTRIBLFORMAT:                     result_ptr = "glVertexArrayAttribLFormat";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXARRAYBINDINGDIVISOR:                    result_ptr = "glVertexArrayBindingDivisor";                    break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXARRAYELEMENTBUFFER:                     result_ptr = "glVertexArrayElementBuffer";                     break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXARRAYVERTEXBUFFER:                      result_ptr = "glVertexArrayVertexBuffer";                      break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLVERTEXARRAYVERTEXBUFFERS:                     result_ptr = "glVertexArrayVertexBuffers";                     break;

        case APIInterceptor::APIFunction::APIFUNCTION_USER32_ADJUSTWINDOWRECTEX: result_ptr = "AdjustWindowRectEx"; break;
        case APIInterceptor::APIFunction::APIFUNCTION_USER32_CREATEDCA:          result_ptr = "CreateDCA";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_USER32_CREATEDCW:          result_ptr = "CreateDCW";          break;
        case APIInterceptor::APIFunction::APIFUNCTION_USER32_CREATEWINDOWEXA:    result_ptr = "CreateWindowExA";    break;
        case APIInterceptor::APIFunction::APIFUNCTION_USER32_CREATEWINDOWEXW:    result_ptr = "CreateWindowExW";    break;
        case APIInterceptor::APIFunction::APIFUNCTION_USER32_GETDC:              result_ptr = "GetDC";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_USER32_RELEASEDC:          result_ptr = "ReleaseDC";          break;

        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLCOPYCONTEXT:             result_ptr = "wglCopyContext";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLCREATECONTEXT:           result_ptr = "wglCreateContext";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLCREATECONTEXTATTRIBSARB: result_ptr = "wglCreateContextAttribsARB"; break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLCREATELAYERCONTEXT:      result_ptr = "wglCreateLayerContext";      break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLDELETECONTEXT:           result_ptr = "wglDeleteContext";           break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLGETCURRENTCONTEXT:       result_ptr = "wglGetCurrentContext";       break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLGETCURRENTDC:            result_ptr = "wglGetCurrentDC";            break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLGETEXTENSIONSSTRINGARB:  result_ptr = "wglGetExtensionsStringARB";  break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLGETSWAPINTERVALEXT:      result_ptr = "wglGetSwapIntervalEXT";      break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLMAKECURRENT:             result_ptr = "wglMakeCurrent";             break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLSHARELISTS:              result_ptr = "wglShareLists";              break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLSWAPINTERVALEXT:         result_ptr = "wglSwapIntervalEXT";         break;
        case APIInterceptor::APIFunction::APIFUNCTION_WGL_WGLSWAPLAYERBUFFERS:        result_ptr = "wglSwapLayerBuffers";        break;

        default:
        {
            assert(false);
        }
    }

    return result_ptr;
}

void main(int   in_argc,
          char* in_argv[])
{
    const char*                      dump_filename_ptr = nullptr;
    APIDumpLoader::WorkloadUniquePtr workload_ptr;

    if (in_argc > 1)
    {
        dump_filename_ptr = in_argv[1];
    }

    if (dump_filename_ptr == nullptr)
    {
        fprintf(stdout,
                "In order to use the tool, workload file must be specified via cmd line arg. Example:\n"
                "\n"
                "APIDumpPrinter drive:\\path\\to\\file.workload\n"
                "\n"
                "If any surface dumps are included in the workload, they will be stored in the working directory.\n");

        goto end;
    }

    /* Load the workload */
    workload_ptr = APIDumpLoader::create_workload_from_file(dump_filename_ptr);

    if (workload_ptr == nullptr)
    {
        fprintf(stderr,
                "[!] Could not parse the specified workload.\n");

        assert(workload_ptr != nullptr);
        goto end;
    }

    /* Dump the contents in human-readable format. */
    for (const auto& current_api_call : *workload_ptr->dumped_api_call_vec_ptr)
    {
        const auto n_args = static_cast<uint32_t>(current_api_call.arg_in_vec.size() );

        fprintf(stdout,
                "%s(",
                get_string(current_api_call.func) );

        for (uint32_t n_arg = 0;
                      n_arg < n_args + 1;
                    ++n_arg)
        {
            bool       arg_valid       = true;
            const auto current_arg_ptr = (n_arg != n_args) ? &current_api_call.arg_in_vec.at         (n_arg)
                                                           :  current_api_call.returned_value_ptr.get();

            if (n_arg == n_args)
            {
                /* Returned value is optional */
                if (current_arg_ptr       == nullptr                                          ||
                    current_arg_ptr->type == APIInterceptor::APIFunctionArgumentType::UNKNOWN)
                {
                    arg_valid = false;
                }
                else
                {
                    fprintf(stdout, " returned ");
                }
            }

            if (arg_valid)
            {
                switch (current_arg_ptr->type)
                {
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_F32: fprintf(stdout, "%f",                        current_arg_ptr->get_fp32() );  break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_F64: fprintf(stdout, "%lf",                       current_arg_ptr->get_fp64() );  break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_I8:  fprintf(stdout, "%d",  static_cast<int32_t> (current_arg_ptr->get_i8  () )); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_I16: fprintf(stdout, "%d",  static_cast<int32_t> (current_arg_ptr->get_i16 () )); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_I32: fprintf(stdout, "%d",                        current_arg_ptr->get_i32 () );  break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_U8:  fprintf(stdout, "%u",  static_cast<uint32_t>(current_arg_ptr->get_u8  () )); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_U16: fprintf(stdout, "%u",  static_cast<uint32_t>(current_arg_ptr->get_u16 () )); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_U32: fprintf(stdout, "%u",                        current_arg_ptr->get_u32 () );  break;

                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_F32_PTR:  fprintf(stdout, "[!] 0x%p", current_arg_ptr->get_fp32_ptr() ); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_F64_PTR:  fprintf(stdout, "[!] 0x%p", current_arg_ptr->get_fp64_ptr() ); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_I8_PTR:   fprintf(stdout, "[!] 0x%p", current_arg_ptr->get_i8_ptr  () ); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_I16_PTR:  fprintf(stdout, "[!] 0x%p", current_arg_ptr->get_i16_ptr () ); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_I32_PTR:  fprintf(stdout, "[!] 0x%p", current_arg_ptr->get_i32_ptr () ); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_U8_PTR:   fprintf(stdout, "[!] 0x%p", current_arg_ptr->get_u8_ptr  () ); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_U16_PTR:  fprintf(stdout, "[!] 0x%p", current_arg_ptr->get_u16_ptr () ); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_U32_PTR:  fprintf(stdout, "[!] 0x%p", current_arg_ptr->get_u32_ptr () ); break;
                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_VOID_PTR: fprintf(stdout, "[!] 0x%p", current_arg_ptr->get_ptr     () ); break;

                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_DATA_CHUNK_ID:  fprintf(stdout, "[data chunk %d]", current_arg_ptr->get_data_chunk_id() ); break;

                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_I32_GLENUM:
                    {
                        const auto arg_gl_enum = current_arg_ptr->get_i32_glenum();

                        fprintf(stdout,
                                OpenGL::Utils::get_raw_string_for_gl_enum(arg_gl_enum) );

                        break;
                    }

                    case APIInterceptor::APIFunctionArgumentType::ARGTYPE_U32_GLENUM:
                    {
                        const auto arg_gl_enum = current_arg_ptr->get_u32_glenum();

                        fprintf(stdout,
                                OpenGL::Utils::get_raw_string_for_gl_enum(arg_gl_enum) );

                        break;
                    }

                    default:
                    {
                        assert(false);
                    }
                }
            }

            if (n_args != 0           &&
                n_arg  < (n_args - 1) )
            {
                fprintf(stdout,
                        ", ");
            }
            else
            if (n_args == 0           ||
                n_arg  == n_args - 1)
            {
                fprintf(stdout,
                        ")");
            }
        }

        fprintf(stdout,
                "\n");
    }

    /* Any surfaces included in the workload? */
    if (workload_ptr->dumped_surface_vec_ptr->size() > 0)
    {
        std::string target_directory;
        {
            const DWORD          n_bytes_needed          = ::GetCurrentDirectoryA(0,        /* nBufferLength */
                                                                                  nullptr); /* lpBuffer      */
            std::vector<uint8_t> target_directory_u8_vec(n_bytes_needed);

            ::GetCurrentDirectoryA(n_bytes_needed,
                                   reinterpret_cast<LPTSTR>(target_directory_u8_vec.data() ));

            target_directory = std::string(reinterpret_cast<char*>(target_directory_u8_vec.data() ));
        }

        for (uint32_t n_surface = 0;
                      n_surface < workload_ptr->dumped_surface_vec_ptr->size();
                    ++n_surface)
        {
            auto              surface_props_ptr = &workload_ptr->dumped_surface_vec_ptr->at(n_surface);
            const std::string filename          = target_directory                              +
                                                  "//surface_"                                  +
                                                  std::to_string(n_surface)                     +
                                                  "_"                                           +
                                                  std::to_string(surface_props_ptr->extents[0]) +
                                                  "x"                                           +
                                                  std::to_string(surface_props_ptr->extents[1]) +
                                                  ".raw";
            FILE*             file_handle       = nullptr;

            file_handle = ::fopen(filename.c_str(),
                                  "wb");

            if (file_handle == nullptr)
            {
                fprintf(stderr,
                        "[!] Could not open [%s] for writing.\n",
                        filename.c_str() );

                continue;
            }

            ::fwrite(surface_props_ptr->data_u8_vec.data(),
                     surface_props_ptr->data_u8_vec.size(),
                     1,
                     file_handle);
            ::fclose(file_handle);
        }
    }
end:
    ;
}