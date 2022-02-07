//Plik: Towns.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//PaŸdziernik 2021r.

#include "Towns.h"

//Konstruktor przypisuje wartoœci argumentów 
Towns::Towns()
{
	this->amountOfTowns = 0;
}

//Metoda uploadTowns() s³u¿y do wczytywania danych z pliku
void Towns::uploadTowns()
{
	string s, fileName;
	cout << "Enter file name" << endl;
	cin >> fileName;
	fileName = fileName + ".txt";
	ifstream file(fileName);
	if (!file)
	{
		cout << "Error: Unable to open a file" << endl;
		system("pause");
	}
	else
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
			system("pause");
			return;
		}
	}
}

//Metoda randomTowns() s³u¿y do generowania losowych danych 
void Towns::randomTowns()
{
	cout << "Insert amount of towns:" << endl;
	cout << "> ";
	cin >> this->amountOfTowns;
	if (this->amountOfTowns > 1)
	{
		vector<vector<int>> temp(this->amountOfTowns, vector<int> (this->amountOfTowns,0));
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

//Metoda showTownsMenu() odpowiedzialna jest za interakcjê z u¿ytkownikiem, gdzie u¿ytkownik mo¿e zdecydowaæ 
//które dzia³anie wykonaæ nad aktualnymi danymi
void Towns::showTownsMenu()
{
	int choice;
	string choice_s;
	if (!matrix.empty())
	{
		do
		{
			cout << "Actual data consists of " << this->amountOfTowns << " towns" << endl;
			cout << "0 - Change data" << endl;
			cout << "1 - Show town matrix" << endl;
			cout << "2 - Brute Force alghoritm " << endl;
			cout << "3 - Dynamic Programming alghoritm " << endl;
			cout << "> ";
			cin >> choice_s;
			if (isNumber(choice_s))
			{
				choice = atoi(choice_s.c_str());
				switch (choice)
				{
				case 0:
					system("cls");
					return;
					break;
				case 1:
					showTowns();
					system("pause");
					system("cls");
					break;
				case 2:
				{
					BruteForce bf = BruteForce(matrix);
					bf.doBruteForce();
					bf.showPath();
					system("pause");
					system("cls");
					break;
				}
				case 3:
				{
					DynamicProgramming dp = DynamicProgramming(matrix);
					dp.doDynamicProgramming();
					dp.showPath();
					system("pause");
					system("cls");
					break;
				}
				default:
					{
					cout << "Error: Incorrect option choosen" << endl;
					system("pause");
					system("cls");
					break;
					}
				}
			}
			else
			{
				cout << "Error: String detected instead of integer" << endl;
				system("pause");
			}
		} while (choice!=0);

	}
}

//Metoda showTowns() pokazuje aktualne dane
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
}

vector<vector<int>> Towns::getMatrix()
{	
	return this->matrix;
}

//Metoda isNumber(string s) s³u¿y do sprawdzenia, czy dany ³añcuch znaków jest liczb¹.
bool Towns::isNumber(string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}