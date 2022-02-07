//Plik: DynamicProgramming.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//PaŸdziernik 2021r.

#include "DynamicProgramming.h"

//Konstruktor przypisuje wartoœci do zmiennych, przekazywany argument to macierz miast i tras pomiêdzy nimi, nad któr¹ bêd¹ przeprowadzane obliczenia
DynamicProgramming::DynamicProgramming(vector<vector<int>> matrix)
{
	//Tymczasowa macierz jest równa przekazanej w argumencie
	this->temp = matrix;
	//Zmienna size przyjmuje wartoœæ iloœci miast zgodnie z otrzyman¹ macierz¹
	this->size = temp.size();
	//Zmienna przechowuj¹ca bity odpowiadaj¹ce iloœci miast (2 ^ size)
	this->bits = 1 << size;
	//Macierze subProblems i track maj¹ rozmiar size na 2^size i s¹ wype³nione pocz¹tkowo wartoœciami -1
	this->subProblems = vector<vector<int>>(size, vector<int>(bits, -1));
	this->track = vector<vector<int>>(size, vector<int>(bits, -1));
	this->cost = 0;
}


//Metoda dpAlghoritm zwraca wartoœæ rekurencyjnie obliczonej najkrótszej œcie¿ki od firstTownIndex przez townsBits
int DynamicProgramming::dpAlghoritm(int firstTownIndex, int townsBits)
{
	//Zmienna tymczasowa result s³u¿y do kontrolowania stworzenia rozwi¹zania
	int result = -1;
	//Je¿eli dany podproblem zosta³ rozwi¹zany to zwracamy jego wynik
	if (subProblems[firstTownIndex][townsBits] != -1)
	{
		return subProblems[firstTownIndex][townsBits];
	}

	for (int i = 0; i < size; i++)
	{
		//Zmienna mask ustawia 0 na i-tym wierzcho³ku
		int mask = bits - (1 << i);
		//Zmienna masked przechowuje logiczny AND pomiêdzy bitami miast i zamaskowanymi miastami
		int masked = townsBits & mask;
		//Jeœli skutecznie zamaskowaliœmy bit miasta (wyznaczyliœmy miasto zawarte w townsBits) to obliczamy pozosta³e mo¿liwoœci
		if (masked != townsBits)
		{
			//True jeœli w pêtli for zosta³o wyznaczone miasto zadane przez townsBits
			//Zmienna value przechowuje koszt z miasta pocz¹tkowego do i-tego miasta + koszt od i-tego przez pozosta³e
			int value = temp[firstTownIndex][i] + dpAlghoritm(i, masked);
			//Je¿eli jeszcze nie zosta³o znalezione rozwi¹zanie lub nowe rozwi¹zanie jest lepsze od poprzedniego 
			if (result == -1 || value < result)
			{
				result = value;
				track[firstTownIndex][townsBits] = i;
			}
		}
	}
	//Przypisanie wyznaczonego rozwi¹zania do macierzy podproblemów
	subProblems[firstTownIndex][townsBits] = result;
	//Zwrócenie sk³adowej kosztu najkrótszej drogi
	return result;
}

//Metoda countPath(int firstTown, int townsBits) s³u¿y do okreœlenia najkrótszej œcie¿ki od firstTownIndex, przez townsBits
void DynamicProgramming::countPath(int firstTownIndex, int townsBits)
{
	//Dodanie miasta startowego do wektora œcie¿ki
	path.push_back(0);
	//Zmienna x przechowuje kolejne miasto do którego nale¿y siê udaæ
	int x = track[firstTownIndex][townsBits];
	//Je¿eli istnieje jeszcze dalsza œcie¿ka
	while (x != -1)
	{
		//Dodanie miasta do wektora œcie¿ki
		path.push_back(x);
		//Zmienna mask ustawia maskê na odwiedzone miasto ( 0 na indeksie odwiedzonego miasta )
		int mask = bits - (1 << x);
		//Zmienna masked maskuje bity miast ( wynikiem jest zbiór miast bez odwiedzonego )
		int masked = townsBits & mask;
		//Kolejne miasto, do którego nale¿y siê udaæ
		x = track[x][masked];
		//Kolejny przeszukiwany zbiór miast
		townsBits = masked;
	}
	//Dodanie do wektora miast miasta pocz¹tkowego
	path.push_back(0);
}

//Metoda doDynamicProgramming() s³u¿y do wykonania algorytmu programowania dynamicznego na danych przekazanych w konstruktorze
void DynamicProgramming::doDynamicProgramming()
{
	//Od wartoœci bits odejmowana jest liczba jeden, w celu otrzymania 1 na miejscach odpowiadaj¹cym indeksom miast
	bits--;
	//Drogi z ka¿dego miasta do pocz¹tkowego
	for (int i = 0; i < size; i++)
	{
		subProblems[i][0] = temp[i][0];
	}
	//Obliczenie kosztu najkrótszej œcie¿ki wywo³uj¹æ rekurencyjnie dpAlghoritm od zerowego wierzcho³ka
	//przez wszystkie wierzcho³ki z wy³¹czeniem zerowego (dlatego bits-1)
	cost = dpAlghoritm(0, bits - 1);
	countPath(0, bits - 1);
}

//Metoda showPath() s³u¿y do wyœwietlenia wyników algorytmu
void DynamicProgramming::showPath()
{
	if (cost != 0)
	{
		cout << "DP Shortest path: " << endl;
		for (int i = 0; i < path.size() - 1; i++)
		{
			cout << path[i] << " -> ";
		}
		cout << path[path.size() - 1] << endl;
		cout << "Cost = " << cost << endl;
	}
}