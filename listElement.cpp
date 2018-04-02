#pragma once
#include "stdafx.h"

class listElement {
	friend class Lista;
private:
	int value;
	listElement* leftPtr;
	listElement* rightPtr;
public:

	//konstruktor elementu listy
	listElement(listElement* _leftPtr, int _value, listElement* _rightPtr) {
		value = _value;
		leftPtr = _leftPtr;
		rightPtr = _rightPtr;
	}

	//bezargumentowy konstruktor elementu listy
	//tworzy "pusty" element o wartości 0 i wskaznikach na NULL
	listElement() {
		new listElement(nullptr, 0, nullptr);
	}

	//destruktr, zamienia wskazniki sasiednich elementow by wskazywaly na siebie
	~listElement() {
		if (leftPtr != nullptr) leftPtr->rightPtr = this->rightPtr;
		if (rightPtr != nullptr) rightPtr->leftPtr = this->leftPtr;
	}
};