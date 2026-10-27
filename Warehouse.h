#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "Product.h"

class WarehouseIterator {
    using Iter = std::vector<std::unique_ptr<Product>>::iterator;
    Iter current_;
    Iter end_;
public:
    WarehouseIterator(Iter current, Iter end) : current_(current), end_(end) {}

    Product& operator*() const { return **current_; }
    Product* operator->() const { return current_->get(); }

    WarehouseIterator& operator++() { ++current_; return *this; }

    bool operator!=(const WarehouseIterator& other) const { return current_ != other.current_; }
    bool operator==(const WarehouseIterator& other) const { return current_ == other.current_; }
};

class ConstWarehouseIterator {
    using Iter = std::vector<std::unique_ptr<Product>>::const_iterator;
    Iter current_;
    Iter end_;
public:
    ConstWarehouseIterator(Iter current, Iter end) : current_(current), end_(end) {}

    const Product& operator*() const { return **current_; }
    const Product* operator->() const { return current_->get(); }

    ConstWarehouseIterator& operator++() { ++current_; return *this; }

    bool operator!=(const ConstWarehouseIterator& other) const { return current_ != other.current_; }
    bool operator==(const ConstWarehouseIterator& other) const { return current_ == other.current_; }
};

class Warehouse {
private:
    std::vector<std::unique_ptr<Product>> products;
    size_t maxSize;
public:
    explicit Warehouse(size_t maxSize) : maxSize(maxSize) {
        if (maxSize == 0)
            throw std::invalid_argument("Размер не может быть нулевым");
    }

    Warehouse(const Warehouse& other) : maxSize(other.maxSize) {
        for (const auto& p : other.products)
            products.push_back(p->clone());
    }

    Warehouse& operator=(const Warehouse& other) {
        if (this != &other) {
            Warehouse temp(other);
            std::swap(products, temp.products);
            std::swap(maxSize, temp.maxSize);
        }
        return *this;
    }

    Warehouse(Warehouse&& other) 
        : products(std::move(other.products)), maxSize(other.maxSize) {
        other.maxSize = 0;
    }

    Warehouse& operator=(Warehouse&& other) {
        if (this != &other) {
            products = std::move(other.products);
            maxSize = other.maxSize;
            other.maxSize = 0;
        }
        return *this;
    }

    ~Warehouse() = default;

    bool addProduct(std::unique_ptr<Product> product) {
        if (!product) return false;
        if (products.size() >= maxSize) return false;
        products.push_back(std::move(product));
        return true;
    }

    bool removeById(int id) {
        auto it = std::find_if(products.begin(), products.end(),
            [id](const std::unique_ptr<Product>& p) { return p->getId() == id; });
        if (it == products.end()) return false;
        products.erase(it);
        return true;
    }

    bool removeByIndex(size_t index) {
        if (index >= products.size()) return false;
        products.erase(products.begin() + index);
        return true;
    }

    bool transferProduct(int id, Warehouse& other) {
        auto it = std::find_if(products.begin(), products.end(),
            [id](const std::unique_ptr<Product>& p) { return p->getId() == id; });

        if (it == products.end()) return false;

        auto copy = (*it)->clone();

        if (other.addProduct(std::move(copy))) {
            products.erase(it);
            return true;
        }
        return false; 
    }

    Product* findById(int id) {
        for (const auto& p : products)
            if (p->getId() == id) return p.get();
        return nullptr;
    }

    std::vector<Product*> findByCategory(const std::string& category) {
        std::vector<Product*> result;
        for (const auto& p : products)
            if (p->getCategory() == category)
                result.push_back(p.get());
        return result;
    }

    std::vector<Product*> findByPrice(const Price& price) {
        std::vector<Product*> result;
        for (const auto& p : products)
            if (p->getPrice().getValue() == price.getValue())
                result.push_back(p.get());
        return result;
    }

    size_t size() const { return products.size(); }

    WarehouseIterator begin() { return WarehouseIterator(products.begin(), products.end()); }
    WarehouseIterator end() { return WarehouseIterator(products.end(), products.end()); }

    ConstWarehouseIterator begin() const { return ConstWarehouseIterator(products.begin(), products.end()); }
    ConstWarehouseIterator end()   const { return ConstWarehouseIterator(products.end(), products.end()); }
};