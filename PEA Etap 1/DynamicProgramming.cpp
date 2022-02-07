//Plik: DynamicProgramming.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//Pa�dziernik 2021r.

#include "DynamicProgramming.h"

//Konstruktor przypisuje warto�ci do zmiennych, przekazywany argument to macierz miast i tras pomi�dzy nimi, nad kt�r� b�d� przeprowadzane obliczenia
DynamicProgramming::DynamicProgramming(vector<vector<int>> matrix)
{
	//Tymczasowa macierz jest r�wna przekazanej w argumencie
	this->temp = matrix;
	//Zmienna size przyjmuje warto�� ilo�ci miast zgodnie z otrzyman� macierz�
	this->size = temp.size();
	//Zmienna przechowuj�ca bity odpowiadaj�ce ilo�ci miast (2 ^ size)
	this->bits = 1 << size;
	//Macierze subProblems i track maj� rozmiar size na 2^size i s� wype�nione pocz�tkowo warto�ciami -1
	this->subProblems = vector<vector<int>>(size, vector<int>(bits, -1));
	this->track = vector<vector<int>>(size, vector<int>(bits, -1));
	this->cost = 0;
}


//Metoda dpAlghoritm zwraca warto�� rekurencyjnie obliczonej najkr�tszej �cie�ki od firstTownIndex przez townsBits
int DynamicProgramming::dpAlghoritm(int firstTownIndex, int townsBits)
{
	//Zmienna tymczasowa result s�u�y do kontrolowania stworzenia rozwi�zania
	int result = -1;
	//Je�eli dany podproblem zosta� rozwi�zany to zwracamy jego wynik
	if (subProblems[firstTownIndex][townsBits] != -1)
	{
		return subProblems[firstTownIndex][townsBits];
	}

	for (int i = 0; i < size; i++)
	{
		//Zmienna mask ustawia 0 na i-tym wierzcho�ku
		int mask = bits - (1 << i);
		//Zmienna masked przechowuje logiczny AND pomi�dzy bitami miast i zamaskowanymi miastami
		int masked = townsBits & mask;
		//Je�li skutecznie zamaskowali�my bit miasta (wyznaczyli�my miasto zawarte w townsBits) to obliczamy pozosta�e mo�liwo�ci
		if (masked != townsBits)
		{
			//True je�li w p�tli for zosta�o wyznaczone miasto zadane przez townsBits
			//Zmienna value przechowuje koszt z miasta pocz�tkowego do i-tego miasta + koszt od i-tego przez pozosta�e
			int value = temp[firstTownIndex][i] + dpAlghoritm(i, masked);
			//Je�eli jeszcze nie zosta�o znalezione rozwi�zanie lub nowe rozwi�zanie jest lepsze od poprzedniego 
			if (result == -1 || value < result)
			{
				result = value;
				track[firstTownIndex][townsBits] = i;
			}
		}
	}
	//Przypisanie wyznaczonego rozwi�zania do macierzy podproblem�w
	subProblems[firstTownIndex][townsBits] = result;
	//Zwr�cenie sk�adowej kosztu najkr�tszej drogi
	return result;
}

//Metoda countPath(int firstTown, int townsBits) s�u�y do okre�lenia najkr�tszej �cie�ki od firstTownIndex, przez townsBits
void DynamicProgramming::countPath(int firstTownIndex, int townsBits)
{
	//Dodanie miasta startowego do wektora �cie�ki
	path.push_back(0);
	//Zmienna x przechowuje kolejne miasto do kt�rego nale�y si� uda�
	int x = track[firstTownIndex][townsBits];
	//Je�eli istnieje jeszcze dalsza �cie�ka
	while (x != -1)
	{
		//Dodanie miasta do wektora �cie�ki
		path.push_back(x);
		//Zmienna mask ustawia mask� na odwiedzone miasto ( 0 na indeksie odwiedzonego miasta )
		int mask = bits - (1 << x);
		//Zmienna masked maskuje bity miast ( wynikiem jest zbi�r miast bez odwiedzonego )
		int masked = townsBits & mask;
		//Kolejne miasto, do kt�rego nale�y si� uda�
		x = track[x][masked];
		//Kolejny przeszukiwany zbi�r miast
		townsBits = masked;
	}
	//Dodanie do wektora miast miasta pocz�tkowego
	path.push_back(0);
}

//Metoda doDynamicProgramming() s�u�y do wykonania algorytmu programowania dynamicznego na danych przekazanych w konstruktorze
void DynamicProgramming::doDynamicProgramming()
{
	//Od warto�ci bits odejmowana jest liczba jeden, w celu otrzymania 1 na miejscach odpowiadaj�cym indeksom miast
	bits--;
	//Drogi z ka�dego miasta do pocz�tkowego
	for (int i = 0; i < size; i++)
	{
		subProblems[i][0] = temp[i][0];
	}
	//Obliczenie kosztu najkr�tszej �cie�ki wywo�uj�� rekurencyjnie dpAlghoritm od zerowego wierzcho�ka
	//przez wszystkie wierzcho�ki z wy��czeniem zerowego (dlatego bits-1)
	cost = dpAlghoritm(0, bits - 1);
	countPath(0, bits - 1);
}

//Metoda showPath() s�u�y do wy�wietlenia wynik�w algorytmu
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