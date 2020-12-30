#include <gtest/gtest.h>
#include <HSGIL/hsgil.hpp>

#include <cmath>

TEST(MathUtilsTest, AbsoluteValInteger)
{
    // SPECIFIC TESTS
    ASSERT_EQ(1, gil::absolute(1));
    ASSERT_EQ(2, gil::absolute(2));
    ASSERT_EQ(4, gil::absolute(4));
    ASSERT_EQ(1, gil::absolute(-1));
    ASSERT_EQ(2, gil::absolute(-2));
    ASSERT_EQ(4, gil::absolute(-4));

    // GENERIC TESTS
    ASSERT_EQ(0, gil::absolute(0));
    for(int i = -128; i <= -1; ++i)
        ASSERT_EQ(-i, gil::absolute(-i));
    for(int i = 1; i <= 128; ++i)
        ASSERT_EQ(i, gil::absolute(-i));

    // CMATH STDLIB COMPARISON
    ASSERT_EQ(abs(0), gil::absolute(0));
    for(int i = -128; i <= 128; ++i)
        ASSERT_EQ(abs(i), gil::absolute(i));
}

TEST(MathUtilsTest, AbsoluteValFloat)
{
    // SPECIFIC TESTS
    ASSERT_EQ(1.0f, gil::absolute(1.0f));
    ASSERT_EQ(2.0f, gil::absolute(2.0f));
    ASSERT_EQ(4.0f, gil::absolute(4.0f));
    ASSERT_EQ(1.0f, gil::absolute(-1.0f));
    ASSERT_EQ(2.0f, gil::absolute(-2.0f));
    ASSERT_EQ(4.0f, gil::absolute(-4.0f));

    // GENERIC TESTS
    ASSERT_EQ(0.0f, gil::absolute(0.0f));
    for(float i = -128.0f; i <= -1.0f; i += 0.5f)
        ASSERT_EQ(-i, gil::absolute(-i));
    for(float i = 1.0f; i <= 128.0f; i += 0.5f)
        ASSERT_EQ(i, gil::absolute(-i));

    // CMATH STDLIB COMPARISON
    for(float i = -128.0f; i <= 128.0f; i += 0.5f)
        ASSERT_EQ(fabs(i), gil::absolute(i));
}

TEST(MathUtilsTest, NumericPowerInteger)
{
    // SPECIFIC TESTS
    ASSERT_EQ(1, gil::npow(1, 0));
    ASSERT_EQ(1, gil::npow(1, 1));
    ASSERT_EQ(1, gil::npow(1, 2));
    ASSERT_EQ(1, gil::npow(1, 3));
    ASSERT_EQ(1, gil::npow(2, 0));
    ASSERT_EQ(2, gil::npow(2, 1));
    ASSERT_EQ(4, gil::npow(2, 2));
    ASSERT_EQ(8, gil::npow(2, 3));
    ASSERT_EQ( 1, gil::npow(-1, 0));
    ASSERT_EQ(-1, gil::npow(-1, 1));
    ASSERT_EQ( 1, gil::npow(-1, 2));
    ASSERT_EQ(-1, gil::npow(-1, 3));
    ASSERT_EQ( 1, gil::npow(-2, 0));
    ASSERT_EQ(-2, gil::npow(-2, 1));
    ASSERT_EQ( 4, gil::npow(-2, 2));
    ASSERT_EQ(-8, gil::npow(-2, 3));
}

TEST(MathUtilsTest, NumericPowerUnsignedInteger)
{
    // SPECIFIC TESTS
    ASSERT_EQ( 1u, gil::npow(1u, 0));
    ASSERT_EQ( 1u, gil::npow(1u, 1));
    ASSERT_EQ( 1u, gil::npow(1u, 2));
    ASSERT_EQ( 1u, gil::npow(1u, 3));
    ASSERT_EQ( 1u, gil::npow(2u, 0));
    ASSERT_EQ( 2u, gil::npow(2u, 1));
    ASSERT_EQ( 4u, gil::npow(2u, 2));
    ASSERT_EQ( 8u, gil::npow(2u, 3));
    ASSERT_EQ( 1u, gil::npow(3u, 0));
    ASSERT_EQ( 3u, gil::npow(3u, 1));
    ASSERT_EQ( 9u, gil::npow(3u, 2));
    ASSERT_EQ(27u, gil::npow(3u, 3));
    ASSERT_EQ( 1u, gil::npow(4u, 0));
    ASSERT_EQ( 4u, gil::npow(4u, 1));
    ASSERT_EQ(16u, gil::npow(4u, 2));
    ASSERT_EQ(64u, gil::npow(4u, 3));
}

TEST(MathUtilsTest, NumericPowerFloat)
{
    // SPECIFIC TESTS
    ASSERT_EQ(1.0f, gil::npow(1.0f, 0));
    ASSERT_EQ(1.0f, gil::npow(1.0f, 1));
    ASSERT_EQ(1.0f, gil::npow(1.0f, 2));
    ASSERT_EQ(1.0f, gil::npow(1.0f, 3));
    ASSERT_EQ(1.0f, gil::npow(2.0f, 0));
    ASSERT_EQ(2.0f, gil::npow(2.0f, 1));
    ASSERT_EQ(4.0f, gil::npow(2.0f, 2));
    ASSERT_EQ(8.0f, gil::npow(2.0f, 3));
    ASSERT_EQ( 1.0f, gil::npow(-1.0f, 0));
    ASSERT_EQ(-1.0f, gil::npow(-1.0f, 1));
    ASSERT_EQ( 1.0f, gil::npow(-1.0f, 2));
    ASSERT_EQ(-1.0f, gil::npow(-1.0f, 3));
    ASSERT_EQ( 1.0f, gil::npow(-2.0f, 0));
    ASSERT_EQ(-2.0f, gil::npow(-2.0f, 1));
    ASSERT_EQ( 4.0f, gil::npow(-2.0f, 2));
    ASSERT_EQ(-8.0f, gil::npow(-2.0f, 3));
}

TEST(MathUtilsTest, ClampInteger)
{
    // SPECIFIC TESTS
    ASSERT_EQ( 0, gil::clamp( 0, -1, 1));
    ASSERT_EQ(-1, gil::clamp(-1, -1, 1));
    ASSERT_EQ(-1, gil::clamp(-2, -1, 1));
    ASSERT_EQ(-1, gil::clamp(-3, -1, 1));
    ASSERT_EQ(-1, gil::clamp(-4, -1, 1));
    ASSERT_EQ( 1, gil::clamp( 1, -1, 1));
    ASSERT_EQ( 1, gil::clamp( 2, -1, 1));
    ASSERT_EQ( 1, gil::clamp( 3, -1, 1));
    ASSERT_EQ( 1, gil::clamp( 4, -1, 1));

    // GENERIC TESTS
    for(int i = -128; i <= -64; ++i)
        ASSERT_EQ(-64, gil::clamp(i, -64, 64));
    for(int i = -63; i <= 63; ++i)
        ASSERT_EQ(  i, gil::clamp(i, -64, 64));
    for(int i = 64; i <= 128; ++i)
        ASSERT_EQ( 64, gil::clamp(i, -64, 64));
}

TEST(MathUtilsTest, ClampUnsignedInteger)
{
    // SPECIFIC TESTS
    ASSERT_EQ(4u, gil::clamp(0u, 4u, 6u));
    ASSERT_EQ(4u, gil::clamp(2u, 4u, 6u));
    ASSERT_EQ(4u, gil::clamp(3u, 4u, 6u));
    ASSERT_EQ(4u, gil::clamp(4u, 4u, 6u));
    ASSERT_EQ(5u, gil::clamp(5u, 4u, 6u));
    ASSERT_EQ(6u, gil::clamp(6u, 4u, 6u));
    ASSERT_EQ(6u, gil::clamp(7u, 4u, 6u));
    ASSERT_EQ(6u, gil::clamp(8u, 4u, 6u));

    // GENERIC TESTS
    for(unsigned int i = 0u; i <= 64u; ++i)
        ASSERT_EQ( 64u, gil::clamp(i, 64u, 128u));
    for(unsigned int i = 65u; i <= 127u; ++i)
        ASSERT_EQ(   i, gil::clamp(i, 64u, 128u));
    for(unsigned int i = 128u; i <= 256u; ++i)
        ASSERT_EQ(128u, gil::clamp(i, 64u, 128u));
}

TEST(MathUtilsTest, ClampFloat)
{
    // SPECIFIC TESTS
    ASSERT_EQ( 0.0f, gil::clamp( 0.0f, -1.0f, 1.0f));
    ASSERT_EQ(-1.0f, gil::clamp(-1.0f, -1.0f, 1.0f));
    ASSERT_EQ(-1.0f, gil::clamp(-2.0f, -1.0f, 1.0f));
    ASSERT_EQ(-1.0f, gil::clamp(-3.0f, -1.0f, 1.0f));
    ASSERT_EQ( 1.0f, gil::clamp( 1.0f, -1.0f, 1.0f));
    ASSERT_EQ( 1.0f, gil::clamp( 2.0f, -1.0f, 1.0f));
    ASSERT_EQ( 1.0f, gil::clamp( 3.0f, -1.0f, 1.0f));

    // GENERIC TESTS
    for(float i = -128.0f; i <= -64.0f; i += 0.5f)
        ASSERT_EQ(-64.0f, gil::clamp(i, -64.0f, 64.0f));
    for(float i = -63.0f; i <= 63.0f; i += 0.5f)
        ASSERT_EQ(     i, gil::clamp(i, -64.0f, 64.0f));
    for(float i = 64.0f; i <= 128.0f; i += 0.5f)
        ASSERT_EQ( 64.0f, gil::clamp(i, -64.0f, 64.0f));
}

TEST(MathUtilsTest, IsBetweenInteger)
{
    // SPECIFIC TESTS
    ASSERT_EQ(false, gil::isBetween(-8, -4, 4));
    ASSERT_EQ(false, gil::isBetween(-6, -4, 4));
    ASSERT_EQ( true, gil::isBetween(-4, -4, 4));
    ASSERT_EQ( true, gil::isBetween(-2, -4, 4));
    ASSERT_EQ( true, gil::isBetween( 0, -4, 4));
    ASSERT_EQ( true, gil::isBetween( 2, -4, 4));
    ASSERT_EQ( true, gil::isBetween( 4, -4, 4));
    ASSERT_EQ(false, gil::isBetween( 6, -4, 4));
    ASSERT_EQ(false, gil::isBetween( 8, -4, 4));

    // GENERIC TESTS
    for(int i = -128; i <= -65; ++i)
        ASSERT_EQ(false, gil::isBetween(i, -64, 64));
    for(int i = -64; i <= 64; ++i)
        ASSERT_EQ( true, gil::isBetween(i, -64, 64));
    for(int i = 65; i <= 128; ++i)
        ASSERT_EQ(false, gil::isBetween(i, -64, 64));
}

TEST(MathUtilsTest, IsBetweenUnsignedInteger)
{
    // SPECIFIC TESTS
    ASSERT_EQ(false, gil::isBetween( 0, 4, 12));
    ASSERT_EQ(false, gil::isBetween( 2, 4, 12));
    ASSERT_EQ( true, gil::isBetween( 4, 4, 12));
    ASSERT_EQ( true, gil::isBetween( 6, 4, 12));
    ASSERT_EQ( true, gil::isBetween( 8, 4, 12));
    ASSERT_EQ( true, gil::isBetween(10, 4, 12));
    ASSERT_EQ( true, gil::isBetween(12, 4, 12));
    ASSERT_EQ(false, gil::isBetween(14, 4, 12));
    ASSERT_EQ(false, gil::isBetween(16, 4, 12));

    // GENERIC TESTS
    for(unsigned int i = 0u; i <= 63u; ++i)
        ASSERT_EQ(false, gil::isBetween(i, 64u, 128u));
    for(unsigned int i = 64u; i <= 128u; ++i)
        ASSERT_EQ( true, gil::isBetween(i, 64u, 128u));
    for(unsigned int i = 129u; i <= 256u; ++i)
        ASSERT_EQ(false, gil::isBetween(i, 64u, 128u));
}

TEST(MathUtilsTest, IsBetweenFloat)
{
    // SPECIFIC TESTS
    ASSERT_EQ(false, gil::isBetween(-8.0f, -4.0f, 4.0f));
    ASSERT_EQ(false, gil::isBetween(-6.0f, -4.0f, 4.0f));
    ASSERT_EQ( true, gil::isBetween(-4.0f, -4.0f, 4.0f));
    ASSERT_EQ( true, gil::isBetween(-2.0f, -4.0f, 4.0f));
    ASSERT_EQ( true, gil::isBetween( 0.0f, -4.0f, 4.0f));
    ASSERT_EQ( true, gil::isBetween( 2.0f, -4.0f, 4.0f));
    ASSERT_EQ( true, gil::isBetween( 4.0f, -4.0f, 4.0f));
    ASSERT_EQ(false, gil::isBetween( 6.0f, -4.0f, 4.0f));
    ASSERT_EQ(false, gil::isBetween( 8.0f, -4.0f, 4.0f));

    // GENERIC TESTS
    for(float i = -128.0f; i <= -65.0f; i += 0.5f)
        ASSERT_EQ(false, gil::isBetween(i, -64.0f, 64.0f));
    for(float i = -64.0f; i <= 64.0f; i += 0.5f)
        ASSERT_EQ( true, gil::isBetween(i, -64.0f, 64.0f));
    for(float i = 65.0f; i <= 128.0f; i += 0.5f)
        ASSERT_EQ(false, gil::isBetween(i, -64.0f, 64.0f));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
