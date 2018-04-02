#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "IndexOutOfBoundsException.h"
#include "FileNotFoundException.h"


class Tablica {
private:
	int* head;
	int size;
public:
	Tablica(int* tab, int lenght) {
		head = tab;
		size = lenght;
	}
	Tablica() {
		head = nullptr;
		size = 0;
	}
	~Tablica() {
		delete[] head;
	}

	//tworzy tablice na podstawie danych z pliku
	void readFile() {
		std::string fileName;
		std::cout << "Podaj nazwe pliku (razem z rozszerzeniem): ";
		std::getline(std::cin, fileName);

		std::fstream input;
		input.open(fileName, std::ios::in);

		//sprawdzenie czy udalo sie otworzyc, w przeciwnym razie rzucamy wyjatek
		if (!input.good()) throw FileNotFoundException();

		//pobranie pierwszej liczby (rozmiaru tablicy)
		bool end = false;
		bool opened = false;
		std::string line;
		getline(input, line);
		int _size = std::stoi(line, nullptr);
		size = _size;

		//pobieranie kolejno liczb z linii oraz zamiana string na int
		while (!input.eof()) {
			getline(input, line);
			this->pushBack(std::stoi(line, nullptr));
		}
	}

	//zwraca wartosc dla danego elementu
	int get(int index) {
		if (index < 0 || index >= size) throw IndexOutOfBoundsException();
		return *(head + index);
	}

	//zwraca rozmiar tablicy
	int getSize() {
		return size;
	}

	//podmiana wartosci na zadanym indeksie
	void replace(int index, int value) {
		if (size == 0) {
			head = new int[1];
			size++;
		}
		if (index < 0 || index >= size) throw IndexOutOfBoundsException();
		*(head + index) = value;
	}

	//dodanie klucza na poczatku tablicy
	void pushFront(int value) {
		if (size == 0) {
			head = new int[1];
			*head = value;
			size++;
		}
		else {
			int* ptr = new int[size + 1];
			memcpy(ptr + 1, head, size * sizeof(int));
			*ptr = value;
			head = ptr;
			size++;
		}
	}

	//dodanie klucza na koncu tablicy
	void pushBack(int value) {
		if (size == 0) {
			head = new int[1];
			*head = value;
			size++;
		}
		else {
			int* ptr = new int[size + 1];
			memcpy(ptr, head, size * sizeof(int));
			*(ptr + size) = value;
			head = ptr;
			size++;
		}
	}

	//usuwanie elementu o podanym indeksie
	void removeIndex(int index) {
		if (size == 0) return;
		if (index < 0 || index >= size) throw IndexOutOfBoundsException();

		int* ptr = new int[size - 1];
		memcpy(ptr, head, index * sizeof(int));
		size--;
		memcpy(ptr + index, head + index + 1, (size - index) * sizeof(int));
		head = ptr;
	}

	//usuwanie elementu na koncu tablicy
	void popBack() {
		removeIndex(this->size - 1);
	}

	//usuwanie elementu na poczatku tablicy
	void popFront() {
		removeIndex(0);
	}

	//wstawianie elementu na dwolne miejsce tablicy oraz przesuniecie dotychczasowego o jeden wyzej
	void put(int index, int value) {
		if (size == 0) return;
		if (index < 0 || index >= size) throw IndexOutOfBoundsException();

		int* ptr = new int[size + 1];
		memcpy(ptr, head, index * sizeof(int));
		*(ptr + index) = value;
		memcpy(ptr + index + 1, head + index, (size - index) * sizeof(int));
		head = ptr;
		size++;
	}

	//szukanie danej wartosci
	int search(int value) {
		for (int i = 0; i < size; i++) {
			if ((*head + i) == value) return i;
		}
		return -1; //zwraca -1 gdy nie odnaleziono elementu
	}

	//przeladowanie operatora by moc wypisywac tablice
	friend std::ostream & operator<<(std::ostream& output, Tablica& tab) {
		output << "Tablica: [";
		for (int i = 0; i < tab.getSize(); i++) {
			output << tab.get(i);
			if (i == tab.getSize() - 1)
				output << "]\n";
			else
				output << ",";
		}
		return output;
	}

};
