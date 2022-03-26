#include "Meiosis/Util/FileUtils.hpp"
#include <gtest/gtest.h>
// 
TEST(UtilTest, NoRemoveExtension)
{
    EXPECT_EQ( Meiosis::Util::filenameFromPath("C:SomeDir\\SomeDir\\filename.txt"), std::string("filename.txt") );
    EXPECT_EQ( Meiosis::Util::filenameFromPath("filename.txt"), std::string("filename.txt") );
}

TEST(UtilTest, RemoveExtension)
{
    EXPECT_EQ( Meiosis::Util::filenameFromPath("C:SomeDir\\SomeDir\\filename.txt", true), std::string("filename") );
    EXPECT_EQ( Meiosis::Util::filenameFromPath("filename.txt", true), std::string("filename") );
}

TEST(UtilTest, WorkWithNoExtension)
{
    EXPECT_EQ( Meiosis::Util::filenameFromPath("C:SomeDir\\SomeDir\\filename"), std::string("filename") );
    EXPECT_EQ( Meiosis::Util::filenameFromPath("filename"), std::string("filename") );
    EXPECT_EQ( Meiosis::Util::filenameFromPath("C:SomeDir\\SomeDir\\filename", true), std::string("filename") );
    EXPECT_EQ( Meiosis::Util::filenameFromPath("filename", true), std::string("filename") );
}

// #include <iostream>
// int main()
// {
//     std::cout << "Testing: ...\n";
//     std::cout << (Meiosis::Util::filenameFromPath(std::string("Test/test.cpp"), true) == std::string("test")) << '\n';
//     return 0;
// }