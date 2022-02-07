//Plik: SimulatedAnealing.h
//Autor: Bartosz Szymczak, 252734
//Projekt 2 PEA
//Grudzieñ 2021r.

#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include "Timer.h"

using namespace std;

#pragma once

//Klasa SimulatedAnealing odpowiedzialna jest za przeprowadzanie algorytmu symulowanego wy¿arzania dla asymetrycznego problemu komiwoja¿era na podanych danych
class SimulatedAnealing
{
public:
	//Konstruktor przypisuje wartoœci zmiennym, 
	//przekazywane argumenty to macierz miast i tras pomiêdzy nimi, nad któr¹ bêd¹ przeprowadzane obliczenia oraz kryterium stopu
	SimulatedAnealing(vector<vector<int>> matrix, float sc);
	//Metoda wykonuje algorytm symulowanego wy¿arzania na podanych w konstruktorze danych
	void doSimulatedAnealing();
private:
	//Zmienna przechowuj¹ca minimaln¹ wartoœæ temperatury
	float minTemperature;
	//Zmienna przechowuj¹ca wartoœæ temperatury
	float temperature;
	//Zmienna przechowuj¹ca wspó³czynnik zwi¹zany ze zmian¹ temperatury - sch³adzanie
	float a;
	//Zmienna przechowuj¹ca indeks miasta startowego 
	int firstTown;
	//Macierz miast i tras pomiêdzy nimi, nad któr¹ bêd¹ przeprowadzane obliczenia
	vector<vector<int>> temp;
	//Iloœæ miast w macierzy
	int size;
	//Zmienna przechowuj¹ca kryterium stopu
	float stopCriterion;
	//Metoda pomocnicza oblicza i zwraca koszt podanej œcie¿ki
	int countPath(vector<int> path);
	//Metoda pomocnicza ustala pierwsze rozwi¹zanie przy u¿yciu prostego algorytmu zach³annego i zwraca jej koszt
	int greedySA(vector<int>& path);
	//Metoda pomocnicza umieszcza miasto o indeksie indexToDelete, w miejscu o indeksie indexToPut w œcie¿ce path
	void insert(int indexToDelete, int indexToPut, vector<int>& path);
};

