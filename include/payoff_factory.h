#ifndef PAYOFF_FACTORY_H
#define PAYOFF_FACTORY_H

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include "payoff.h"

class PayOffFactory {
public:
    static std::unique_ptr<PayOff> createPayOff(const std::string& type, double strike);
    static void registerPayOff(const std::string& type, std::function<std::unique_ptr<PayOff>(double)> creator);

private:
    static std::unordered_map<std::string, std::function<std::unique_ptr<PayOff>(double)>> registry;
};

#endif
