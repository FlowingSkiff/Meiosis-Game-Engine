#include "Meiosis/Platform/OpenGL/OpenGLShader.hpp"
#include <gtest/gtest.h>
#include <string>

namespace details
{
const std::string test_1_str = R"..(
#shader-type VERTEX
do nothing
#shader-type FRAGMENT
do something
)..";
const std::string test_2_str = R"..(
#shader-type FRAGMENT
do nothing
#shader-type VERTEX
do something
)..";
const std::string test_empty_str_1 = R"..(
        #shader-type FRAG
        nothing
        #shader-type VERTEX
    )..";
const std::string test_empty_str_2 = R"..(
        #shader-type FRAGMENT
        nothing
        #shader-type Vert
    )..";
const std::string test_empty_str_3 = R"..(
        #shader type FRAGMENT
        nothing
        #shader-type VERTEX
    )..";
const std::string test_empty_str_4 = R"..(
        #shader-type FRAGMENT
        nothing
        #shader-type Vertex
    )..";
const std::unordered_map<GLenum, std::string> expected_1{
    { GL_VERTEX_SHADER, "\ndo nothing\n" },
    { GL_FRAGMENT_SHADER, "\ndo something\n" }
};
const std::unordered_map<GLenum, std::string> expected_2{
    { GL_VERTEX_SHADER, "\ndo something\n" },
    { GL_FRAGMENT_SHADER, "\ndo nothing\n" }
};
const Meiosis::OpenGLShader::source_map expected_empty;
}// namespace details


TEST(OpenGL, SourceSplit)
{
    EXPECT_EQ(Meiosis::details::splitSource(details::test_1_str), details::expected_1);
    EXPECT_EQ(Meiosis::details::splitSource(details::test_2_str), details::expected_2);
    // EXPECT_EQ( Meiosis::Util::filenameFromPath("C:SomeDir\\SomeDir\\filename.txt"), std::string("filename.txt") );
    // EXPECT_EQ( Meiosis::Util::filenameFromPath("filename.txt"), std::string("filename.txt") );
}

TEST(OpenGL, SourceSplitFailure)
{
    EXPECT_EQ(Meiosis::details::splitSource(details::test_empty_str_1), details::expected_empty);
    EXPECT_EQ(Meiosis::details::splitSource(details::test_empty_str_2), details::expected_empty);
    EXPECT_EQ(Meiosis::details::splitSource(details::test_empty_str_3), details::expected_empty);
    EXPECT_EQ(Meiosis::details::splitSource(details::test_empty_str_4), details::expected_empty);
}