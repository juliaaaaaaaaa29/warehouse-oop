#pragma once
#include <stdexcept>

class Price {
private:
	int value;
public:
	Price(int val) :value(val) {
		if (val < 0) {
			throw std::invalid_argument("Öåíà íå ìîæåò áûòü îòðèöàòåëüíîé");
		}
	}
	int getValue() const {
		return value;
	}
	void setValue(int newVal) {
		if (newVal < 0) throw std::invalid_argument("Öåíà íå ìîæåò áûòü îòðèöàòåëüíîé");
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
			throw std::invalid_argument("Êîëè÷åñòâî íå ìîæåò áûòü îòðèöàòåëüíîé");
		}
	}
	int getValue() const {
		return value;
	}
	void setValue(int newVal) {
		if (newVal < 0) throw std::invalid_argument("Êîëè÷åñòâî íå ìîæåò áûòü îòðèöàòåëüíîé");
			value = newVal;
	}
	void change(int delta) {
		if (value + delta < 0) {
			throw std::invalid_argument("Êîëè÷åñòâî íå ìîæåò ñòàòü îòðèöàòåëüíûì");
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
			throw std::invalid_argument("Âåñ íå ìîæåò áûòü îòðèöàòåëüíîé");
		}
	}
	int getValue() const {
		return grams;
	}
	void setValue(double newGram) {
		if (newGram < 0) throw std::invalid_argument("Âåñ íå ìîæåò áûòü îòðèöàòåëüíîé");
			grams = newGram;
	}
	double asKg() const{
		return grams / 1000.0;
	}
};
