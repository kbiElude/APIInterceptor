/* API Interceptor (c) 2025 Dominik Witczak
 *
 * This code is licensed under MIT license (see LICENSE.txt for details)
 *
 * Tests for what is shared by the programs which start an application with a DLL in it: the architecture of an executable, and the
 * command line which is made for it.
 */
#include <gtest/gtest.h>
#include "Capture/InjectionLauncher/launcher.h"
#include "fixtures.h"

TEST(InjectionLauncherTest, TheArchitectureOfAnExecutableIsReadFromItsHeaders)
{
    std::string                                   error;
    Capture::InjectionLauncher::TargetArchitecture architecture = Capture::InjectionLauncher::TargetArchitecture::UNKNOWN;

    ASSERT_TRUE(Capture::InjectionLauncher::Launcher::get_target_architecture(Tests::Fixtures::get_test_executable_path(),
                                                                             &architecture,
                                                                             &error) ) << error;

    /* The tests are of the architecture of the program which asks. */
    EXPECT_EQ(architecture,
              Capture::InjectionLauncher::Launcher::get_own_architecture() );
}

TEST(InjectionLauncherTest, WhatIsNotAnExecutableIsRefusedWithTheReason)
{
    std::string                                   error;
    Capture::InjectionLauncher::TargetArchitecture architecture = Capture::InjectionLauncher::TargetArchitecture::X86;

    EXPECT_FALSE(Capture::InjectionLauncher::Launcher::get_target_architecture(Tests::Fixtures::get_text_file_path(),
                                                                              &architecture,
                                                                              &error) );
    EXPECT_NE   (error.find("Not a valid PE"),
                 std::string::npos);
    EXPECT_EQ   (architecture,
                 Capture::InjectionLauncher::TargetArchitecture::UNKNOWN);

    EXPECT_FALSE(Capture::InjectionLauncher::Launcher::get_target_architecture("Z:/no/such/file.exe",
                                                                              &architecture,
                                                                              &error) );
    EXPECT_NE   (error.find("Could not open"),
                 std::string::npos);
}

TEST(InjectionLauncherTest, ThePathOfTheApplicationIsQuotedAndTheArgumentsAreNot)
{
    Capture::InjectionLauncher::LaunchRequest request;

    request.executable_path = "C:\\Program Files\\Demo\\demo.exe";

    EXPECT_EQ(Capture::InjectionLauncher::Launcher::get_command_line(request),
               "\"C:\\Program Files\\Demo\\demo.exe\"");

    request.arguments = "-windowed -w 800";

    EXPECT_EQ(Capture::InjectionLauncher::Launcher::get_command_line(request),
               "\"C:\\Program Files\\Demo\\demo.exe\" -windowed -w 800");
}
