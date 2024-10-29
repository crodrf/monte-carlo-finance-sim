#include "payoff.h"
#include <gtest/gtest.h>

TEST(PayOffTest, CallPayOffAboveStrike) {
    PayOffCall call(100.0);
    EXPECT_DOUBLE_EQ(call(120.0), 20.0);  // Spot > Strike
}

TEST(PayOffTest, CallPayOffBelowStrike) {
    PayOffCall call(100.0);
    EXPECT_DOUBLE_EQ(call(80.0), 0.0);  // Spot < Strike
}

TEST(PayOffTest, CallPayOffAtStrike) {
    PayOffCall call(100.0);
    EXPECT_DOUBLE_EQ(call(100.0), 0.0);  // Spot == Strike (At the money)
}

TEST(PayOffTest, PutPayOffBelowStrike) {
    PayOffPut put(100.0);
    EXPECT_DOUBLE_EQ(put(80.0), 20.0);  // Strike > Spot
}

TEST(PayOffTest, PutPayOffAboveStrike) {
    PayOffPut put(100.0);
    EXPECT_DOUBLE_EQ(put(120.0), 0.0);  // Strike < Spot
}

TEST(PayOffTest, PutPayOffAtStrike) {
    PayOffPut put(100.0);
    EXPECT_DOUBLE_EQ(put(100.0), 0.0);  // Spot == Strike (At the money)
}
