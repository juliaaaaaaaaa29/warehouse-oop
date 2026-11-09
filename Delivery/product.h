#pragma once
#include <string>
#include <memory>
#include <unordered_map>

class ProductType {
protected:
    std::string category;
    double basePrice;
    double baseWeight;
public:
    ProductType(std::string cat, double price, double weight)
        : category(cat), basePrice(price), baseWeight(weight) {
    }
    virtual ~ProductType() = default;

    double getBasePrice() const { return basePrice; }
    double getBaseWeight() const { return baseWeight; }
};

class Product {
private:
    int id;
    int quantity;
    double currentPrice;
    std::shared_ptr<ProductType> type;

public:
    Product(int id, int qty, double price, std::shared_ptr<ProductType> t)
        : id(id), quantity(qty), currentPrice(price), type(t) {
    }

    static std::shared_ptr<ProductType> getType(const std::string& category, double price, double weight) {
        static std::unordered_map<std::string, std::shared_ptr<ProductType>> typePool;

        if (typePool.find(category) == typePool.end()) {
            typePool[category] = std::make_shared<ProductType>(category, price, weight);
        }
        return typePool[category];
    }

    double getTotalPrice() const { return currentPrice * quantity; }
    double getWeight() const { return type->getBaseWeight() * quantity; }
};