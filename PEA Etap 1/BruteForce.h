//Plik: BruteForce.h
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//Pa�dziernik 2021r.

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using std::string;
using namespace std;

//Klasa BruteForce odpowiedzialna jest za przeprowadzaniu algorytmu przeszukania zupe�nego dla asymetrycznego problemu komiwoja�era na podanych danych
class BruteForce
{
private:
	//Zmienne przechowuj�ce odpowiednio koszt najkr�tszej �cie�ki oraz ilo�� miast
	int cost,size;
	//Wektor przechowuj�cy miasta wchodz�ce w sk�ad najkr�tszej �cie�ki 
	vector<int> path;
	//Macierz przechowuj�ca tymczasowo przekazan� macierz po��cze� mi�dzy miastami
	vector<vector<int>> temp;
public:
	//Konstruktor przypisuje warto�ci zmiennym, przekazywany argument to macierz miast i tras pomi�dzy nimi, nad kt�r� b�d� przeprowadzane obliczenia
	BruteForce(vector<vector<int>> matrix);
	//Metoda doBruteForce() s�u�y do wykonania algorytmu przeszukania zupe�nego na danych przekazanych w konstruktorze
	void doBruteForce();
	//Metoda pomocnicza countCost(vector<int> path) oblicza i zwraca koszt �cie�ki przekazanej w argumencie
	int countCost(vector<int> path);
	//Metoda showPath() s�u�y do wy�wietlenia wyznaczonej �cie�ki
	void showPath();
};

