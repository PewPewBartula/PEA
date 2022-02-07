//Plik: GeneticAlghoritm.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 3 PEA
//Styczeñ 2022r.

#include "GeneticAlghoritm.h"

GeneticAlghoritm::GeneticAlghoritm(vector<vector<int>> matrix, float sc, float cross, float mut, int popSize, int mutMethod)
{
	this->temp = matrix;
	this->size = temp.size();
	this->stopCriterion = sc;
	this->crossoverRate = cross;
	this->mutationRate = mut;
	this->populationSize = popSize;
	population = vector<PopulationElement>(populationSize);
	this->mutMethod = mutMethod;
}

void GeneticAlghoritm::doGA()
{
	resultTime = 0;
	best.cost = INT_MAX;
	t.startTimer();
	//Stworzenie populacji poczatkowej
	makePopulation(populationSize);
	//Kolejna populacja - poczatkowo kopia poczatkowej
	vector<PopulationElement> nextPopulation(population);
	//Glowna petla programu trwa przez czas zadany przez kryterium stopu
	while (t.getTimeWithoutStopping() < stopCriterion)
	{
		//Obliczanie wlasciwosci elementow populacji
		countElements();
		//Tworzenie nowej populacji poprzez mutacje oraz krzyzowanie
		nextGeneration(nextPopulation);
		//Zamiana rozpatrywanej populacji z kolejna populacja
		population.swap(nextPopulation);
	}
	//Wyswietlenie najlepszej wyznaczonej sciezki
	system("cls");
	cout << "Result path: " << endl;
	for (int i = 0; i < size; i++)
	{
		cout << best.path[i] << " -> ";
	}
	cout << "0" << endl;
	cout << "Cost: " << best.cost << endl;
	cout << "Set after " << resultTime << "ms" << endl;
}

int GeneticAlghoritm::countPath(vector<int> path)
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

void GeneticAlghoritm::makePopulation(int n)
{
	vector<int> order = vector<int>(size,-1);
	//Wypelnianie wektora wszystkimi indeksami miast
	for (int i = 0; i < size; i++)
	{
		order[i] = i;
	}
	//Dla podanej ilosci populacji
	for (int i = 0; i < n; i++)
	{
		//Losowanie sciezki
		random_shuffle(order.begin() + 1, order.end());
		PopulationElement pe;
		//Dodanie jej do elementu populacji
		pe.path = order;
		//Dodanie elementu populacji do populacji
		population[i] = pe;
	}
}

void GeneticAlghoritm::countElements()
{
	//Suma wspolczynnikow przystosowania elementow populacji
	float total = 0.0f;
	for (int i = 0; i < population.size(); i++)
	{
		//Obliczanie kosztu sciezki
		population[i].cost = countPath(population[i].path);
		//Obliczanie wspolczynnika przystosowania
		population[i].fitness = 1 / (pow(population[i].cost,8) + 1);
		//Obliczanie sumy wspolczynnikow przystosowania
		total += population[i].fitness;
		//Porownianie obliczonej sciezki z globalnym roziwazaniem
		if (population[i].cost < best.cost)
		{
			//Aktualizacja globalnego rozwiazania
			best.cost = population[i].cost;
			best.path = population[i].path;
			resultTime = t.getTimeMSWithoutStopping();
			//Wypisanie obecnie najlepszego rozwiazanie
			system("cls");
			cout << "Performing algorithm..." << endl;
			cout << "Current best cost: " << best.cost << endl;
		}
	}
	//Normalizacja wspolczynnikow przystosowania
	for (int i = 0; i < population.size(); i++)
	{		
		population[i].fitness /= total;
	}
}

void GeneticAlghoritm::nextGeneration(vector<PopulationElement> &newPopulation)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> distrReal(0.0, 1.0);
	for (int i = 0; i < population.size(); i++)
	{
		//Wybranie dwoch sciezek do skrzyzowania
		vector<int> orderA = pickPath();
		vector<int> orderB = pickPath();
		//Skrzyzowanie sciezek z danym prawdopodobienstwem
		if (crossoverRate > distrReal(gen)) newPopulation[i].path = crossOver(orderA, orderB);
		else newPopulation[i].path = orderA;
		//Mutacja sciezki z danym prawdopodobienstwem
		if (mutationRate > distrReal(gen)) mutate(newPopulation[i].path);
	}
}

vector<int> GeneticAlghoritm::pickPath()
{
	int index = 0;
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<> distrReal(0.0, 1.0);
	float r = distrReal(gen);
	//Wylosowanie sciezki metoda ruletkowa
	while (r > 0 && index < populationSize)
	{
		r -=  population[index].fitness;
		index++;
	}
	index--;
	return population[index].path;
}

void GeneticAlghoritm::mutate(vector<int>& path)
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1, size - 1);
	//Wylosowanie indeksow do zmiany
	int firstIndex = distr(gen);
	int secondIndex = distr(gen);
	//Zabezpieczenie przed dwoma rownymi indeksami
	while (firstIndex == secondIndex)
	{
		secondIndex = distr(gen);
	}
	//Mutacja wylosowanych indeksow wybrana metoda
	if (mutMethod == 0) swap(path, firstIndex, secondIndex);
	else if (mutMethod == 1) insert(path,firstIndex, secondIndex);
	
}

void GeneticAlghoritm::swap(vector<int>& path, int town1, int town2)
{
	if (town1 != town2)
	{
		int x = path[town1];
		path[town1] = path[town2];
		path[town2] = x;
	}
}

void GeneticAlghoritm::insert(vector<int>& path, int indexToDelete, int indexToPut)
{
	if (indexToDelete != indexToPut)
	{
		int town = path.at(indexToDelete);
		path.erase(path.begin() + indexToDelete);
		path.insert(path.begin() + indexToPut, town);
	}
}


vector<int> GeneticAlghoritm::crossOver(vector<int> pathA, vector<int> pathB)
{
	random_device rd;
	mt19937 gen(rd());
	//Wylosowanie przedzialu pierwszej sciezki do skopiowania
	uniform_int_distribution<> distrA(1, size - 2);
	int start = distrA(gen);
	uniform_int_distribution<> distrB(start + 1, size - 1);
	int end = distrB(gen);
	//Sciezka potomka
	vector<int> newPath(size);
	//Skopiowanie wylosowanego przedzialu do sciezki potomka
	copy(pathA.begin() + start, pathA.begin() + end + 1, newPath.begin() + start);
	newPath[0] = 0;
	//Ustawienie indeksu sciezki potomnej
	int childIndex = end + 1;
	if (childIndex == size) childIndex = 1;
	//Ustawienie indeksu sciezki rodzica
	int parentIndex = end + 1;
	if (parentIndex == size) parentIndex = 1;
	//Glowna petla krzyzowania trwa do momentu wypelnienia sciezki potomnej
	while (childIndex != start)
	{
		//Zmienna przechowuje stan znalezienia danego miasta z rodzica w skopiowanej czesci
		bool found = false;
		//Szukanie danego miasta z rodzica w skopiowanej czesci
		for (int i = start; i < end + 1; i++)
		{
			if (pathB[parentIndex] == newPath[i]) 
			{
				found = true;
				break;
			}
		}
		//Jezeli rozpatrywane miasto rodzica nie wystepuje w skopiowanej czesci to jest przepisane do potomka
		if (!found)
		{
			newPath[childIndex] = pathB[parentIndex];
			childIndex++;
			if (childIndex == size) childIndex = 1;
		}
		//Rozpatrujemy kolejne miasto rodzica
		parentIndex++;
		if (parentIndex == size) parentIndex = 1;
	}
	return newPath;
}
