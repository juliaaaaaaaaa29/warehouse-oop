#pragma once
#include <map>
#include <vector>
#include <iostream>
#include "core.h"

class OrderManager : public IObserver, public std::enable_shared_from_this<OrderManager> {
    std::vector<std::shared_ptr<Order>> orders;
    std::map<std::string, int> activeOrders;
    double turnover = 0;
    int maxActive = 5;

public:
    std::shared_ptr<Order> createOrder(const std::string& customer) {
        if (activeOrders[customer] >= maxActive) throw std::runtime_error("Лимит заказов");
        auto order = std::make_shared<Order>(orders.size() + 1, customer);
        order->subscribe(shared_from_this()); 
        orders.push_back(order);
        activeOrders[customer]++;
        return order;
    }

    void onOrderEvent(const OrderEvent& event) override {
        if (event.newStatus == OrderStatus::Paid) {
            for (auto& o : orders) {
                if (o->getId() == event.orderId) {
                    turnover += o->getTotalPrice();
                    std::cout << "[Manager] Заказ " << event.orderId << " оплачен. Оборот: " << turnover << "\n";
                }
            }
        }
        else if (event.newStatus == OrderStatus::Cancelled || event.newStatus == OrderStatus::Delivered) {
            for (auto& o : orders) {
                if (o->getId() == event.orderId) activeOrders[o->getCustomer()]--;
            }
        }
    }
    double getTurnover() const { return turnover; }
};
