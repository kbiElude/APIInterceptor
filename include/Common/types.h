/* API Interceptor (c) 2024 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 */
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include "globals.h"
#include "Common/macros.h"
#include <cstdint>

namespace APIInterceptor
{
    enum APIFunction : uint32_t
    {
        APIFUNCTION_GL_GLACCUM         = 0,
        APIFUNCTION_GL_GLACTIVETEXTURE,
        APIFUNCTION_GL_GLALPHAFUNC,
        APIFUNCTION_GL_GLBEGIN,
        APIFUNCTION_GL_GLBINDTEXTURE,
        APIFUNCTION_GL_GLCLEAR,
        APIFUNCTION_GL_GLCLEARCOLOR,
        APIFUNCTION_GL_GLCLEARDEPTH,
        APIFUNCTION_GL_GLCLEARSTENCIL,
        APIFUNCTION_GL_GLCOLOR3FV,
        APIFUNCTION_GL_GLCOLOR4FV,
        APIFUNCTION_GL_GLCULLFACE,
        APIFUNCTION_GL_GLDELETETEXTURES,
        APIFUNCTION_GL_GLDEPTHFUNC,
        APIFUNCTION_GL_GLDISABLE,
        APIFUNCTION_GL_GLENABLE,
        APIFUNCTION_GL_GLEND,
        APIFUNCTION_GL_GLFINISH,
        APIFUNCTION_GL_GLFLUSH,
        APIFUNCTION_GL_GLFRONTFACE,
        APIFUNCTION_GL_GLFRUSTUM,
        APIFUNCTION_GL_GLGENTEXTURES,
        APIFUNCTION_GL_GLLOADIDENTITY,
        APIFUNCTION_GL_GLLOADMATRIXF,
        APIFUNCTION_GL_GLMATRIXMODE,
        APIFUNCTION_GL_GLMULTMATRIXF,
        APIFUNCTION_GL_GLNORMAL3FV,
        APIFUNCTION_GL_GLORTHO,
        APIFUNCTION_GL_GLPOLYGONMODE,
        APIFUNCTION_GL_GLREADPIXELS,
        APIFUNCTION_GL_GLROTATEF,
        APIFUNCTION_GL_GLSCALEF,
        APIFUNCTION_GL_GLTEXCOORD2FV,
        APIFUNCTION_GL_GLTEXCOORD3FV,
        APIFUNCTION_GL_GLTEXCOORD4FV,
        APIFUNCTION_GL_GLTEXIMAGE2D,
        APIFUNCTION_GL_GLTEXPARAMETERF,
        APIFUNCTION_GL_GLTEXPARAMETERFV,
        APIFUNCTION_GL_GLTRANSLATEF,
        APIFUNCTION_GL_GLVERTEX2F,
        APIFUNCTION_GL_GLVERTEX2FV,
        APIFUNCTION_GL_GLVERTEX3F,
        APIFUNCTION_GL_GLVERTEX3FV,
        APIFUNCTION_GL_GLVERTEX4F,
        APIFUNCTION_GL_GLVERTEX4FV,
        APIFUNCTION_GL_GLVIEWPORT,

        APIFUNCTION_WGL_WGLMAKECURRENT,

        APIFUNCTION_COUNT,
        APIFUNCTION_UNKNOWN = APIFUNCTION_COUNT
    };

    enum APIFunctionArgumentType : uint8_t
    {
        ARGTYPE_F32,
        ARGTYPE_F32_PTR,
        ARGTYPE_F64,
        ARGTYPE_I16,
        ARGTYPE_I16_PTR,
        ARGTYPE_I32,
        ARGTYPE_I32_PTR,
        ARGTYPE_U32,
        ARGTYPE_U32_PTR,
        ARGTYPE_VOID_PTR,

        UNKNOWN
    };

    typedef struct APIFunctionArgument
    {
        APIFunctionArgumentType type;

        union
        {
            float               value_fp32;
            const float*        value_fp32_ptr;
            double              value_fp64;
            short               value_i16;
            const short*        value_i16_ptr;
            int                 value_i32;
            const int*          value_i32_ptr;
            unsigned int        value_u32;
            const unsigned int* value_u32_ptr;
            const void*         value_ptr;
        } value;

        static APIFunctionArgument create_fp32(const float& in_value)
        {
            APIFunctionArgument result;

            result.type             = ARGTYPE_F32;
            result.value.value_fp32 = in_value;

            return result;
        }

        static APIFunctionArgument create_fp32_ptr(const float* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type                 = ARGTYPE_F32_PTR;
            result.value.value_fp32_ptr = in_value_ptr;

            return result;
        }

        static APIFunctionArgument create_fp64(const double& in_value)
        {
            APIFunctionArgument result;

            result.type             = ARGTYPE_F64;
            result.value.value_fp64 = in_value;

            return result;
        }

        static APIFunctionArgument create_i16(const short& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_I16;
            result.value.value_i16 = in_value;

            return result;
        }

        static APIFunctionArgument create_i16_ptr(const short* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type                = ARGTYPE_I16_PTR;
            result.value.value_i16_ptr = in_value_ptr;

            return result;
        }

        static APIFunctionArgument create_i32(const int& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_I32;
            result.value.value_i32 = in_value;

            return result;
        }

        static APIFunctionArgument create_i32_ptr(const int* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type                = ARGTYPE_I32_PTR;
            result.value.value_i32_ptr = in_value_ptr;

            return result;
        }

        static APIFunctionArgument create_u32(const unsigned int& in_value)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_U32;
            result.value.value_u32 = in_value;

            return result;
        }

        static APIFunctionArgument create_u32_ptr(const unsigned int* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type                = ARGTYPE_U32_PTR;
            result.value.value_u32_ptr = in_value_ptr;

            return result;
        }

        static APIFunctionArgument create_void_ptr(const void* in_value_ptr)
        {
            APIFunctionArgument result;

            result.type            = ARGTYPE_VOID_PTR;
            result.value.value_ptr = in_value_ptr;

            return result;
        }

    private:
        APIFunctionArgument()
            :type(UNKNOWN)
        {
            /* Stub */
        }
    } APIFunctionArgument;

    struct FunctionInterceptor
    {
        void** pfn_func_to_intercept_ptr_ptr;
        void*  pfn_interceptor_func_ptr;

        FunctionInterceptor()
        {
            pfn_func_to_intercept_ptr_ptr = nullptr;
            pfn_interceptor_func_ptr      = nullptr;
        }

        FunctionInterceptor(void** in_pfn_func_to_intercept_ptr_ptr,
                            void*  in_pfn_interceptor_func_ptr)
        {
            pfn_func_to_intercept_ptr_ptr = in_pfn_func_to_intercept_ptr_ptr;
            pfn_interceptor_func_ptr      = in_pfn_interceptor_func_ptr;
        }
    };
}

#endif /* COMMON_TYPES_H */