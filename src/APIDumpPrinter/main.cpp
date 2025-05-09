#include <assert.h>
#include <stdio.h>
#include "APIDumpLoader/APIDumpLoader.h"

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
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSELECTBUFFER:                            result_ptr = "glSelectBuffer";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSHADEMODEL:                              result_ptr = "glShadeModel";                          break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSHADERSOURCE:                            result_ptr = "glShaderSource";                        break;
        case APIInterceptor::APIFunction::APIFUNCTION_GL_GLSTENCILFUNC:                             result_ptr = "glStencilFunc";                         break;
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

        case APIInterceptor::APIFunction::APIFUNCTION_USER32_CREATEWINDOWEXA: result_ptr = "CreateWindowExA"; break;
        case APIInterceptor::APIFunction::APIFUNCTION_USER32_GETDC:           result_ptr = "GetDC";           break;

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
                "APIDumpPrinter drive:\\path\\to\\file.workload\n");

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
        const auto n_args = static_cast<uint32_t>(current_api_call.arg_vec.size() );

        fprintf(stdout,
                "%s(",
                get_string(current_api_call.func) );

        for (uint32_t n_arg = 0;
                      n_arg < n_args + 1;
                    ++n_arg)
        {
            bool       arg_valid       = true;
            const auto current_arg_ptr = (n_arg != n_args) ? &current_api_call.arg_vec.at            (n_arg)
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
end:
    ;
}