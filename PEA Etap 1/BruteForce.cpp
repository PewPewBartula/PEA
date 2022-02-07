//Plik: BruteForce.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//Pa�dziernik 2021r.

#include "BruteForce.h"

//Konstruktor definiuj�cy zmienne, przekazywany argument to macierz miast i tras pomi�dzy nimi, nad kt�r� b�d� przeprowadzane obliczenia
BruteForce::BruteForce(vector<vector<int>> matrix)
{
	//Warto�� kosztu �cie�ki pocz�tkowo ustawiona na maksymalny int w celu p�niejszych por�wna�
	this->cost = INT_MAX;
	//Tymczasowa macierz jest r�wna przekazanej w argumencie
	this->temp = matrix;
	//Zmienna size przyjmuje warto�� ilo�ci miast zgodnie z otrzyman� macierz�
	this->size = temp.size();
	//Zmienna path przechowuje najkr�tsz� �cie�k�, pocz�tkowo jest wektorem o ilo�ci element�w r�wnej ilo�ci miast
	//Warto�ci wektora to pocz�tkowo zera
	this->path = vector<int>(size,0);
}

//Metoda doBruteForce() s�u�y do wykonania algorytmu przeszukania zupe�nego na danych przekazanych w konstruktorze
void BruteForce::doBruteForce()
{
	//Zmienna pomocnicza przechowuj�ca tymczasow� najkr�tsz� �cie�k�
	//Wektor ma rozmiar r�wny ilo�ci miast oraz pocz�tkowo jest wype�niony zerami
	vector<int>shortestPath(size, 0);

	//Kolejne warto�ci wektora s� uzupe�nione warto�ciami od zera do size-1
	//w celu tworzenia dalszych permutacji
	for (int i = 0; i < size; i++)
	{
		shortestPath[i] = i;
	}
	//Zmienna pomocnicza przechowujaca tymczasow� warto�� najni�szej �cie�ki
	//Pocz�tkowo usatwiona na zero
	int lowestCost = 0;
	//P�tla do while korzysta z funkcji next_permutation, kt�ra ustawia kolejne permutacje miast nie uwzgl�dniaj�c miasta zerowego, 
	//kt�re przyjmujemy za pocz�tkowe
	do
	{
		//Obliczanie aktualnej warto�ci �cie�ki
		lowestCost = countCost(shortestPath);
		//Je�eli obliczona �cie�ka jest kr�tsza od aktualnej najkr�tszej to zast�pujemy 
		//g��wne zmienne przechowuj�ce wynik dzia�ania
		if (lowestCost < this->cost)
		{
			this->cost = lowestCost;
			this->path = shortestPath;
		}

	} while (next_permutation(shortestPath.begin() + 1, shortestPath.end()));
	
}

//Metoda pomocnicza countCost(vector<int> path) oblicza i zwraca koszt �cie�ki przekazanej w argumencie
int BruteForce::countCost(vector<int> path)
{
	int cost=0;
	//Obliczanie sumy z�o�onej z koljenych warto�ci macierzy, o indeksach zawartych w wektorze path
	for (int i = 0; i < size - 1; i++)
	{
		cost += temp[path[i]][path[i + 1]];
	}
	//Na koniec dodawana jest �cie�ka z ostatniego miasta do miasta pocz�tkowego
	cost += temp[path[size-1]][path[0]];
	return cost;
}

//Metoda showPath() s�u�y do wy�wietlenia wyznaczonej �cie�ki
void BruteForce::showPath()
{
	//�cie�ka zostaje wy�wietlona je�li zosta�a obliczona tj. jej warto�� jest r�na od INT_MAX
	if (cost != INT_MAX)
	{
		cout << "BF Shortest path: " << endl;
		for (int i = 0; i < this->size; i++)
		{
			cout << path[i] << " -> ";
		}
		cout << "0" << endl;
		cout << "Cost = " << cost << endl;
	}
}
