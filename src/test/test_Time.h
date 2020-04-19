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
        t = new TIME(1, 0);
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
    TIME *t;
};

TEST_F(TimeTest, Time2TicksTest)
{
    ASSERT_EQ(t->Time2Ticks(), 3600000);
}

TEST(Time, Time2Ticks)
{
    TIME t(0, 1);
    ASSERT_EQ(t.Time2Ticks(), 60000);
}

TEST(Time, operator_GT)
{
    TIME t1(15, 30), t2(14, 45);
    ASSERT_TRUE(t1 > t2);
    ASSERT_FALSE(t2 > t1);
}

TEST(Time, operator_GTE)
{
    TIME t1(15, 30), t2(14, 45), t3(15, 30);
    ASSERT_TRUE(t1 >= t2);
    ASSERT_FALSE(t2 >= t1);
    ASSERT_TRUE(t1 >= t3);
    ASSERT_TRUE(t3 >= t1);
}

TEST(Time, operator_LT)
{
    TIME t2(15, 30), t1(14, 45);
    ASSERT_TRUE(t1 < t2);
    ASSERT_FALSE(t2 < t1);
}

TEST(Time, operator_LTE)
{
    TIME t2(15, 30), t1(14, 45), t3(15, 30);
    ASSERT_TRUE(t1 <= t2);
    ASSERT_FALSE(t2 <= t1);
    ASSERT_TRUE(t2 <= t3);
    ASSERT_TRUE(t3 <= t2);
}

TEST(Time, operator_EQ)
{
    TIME t1(15, 30), t2(15, 30);
    ASSERT_TRUE(t1 == t2);
}

TEST(Time, operator_plus)
{
    TIME t1(14, 45), t2(15, 30), t3(6, 15);
    ASSERT_TRUE((t1 + t2) == t3);
    t1.set_Time(5, 0);
    t2.set_Time(6, 30);
    t3.set_Time(11, 30);
    ASSERT_TRUE((t1 + t2) == t3);
}

TEST(Time, operator_minus)
{
    TIME t2(14, 45), t1(15, 30), t3(0, 45);
    ASSERT_TRUE((t1 - t2) == t3);
    t2.set_Time(5, 0);
    t1.set_Time(6, 30);
    t3.set_Time(1, 30);
    ASSERT_TRUE((t1 - t2) == t3);
}
