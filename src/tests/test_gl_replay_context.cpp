/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Checks of the mapping of the names and locations of GL objects from the dump to the replay.
 */
#include "call_walker.h"
#include <gtest/gtest.h>
#include "gl_argument_restorer.h"
#include "gl_replay_context.h"

namespace
{
    /* A call of a function with the given kinds of parameters. */
    struct ContextFixture
    {
        Capture::APIDumpLoader::DumpedAPICall call;
        Replay::ReplayEngineDLL::CallWalker  walker;
        Replay::ReplayEngineDLL::GLFunctionInfo info;
        Replay::ReplayEngineDLL::ObjectRemapper remapper;
        Replay::ReplayEngineDLL::GLReplayContext context;

        ContextFixture()
            :context(&remapper)
        {
            info.has_explicit_program = false;
            info.ignored_param_mask   = 0;
            info.name_ptr             = "glTest";
            info.return_kind          = Replay::ReplayEngineDLL::ObjectKind::NONE;

            call.func = APIInterceptor::APIFUNCTION_GL_GLACCUM;

            context.begin_call(&call,
                               &walker,
                               0,
                               &info);
        }
    };
}

TEST(GLReplayContext, UnknownNamesPassThrough)
{
    ContextFixture fixture;

    EXPECT_EQ(fixture.context.map_name(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                                               7),
                      7u);
}

TEST(GLReplayContext, NamesAreMappedPerKind)
{
    ContextFixture fixture;

    fixture.context.register_name(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                                          1,
                                          5);

    EXPECT_EQ(fixture.context.map_name(Replay::ReplayEngineDLL::ObjectKind::TEXTURE,
                                               1),
                      5u);
    EXPECT_EQ(fixture.context.map_name(Replay::ReplayEngineDLL::ObjectKind::BUFFER,
                                               1),
                      1u);
}

TEST(GLReplayContext, ElementsOfAUniformArrayFollowTheFirstOne)
{
    ContextFixture fixture;

    fixture.context.set_current_program(3);
    fixture.context.register_uniform_location(3,
                                              4,
                                              10);

    EXPECT_EQ(fixture.context.map_uniform_location(4),
              10);
    EXPECT_EQ(fixture.context.map_uniform_location(6),
              12);
}

TEST(GLReplayContext, LocationsOfAnotherProgramAreNotUsed)
{
    ContextFixture fixture;

    fixture.context.register_uniform_location(3,
                                              4,
                                              10);
    fixture.context.set_current_program(8);

    EXPECT_EQ(fixture.context.map_uniform_location(4),
              4);
}

TEST(GLReplayContext, ARangeOfDisplayListsIsMappedOneByOne)
{
    ContextFixture fixture;

    fixture.info.return_kind = Replay::ReplayEngineDLL::ObjectKind::DISPLAY_LIST;

    fixture.call.arg_in_vec.push_back(APIInterceptor::APIFunctionArgument::create_i32(3) );
    fixture.call.returned_value_ptr.reset(new APIInterceptor::APIFunctionArgument(APIInterceptor::APIFunctionArgument::create_u32(10) ));

    fixture.context.begin_call(&fixture.call,
                               &fixture.walker,
                               1,
                               &fixture.info);
    fixture.context.register_returned_name(100);

    EXPECT_EQ(fixture.context.map_name(Replay::ReplayEngineDLL::ObjectKind::DISPLAY_LIST,
                                               10),
                      100u);
    EXPECT_EQ(fixture.context.map_name(Replay::ReplayEngineDLL::ObjectKind::DISPLAY_LIST,
                                               12),
                      102u);
}

namespace
{
    /* The call as the dump holds it, started in the context. */
    void begin_call(ContextFixture*                                         inout_fixture_ptr,
                    const APIInterceptor::APIFunction&                      in_function,
                    const std::vector<APIInterceptor::APIFunctionArgument>& in_argument_vec)
    {
        inout_fixture_ptr->call.arg_in_vec = in_argument_vec;
        inout_fixture_ptr->call.func       = in_function;

        inout_fixture_ptr->context.begin_call(&inout_fixture_ptr->call,
                                              &inout_fixture_ptr->walker,
                                              in_argument_vec.size(),
                                              &inout_fixture_ptr->info);
    }

    /* A pointer of the dumped process, which is a place on its stack. */
    APIInterceptor::APIFunctionArgument make_stack_pointer()
    {
        return APIInterceptor::APIFunctionArgument::create_fp32_ptr(reinterpret_cast<const float*>(static_cast<uintptr_t>(0x19fd6c) ) );
    }

    /* glReadPixels(0, 0, width, height, format, type, pointer). */
    std::vector<APIInterceptor::APIFunctionArgument> make_read_pixels_arguments(const int32_t&  in_width,
                                                                                const int32_t&  in_height,
                                                                                const uint32_t& in_format,
                                                                                const uint32_t& in_type)
    {
        return {APIInterceptor::APIFunctionArgument::create_i32       (0),
                APIInterceptor::APIFunctionArgument::create_i32       (0),
                APIInterceptor::APIFunctionArgument::create_i32       (in_width),
                APIInterceptor::APIFunctionArgument::create_i32       (in_height),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(in_format),
                APIInterceptor::APIFunctionArgument::create_u32_glenum(in_type),
                make_stack_pointer()};
    }
}

TEST(GLReplayContext, AQueryOfGlWritesAKnownNumberOfBytesToTheMemoryOfTheProgram)
{
    ContextFixture fixture;

    begin_call(&fixture,
               APIInterceptor::APIFUNCTION_GL_GLGETFLOATV,
               {APIInterceptor::APIFunctionArgument::create_u32_glenum(0xBA6),
                make_stack_pointer()});

    EXPECT_GE(fixture.context.get_unrecorded_output_n_bytes(1),
              16 * sizeof(double) );
    EXPECT_EQ(fixture.context.get_unrecorded_output_n_bytes(0),
              0u);
}

TEST(GLReplayContext, ThePixelsOfAReadAreAsManyAsItsSizeSays)
{
    ContextFixture fixture;

    /* Three bytes, in a row which may be padded. */
    begin_call(&fixture,
               APIInterceptor::APIFUNCTION_GL_GLREADPIXELS,
               make_read_pixels_arguments(1,
                                          1,
                                          0x1907,
                                          0x1401) );

    EXPECT_GE(fixture.context.get_unrecorded_output_n_bytes(6),
              3u);
    EXPECT_LT(fixture.context.get_unrecorded_output_n_bytes(6),
              64u);
}

TEST(GLReplayContext, TheRowsOfAReadAreCountedWhole)
{
    ContextFixture fixture;

    begin_call(&fixture,
               APIInterceptor::APIFUNCTION_GL_GLREADPIXELS,
               make_read_pixels_arguments(640,
                                          480,
                                          0x1908,
                                          0x1401) );

    EXPECT_GE(fixture.context.get_unrecorded_output_n_bytes(6),
              640u * 480u * 4u);
}

TEST(GLReplayContext, AReadThatIsTooLargeIsNotGivenMemory)
{
    ContextFixture fixture;

    begin_call(&fixture,
               APIInterceptor::APIFUNCTION_GL_GLREADPIXELS,
               make_read_pixels_arguments(100000,
                                          100000,
                                          0x1908,
                                          0x1401) );

    EXPECT_EQ(fixture.context.get_unrecorded_output_n_bytes(6),
              0u);
}

TEST(GLReplayContext, WithABufferBoundToThePixelsOfAReadThePointerIsAnOffset)
{
    ContextFixture fixture;

    fixture.context.set_pixel_pack_buffer_bound(true);

    begin_call(&fixture,
               APIInterceptor::APIFUNCTION_GL_GLREADPIXELS,
               make_read_pixels_arguments(1,
                                          1,
                                          0x1907,
                                          0x1401) );

    EXPECT_EQ(fixture.context.get_unrecorded_output_n_bytes(6),
              0u);
}

TEST(GLReplayContext, AFunctionOfNoKnownOutputIsGivenNoMemory)
{
    ContextFixture fixture;

    begin_call(&fixture,
               APIInterceptor::APIFUNCTION_GL_GLACCUM,
               {APIInterceptor::APIFunctionArgument::create_u32_glenum(0x100),
                make_stack_pointer()});

    EXPECT_EQ(fixture.context.get_unrecorded_output_n_bytes(1),
              0u);
}

TEST(GLArgumentRestorer, APlaceThatACallWritesToIsMemoryOfTheReplay)
{
    typedef Replay::ReplayEngineDLL::GLRestore::ArgumentRestorer<GLfloat*,
                                                                 Replay::ReplayEngineDLL::GLRestore::ArgumentCategory::POINTER> OutputRestorer;

    ContextFixture fixture;
    OutputRestorer restorer;
    std::string    error;

    begin_call(&fixture,
               APIInterceptor::APIFUNCTION_GL_GLGETFLOATV,
               {APIInterceptor::APIFunctionArgument::create_u32_glenum(0xBA6),
                make_stack_pointer()});

    ASSERT_TRUE(restorer.prepare(&fixture.context,
                                 1,
                                 &error) ) << error;

    /* Not the address of the dumped process, which the replay cannot write to. */
    EXPECT_NE(restorer.get(),
              nullptr);
    EXPECT_NE(restorer.get(),
              reinterpret_cast<GLfloat*>(static_cast<uintptr_t>(0x19fd6c) ) );
    EXPECT_FALSE(fixture.context.is_skipped() );
}

TEST(GLArgumentRestorer, APlaceThatIsOnlyReadFromIsNotMadeUp)
{
    typedef Replay::ReplayEngineDLL::GLRestore::ArgumentRestorer<const GLfloat*,
                                                                 Replay::ReplayEngineDLL::GLRestore::ArgumentCategory::POINTER> InputRestorer;

    ContextFixture fixture;
    InputRestorer  restorer;
    std::string    error;

    begin_call(&fixture,
               APIInterceptor::APIFUNCTION_GL_GLGETFLOATV,
               {APIInterceptor::APIFunctionArgument::create_u32_glenum(0xBA6),
                APIInterceptor::APIFunctionArgument::create_fp32_ptr(reinterpret_cast<const float*>(static_cast<uintptr_t>(0x20000000) ) )});

    ASSERT_TRUE(restorer.prepare(&fixture.context,
                                 1,
                                 &error) ) << error;

    /* An address above the offsets of a buffer, with nothing in the dump: the call cannot be replayed. */
    EXPECT_TRUE(fixture.context.is_skipped() );
}
