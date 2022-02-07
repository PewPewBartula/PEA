//Plik: Towns.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 3 PEA
//Styczeñ 2022r.

#include "Towns.h"
#include "GeneticAlghoritm.h"

Towns::Towns()
{
	this->amountOfTowns = 0;
	this->stopCriterion = 30;
	this->crossover = 0.8;
	this->mutation = 0.01;
	this->populationSize = 1000;
	this->mutMethod = 0;
}

bool Towns::searchInFile(ifstream& inputFile, string toFind) {
	string tmp;
	string toFind2;
	if (toFind.substr(toFind.size() - 1, 1) == ":") {
		toFind2 = toFind.substr(0, toFind.size() - 1);
	}
	int check = 20;
	do {
		inputFile >> tmp;
		check--;
	} while (tmp != toFind && tmp != toFind2 && check > 0);
	if (check == 0) return false;
	return true;
}

void Towns::uploadTowns()
{
	string s, fileName;
	cout << "Enter file name" << endl;
	cin >> fileName;
	ifstream file(fileName);
	if (!file)
	{
		cout << "Error: Unable to open a file" << endl;
	}
	else
	{
		if (fileName.find(".txt") != std::string::npos)
		{
			file >> this->amountOfTowns;
			if (!file || this->amountOfTowns > 1)
			{
				vector<vector<int>> temp(amountOfTowns, vector<int>(amountOfTowns, 0));
				for (int i = 0; i < this->amountOfTowns; i++)
				{
					for (int j = 0; j < this->amountOfTowns; j++)
					{
						file >> temp[i][j];
					}
				}
				for (int i = 0; i < this->amountOfTowns; i++)
				{
					for (int j = 0; j < this->amountOfTowns; j++)
					{
						if (i == j) temp[i][j] = -1;
					}
				}
				matrix = temp;
			}
			else
			{
				cout << "Error: Amount of towns given incorrectly" << endl;
				return;
			}
		}
		else if (fileName.find(".atsp") != std::string::npos)
		{
			if (!searchInFile(file, "DIMENSION:")) return;

			file >> this->amountOfTowns;
			vector<vector<int>> temp(amountOfTowns, vector<int>(amountOfTowns, 0));

			if (!searchInFile(file, "EDGE_WEIGHT_TYPE:")) return;
			if (!searchInFile(file, "EXPLICIT")) return;
			if (!searchInFile(file, "EDGE_WEIGHT_FORMAT:")) return;
			if (!searchInFile(file, "FULL_MATRIX")) return;

			if (!searchInFile(file, "EDGE_WEIGHT_SECTION")) return;

			for (int i = 0; i < this->amountOfTowns; i++)
			{
				for (int j = 0; j < this->amountOfTowns; j++)
				{
					file >> temp[i][j];
				}
			}
			for (int i = 0; i < this->amountOfTowns; i++)
			{
				for (int j = 0; j < this->amountOfTowns; j++)
				{
					if (i == j) temp[i][j] = -1;
				}
			}
			matrix = temp;
		}
	}
}

void Towns::randomTowns()
{
	cout << "Insert amount of towns:" << endl;
	cout << "> ";
	cin >> this->amountOfTowns;
	if (this->amountOfTowns > 1)
	{
		vector<vector<int>> temp(this->amountOfTowns, vector<int>(this->amountOfTowns, 0));
		srand(time(NULL));
		for (int i = 0; i < this->amountOfTowns; i++)
		{
			for (int j = 0; j < this->amountOfTowns; j++)
			{
				if (i == j)
				{
					temp[i][j] = -1;
				}
				else
				{
					temp[i][j] = rand() % 100;
				}
			}
		}
		matrix = temp;
	}
	else
	{
		cout << "Error: Amount of towns given incorrectly" << endl;
		system("pause");
		return;
	}
}


void Towns::randomTowns(int n)
{
	this->amountOfTowns = n;
	vector<vector<int>> temp(this->amountOfTowns, vector<int>(this->amountOfTowns, 0));
	srand(time(NULL));
	for (int i = 0; i < this->amountOfTowns; i++)
	{
		for (int j = 0; j < this->amountOfTowns; j++)
		{
			if (i == j)
			{
				temp[i][j] = -1;
			}
			else
			{
				temp[i][j] = rand() % 100;
			}
		}
	}
	matrix = temp;
}

void Towns::showTowns()
{
	if (!matrix.empty())
	{
		for (int i = 0; i < this->amountOfTowns; i++)
		{
			for (int j = 0; j < this->amountOfTowns; j++)
			{
				cout << matrix[i][j] << "\t";
			}
			cout << endl;
		}
	}
	else cout << "There are no towns to be shown" << endl;
}

bool Towns::isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

void Towns::showTownsMenu()
{
	int choice;
	string choice_s;
	do
	{
		GeneticAlghoritm ga = GeneticAlghoritm(matrix, stopCriterion, crossover, mutation,populationSize, mutMethod);
		cout << "Actual data consists of " << this->amountOfTowns << " towns" << endl;
		cout << "Actual stop criterion: " << this->stopCriterion << " seconds" << endl;
		cout << "Actual population size: " << this->populationSize << endl;
		cout << "Actual crossover rate: " << this->crossover  << endl;
		cout << "Actual mutation rate: " << this->mutation <<  endl;
		cout << "Actual mutation method: ";
		if (this -> mutMethod == 0) cout << "SWAP";
		else if (this->mutMethod == 1) cout << "INSERT";
		cout << endl;
		cout << endl << "0 - End simulation" << endl;
		cout << "1 - Upload data from file" << endl;
		cout << "2 - Change population size" << endl;
		cout << "3 - Change stop criterion" << endl;
		cout << "4 - Change crossover rate" << endl;
		cout << "5 - Change mutation rate" << endl;
		cout << "6 - Change mutation method" << endl;
		cout << "7 - Perform Genetic Alghoritm" << endl;
		cout << endl << "> ";
		cin >> choice_s;
		system("cls");
		if (isNumber(choice_s))
		{
			choice = atoi(choice_s.c_str());
			switch (choice)
			{
			case 0:
				cout << "Simulation ended" << endl;
				break;
			case 1:
				uploadTowns();
				system("pause");
				system("cls");
				break;
			case 2:
				cout << "Enter new population size: " << endl;
				int ps;
				cin >> ps;
				this->populationSize = ps;
				system("pause");
				system("cls");
				break;
			case 3:
				cout << "Enter new stop criterion (in seconds): " << endl;
				float sc;
				cin >> sc;
				this->stopCriterion = sc;
				system("pause");
				system("cls");
				break;
			case 4:
				cout << "Enter new crossover rate: " << endl;
				float cross;
				cin >> cross;
				this->crossover = cross;
				system("pause");
				system("cls");
				break;
			case 5:
				cout << "Enter new mutation rate: " << endl;
				float mut;
				cin >> mut;
				this->mutation = mut;
				system("pause");
				system("cls");
				break;
			case 6:
				if (this->mutMethod == 0) this->mutMethod = 1;
				else if (this->mutMethod == 1) this->mutMethod = 0;
				break;
			case 7:
				if (amountOfTowns > 0) ga.doGA();
				else cout << "Error: No data given" << endl;
				system("pause");
				system("cls");
				break;
			default:
				cout << "Error: Incorrect option choosen" << endl;
				system("pause");
				system("cls");
				break;
			}
		}
		else
		{
			cout << "Error: String detected instead of integer" << endl;
			system("pause");
			system("cls");
		}

	} while (choice != 0);
}
