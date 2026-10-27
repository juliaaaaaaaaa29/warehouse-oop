#pragma once
#include <memory>
#include <string>
#include "Product.h" 
#include "Attributes.h"

class ProductFactory {
public:
    virtual ~ProductFactory() = default;
    virtual std::unique_ptr<Product> createProduct(
      const std::string& name, int price, int quantity, double weight) = 0;
};

class SmartphoneFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(const std::string& name,
        int price, int quantity, double weight) override {
        return std::make_unique<Smartphone>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

class LaptopFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct( const std::string& name,
        int price, int quantity, double weight) override {
        return std::make_unique<Laptop>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

class TShirtFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(const std::string& name,
        int price, int quantity, double weight) override {
        return std::make_unique<TShirt>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

class JacketFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct(const std::string& name,
        int price, int quantity, double weight) override {
        return std::make_unique<Jacket>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

class MilkFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct( const std::string& name,
        int price, int quantity, double weight) override {
        return std::make_unique<Milk>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};

class BreadFactory : public ProductFactory {
public:
    std::unique_ptr<Product> createProduct( const std::string& name,
        int price, int quantity, double weight) override {
        return std::make_unique<Bread>(name, Price(price), Quantity(quantity), Weight(weight));
    }
};