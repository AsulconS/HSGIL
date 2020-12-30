#include <gtest/gtest.h>
#include <HSGIL/hsgil.hpp>

TEST(WindowIntegrity, Construction)
{
    glm::mat4 identity {1.0f};
    for(int i {0}; i < 4; ++i)
        ASSERT_EQ(1.0f, identity[i][i]);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
