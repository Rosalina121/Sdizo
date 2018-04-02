#pragma once
#include "stdafx.h"
#include "Tablica.cpp"
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

class Kopiec {
private:
	Tablica* root;
	int size;

	//szukanie danej wartosci od podanego indeksu
	int search(int index, int value) {
		if (index >= this->size || index < 0) return -1;
		if (root->get(index) == value) return index;
		int leftChild = 2 * index + 1;
		int rightChild = leftChild + 1;
		int x = -1;
		x = search(leftChild, value);
		if (x == -1) x = search(rightChild, value);
		return x;
	}

	//rekurencyjne rysowanie kopca
	void drawHeap(std::ostream &  output, int index) {
		int child = 2 * index + 2;

		//dla prawego syna (jesli istnieje) wywolujemy funkcje
		if (child < size) drawHeap(output, child);

		//poziom elementu
		int elementLvl = (int)log2(index);

		//sprawdzenie czy jest maksymalnie lewy i ewentualne podwyzszenie poziomu o 1
		if (index == (int)exp2(elementLvl + 1) - 1) elementLvl++;

		//petla rysujaca
		for (int i = 0; i < elementLvl * 3; i++) {

			//przypadek gdzie jestesmy na ostatnim miejscu przed elementem do rysowania
			if (i == elementLvl * 3 - 1) {
				
				//dla prawego syna
				if (index % 2 == 0) output << "/";

				//dla lewego syna
				else output << "\\";
			}
			else {
				output << " ";
			}
		}

		//wartosc elementu
		output << root->get(index) << std::endl;

		child = 2 * index + 1;

		//dla lewego syna rowniez wywolujemy rekurencyjnie funkcje
		if (child < size) drawHeap(output, child);
	}

	//naprawa kopca w gore

	void fixUp(Tablica* tab, int len) {
		int i = len - 1;
		int parent = (i - 1) / 2;
		while (tab->get(parent) < tab->get(i)) {
			int bufor = tab->get(parent);

			//zamiana rodzica i nowego elementu
			tab->replace(parent, tab->get(i));
			tab->replace(i, bufor);

			//indeks nowego elementu
			i = parent;

			//rodzic nowego indeksu
			parent = (i - 1) / 2;
		}
	}

	void fixDown(Tablica* tab, int i, int len) {

		//indeks lewego syna
		int j = 2 * 1 + 1;

		while (j < len) {

			//szukamy wiekszego syna
			if (j + 1 < len && tab->get(j) < tab->get(j + 1)) j = j + 1;
			if (tab->get(i) >= tab->get(j)) break;
			int bufor = tab->get(i);

			//podmieniamy
			tab->replace(i, tab->get(j));
			tab->replace(j, bufor);
			i = j;
			j = 2 * i + 1;
		}
	}

public:

	//konstruktor, przypisuje pusta tablice pod korzen
	Kopiec() {
		root = new Tablica();
		size = 0;
	}

	//destruktor
	~Kopiec() {
		delete root;
	}
	
	//tworzy kopiec na podstawie danych z pliku
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
			this->push(std::stoi(line, nullptr));
		}
	}

	//zwraca element dla podanego indeksu
	int get(int index) {
		return root->get(index);
	}

	//dodawanie elementow
	void push(int value) {
		if (size == 0) {
			root->pushFront(value);
			size++;
			return;
		}
		size++;
		root->pushBack(value);
		fixUp(root, size);
	}

	//usuwanie elementu z korzenia
	void pop() {
		if (size == 0) return;

		//ostatni lisc idzie na miejsce korzenia
		root->replace(0, root->get(size - 1));

		//usuwamy ostatni lisc
		root->removeIndex(size - 1);
		size--;
		fixDown(root, 0, size);
	}

	//szukanie w kopcu po podanej wartosci
	int searchVal(int value) {
		return search(0, value);
	}

	//przeladowanie operatora
	friend std::ostream & operator<<(std::ostream & output, Kopiec & heap) {
		output << "Kopiec: " << *(heap.root);
		return output;
	}

	//rysowanie kopca
	void draw(std::ostream & output) {
		output << *this << std::endl;
		drawHeap(output, 0);
	}
};