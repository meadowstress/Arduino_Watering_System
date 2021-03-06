#include <iostream>
#include <string>
#include <unistd.h>
#include <gtest/gtest.h>
#include "time.h"
#include "mock_arduino.h"
#include "PS_func.h"
#include "parameter.h"

class TimeTest : public ::testing::Test
{
 protected:
    TimeTest()
    {
        // initialization code here
    }

    void SetUp()
    {
        // code here will execute just before the test ensues
        t = new TIME(1, 0, 0);
    }

    void TearDown()
    {
        // code here will be called just after the test completes
        // ok to through exceptions from here if need be
        delete (t);
    }

    ~TimeTest()
    {
        // cleanup any pending stuff, but no exceptions allowed
    }

    // put in any custom data members that you need
    TIME* t;
};

TEST_F(TimeTest, Time2TicksTest)
{
    ASSERT_EQ(t->Time2Ticks(), 3600000);
}

TEST(Time, Time2Ticks)
{
    TIME t(0, 1, 0);
    ASSERT_EQ(t.Time2Ticks(), 60000);
}

TEST(Time, operator_GT)
{
    TIME t1(15, 30, 15), t2(14, 45, 30);
    ASSERT_TRUE(t1 > t2);
    ASSERT_FALSE(t2 > t1);

    t1.set_Time(-15, 30, 15), t2.set_Time(14, 45, 30);
    ASSERT_TRUE(t2 > t1);
    ASSERT_FALSE(t1 > t2);

    t1.set_Time(15, 30, 15), t2.set_Time(14, -45, -30);
    ASSERT_TRUE(t1 > t2);
    ASSERT_FALSE(t2 > t1);
}

TEST(Time, const_operator_GT)
{
    const TIME t1(15, 30, 15);
    const TIME t2(14, 45, 30);
    ASSERT_TRUE(t1 > t2);
    ASSERT_FALSE(t2 > t1);
}

TEST(Time, operator_GTE)
{
    TIME t1(15, 30, 15), t2(14, 45, 15), t3(15, 30, 15);

    ASSERT_TRUE(t1 >= t2);
    ASSERT_FALSE(t2 >= t1);
    ASSERT_TRUE(t1 >= t3);
    ASSERT_TRUE(t3 >= t1);

    t1.set_Time(16, -30, -15), t2.set_Time(14, 45, 30),
        t3.set_Time(16, -30, -15);

    ASSERT_TRUE(t1 >= t2);
    ASSERT_FALSE(t2 >= t1);
    ASSERT_TRUE(t1 >= t3);
    ASSERT_TRUE(t3 >= t1);
}

TEST(Time, const_operator_GTE)
{
    const TIME t1(15, 30, 15);
    const TIME t2(14, 45, 15);
    const TIME t3(15, 30, 15);

    ASSERT_TRUE(t1 >= t2);
    ASSERT_FALSE(t2 >= t1);
    ASSERT_TRUE(t1 >= t3);
    ASSERT_TRUE(t3 >= t1);
}

TEST(Time, operator_LT)
{
    TIME t2(15, 30, 15), t1(14, 45, 30);
    ASSERT_TRUE(t1 < t2);
    ASSERT_FALSE(t2 < t1);

    t2.set_Time(15, 30, 15), t1.set_Time(14, -45, -30);
    ASSERT_TRUE(t1 < t2);
    ASSERT_FALSE(t2 < t1);
}

TEST(Time, const_operator_LT)
{
    const TIME t2(15, 30, 15);
    const TIME t1(14, 45, 30);
    ASSERT_TRUE(t1 < t2);
    ASSERT_FALSE(t2 < t1);
}

TEST(Time, operator_LTE)
{
    TIME t2(15, 30, 15), t1(14, 45, 10), t3(15, 30, 15);
    ASSERT_TRUE(t1 <= t2);
    ASSERT_FALSE(t2 <= t1);
    ASSERT_TRUE(t2 <= t3);
    ASSERT_TRUE(t3 <= t2);

    t2.set_Time(16, -30, -15), t1.set_Time(14, 45, 30),
        t3.set_Time(16, -30, -15);
    ASSERT_TRUE(t1 <= t2);
    ASSERT_FALSE(t2 <= t1);
    ASSERT_TRUE(t2 <= t3);
    ASSERT_TRUE(t3 <= t2);
}

TEST(Time, const_operator_LTE)
{
    const TIME t2(15, 30, 15);
    const TIME t1(14, 45, 10);
    const TIME t3(15, 30, 15);

    ASSERT_TRUE(t1 <= t2);
    ASSERT_FALSE(t2 <= t1);
    ASSERT_TRUE(t2 <= t3);
    ASSERT_TRUE(t3 <= t2);
}

TEST(Time, operator_EQ)
{
    TIME t1(15, 30, 21), t2(15, 30, 21);
    ASSERT_TRUE(t1 == t2);

    t1.set_Time(15, -30, -21), t2.set_Time(15, -30, -21);
    ASSERT_TRUE(t1 == t2);

    t1.set_Time(-15, -30, -21), t2.set_Time(-15, -30, -21);
    ASSERT_TRUE(t1 == t2);
}

TEST(Time, const_operator_EQ)
{
    const TIME t1(15, 30, 21);
    const TIME t2(15, 30, 21);
    ASSERT_TRUE(t1 == t2);
}

TEST(Time, operator_plus)
{
    TIME t1(14, 45, 45), t2(15, 30, 30), t3(6, 16, 15);
    ASSERT_TRUE((t1 + t2) == t3);

    t1.set_Time(5, 0, 15);
    t2.set_Time(6, 30, 15);
    t3.set_Time(11, 30, 30);

    ASSERT_TRUE((t1 + t2) == t3);

    t1.set_Time(5, 22, 15);
    t2.set_Time(-1, -22, -15);
    t3.set_Time(4, 0, 0);

    ASSERT_TRUE((t1 + t2) == t3);
}

TEST(Time, const_operator_plus)
{
    const TIME t1(14, 45, 45);
    const TIME t2(15, 30, 30);
    const TIME t3(6, 16, 15);

    ASSERT_TRUE((t1 + t2) == t3);
}

TEST(Time, operator_minus)
{
    TIME t1(15, 30, 15), t2(14, 45, 30), t3(0, 44, 45);

    ASSERT_TRUE((t1 - t2) == t3);

    t1.set_Time(6, 30, 15);
    t2.set_Time(5, 0, 15);
    t3.set_Time(1, 30, 0);

    ASSERT_TRUE((t1 - t2) == t3);

    t1.set_Time(6, 30, 15);
    t2.set_Time(5, 0, 16);
    t3.set_Time(1, 29, 59);

    ASSERT_TRUE((t1 - t2) == t3);
}

TEST(Time, const_operator_minus)
{
    const TIME t1(15, 30, 15);
    const TIME t2(14, 45, 30);
    const TIME t3(0, 44, 45);

    ASSERT_TRUE((t1 - t2) == t3);
}
