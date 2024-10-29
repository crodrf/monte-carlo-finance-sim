#ifndef MONTE_CARLO_SIMULATION_H
#define MONTE_CARLO_SIMULATION_H

#include "statistical_strategy.h"
#include "payoff.h"
#include "thread_pool.h"
#include <vector>
#include <future>
#include <memory>

class MonteCarloSimulation {
public:
    MonteCarloSimulation(size_t num_sims, std::shared_ptr<StatisticalStrategy> strategy, std::unique_ptr<PayOff> payoff, ThreadPool& pool)
        : num_sims_(num_sims), strategy_(std::move(strategy)), payoff_(std::move(payoff)), pool_(pool) {}

    double run();

private:
    size_t num_sims_;
    std::shared_ptr<StatisticalStrategy> strategy_;
    std::unique_ptr<PayOff> payoff_;
    ThreadPool& pool_;
};

#endif // MONTE_CARLO_SIMULATION_H
