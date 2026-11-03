/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Which calls end a frame.
 */
#include <gtest/gtest.h>
#include "Common/frame_boundary.h"

TEST(FrameBoundary, CallsWhichAlwaysEndAFrame)
{
    EXPECT_TRUE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DDEVICE8_PRESENT,     0, nullptr) );
    EXPECT_TRUE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_FLIP,     0, nullptr) );
    EXPECT_TRUE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_GDI32_SWAPBUFFERS,                 0, nullptr) );
}

TEST(FrameBoundary, OtherCallsDoNot)
{
    EXPECT_FALSE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D8_IDIRECT3DSWAPCHAIN8_PRESENT,       0, nullptr) ); /* additional swap chains */
    EXPECT_FALSE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_ENDSCENE,         0, nullptr) );
    EXPECT_FALSE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D7_IDIRECT3DDEVICE7_SETRENDERSTATE,   0, nullptr) );
}

TEST(FrameBoundary, ABlitEndsAFrameOnlyIfItIsMadeToThePrimarySurface)
{
    const unsigned int                  to_primary      = 1;
    const unsigned int                  not_to_primary  = 0;
    APIInterceptor::APIFunctionArgument argument_array[APIInterceptor::D3D7_BLT_PRESENTS_ARGUMENT + 1];

    argument_array[APIInterceptor::D3D7_BLT_PRESENTS_ARGUMENT] = APIInterceptor::APIFunctionArgument::create_u32(to_primary);

    EXPECT_TRUE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT,
                                                  APIInterceptor::D3D7_BLT_PRESENTS_ARGUMENT + 1,
                                                  argument_array) );
    EXPECT_TRUE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLTFAST,
                                                  APIInterceptor::D3D7_BLT_PRESENTS_ARGUMENT + 1,
                                                  argument_array) );

    argument_array[APIInterceptor::D3D7_BLT_PRESENTS_ARGUMENT] = APIInterceptor::APIFunctionArgument::create_u32(not_to_primary);

    EXPECT_FALSE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT,
                                                   APIInterceptor::D3D7_BLT_PRESENTS_ARGUMENT + 1,
                                                   argument_array) );

    /* A blit that was dumped without the argument, or not at all, is not a boundary. */
    EXPECT_FALSE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT,
                                                   APIInterceptor::D3D7_BLT_PRESENTS_ARGUMENT,
                                                   argument_array) );
    EXPECT_FALSE(APIInterceptor::is_frame_boundary(APIInterceptor::APIFUNCTION_D3D7_IDIRECTDRAWSURFACE7_BLT,
                                                   0,
                                                   nullptr) );
}
