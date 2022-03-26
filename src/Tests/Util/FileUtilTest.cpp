// #include "Meiosis/Util/FileUtils.hpp"
#include <string>
#include <gtest/gtest.h>


TEST(UtilTest, InitialTest)
{
    // EXPECT_EQ( Meiosis::Util::filenameFromPath("C:SomeDir\\SomeDir\\filename.txt"), std::string("filename.txt") );
    EXPECT_EQ(1, 2);
    EXPECT_EQ(std::string("None"), std::string("Yes"));
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }