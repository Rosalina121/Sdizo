#pragma once
#include "stdafx.h"
#include <string>
#include <fstream>
#include <time.h>


class RandomInputGenerator {
	int* tab;
	int size;

public:
	RandomInputGenerator() {
		tab = nullptr;
		size = 0;
	}

	~RandomInputGenerator() {
		delete[] tab;
	}

	//losowanie podanej ilosci liczb z danego zakresu
	void generate(int length, int range) {
		tab = new int[length];
		size = length;
		int x;
		srand(time(NULL));
		for (int i = 0; i < size; i++) {
			x = rand() % range;
			tab[i] = x;
		}
	}

	std::string saveToFile(std::string file_name) {

	}

	//zwracanie wskaznika na poczatek tablicy z liczbami
	int* getData() {
		return this->tab;
	}
};
