#pragma once
#include "stdafx.h"
#include<iostream>

class IndexOutOfBoundsException {
public:
	IndexOutOfBoundsException() {}
	~IndexOutOfBoundsException() {}
	friend std::ostream& operator<<(std::ostream& output, IndexOutOfBoundsException ex) {
		output << "\nIndexOutOfBoundsException";
		return output;
	}
};