/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "OpenGL/entrypoints/GL1.1/gl_bitmap.h"
#include "OpenGL/globals.h"
#include "OpenGL/utils_enum.h"
#include "WGL/globals.h"

void AI_APIENTRY OpenGL::aiBitmap(GLsizei        width,
                                  GLsizei        height,
                                  GLfloat        xorig,
                                  GLfloat        yorig,
                                  GLfloat        xmove,
                                  GLfloat        ymove,
                                  const GLubyte* bitmapef)
{
    AI_WARN("TODO: API call interception not implemented in %s", __FILE__);

    AI_TRACE("glBitmap(width=[%d] width=[%d] xorig=[%.4f] yorig=[%.4f] xmove=[%.4f] ymove=[%.4f] bitmapef=[%p])",
             width,
             height,
             xorig,
             yorig,
             xmove,
             ymove,
             bitmapef);

    reinterpret_cast<PFNGLBITMAPPROC>(OpenGL::g_cached_gl_bitmap)(width,
                                                                  height,
                                                                  xorig,
                                                                  yorig,
                                                                  xmove,
                                                                  ymove,
                                                                  bitmapef);
}