#pragma once
#include "core.h"
#include <iostream>
#include <stdexcept>

class Delivery {
public:
    virtual ~Delivery() = default;
    virtual double getCost(const Order& order) const = 0;
    virtual std::string getEstimatedTime() const = 0;
    virtual bool isAvailable(const Order& order) const = 0;
};

inline void Order::setDelivery(std::shared_ptr<Delivery> d) {
    currentDelivery = d;
    if (d) deliveryCost = d->getCost(*this);
}

class CourierDelivery : public Delivery {
public:
    double getCost(const Order&) const override { return 500.0; }
    std::string getEstimatedTime() const override { return "1-2 дн€"; }
    bool isAvailable(const Order& order) const override { return order.getTotalWeight() <= 20.0; }
};

class PickupDelivery : public Delivery {
public:
    double getCost(const Order&) const override { return 0.0; }
    std::string getEstimatedTime() const override { return "1-3 дн€"; }
    bool isAvailable(const Order&) const override { return true; }
};

class PostDelivery : public Delivery {
public:
    double getCost(const Order&) const override { return 200.0; }
    std::string getEstimatedTime() const override { return "5-10 дней"; }
    bool isAvailable(const Order& order) const override { return order.getTotalWeight() <= 10.0; }
};

class DeliveryProxy : public Delivery {
    std::shared_ptr<Delivery> realDelivery;
    mutable double cachedCost = -1.0;
public:
    DeliveryProxy(std::shared_ptr<Delivery> real) : realDelivery(real) {}

    double getCost(const Order& order) const override {
        if (cachedCost >= 0) return cachedCost;
        if (!realDelivery->isAvailable(order)) throw std::runtime_error("ƒоставка недоступна (превышен вес)");
        cachedCost = realDelivery->getCost(order);
        return cachedCost;
    }
    std::string getEstimatedTime() const override { return realDelivery->getEstimatedTime(); }
    bool isAvailable(const Order& order) const override { return realDelivery->isAvailable(order); }
};
