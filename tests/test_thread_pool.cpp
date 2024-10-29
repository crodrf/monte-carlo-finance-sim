#include "payoff_factory.h"
#include "statistical_strategy.h"
#include "monte_carlo_simulation.h"
#include "thread_pool.h"
#include <gtest/gtest.h>
#include <memory>
#include <vector>
#include <iostream>

// Use the factory directly without redefining payoffs_registered
double run_simulation(size_t num_sims, std::shared_ptr<StatisticalStrategy> strategy, double strike_price, ThreadPool& pool) {
    auto payoff = PayOffFactory::createPayOff("call", strike_price);
    MonteCarloSimulation simulation(num_sims, strategy, std::move(payoff), pool);
    return simulation.run();
}

// Test convergence of Standard Normal Strategy with increasing simulations
TEST(MonteCarloSimulationTest, ConvergenceTestStandardNormal) {
    double strike = 100.0;
    double initial_spot = 100.0;
    double risk_free_rate = 0.05;
    double volatility = 0.2;
    ThreadPool pool(4);
    auto strategy = std::make_shared<StandardNormalStrategy>(initial_spot, risk_free_rate, volatility);

    // Define different simulation sizes for testing convergence
    std::vector<size_t> num_simulations = {1000, 10000, 100000};
    std::vector<double> results;

    for (size_t num_sims : num_simulations) {
        double result = run_simulation(num_sims, strategy, strike, pool);
        results.push_back(result);
        std::cout << "Standard Normal Strategy with " << num_sims << " simulations: " << result << std::endl;
    }

    // Check if results are converging
    EXPECT_NEAR(results[1], results[2], 0.05 * results[2]);  // Allow 5% tolerance
}

// Test convergence of Heston Strategy with increasing simulations
TEST(MonteCarloSimulationTest, ConvergenceTestHeston) {
    double strike = 100.0;
    double initial_spot = 100.0;
    double risk_free_rate = 0.05;
    double volatility = 0.2;
    double maturity = 1.0;
    double kappa = 2.0;
    double theta = 0.1;
    double xi = 0.3;
    double rho = -0.7;

    ThreadPool pool(4);
    auto strategy = std::make_shared<HestonStrategy>(initial_spot, risk_free_rate, volatility, kappa, theta, xi, rho, maturity);

    // Define different simulation sizes for testing convergence
    std::vector<size_t> num_simulations = {1000, 10000, 100000};
    std::vector<double> results;

    for (size_t num_sims : num_simulations) {
        double result = run_simulation(num_sims, strategy, strike, pool);
        results.push_back(result);
        std::cout << "Heston Strategy with " << num_sims << " simulations: " << result << std::endl;
    }

    // Check if results are converging
    EXPECT_NEAR(results[1], results[2], 0.1 * results[2]);  // Allow 10% tolerance
}
