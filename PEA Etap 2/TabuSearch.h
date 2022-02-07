//Plik: TabuSearch.h
//Autor: Bartosz Szymczak, 252734
//Projekt 2 PEA
//Grudzieñ 2021r.

#pragma once

#include "Towns.h"
#include <vector>
#include <algorithm>
#include "Timer.h"
using namespace std;

//Struktura elementów tabu przechowuje informacje o indeksach modyfikowanych miast oraz o "czasie ¿ycia" elementu
struct TabuElement
{
	int town1, town2, lifetime;
};

//Klasa TabuSearch odpowiedzialna jest za przeprowadzanie algorytmu przeszukiwania Tabu dla asymetrycznego problemu komiwoja¿era na podanych danych
class TabuSearch
{
public:
	Timer t;
	//Konstruktor przypisuje wartoœci zmiennym, 
	//przekazywane argumenty to macierz miast i tras pomiêdzy nimi, nad któr¹ bêd¹ przeprowadzane obliczenia oraz kryterium stopu
	TabuSearch(vector<vector<int>> matrix, float sc);
	//Metoda wykonuje algorytm przeszukiwania Tabu na podanych w konstruktorze danych
	void doTabuSearch();
private:
	//Wektor przechowuje elementy tabu
	vector<TabuElement> tabuList;
	//Macierz miast i tras pomiêdzy nimi, nad któr¹ bêd¹ przeprowadzane obliczenia
	vector<vector<int>> temp;
	//Iloœæ miast w macierzy
	int size;
	//Zmienna przechowuje istnienie dywersyfikacji 
	bool diversification;
	//Zmienna przechowuj¹ca kryterium stopu
	float stopCriterion;
	//Zmienna przechowuj¹ca indeks miasta startowego 
	int firstTown;
	//Metoda pomocnicza ustala pierwsze rozwi¹zanie przy u¿yciu prostego algorytmu zach³annego i zwraca jej koszt
	int greedyTS(vector<int>& path);
	//Metoda pomocnicza oblicza i zwraca koszt podanej œcie¿ki
	int countPath(vector<int> path);
	//Metoda pomocnicza sprawdza, czy element o podanych indeksach miast znajduje siê w liœcie tabu
	bool inTabuList(int town1, int town2);
	//Metoda pomocnicza zamienia miejscami miasta o podanych indeksach w podanej œcie¿ce 
	void swap(vector<int>& path, int town1, int town2);
	//Metoda pomocnicza wyszukuje najlepsze lokalne rozwi¹zanie i modyfikuje wektor elementów tabu
	void localSolution(vector<int>& path);
};

