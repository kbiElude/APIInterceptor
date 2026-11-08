/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for when the GL calls of a frame that is executed more than once are made: what makes an object is made once (a second execution would make others), what
 * destroys one waits for the last execution, and the rest (state, matrices, draws, uploads) is made in each.
 */
#include <gtest/gtest.h>
#include "gl_call_executor.h"
#include "object_remapper.h"

namespace
{
    typedef Replay::ReplayEngineDLL::ExecutionClass ExecutionClass;

    ExecutionClass get_class_of(const APIInterceptor::APIFunction& in_function)
    {
        Replay::ReplayEngineDLL::ObjectRemapper  remapper;
        Replay::ReplayEngineDLL::GlCallExecutor  executor(&remapper);
        Capture::APIDumpLoader::DumpedAPICall    call;

        call.func = in_function;

        return executor.get_execution_class(call);
    }
}

TEST(GlCallExecutor, WhatMakesAnObjectIsMadeInTheFirstExecutionOnly)
{
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLGENTEXTURES),
              ExecutionClass::FIRST_TIME_ONLY);
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLGENLISTS),
              ExecutionClass::FIRST_TIME_ONLY);
}

TEST(GlCallExecutor, WhatDestroysAnObjectWaitsForTheLastExecution)
{
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLDELETETEXTURES),
              ExecutionClass::AFTER_ALL);
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLDELETELISTS),
              ExecutionClass::AFTER_ALL);
}

TEST(GlCallExecutor, StateMatricesDrawsAndUploadsAreMadeInEachExecution)
{
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLENABLE),
              ExecutionClass::EVERY_TIME);
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLLOADIDENTITY),
              ExecutionClass::EVERY_TIME);
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLBEGIN),
              ExecutionClass::EVERY_TIME);
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLTEXIMAGE2D),
              ExecutionClass::EVERY_TIME);
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLBINDTEXTURE),
              ExecutionClass::EVERY_TIME);
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLCALLLIST),
              ExecutionClass::EVERY_TIME);
}

TEST(GlCallExecutor, GlGenerateMipmapMakesNoObject)
{
    /* It starts like glGenTextures does, and generates the levels of a texture that is there. */
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLGENERATEMIPMAP),
              ExecutionClass::EVERY_TIME);
}

TEST(GlCallExecutor, WhatMakesAShaderOrAProgramIsMadeInTheFirstExecutionOnly)
{
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLCREATESHADER),
              ExecutionClass::FIRST_TIME_ONLY);
    EXPECT_EQ(get_class_of(APIInterceptor::APIFUNCTION_GL_GLCREATEPROGRAM),
              ExecutionClass::FIRST_TIME_ONLY);
}
