//Plik: TabuSearch.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 2 PEA
//Grudzieñ 2021r.

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
	//Wyczyszczenie i ustawienie tymczasowej prostej œcie¿ki
	path.clear();
	for (int i = 0; i < size; ++i) 
	{
		path.push_back(i);
	}
	for (int i = 0; i < (size - 1); ++i)
	{
		//Zmienna przechowuje aktualny, najmniejszy koszt, w celu dalszych porównywañ
		int min = INT_MAX;
		//Zmienna przechouje pozycje rozpatrywanego miasta
		int nearestIndex = i + 1;
		for (int j = (i + 1); j < size; ++j)
		{
			//Wyszukanie najkrótszej œcie¿ki wychodz¹cej z rozpatrywanego miasta 
			if (temp[path[i]][path[j]] < min) 
			{
				//Nowa pozycja ropatrywanego docelowego miasta
				nearestIndex = j;
				//Nowe najtañsze po³¹czenie
				min = temp[path[i]][path[j]];
			}
		}
		//Podstawienie wyznaczonego miasta docelowego do œcie¿ki wynikowej 
		int x = path[i + 1];
		path[i + 1] = path[nearestIndex];
		path[nearestIndex] = x;
	}
	//Zwraca koszt wyzanczonej œcie¿ki 
	return countPath(path);
}

void TabuSearch::localSolution(vector<int>& path)
{
	TabuElement tabuElement;
	//Zmienna przechowuj¹ca najkrótsz¹ wartoœæ œcie¿ki 
	int min = INT_MAX;
	//Kopia ropatrywanej œcie¿ki 
	vector<int> currentPath = path;
	//Zaczyna siê od drugiego miasta, poniewa¿ nie zamienia siê po³o¿enia miasta pierwszego
	for (int i = 1; i < size - 1; ++i)
	{
		for (int j = 1; j < size - 1; ++j)
		{
			//Jeœli ró¿ne indeksy miast oraz nie istnieje element z podanymi miastami w liœcie tabu
			if (i != j && !inTabuList(i, j))
			{
				//Zamiana kolejnoœci miast w kopii rozpatrywanej œcie¿ki
				swap(currentPath, i, j);
				//Obliczenie kosztu zmodyfikowanej œcie¿ki
				int temp = countPath(currentPath);
				//Jeœli obliczony koszt jest mniejszy ni¿ aktualnie najmniejszy 
				if (temp <= min)
				{
					//Stworzenie elementu listy tabu z podanymi indeksami miast
					tabuElement.town1 = j;
					tabuElement.town2 = i;
					//Aktualizacja najkrótszej œcie¿ki
					min = temp;
					//Modyfikacja rozpatrywanej œcie¿ki 
					path = currentPath;
				}
				//Przywrócenie poprzedniej postaci œcie¿ki 
				swap(currentPath, i, j);
			}
		}
	}
	//Aktualizacja listy tabu, zmniejszenie "czasu ¿ycia" elementów
	for (auto town = tabuList.begin(); town != tabuList.end(); ++town)
	{
		town->lifetime--;
		//Usuniêcie elementu przy "czasu ¿ycia" równym 0
		if (town->lifetime == 0)
		{
			tabuList.erase(town);
			--town;
		}
	}
	//Jeœli jest miejsce w liœcie tabu to dodajemy wyznaczony element i ustawiamy jego "czas ¿ycia"
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
	//Zmienna przechowuje czas wyznaczenia rozwi¹zania
	int foundTime = 0;
	//Obecnie rozpatrywana, lokalna scie¿ka
	vector<int> currentPath;
	//Koszt globalnie optymalnej œcie¿ki
	int cost = greedyTS(currentPath);
	//Wektor przechowuje najlepsz¹ globaln¹ œcie¿k¹
	vector<int> resultPath = currentPath;
	//Iloœæ iteracji bez dokonywania zmian - dywersyfikacja
	int iterationsWithoutChange = 1000;
	//Sprawdzenie czy przekroczono kryterium stopu
	while (t.getTimeWithoutStopping() < stopCriterion)
	{
		//Wyznaczenie elementu listy Tabu oraz zmodyfikowanie aktualnej œcie¿ki
		localSolution(currentPath);
		//Zmienna przechowuje koszt lokalnie optymalnej œcie¿ki 
		int temp = countPath(currentPath);
		//Porównanie wartoœci œcie¿ek, jeœli lokalne rozwi¹zanie jest tañsze od globalnego 
		if (temp < cost)
		{
			//Restart iloœci iteracji bez dokonywania zmian
			iterationsWithoutChange = 1000;
			//Lokalne rozwi¹zanie staje siê globalnym
			cost = temp;
			resultPath = currentPath;
			foundTime = t.getTimeMSWithoutStopping();
		}
		//Jeœli iloœæ iteracji bez dokonywania zmian jest niewiêksza od 0
		if (diversification && (iterationsWithoutChange <= 0))
		{
			//Stworzenie kolejnego rozwi¹zania i przechowanie jego kosztów
			random_shuffle(currentPath.begin() + 1, currentPath.end());
			temp = countPath(currentPath);
			//Resetowanie iloœci iteracji bez zmian 
			iterationsWithoutChange = 1000;
			//Jeœli nowe rozwi¹zanie jest tañsze od globalnego
			if (temp <= cost)
			{
				//Nowe rozwi¹zanie staje siê globalnym
				cost = temp;
				resultPath = currentPath;
				foundTime = t.getTimeMSWithoutStopping();
			}
		}
		//Redukcja iteracji bez zmian
		iterationsWithoutChange--;
	}
	//Wyœwietlenie wyniku
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
