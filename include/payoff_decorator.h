#ifndef PAYOFF_DECORATOR_H
#define PAYOFF_DECORATOR_H

#include "payoff.h"
#include <iostream>

class PayOffDecorator : public PayOff {
protected:
    PayOff* wrappee;
public:
    explicit PayOffDecorator(PayOff* wrappee) : wrappee(wrappee) {}
    double operator()(double spot) const override {
        double result = (*wrappee)(spot);
        std::cout << "PayOff at spot " << spot << ": " << result << std::endl;
        return result;
    }
};

#endif
