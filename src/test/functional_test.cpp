#include <gtest/gtest.h>
#include <HSGIL/hsgil.hpp>

TEST(WindowIntegrity, Construction)
{
    gil::RenderingWindow window(800, 600, "Window Integrity Test");
    ASSERT_EQ(true, window.isReady());
    ASSERT_EQ(true, window.isActive());
    ASSERT_EQ(800.0f / 600.0f, window.getAspectRatio());
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
