#include "monte_carlo_simulation.h"
#include <iostream>

double MonteCarloSimulation::run() {
    double payoff_sum = 0.0;
    std::vector<std::future<double>> futures;

    for (size_t i = 0; i < num_sims_; ++i) {
        futures.push_back(pool_.enqueue([this] {
            try {
                auto path = strategy_->random_draws(1000);
                double final_price = path.back();
                double result = (*payoff_)(final_price);
                return result;
            } catch (const std::exception& e) {
                std::cerr << "Simulation task exception: " << e.what() << std::endl;
                return 0.0;
            }
        }));
    }

    for (auto& future : futures) {
        payoff_sum += future.get();
    }

    return payoff_sum / num_sims_;
}
