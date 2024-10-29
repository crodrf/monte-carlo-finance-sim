#include "statistical_strategy.h"
#include <cmath>

// Standard Normal Strategy path generation using GBM
std::vector<double> StandardNormalStrategy::random_draws(size_t n) const {
    std::vector<double> path(n);
    std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> distribution(0.0, 1.0);

    double dt = 1.0 / n;
    path[0] = initial_spot_;

    for (size_t i = 1; i < n; ++i) {
        double Z = distribution(generator);
        path[i] = path[i - 1] * exp((risk_free_rate_ - 0.5 * volatility_ * volatility_) * dt + volatility_ * sqrt(dt) * Z);
    }
    return path;
}

// Heston Strategy path generation with stochastic volatility
std::vector<double> HestonStrategy::random_draws(size_t n) const {
    std::vector<double> path(n);
    std::vector<double> vol_path(n);
    std::mt19937 generator(std::random_device{}());
    std::normal_distribution<double> norm_dist(0.0, 1.0);

    double dt = maturity_ / n;
    path[0] = initial_spot_;
    vol_path[0] = volatility_ * volatility_;

    for (size_t i = 1; i < n; ++i) {
        double Z1 = norm_dist(generator);
        double Z2 = rho_ * Z1 + sqrt(1 - rho_ * rho_) * norm_dist(generator);

        vol_path[i] = std::max(vol_path[i - 1] + kappa_ * (theta_ - vol_path[i - 1]) * dt + xi_ * sqrt(vol_path[i - 1] * dt) * Z2, 0.0);
        path[i] = path[i - 1] * exp((risk_free_rate_ - 0.5 * vol_path[i]) * dt + sqrt(vol_path[i] * dt) * Z1);
    }
    return path;
}
