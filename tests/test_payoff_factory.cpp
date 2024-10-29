#include "payoff_factory.h"
#include "payoff.h"
#include <gtest/gtest.h>
#include <memory>

TEST(PayOffFactoryTest, CreateCallPayOff) {
    auto payoff = PayOffFactory::createPayOff("call", 100.0);
    EXPECT_TRUE(dynamic_cast<PayOffCall*>(payoff.get()) != nullptr);

    // Verify basic payoff calculation
    EXPECT_DOUBLE_EQ((*payoff)(120.0), 20.0);  // Spot > Strike
    EXPECT_DOUBLE_EQ((*payoff)(80.0), 0.0);    // Spot < Strike
}

TEST(PayOffFactoryTest, CreatePutPayOff) {
    auto payoff = PayOffFactory::createPayOff("put", 100.0);
    EXPECT_TRUE(dynamic_cast<PayOffPut*>(payoff.get()) != nullptr);

    // Verify basic payoff calculation
    EXPECT_DOUBLE_EQ((*payoff)(80.0), 20.0);   // Strike > Spot
    EXPECT_DOUBLE_EQ((*payoff)(120.0), 0.0);   // Strike < Spot
}

TEST(PayOffFactoryTest, InvalidPayOffType) {
    EXPECT_THROW(PayOffFactory::createPayOff("invalid", 100.0), std::invalid_argument);
}
