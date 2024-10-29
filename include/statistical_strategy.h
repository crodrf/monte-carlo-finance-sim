#ifndef STATISTICAL_STRATEGY_H
#define STATISTICAL_STRATEGY_H

#include <vector>
#include <random>

class StatisticalStrategy {
public:
    virtual ~StatisticalStrategy() = default;
    virtual std::vector<double> random_draws(size_t n) const = 0;
};

class StandardNormalStrategy : public StatisticalStrategy {
public:
    StandardNormalStrategy(double initial_spot, double risk_free_rate, double volatility)
        : initial_spot_(initial_spot), risk_free_rate_(risk_free_rate), volatility_(volatility) {}

    std::vector<double> random_draws(size_t n) const override;

private:
    double initial_spot_;
    double risk_free_rate_;
    double volatility_;
};

class HestonStrategy : public StatisticalStrategy {
public:
    HestonStrategy(double initial_spot, double risk_free_rate, double volatility, double kappa, double theta, double xi, double rho, double maturity)
        : initial_spot_(initial_spot), risk_free_rate_(risk_free_rate), volatility_(volatility),
          kappa_(kappa), theta_(theta), xi_(xi), rho_(rho), maturity_(maturity) {}

    std::vector<double> random_draws(size_t n) const override;

private:
    double initial_spot_;
    double risk_free_rate_;
    double volatility_;
    double kappa_;
    double theta_;
    double xi_;
    double rho_;
    double maturity_;
};

#endif // STATISTICAL_STRATEGY_H
