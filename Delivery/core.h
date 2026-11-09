#pragma once
#include <vector>
#include <memory>
#include <string>
#include "product.h"

enum class OrderStatus { Pending, Paid, Shipped, Delivered, Cancelled };

class OrderEvent {
public:
    int orderId;
    OrderStatus oldStatus;
    OrderStatus newStatus;
    int timestamp; 

    OrderEvent(int id, OrderStatus oldS, OrderStatus newS)
        : orderId(id), oldStatus(oldS), newStatus(newS) {
        static int eventCounter = 0;
        timestamp = ++eventCounter;
    }
};

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void onOrderEvent(const OrderEvent& event) = 0;
};

class IObservable {
public:
    virtual ~IObservable() = default;
    virtual void subscribe(std::shared_ptr<IObserver> obs) = 0; 
    virtual void notify(const OrderEvent& event) = 0;
};
class Delivery;

class Order : public IObservable {
private:
    int id;
    std::string customer;
    std::vector<std::shared_ptr<Product>> items;
    OrderStatus status = OrderStatus::Pending;

    double deliveryCost = 0.0;
    double discountAmount = 0.0;
    std::shared_ptr<Delivery> currentDelivery = nullptr;

    std::vector<std::weak_ptr<IObserver>> observers;

public:
    Order(int id, std::string cust) : id(id), customer(cust) {}

    void subscribe(std::shared_ptr<IObserver> obs) override {
        observers.push_back(obs);
    }

    void notify(const OrderEvent& event) override {
        for (auto& weak_obs : observers) {
            if (auto obs = weak_obs.lock()) { 
                obs->onOrderEvent(event);
            }
        }
    }

    void setStatus(OrderStatus newStatus) {
        if (status != newStatus) {
            OrderStatus old = status;
            status = newStatus;
            notify(OrderEvent(id, old, status));
        }
    }

    void addItem(std::shared_ptr<Product> item) { items.push_back(item); }
    int getId() const { return id; }
    std::string getCustomer() const { return customer; }
    OrderStatus getStatus() const { return status; }

    void setDelivery(std::shared_ptr<Delivery> d);

    void setDiscountAmount(double amount) { discountAmount = amount; }
    void addDiscount(double amount) { discountAmount += amount; }

    double getTotalWeight() const {
        if (status == OrderStatus::Cancelled) return 0.0;
        double w = 0;
        for (auto& i : items) w += i->getWeight();
        return w;
    }

    double getTotalPrice() const {
        if (status == OrderStatus::Cancelled) return 0.0;
        double p = 0;
        for (auto& i : items) p += i->getTotalPrice();
        p += deliveryCost - discountAmount;
        return (p < 0) ? 0 : p;
    }
};