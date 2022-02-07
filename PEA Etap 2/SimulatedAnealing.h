//Plik: SimulatedAnealing.h
//Autor: Bartosz Szymczak, 252734
//Projekt 2 PEA
//Grudzie� 2021r.

#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include "Timer.h"

using namespace std;

#pragma once

//Klasa SimulatedAnealing odpowiedzialna jest za przeprowadzanie algorytmu symulowanego wy�arzania dla asymetrycznego problemu komiwoja�era na podanych danych
class SimulatedAnealing
{
public:
	//Konstruktor przypisuje warto�ci zmiennym, 
	//przekazywane argumenty to macierz miast i tras pomi�dzy nimi, nad kt�r� b�d� przeprowadzane obliczenia oraz kryterium stopu
	SimulatedAnealing(vector<vector<int>> matrix, float sc);
	//Metoda wykonuje algorytm symulowanego wy�arzania na podanych w konstruktorze danych
	void doSimulatedAnealing();
private:
	//Zmienna przechowuj�ca minimaln� warto�� temperatury
	float minTemperature;
	//Zmienna przechowuj�ca warto�� temperatury
	float temperature;
	//Zmienna przechowuj�ca wsp�czynnik zwi�zany ze zmian� temperatury - sch�adzanie
	float a;
	//Zmienna przechowuj�ca indeks miasta startowego 
	int firstTown;
	//Macierz miast i tras pomi�dzy nimi, nad kt�r� b�d� przeprowadzane obliczenia
	vector<vector<int>> temp;
	//Ilo�� miast w macierzy
	int size;
	//Zmienna przechowuj�ca kryterium stopu
	float stopCriterion;
	//Metoda pomocnicza oblicza i zwraca koszt podanej �cie�ki
	int countPath(vector<int> path);
	//Metoda pomocnicza ustala pierwsze rozwi�zanie przy u�yciu prostego algorytmu zach�annego i zwraca jej koszt
	int greedySA(vector<int>& path);
	//Metoda pomocnicza umieszcza miasto o indeksie indexToDelete, w miejscu o indeksie indexToPut w �cie�ce path
	void insert(int indexToDelete, int indexToPut, vector<int>& path);
};

