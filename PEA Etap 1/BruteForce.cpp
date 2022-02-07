//Plik: BruteForce.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//PaŸdziernik 2021r.

#include "BruteForce.h"

//Konstruktor definiuj¹cy zmienne, przekazywany argument to macierz miast i tras pomiêdzy nimi, nad któr¹ bêd¹ przeprowadzane obliczenia
BruteForce::BruteForce(vector<vector<int>> matrix)
{
	//Wartoœæ kosztu œcie¿ki pocz¹tkowo ustawiona na maksymalny int w celu póŸniejszych porównañ
	this->cost = INT_MAX;
	//Tymczasowa macierz jest równa przekazanej w argumencie
	this->temp = matrix;
	//Zmienna size przyjmuje wartoœæ iloœci miast zgodnie z otrzyman¹ macierz¹
	this->size = temp.size();
	//Zmienna path przechowuje najkrótsz¹ œcie¿kê, pocz¹tkowo jest wektorem o iloœci elementów równej iloœci miast
	//Wartoœci wektora to pocz¹tkowo zera
	this->path = vector<int>(size,0);
}

//Metoda doBruteForce() s³u¿y do wykonania algorytmu przeszukania zupe³nego na danych przekazanych w konstruktorze
void BruteForce::doBruteForce()
{
	//Zmienna pomocnicza przechowuj¹ca tymczasow¹ najkrótsz¹ œcie¿kê
	//Wektor ma rozmiar równy iloœci miast oraz pocz¹tkowo jest wype³niony zerami
	vector<int>shortestPath(size, 0);

	//Kolejne wartoœci wektora s¹ uzupe³nione wartoœciami od zera do size-1
	//w celu tworzenia dalszych permutacji
	for (int i = 0; i < size; i++)
	{
		shortestPath[i] = i;
	}
	//Zmienna pomocnicza przechowujaca tymczasow¹ wartoœæ najni¿szej œcie¿ki
	//Pocz¹tkowo usatwiona na zero
	int lowestCost = 0;
	//Pêtla do while korzysta z funkcji next_permutation, która ustawia kolejne permutacje miast nie uwzglêdniaj¹c miasta zerowego, 
	//które przyjmujemy za pocz¹tkowe
	do
	{
		//Obliczanie aktualnej wartoœci œcie¿ki
		lowestCost = countCost(shortestPath);
		//Je¿eli obliczona œcie¿ka jest krótsza od aktualnej najkrótszej to zastêpujemy 
		//g³ówne zmienne przechowuj¹ce wynik dzia³ania
		if (lowestCost < this->cost)
		{
			this->cost = lowestCost;
			this->path = shortestPath;
		}

	} while (next_permutation(shortestPath.begin() + 1, shortestPath.end()));
	
}

//Metoda pomocnicza countCost(vector<int> path) oblicza i zwraca koszt œcie¿ki przekazanej w argumencie
int BruteForce::countCost(vector<int> path)
{
	int cost=0;
	//Obliczanie sumy z³o¿onej z koljenych wartoœci macierzy, o indeksach zawartych w wektorze path
	for (int i = 0; i < size - 1; i++)
	{
		cost += temp[path[i]][path[i + 1]];
	}
	//Na koniec dodawana jest œcie¿ka z ostatniego miasta do miasta pocz¹tkowego
	cost += temp[path[size-1]][path[0]];
	return cost;
}

//Metoda showPath() s³u¿y do wyœwietlenia wyznaczonej œcie¿ki
void BruteForce::showPath()
{
	//Œcie¿ka zostaje wyœwietlona jeœli zosta³a obliczona tj. jej wartoœæ jest ró¿na od INT_MAX
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
