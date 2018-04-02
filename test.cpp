#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "tablica.cpp"
#include "lista.cpp"
#include "kopiec.cpp"
#include "RNG.cpp"
#include <Windows.h>
#include <time.h>

double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter() {
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		std::cout << "QueryPerformanceFrequency failed!\n";

	PCFreq = double(li.QuadPart) / 1000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter() {
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

inline void test() {

	int rozmiaryTab[4] = { 1000,2000,5000,10000 };

	for (int i = 0, range = 25000; i < 2; i++, range = 3 * range) {

		double srednie[4];
		for (int kolejny_rozm = 0; kolejny_rozm < 4; kolejny_rozm++) {

			int rozmiar = rozmiaryTab[kolejny_rozm];
			RandomInputGenerator gen = *(new RandomInputGenerator());
			gen.generate(rozmiar, range);
			int* data = gen.getData();

			Lista tab = *(new Lista());

			for (int i = 0; i < rozmiar; i++) {
				tab.pushBack(*(data + i));
				/*if (i == rozmiar - 100)
				tab.push(50000);
				else
				tab.push(100000);*/
			}

			std::cout << tab << std::endl;

			double avg[10];

			srand(time(NULL));
			for (int i = 0; i < 10; i++) {

				double wyniki[100];

				//testy
				//LARGE_INTEGER countStart, countEnd;
				for (int i = 0; i < 100; i++) {

					int x = rand() % range;
					//tab.pop();
					//tab.push(x);
					//int index = rozmiar / 2;
					//tab.replace(index, x);
					//int index = rozmiar;
					//index = index - 100;
					//int value = tab.get(index);
					/*POMIAR*/
					StartCounter();
					//tab.pushFront(x); //!!!!!!!!!!!!!!!!!!!!!!!!TESTOWANA FUNKCJA!!!!!!!!!!!!!!!!!!!!!!!!!!!!
					//endtim
					/*--------*/
					//tab.pop();
					tab.popFront();
					//tab.put(index,x);
					//tab.removeIndex(index);
					//obliczenie pojedynczego wyniku
					double result = GetCounter();

					//zapisanie wyniku do tablicy
					wyniki[i] = result;
					//delete &tab;
				}
				double suma = 0;
				for (int i = 0; i < 100; i++)
					suma += wyniki[i];
				suma = suma / 100;

				avg[i] = suma;
			}
			double suma = 0;
			for (int i = 0; i < 10; i++)
				suma += avg[i];
			suma = suma / 10;
			srednie[kolejny_rozm] = suma;
		}
		
		//zapisanie srednich czasow do pliku
		std::fstream plik;
		std::stringstream konwerter;
		std::string buf;

		std::string nazwa = "srednieCzasy";

		konwerter << range;
		buf = konwerter.str();

		nazwa.append("range");
		nazwa.append(buf);
		nazwa.append(".txt");

		plik.open(nazwa, std::ios::out);
		for (int i = 0; i < 4; i++) plik << srednie[i] << ";";
		plik.close();

	}
	return;
}