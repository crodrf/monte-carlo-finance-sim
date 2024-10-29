#include "payoff.h"
#include <algorithm>

PayOffCall::PayOffCall(double strike) : strike_(strike) {}

double PayOffCall::operator()(double spot) const {
    return std::max(spot - strike_, 0.0);
}

PayOffPut::PayOffPut(double strike) : strike_(strike) {}

double PayOffPut::operator()(double spot) const {
    return std::max(strike_ - spot, 0.0);
}
