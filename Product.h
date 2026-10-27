#pragma once
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include "Attributes.h"
class Warehouse;

class Product {
protected:
	int id;
	std::string name;
	Price price;
	Quantity quantity;
	Weight weight;
	std::string category;

	static int generateId() {
		static int nextId = 1; 
		return nextId++;
	}

public:
	Product(const std::string& name, const Price& price, const Quantity& quantity, const Weight& weight, const std::string& category) :
		id(generateId()), name(name), price(price), quantity(quantity), weight(weight), category(category) {}

	virtual ~Product() = default;
	virtual std::unique_ptr<Product> clone() const = 0;
	virtual void describe() const = 0;

	int getId() const { return id; }
	const std::string& getName() const { return name; }
	const Price& getPrice() const { return price; }
	const Quantity& getQuantity() const { return quantity; }
	const Weight& getWeight() const { return weight; }
	const std::string& getCategory() const{ return category; }

	void setPrice(const Price& newPrice) {
		price= newPrice;
	}

	void changeQuantity(int delta) {
		int newVal = quantity.getValue() + delta;
		if (newVal < 0) {
			throw std::invalid_argument("Количество не может быть отрицательным");
		}
		quantity.setValue(newVal);
	}
};

class Clothing : public Product {
public:
	Clothing(const std::string& name, const Price& p, const Quantity& q, const Weight& w) :
		Product(name, p, q, w, "одежда") {}
};

class Food : public Product {
public:
	Food(const std::string& name, const Price& p, const Quantity& q, const Weight& w) :
		Product(name, p, q, w, "еда") {
	}
};

class Electronics : public Product {
public:
	Electronics(const std::string& name, const Price& p, const Quantity& q, const Weight& w) :
		Product(name, p, q, w, "электроника") {
	}
};

class Smartphone : public Electronics {
	std::string model;
public:
	Smartphone(const std::string& name, const Price& p, const Quantity& q, const Weight& w, std::string model = "iphone") :
		Electronics(name, p, q, w), model(model) {
	}

	std::unique_ptr<Product> clone() const override {
		return std::make_unique<Smartphone>(*this);
	}

	void describe() const override {
		std::cout << "Телефон " << id << "\n";
		std::cout << "Название: " << name << "\n";
		std::cout << "Цена: " << price.asRubles() << "\n";
		std::cout << "Количество: " << quantity.getValue() << "\n";
		std::cout << "Вес: " << weight.asKg() << "\n";
		std::cout << "Модель: " << model << "\n";
	}
};

class Laptop : public Electronics {
	int memoryGB;
public:
	Laptop(const std::string& name, const Price& p, const Quantity& q, const Weight& w, int memoryGB = 16) :
		Electronics( name, p, q, w), memoryGB(memoryGB) {
	}

	std::unique_ptr<Product> clone() const override {
		return std::make_unique<Laptop>(*this);
	}

	void describe() const override {
		std::cout << "Ноутбук " << id << "\n";
		std::cout << "Название: " << name << "\n";
		std::cout << "Цена: " << price.asRubles() << "\n";
		std::cout << "Количество: " << quantity.getValue() << "\n";
		std::cout << "Вес: " << weight.asKg() << "\n";
		std::cout << "Память Гб: " << memoryGB << "\n";
	}
};

class Jacket : public Clothing {
	int size;
public:
	Jacket(const std::string& name, const Price& p, const Quantity& q, const Weight& w, int size = 42) :
		Clothing(name, p, q, w), size(size) {
	}

	std::unique_ptr<Product> clone() const override {
		return std::make_unique<Jacket>(*this);
	}

	void describe() const override {
		std::cout << "Куртка " << id << "\n";
		std::cout << "Название: " << name << "\n";
		std::cout << "Цена: " << price.asRubles() << "\n";
		std::cout << "Количество: " << quantity.getValue() << "\n";
		std::cout << "Вес: " << weight.asKg() << "\n";
		std::cout << "Размер: " << size << "\n";
	}
};

class  TShirt : public Clothing {
	std::string color;
public:
	TShirt(const std::string& name, const Price& p, const Quantity& q, const Weight& w, std::string color = "белая") :
		Clothing(name, p, q, w), color(color) {
	}

	std::unique_ptr<Product> clone() const override {
		return std::make_unique<TShirt>(*this);
	}

	void describe() const override {
		std::cout << "Футболка " << id << "\n";
		std::cout << "Название: " << name << "\n";
		std::cout << "Цена: " << price.asRubles() << "\n";
		std::cout << "Количество: " << quantity.getValue() << "\n";
		std::cout << "Вес: " << weight.asKg() << "\n";
		std::cout << "Цвет: " << color << "\n";
	}
};

class Milk : public Food {
	double fatPercent;
public:
	Milk(const std::string& name, const Price& p, const Quantity& q, const Weight& w, double fat = 3.2) :
		Food(name, p, q, w), fatPercent(fat) {
	}

	std::unique_ptr<Product> clone() const override {
		return std::make_unique<Milk>(*this);
	}

	void describe() const override {
		std::cout << "Молоко " << id << "\n";
		std::cout << "Название: " << name << "\n";
		std::cout << "Цена: " << price.asRubles() << "\n";
		std::cout << "Количество: " << quantity.getValue() << "\n";
		std::cout << "Вес: " << weight.asKg() << "\n";
		std::cout << "Жирность: " << fatPercent << "%\n";
	}
};

class Bread : public Food {
	bool isGlutenFree;
public:
	Bread(const std::string& name, const Price& p, const Quantity& q, const Weight& w, bool glutenFree = false) :
		Food(name, p, q, w), isGlutenFree(glutenFree) {
	}

	std::unique_ptr<Product> clone() const override {
		return std::make_unique<Bread>(*this);
	}

	void describe() const override {
		std::cout << "Хлеб " << id << "\n";
		std::cout << "Название: " << name << "\n";
		std::cout << "Цена: " << price.asRubles() << "\n";
		std::cout << "Количество: " << quantity.getValue() << "\n";
		std::cout << "Вес: " << weight.asKg() << "\n";
		std::cout << "Без глютена: " << (isGlutenFree ? "Да" : "Нет") << "\n";
	}
};

