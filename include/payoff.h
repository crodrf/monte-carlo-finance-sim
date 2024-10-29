#ifndef PAYOFF_H
#define PAYOFF_H

class PayOff {
public:
    virtual ~PayOff() = default;
    virtual double operator()(double spot) const = 0;
};

class PayOffCall : public PayOff {
public:
    explicit PayOffCall(double strike);
    double operator()(double spot) const override;

private:
    double strike_;
};

class PayOffPut : public PayOff {
public:
    explicit PayOffPut(double strike);
    double operator()(double spot) const override;

private:
    double strike_;
};

#endif // PAYOFF_H
