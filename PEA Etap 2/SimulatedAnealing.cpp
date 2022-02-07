//Plik: SimulatedAnealing.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 2 PEA
//Grudzie� 2021r.

#include "SimulatedAnealing.h"

SimulatedAnealing::SimulatedAnealing(vector<vector<int>> matrix, float sc)
{
	this->temp = matrix;
	this->size = temp.size();
	this->stopCriterion = sc;
	this->firstTown = 0;
	this->temperature = 500.0f;
	this->minTemperature = 0.00001f;
	this->a = 0.99f;
}

void SimulatedAnealing::doSimulatedAnealing()
{
	Timer t;
	t.startTimer();
	//Zmienna przechowuje czas wyznaczenia rozwi�zania
	int foundTime = 0;
	//Zmienna przechowuje koszt �cie�ki
	int cost = 0;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distr(1, size - 1);
	uniform_real_distribution<> distrReal(0.0, 1.0);
	//Wektor przechowuje najlepsz� globaln� �cie�k� 
	vector<int> resultPath;
	//Koszt globalnie optymalnej �cie�ki
	cost = greedySA(resultPath);
	cout << "Koszt po greedy " << cost << endl;
	//Sprawdzenie czy przekroczony kryterium stopu lub przekroczono minimaln� temperatur�
	while (t.getTimeWithoutStopping() < stopCriterion && temperature > minTemperature)
	{
		//Zmienna przechowuje koszt lokalnie optymalnej �cie�ki 
		int temp = INT_MAX;
		//Obecnie rozpatrywana, lokalna �cie�ka
		vector<int> currentPath = resultPath;
		int loop = 0;
		do
		{
			currentPath = resultPath;
			//Losowanie indeksu miasta oraz miejsca do jego umieszczenia
            int firstNumber = distr(gen);
            int secondNumber = distr(gen);
			while (firstNumber == secondNumber) 
			{
				secondNumber = distr(gen);
			}
			insert(firstNumber, secondNumber, currentPath);
			temp = countPath(currentPath);		
		} while (cost < temp && loop++ < 100);
		//Por�wnanie warto�ci �cie�ek, je�li lokalne rozwi�zanie jest ta�sze od globalnego 
		if (temp < cost)
		{
			//Lokalne rozwi�zanie staje si� globalnym
			cost = temp;
			resultPath = currentPath;
			foundTime = t.getTimeMSWithoutStopping();
		}
		//W przeciwnym wypadku, je�li warunek prawdopodobie�stwa zostaje spe�niony
		else if (temp > cost && exp((double(cost - temp) / temperature)) > distrReal(gen)) 
		{
			//Lokalne rozwi�zanie staje si� globalnym
			cost = temp;
			resultPath = currentPath;
			foundTime = t.getTimeMSWithoutStopping();
		}
		//Modyfikacja temperatury - sch�adzanie
		temperature *= a;
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
	cout << "Last temperature: " << temperature << endl;
}

int SimulatedAnealing::greedySA(vector<int>& path)
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
		//Zmienna przechouje pozycje rozpatrywanego docelowego miasta
		int nearestIndex = i + 1;
		for (int j = (i + 1); j < size; ++j)
		{
			//Wyszukanie najkr�tszej �cie�ki 
			if (temp[path[i]][path[j]] < min)
			{
				//Nowa pozycja ropatrywanego miasta
				nearestIndex = j;
				//Nowe najta�sze po��czenie
				min = temp[path[i]][path[j]];
			}
		}
		//Podstawienie wyznaczonego miasta do �cie�ki wynikowej 
		int x = path[i + 1];
		path[i + 1] = path[nearestIndex];
		path[nearestIndex] = x;
	}
	//Zwraca koszt wyzanczonej �cie�ki 
	return countPath(path);
}

void SimulatedAnealing::insert(int indexToDelete, int indexToPut, vector<int>& path) 
{
	if (indexToDelete != indexToPut)
	{
		int town = path.at(indexToDelete);
		path.erase(path.begin() + indexToDelete);
		path.insert(path.begin() + indexToPut, town);
	}
}

int SimulatedAnealing::countPath(vector<int> path)
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