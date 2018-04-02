#pragma once
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "listElement.cpp"
#include "IndexOutOfBoundsException.h"
#include "FileNotFoundException.h"


class Lista {
private:
	int size;
	//wskazniki na glowe i ogon
	listElement* head;
	listElement* tail;

	//zwraca wskaznik na element o podanym indeksie
	listElement* search(int index) {
		if (index < 0 || index >= size) return nullptr; //jezeli nie ma podanego indeksu zwraca wskaznik NULL

		listElement* element;

		//sprawdzamy w ktorej polowie listy jest indeks, pierwsza polowa zaczynamy od glowy a druga od ogona
		if (index <= size / 2) {
			element = head;				//zaczynamy od glowy
			for (int i = 0; i != index; i++) {
				element = element->rightPtr;
			}
		}
		else {
			element = tail->leftPtr;	//zaczynamy od ogona
			for (int i = size - 1; i != index; i--) {
				element = element->leftPtr;
			}
		}
		return element; //zwracanie wskaznika
	}

public:
	Lista() {
		size = 0;
		head = nullptr;
		tail = nullptr;
	}

	//destruktor, usuwa elementy zaczynajac od glowy
	~Lista() {
		while (head != tail) {
		head = head->rightPtr;
		delete head->leftPtr;
		}
		delete tail;
	}

	//tworzy liste na podstawie danych z pliku
	void readFile() {
		std::string fileName;
		std::cout << "Podaj nazwe pliku (razem z rozszerzeniem): ";
		std::getline(std::cin, fileName);

		std::fstream input;
		input.open(fileName, std::ios::in);

		//sprawdzenie czy udalo sie otworzyc, w przeciwnym razie rzucamy wyjatek
		if (!input.good()) throw FileNotFoundException();

		//pobranie pierwszej liczby (rozmiaru listy)
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

	//zwraca rozmiar listy
	int getSize() {
		return size;
	}

	//zwraca wartosc pod zadanym indeksem
	int get(int index) {

		//wyszukanie elementu
		listElement* element = search(index);

		//sprawdzenie czy element o danym indeksie znajduje sie w ogole na liscie
		if (element == nullptr) throw IndexOutOfBoundsException();

		//jezeli jest to zwracane jest jego value
		else return element->value;

	}

	//dodawanie elementu na poczatek listy
	void pushFront(int _value) {
		if (size == 0) {	//rozmiar == 0 wiec tworzymy nowa liste

			//nowa glowa o wartosci _value
			head = new listElement(nullptr, _value, nullptr);

			//pusty ogon ze wskaznikiem na poprzedni element, czyli w tym przypadku glowe
			tail = new listElement(head, 0, nullptr);

			//przypisane do prawego wskaznika glowy adres ogona
			head->rightPtr = tail;
			size++;
		}
		else {				//przypadek gdzie jest juz lista o rozmiarze > 0

			//nowy element z prawym wskaznikiem na glowe i lewym na NULL
			head->leftPtr = new listElement(nullptr, _value, head);

			//zmiana lewego wskaznika starej glowy na nowa
			head = head->leftPtr;
			size++;
		}
	}

	//dodawanie elementu na koniec listy
	void pushBack(int _value) {

		//gdy lista jest pusta tworzymy nowa liste uczywajac kodu z pushFront()
		if (size == 0) pushFront(_value); 

		//przypadek gdzie jest lista o rozmiarze > 0
		else {

			//ogon dostaje wartosc _value
			tail->value = _value;

			//prawy wskaznik dostaje adres nowego ogona a wskaznik na ogon listy dostaje adres nowego elementu
			tail->rightPtr = new listElement(tail, 0, nullptr);
			tail = tail->rightPtr;
			size++;
		}
	}

	//usuwanie elementu z poczatku
	void popFront() {

		//jezeli lista jest pusta to nie robi nic
		if (size == 0) return;

		//jezeli lista ma rozmiar 1 usuwamy glowe i ogon
		if (size == 1) {
			delete head;
			delete tail;
			size = 0;
			head = nullptr;
			tail = nullptr;
		}

		//przypadek gdzie lista ma rozmiar > 1
		else {

			//wskaznik na glowe dostaje adres kolejnego elementu listy
			head = head->rightPtr;

			//usuwamy pierwszy element, czyli ten na lewym wskazniku nowej glowy
			delete head->leftPtr;

			//lewy wskaznik ustawiamy na NULL
			head->leftPtr = nullptr;
			size--;
		}
	}

	//usuwanie elementu z konca
	void popBack() {

		//jezeli rozmiar listy to 1 lub 0 to postepujemy dokladnie jak w popFront()
		if (size == 1 || size == 0) popFront();
		else {

			//wskaznik na ogon dostaje adres poprzedniego elementu, ktory zostaje nowym ogonem
			tail = tail->leftPtr;

			//usuwamy "stary" ogon
			delete tail->rightPtr;
			size--;
		}
	}

	//wstawiane elementu na dowolny indeks w zakresie listy
	void put(int index, int _value) {

		//szukanie elementu o zadanym indeksie
		listElement* element = search(index); 

		//sprawdzenie czy element o danym indeksie znajduje sie w ogole na liscie
		if (element == nullptr) throw IndexOutOfBoundsException();

		//wstawianie i przesuniecie dotychczasowego elementu o podanym indeksie o 1 dalej
		listElement* _element = new listElement(element->leftPtr, _value, element);
		(_element->leftPtr)->rightPtr = _element;
		element->leftPtr = _element;
		size++;
	}

	//usuwanie elementu o podanym indeksie
	void remove(int index) {

		//wyszukanie elementu do usuniecia
		listElement* element = search(index);

		//sprawdzenie czy element o danym indeksie znajduje sie w ogole na liscie
		if (element == nullptr) throw IndexOutOfBoundsException();

		delete element;
		size--;
	}

	//funkcja podmieniajaca klucz pod podanym indeksem
	void replace(int index, int _value) {

		//szukanie elementu do zamiany
		listElement* element = search(index);

		//sprawdzenie czy element o danym indeksie znajduje sie w ogole na liscie
		if (element == nullptr) throw IndexOutOfBoundsException();

		element->value = _value;
	}

	//szukanie podanej wartosci na liscie
	int searchVal(int _value) {
		listElement* frontElement = head;
		listElement* backElement = tail->leftPtr;

		for (int i = 0; i <= size / 2; i++) {

			//jezeli znajdzie wartosc zwraca indeks elementu listy
			if (frontElement->value == _value) return i;
			if (backElement->value == _value) return size - i - 1;

			//przejscie na kolejne elementy do przeszukiwana	
			frontElement = frontElement->rightPtr;
			backElement = backElement->leftPtr;
		}

		//zwraca -1 gdy nie odnajdzie wartosci
		return -1;
	}

	//przeladowanie operatora by wypisac liste
	friend std::ostream & operator<<(std::ostream & output, Lista & lista) {
		output << "Lista: [";
		for (int i = 0; i < lista.getSize(); i++) {
			output << lista.get(i);
			if (i == lista.getSize() - 1) output << "]\n";
			else output << ",";
		}
		return output;
	}
};