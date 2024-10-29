#include "monte_carlo_simulation.h"
#include "statistical_strategy.h"
#include "payoff.h"
#include "thread_pool.h"
#include <iostream>
#include <memory>

int main() {
    double initial_spot = 100.0;
    double strike = 100.0;
    double risk_free_rate = 0.05;
    double volatility = 0.2;
    double kappa = 2.0;
    double theta = 0.1;
    double xi = 0.3;
    double rho = -0.7;
    double maturity = 1.0;
    size_t num_sims = 100000;

    ThreadPool pool(4);

    // Standard Normal Strategy
    auto standard_strategy = std::make_shared<StandardNormalStrategy>(initial_spot, risk_free_rate, volatility);
    auto payoff = std::make_unique<PayOffCall>(strike);
    MonteCarloSimulation mc_standard(num_sims, standard_strategy, std::move(payoff), pool);
    double standard_result = mc_standard.run();
    std::cout << "Monte Carlo result with Standard Normal Strategy: " << standard_result << std::endl;

    // Heston Strategy
    auto heston_strategy = std::make_shared<HestonStrategy>(initial_spot, risk_free_rate, volatility, kappa, theta, xi, rho, maturity);
    payoff = std::make_unique<PayOffCall>(strike);  // Create a new payoff instance
    MonteCarloSimulation mc_heston(num_sims, heston_strategy, std::move(payoff), pool);
    double heston_result = mc_heston.run();
    std::cout << "Monte Carlo result with Heston Strategy: " << heston_result << std::endl;

    return 0;
}
