#pragma once
#include <stdexcept>

class Price {
private:
	int value;
public:
	Price(int val) :value(val) {
		if (val < 0) {
			throw std::invalid_argument("÷ена не может быть отрицательной");
		}
	}
	int getValue() const {
		return value;
	}
	void setValue(int newVal) {
		if (newVal < 0) throw std::invalid_argument("÷ена не может быть отрицательной");
			value= newVal;
	}
	double asRubles() const {
		return value / 100.0 ;
	}
};

class Quantity {
private:
	int value;
public:
	Quantity(int val) :value(val) {
		if (val < 0) {
			throw std::invalid_argument(" оличество не может быть отрицательной");
		}
	}
	int getValue() const {
		return value;
	}
	void setValue(int newVal) {
		if (newVal < 0) throw std::invalid_argument(" оличество не может быть отрицательной");
			value = newVal;
	}
	void change(int delta) {
		if (value + delta < 0) {
			throw std::invalid_argument(" оличество не может стать отрицательным");
		}
		value += delta;
	}
};

class Weight {
private:
	double grams;
public:
	Weight(double gram) :grams(gram) {
		if (gram < 0) {
			throw std::invalid_argument("¬ес не может быть отрицательной");
		}
	}
	int getValue() const {
		return grams;
	}
	void setValue(double newGram) {
		if (newGram < 0) throw std::invalid_argument("¬ес не может быть отрицательной");
			grams = newGram;
	}
	double asKg() const{
		return grams / 1000.0;
	}
};