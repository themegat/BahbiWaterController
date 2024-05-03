#include <TimeUtil.h>
#include "unity.h"

void setUp(void)
{
    // set stuff up here
}

void tearDown(void)
{
    // clean stuff up here
}

#pragma region test_time_is_between

void test_time_is_between_case_1()
{
    TEST_ASSERT_TRUE(TimeUtil::isBetween("10:10:10", "14:10:20", "10:10:15"));
}
void test_time_is_between_case_2()
{
    TEST_ASSERT_TRUE(TimeUtil::isBetween("18:30:00", "07:00:00", "02:20:00"));
}
void test_time_is_between_case_3()
{
    TEST_ASSERT_FALSE(TimeUtil::isBetween("10:10:10", "14:10:20", "15:10:15"));
}

void test_time_is_between_case_4()
{
    TEST_ASSERT_FALSE(TimeUtil::isBetween("18:30:00", "07:00:10", "15:10:15"));
}


void test_time_is_between_case_5()
{
    TEST_ASSERT_FALSE(TimeUtil::isBetween("18:38:00", "06:59:00", "12:21:44"));
}

void run_time_is_between_suit()
{
    RUN_TEST(test_time_is_between_case_1);
    RUN_TEST(test_time_is_between_case_2);
    RUN_TEST(test_time_is_between_case_3);
    RUN_TEST(test_time_is_between_case_4);
    RUN_TEST(test_time_is_between_case_5);
}

#pragma endregion

#pragma region test_time_between

void test_time_between_case_1()
{
    TEST_ASSERT_EQUAL(14400, TimeUtil::getTimeBetween("10:00:00", "14:00:00"));
}

void test_time_between_case_2()
{
    TEST_ASSERT_EQUAL(36000, TimeUtil::getTimeBetween("16:00:00", "02:00:00"));
}

void test_time_between_case_3()
{
    TEST_ASSERT_EQUAL(9000, TimeUtil::getTimeBetween("23:30:00", "02:00:00"));
}

void test_time_between_case_4()
{
    TEST_ASSERT_EQUAL(46740, TimeUtil::getTimeBetween("18:31:00", "07:30:00"));
}

void test_time_between_case_5()
{
    TEST_ASSERT_EQUAL(31480, TimeUtil::getTimeBetween("22:45:20", "07:30:00"));
}

void test_time_between_case_6()
{
    TEST_ASSERT_EQUAL(14955, TimeUtil::getTimeBetween("03:20:45", "07:30:00"));
}

void test_time_between_case_7()
{
    TEST_ASSERT_EQUAL(555, TimeUtil::getTimeBetween("07:20:45", "07:30:00"));
}

void run_time_between_suit()
{
    RUN_TEST(test_time_between_case_1);
    RUN_TEST(test_time_between_case_2);
    RUN_TEST(test_time_between_case_3);
    RUN_TEST(test_time_between_case_4);
    RUN_TEST(test_time_between_case_5);
    RUN_TEST(test_time_between_case_6);
    RUN_TEST(test_time_between_case_7);
}

#pragma endregion
int RUN_UNITY_TESTS(void)
{
    UNITY_BEGIN();
    run_time_is_between_suit();
    run_time_between_suit();
    return UNITY_END();
}

// WARNING!!! PLEASE REMOVE UNNECESSARY MAIN IMPLEMENTATIONS //

/**
 * For native dev-platform or for some embedded frameworks
 */
#ifdef ARDUINO

#include <Arduino.h>
void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    RUN_UNITY_TESTS();
}

#else

int main(int argc, char **argv)
{
    RUN_UNITY_TESTS();
    return 0;
}

#endif