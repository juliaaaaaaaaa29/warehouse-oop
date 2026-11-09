#pragma once
#include "Core.h"
#include "Delivery.h"

class Discount {
public:
    virtual ~Discount() = default;
    virtual void apply(Order& order) const = 0;
};

class PercentDiscount : public Discount {
public:
    void apply(Order& order) const override { order.addDiscount(order.getTotalPrice() * 0.10); }
};

class CashbackDiscount : public Discount {
public:
    void apply(Order& order) const override { order.addDiscount(order.getTotalPrice() * 0.05); }
};

class FreeDeliveryDiscount : public Discount {
public:
    void apply(Order& order) const override {
        order.addDiscount(order.getTotalPrice() - (order.getTotalPrice() - 0.0));
    }
};

class GiftDiscount : public Discount {
public:
    void apply(Order& order) const override {
        auto gift = std::make_shared<Product>(999, 1, 0.0, Product::getType("Подарок", 0.0, 0.3));
        order.addItem(gift);
    }
};

inline Order& operator+(Order& order, const Discount& disc) {
    disc.apply(order);
    return order;
}

inline Order& operator<<(std::shared_ptr<Delivery> delivery, Order& order) {
    if (delivery->isAvailable(order)) {
        order.setDelivery(delivery);
    }
    else {
        throw std::runtime_error("Доставка недоступна");
    }
    return order;
}