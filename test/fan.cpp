#include <unity.h>
#include <Arduino.h>
#include <fan.cpp>
#include <configurations.h>

void test_by_temperature(void) {
  int min = 30;
  int max = 40;
  int minPower = 25;
  TEST_ASSERT_EQUAL(0, getInputFanSpeedPercent(0, min, max, minPower));
  TEST_ASSERT_EQUAL(0, getInputFanSpeedPercent(min - 1, min, max, minPower));
  TEST_ASSERT_EQUAL(minPower, getInputFanSpeedPercent(min, min, max, minPower));
  TEST_ASSERT_GREATER_THAN(minPower, getInputFanSpeedPercent(min + 1, min, max, minPower));
  TEST_ASSERT_LESS_OR_EQUAL(99, getInputFanSpeedPercent(max - 1, min, max, minPower));
  TEST_ASSERT_LESS_OR_EQUAL(75, getInputFanSpeedPercent(10, 5, 15, minPower));
  TEST_ASSERT_EQUAL(100, getInputFanSpeedPercent(max, min, max, minPower));
  TEST_ASSERT_EQUAL(100, getInputFanSpeedPercent(100, min, max, minPower));
}

void setup() {
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(test_by_temperature);
    UNITY_END();

}

void loop() {
  // empty
}