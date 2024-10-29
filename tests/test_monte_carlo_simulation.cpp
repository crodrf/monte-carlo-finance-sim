#include "statistical_strategy.h"
#include "monte_carlo_simulation.h"
#include "payoff.h"
#include <gtest/gtest.h>
#include <memory>
#include "thread_pool.h"

TEST(MonteCarloSimulationTest, StandardNormalStrategySimulation) {
    double initial_spot = 100.0;
    double risk_free_rate = 0.05;
    double volatility = 0.2;
    double strike = 90.0;  // strike lower than spot to ensure payoff
    size_t num_sims = 100;

    ThreadPool pool(4);
    auto strategy = std::make_shared<StandardNormalStrategy>(initial_spot, risk_free_rate, volatility);
    auto payoff = std::make_unique<PayOffCall>(strike);

    MonteCarloSimulation simulation(num_sims, strategy, std::move(payoff), pool);
    double result = simulation.run();

    ASSERT_GT(result, 0) << "Expected a non-zero payoff with spot price above strike price.";
    std::cout << "Monte Carlo result with Standard Normal Strategy: " << result << std::endl;
}

TEST(MonteCarloSimulationTest, HestonStrategySimulation) {
    double initial_spot = 100.0;
    double risk_free_rate = 0.05;
    double volatility = 0.2;
    double kappa = 2.0;
    double theta = 0.1;
    double xi = 0.3;
    double rho = -0.7;
    double maturity = 1.0;
    double strike = 90.0;  // strike lower than spot to ensure payoff
    size_t num_sims = 100;

    ThreadPool pool(4);
    auto strategy = std::make_shared<HestonStrategy>(initial_spot, risk_free_rate, volatility, kappa, theta, xi, rho, maturity);
    auto payoff = std::make_unique<PayOffCall>(strike);

    MonteCarloSimulation simulation(num_sims, strategy, std::move(payoff), pool);
    double result = simulation.run();

    ASSERT_GT(result, 0) << "Expected a non-zero payoff with spot price above strike price in Heston Strategy.";
    std::cout << "Monte Carlo result with Heston Strategy: " << result << std::endl;
}
