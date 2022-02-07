//Plik: BruteForce.h
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//PaŸdziernik 2021r.

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using std::string;
using namespace std;

//Klasa BruteForce odpowiedzialna jest za przeprowadzaniu algorytmu przeszukania zupe³nego dla asymetrycznego problemu komiwoja¿era na podanych danych
class BruteForce
{
private:
	//Zmienne przechowuj¹ce odpowiednio koszt najkrótszej œcie¿ki oraz iloœæ miast
	int cost,size;
	//Wektor przechowuj¹cy miasta wchodz¹ce w sk³ad najkrótszej œcie¿ki 
	vector<int> path;
	//Macierz przechowuj¹ca tymczasowo przekazan¹ macierz po³¹czeñ miêdzy miastami
	vector<vector<int>> temp;
public:
	//Konstruktor przypisuje wartoœci zmiennym, przekazywany argument to macierz miast i tras pomiêdzy nimi, nad któr¹ bêd¹ przeprowadzane obliczenia
	BruteForce(vector<vector<int>> matrix);
	//Metoda doBruteForce() s³u¿y do wykonania algorytmu przeszukania zupe³nego na danych przekazanych w konstruktorze
	void doBruteForce();
	//Metoda pomocnicza countCost(vector<int> path) oblicza i zwraca koszt œcie¿ki przekazanej w argumencie
	int countCost(vector<int> path);
	//Metoda showPath() s³u¿y do wyœwietlenia wyznaczonej œcie¿ki
	void showPath();
};

