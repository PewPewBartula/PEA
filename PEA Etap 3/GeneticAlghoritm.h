//Plik: GeneticAlghoritm.h
//Autor: Bartosz Szymczak, 252734
//Projekt 3 PEA
//Styczeñ 2022r.

#include "Timer.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

//Struktura elementu populacji, zawiera sciezke, jej koszt oraz wspolczynnik przystosowania
struct PopulationElement
{
	//Wektor przechowuj¹cy sciezke
	vector<int> path;
	//Zmienna przechowujaca koszt sciezki
	int cost;
	//Zmienna przechowujaca wspolczynnik przystosowania
	float fitness;
};

#pragma once
//Klasa GeneticAlghoritm odpowiedzialna jest za przeprowadzanie algorytmu genetycznego dla asymetrycznego problemu komiwojazera na podanych danych
class GeneticAlghoritm
{
public:
	Timer t;
	//Konstruktor przypisuje wartosci zmiennym, 
	//przekazywane argumenty to macierz miast i tras pomiedzy nimi,
	//kryterium stopu, wspolczynnik krzyzowania, wspolczynnik mutacji, wielkosc populacji i sposob mutacji
	GeneticAlghoritm(vector<vector<int>> matrix, float sc, float cross, float mut, int popSize,int mutMethod);
	//Metoda glowna, odpowiedzialna za przeprowadzenie algorytmu genetycznego, z uwzglednieniem podanych w konstruktorze danych 
	void doGA();
private:
	int resultTime;
	//Macierz miast i tras pomiedzy nimi, nad ktora beda przeprowadzane obliczenia
	vector<vector<int>> temp;
	//Wektor elementow populacji
	vector<PopulationElement> population;
	//Zmienna przechowujaca element populacji, zawierajacy najkrotsza, wynaczona przez algorytm sciezke - globalne rozwiazanie
	PopulationElement best;
	//Zmienna przechowujaca sposob mutacji
	int mutMethod;
	//Zmienna przechowujaca ilosc miast w macierzy
	int size;
	//Zmienna przechowujaca rozmiar populacji
	int populationSize;
	//Zmienna przechowujaca kryterium stopu
	float stopCriterion;
	//Zmienna przechowujaca wspolczynnik krzyzowania
	float crossoverRate;
	//Zmienna przechowujaca wspolczynnik mutacji
	float mutationRate;
	//Zmienna pomocnicza zwracajaca koszt podanej w argumencie sciezki
	int countPath(vector<int> path);
	//Metoda pomocnicza tworzaca populacje o podanej wielkosci
	void makePopulation(int n);
	//Metoda pomocnicza, uzupelnia wartosci elementow populacji oraz aktualizuje globalne rozwiazanie
	void countElements();
	//Metoda pomocnicza, zwraca sciezke z populacji na podstawie metody ruletkowej
	vector<int> pickPath();
	//Metoda pomocnicza, zwraca zmodyfikowana genetycznie sciezke, uzywajac algorytmu Order crossover (OX, Davis, 1985)
	//Sciezka zostaje stworzona przy uzyciu sciezek podanych w argumencie
	vector<int> crossOver(vector<int> pathA, vector<int>pathB);
	//Metoda pomocnicza, modyfikuje podana w argumencie populacje, uzywajac krzyzowania oraz mutacji
	void nextGeneration(vector<PopulationElement>& newPopulation);
	//Metoda pomocnicza, modyfikuje sciezke podana w argumencie, poprzez mutacje metoda swap lub insert
	void mutate(vector<int>& path);
	//Metoda pomocnicza, zamienia miejscami miasta o podanych indeksach w podanej sciezce
	void swap(vector<int>& path, int town1, int town2);
	//Metoda pomocnicza, zmienia miejsce miasta o indeksie indexToDelete, na miejsce indexToPut, w scie¿ce path
	void insert(vector<int>& path,int indexToDelete, int indexToPut);
};

