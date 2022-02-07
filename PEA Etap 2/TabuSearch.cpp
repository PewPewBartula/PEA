//Plik: TabuSearch.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 2 PEA
//Grudzie� 2021r.

#include "TabuSearch.h"

TabuSearch::TabuSearch(vector<vector<int>> matrix, float sc)
{
	this->temp = matrix;
	this->size = temp.size();
	this->firstTown = 0;
	this->stopCriterion = sc;
	this->diversification = true;
}

int TabuSearch::greedyTS(vector<int>& path)
{
	//Wyczyszczenie i ustawienie tymczasowej prostej �cie�ki
	path.clear();
	for (int i = 0; i < size; ++i) 
	{
		path.push_back(i);
	}
	for (int i = 0; i < (size - 1); ++i)
	{
		//Zmienna przechowuje aktualny, najmniejszy koszt, w celu dalszych por�wnywa�
		int min = INT_MAX;
		//Zmienna przechouje pozycje rozpatrywanego miasta
		int nearestIndex = i + 1;
		for (int j = (i + 1); j < size; ++j)
		{
			//Wyszukanie najkr�tszej �cie�ki wychodz�cej z rozpatrywanego miasta 
			if (temp[path[i]][path[j]] < min) 
			{
				//Nowa pozycja ropatrywanego docelowego miasta
				nearestIndex = j;
				//Nowe najta�sze po��czenie
				min = temp[path[i]][path[j]];
			}
		}
		//Podstawienie wyznaczonego miasta docelowego do �cie�ki wynikowej 
		int x = path[i + 1];
		path[i + 1] = path[nearestIndex];
		path[nearestIndex] = x;
	}
	//Zwraca koszt wyzanczonej �cie�ki 
	return countPath(path);
}

void TabuSearch::localSolution(vector<int>& path)
{
	TabuElement tabuElement;
	//Zmienna przechowuj�ca najkr�tsz� warto�� �cie�ki 
	int min = INT_MAX;
	//Kopia ropatrywanej �cie�ki 
	vector<int> currentPath = path;
	//Zaczyna si� od drugiego miasta, poniewa� nie zamienia si� po�o�enia miasta pierwszego
	for (int i = 1; i < size - 1; ++i)
	{
		for (int j = 1; j < size - 1; ++j)
		{
			//Je�li r�ne indeksy miast oraz nie istnieje element z podanymi miastami w li�cie tabu
			if (i != j && !inTabuList(i, j))
			{
				//Zamiana kolejno�ci miast w kopii rozpatrywanej �cie�ki
				swap(currentPath, i, j);
				//Obliczenie kosztu zmodyfikowanej �cie�ki
				int temp = countPath(currentPath);
				//Je�li obliczony koszt jest mniejszy ni� aktualnie najmniejszy 
				if (temp <= min)
				{
					//Stworzenie elementu listy tabu z podanymi indeksami miast
					tabuElement.town1 = j;
					tabuElement.town2 = i;
					//Aktualizacja najkr�tszej �cie�ki
					min = temp;
					//Modyfikacja rozpatrywanej �cie�ki 
					path = currentPath;
				}
				//Przywr�cenie poprzedniej postaci �cie�ki 
				swap(currentPath, i, j);
			}
		}
	}
	//Aktualizacja listy tabu, zmniejszenie "czasu �ycia" element�w
	for (auto town = tabuList.begin(); town != tabuList.end(); ++town)
	{
		town->lifetime--;
		//Usuni�cie elementu przy "czasu �ycia" r�wnym 0
		if (town->lifetime == 0)
		{
			tabuList.erase(town);
			--town;
		}
	}
	//Je�li jest miejsce w li�cie tabu to dodajemy wyznaczony element i ustawiamy jego "czas �ycia"
	if (tabuList.size() < size)
	{
		tabuElement.lifetime = size;
		tabuList.push_back(tabuElement);
	}
}

void TabuSearch::doTabuSearch()
{
	Timer t;
	tabuList.clear();
	t.startTimer();
	//Zmienna przechowuje czas wyznaczenia rozwi�zania
	int foundTime = 0;
	//Obecnie rozpatrywana, lokalna scie�ka
	vector<int> currentPath;
	//Koszt globalnie optymalnej �cie�ki
	int cost = greedyTS(currentPath);
	//Wektor przechowuje najlepsz� globaln� �cie�k�
	vector<int> resultPath = currentPath;
	//Ilo�� iteracji bez dokonywania zmian - dywersyfikacja
	int iterationsWithoutChange = 1000;
	//Sprawdzenie czy przekroczono kryterium stopu
	while (t.getTimeWithoutStopping() < stopCriterion)
	{
		//Wyznaczenie elementu listy Tabu oraz zmodyfikowanie aktualnej �cie�ki
		localSolution(currentPath);
		//Zmienna przechowuje koszt lokalnie optymalnej �cie�ki 
		int temp = countPath(currentPath);
		//Por�wnanie warto�ci �cie�ek, je�li lokalne rozwi�zanie jest ta�sze od globalnego 
		if (temp < cost)
		{
			//Restart ilo�ci iteracji bez dokonywania zmian
			iterationsWithoutChange = 1000;
			//Lokalne rozwi�zanie staje si� globalnym
			cost = temp;
			resultPath = currentPath;
			foundTime = t.getTimeMSWithoutStopping();
		}
		//Je�li ilo�� iteracji bez dokonywania zmian jest niewi�ksza od 0
		if (diversification && (iterationsWithoutChange <= 0))
		{
			//Stworzenie kolejnego rozwi�zania i przechowanie jego koszt�w
			random_shuffle(currentPath.begin() + 1, currentPath.end());
			temp = countPath(currentPath);
			//Resetowanie ilo�ci iteracji bez zmian 
			iterationsWithoutChange = 1000;
			//Je�li nowe rozwi�zanie jest ta�sze od globalnego
			if (temp <= cost)
			{
				//Nowe rozwi�zanie staje si� globalnym
				cost = temp;
				resultPath = currentPath;
				foundTime = t.getTimeMSWithoutStopping();
			}
		}
		//Redukcja iteracji bez zmian
		iterationsWithoutChange--;
	}
	//Wy�wietlenie wyniku
	cout << "Set after: " << foundTime << " ms" << endl;
	cout << "Path: " << endl;
	for (int i = 0; i < resultPath.size(); ++i)
	{
		cout << resultPath[i] << " -> ";
	}
	cout << "0" << endl;
	cout << "Cost: " << cost << endl;
}

void TabuSearch::swap(vector<int>& path, int town1, int town2)
{
	if (town1 != town2)
	{
		int x = path[town1];
		path[town1] = path[town2];
		path[town2] = x;
	}
}

int TabuSearch::countPath(vector<int> path)
{
	int cost = 0;
	int end;
	for (int i = 1; i < size; ++i)
	{
		cost += temp[path[i - 1]][path[i]];
		end = i;
	}
	cost += temp[path[end]][path[0]];
	return cost;
}

bool TabuSearch::inTabuList(int town1, int town2)
{
	for (auto& towns : tabuList)
	{
		if ((towns.town1 == town1 && towns.town2) || (towns.town1 == town2 && towns.town2 == town1))
		{
			return true;
		}
		else return false;
	}
}
