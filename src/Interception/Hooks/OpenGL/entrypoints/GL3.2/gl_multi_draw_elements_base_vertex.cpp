/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#include "Common/callbacks.h"
#include "Common/logger.h"
#include "Common/macros.h"
#include "Common/memory_chunk.h"
#include "Common/tracker.h"
#include "Interception/Hooks/OpenGL/client_array_chunk.h"
#include "Interception/Hooks/OpenGL/entrypoints/GL3.2/gl_multi_draw_elements_base_vertex.h"
#include "Interception/Hooks/OpenGL/globals.h"
#include "Interception/Core/OpenGLUtils/utils_enum.h"
#include "Interception/Hooks/WGL/globals.h"

void AI_APIENTRY Interception::Hooks::OpenGL::aiMultiDrawElementsBaseVertex(GLenum             mode,
                                                                            const GLsizei*     count,
                                                                            GLenum             type,
                                                                            const void* const* indices,
                                                                            GLsizei            drawcount,
                                                                            const GLint*       basevertex)
{
    APIInterceptor::MemoryChunk             base_vertex_chunk(basevertex,
                                                              drawcount,
                                                              sizeof(GLint));
    Interception::Hooks::OpenGL::ClientArrayChunk                client_arrays_chunk;
    APIInterceptor::MemoryChunk             count_chunk(count,
                                                        drawcount,
                                                        sizeof(GLsizei));
    void*                                   post_callback_func_arg = nullptr;
    APIInterceptor::PFNPOSTCALLBACKFUNCPROC post_callback_func_ptr = nullptr;
    void*                                   pre_callback_func_arg  = nullptr;
    APIInterceptor::PFNPRECALLBACKFUNCPROC  pre_callback_func_ptr  = nullptr;
    bool                                    should_pass_through    = true;
    APIInterceptor::Tracker                 tracker;

    client_arrays_chunk.add_multi_elements(count,
                                           type,
                                           indices,
                                           drawcount,
                                           basevertex);

    if (tracker.is_top_level_api_call() )
    {
        AI_TRACE("glMultiDrawElementsBaseVertex(mode=[%s] count=[%p] type=[%s] indices=[%p] drawcount=[%d] basevertex=[%p])",
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(mode),
                 count,
                 Interception::Core::OpenGLUtils::get_raw_string_for_gl_enum(type),
                 indices,
                 static_cast<int32_t>(drawcount),
                 basevertex);

        if (APIInterceptor::get_pre_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWELEMENTSBASEVERTEX,
                                                         &pre_callback_func_ptr,
                                                         &pre_callback_func_arg) )
        {
            const APIInterceptor::APIFunctionArgument args[] =
            {
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (mode),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(count_chunk.get_id() ),
                APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
                client_arrays_chunk.get_multi_indices_arg(),
                APIInterceptor::APIFunctionArgument::create_i32          (drawcount),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(base_vertex_chunk.get_id() ),
                APIInterceptor::APIFunctionArgument::create_data_chunk_id(client_arrays_chunk.get_id() ),
            };

            pre_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWELEMENTSBASEVERTEX,
                                  sizeof(args) / sizeof(args[0]),
                                  args,
                                  pre_callback_func_arg,
                                 &should_pass_through);
        }
    }

    AI_ASSERT(should_pass_through);

    if (should_pass_through)
    {
        reinterpret_cast<PFNGLMULTIDRAWELEMENTSBASEVERTEXPROC>(Interception::Hooks::OpenGL::g_cached_gl_multi_draw_elements_base_vertex)(mode,
                                                                                                                                         count,
                                                                                                                                         type,
                                                                                                                                         indices,
                                                                                                                                         drawcount,
                                                                                                                                         basevertex);
    }

    if (APIInterceptor::get_post_callback_for_function(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWELEMENTSBASEVERTEX,
                                                      &post_callback_func_ptr,
                                                      &post_callback_func_arg) )
    {
        APIInterceptor::APIFunctionArgument result_arg;

        const APIInterceptor::APIFunctionArgument args[] =
        {
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (mode),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(count_chunk.get_id() ),
            APIInterceptor::APIFunctionArgument::create_u32_glenum   (type),
            client_arrays_chunk.get_multi_indices_arg(),
            APIInterceptor::APIFunctionArgument::create_i32          (drawcount),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(base_vertex_chunk.get_id() ),
            APIInterceptor::APIFunctionArgument::create_data_chunk_id(client_arrays_chunk.get_id() ),
        };

        post_callback_func_ptr(APIInterceptor::APIFUNCTION_GL_GLMULTIDRAWELEMENTSBASEVERTEX,
                               post_callback_func_arg,
                               static_cast<uint32_t>(sizeof(args) / sizeof(args[0]) ),
                               args,
                              &result_arg);
    }
}