#include "payoff_factory.h"
#include <stdexcept>

std::unordered_map<std::string, std::function<std::unique_ptr<PayOff>(double)>> PayOffFactory::registry;

std::unique_ptr<PayOff> PayOffFactory::createPayOff(const std::string& type, double strike) {
    auto it = registry.find(type);
    if (it != registry.end()) {
        return it->second(strike);
    }
    throw std::invalid_argument("Unknown PayOff type: " + type);
}

void PayOffFactory::registerPayOff(const std::string& type, std::function<std::unique_ptr<PayOff>(double)> creator) {
    registry[type] = std::move(creator);
}

// Helper function to register standard payoffs
bool register_standard_payoffs() {
    PayOffFactory::registerPayOff("call", [](double strike) { return std::make_unique<PayOffCall>(strike); });
    PayOffFactory::registerPayOff("put", [](double strike) { return std::make_unique<PayOffPut>(strike); });
    return true;
}

// Automatically register payoffs
bool payoffs_registered = register_standard_payoffs();
