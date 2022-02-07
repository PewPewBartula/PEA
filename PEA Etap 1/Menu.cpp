//Plik: Menu.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//PaŸdziernik 2021r.

#include "menu.h"
using std::string;
using namespace std;

//Metoda showMainMenu() odpowiedzialna jest za interakcjê z u¿ytkownikiem, wczytywanie i generowanie danych
void Menu::showMainMenu()
{
	int choice;
	string choice_s;
	do
	{
        cout << "What would you like to do?" << endl;
        cout << "0 - End simulation" << endl;
        cout << "1 - Upload data from file" << endl;
		cout << "2 - Generate random data" << endl;
		cout << "3 - About" << endl;
		cout << "4 - TESTS" << endl;
        cout << "> ";
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
				{
					towns.uploadTowns();
					system("cls");
					towns.showTownsMenu();
				}
				break;
			case 2:
				{
					towns.randomTowns();
					system("cls");
					towns.showTownsMenu();
				}
				break;
			case 3:
				about();
				system("cls");
				break;
			case 4:
				{
					system("cls");
					Tests tests;
					tests.doTests();
					system("pause");
					system("cls");
				}
				break;
			default: 
				cout << "Error: Incorrect option choosen" << endl;
				break;
			}
		}
		else cout << "Error: String detected instead of integer" << endl;
	} 	
	while (choice != 0);
}

//Metoda about() s³u¿y do wyœwietlenia informacji o autorze i podstawowych informacji o programie.
void Menu::about()
{
	cout << "Author: Bartosz Szymczak, index number: 252734" << endl;
	cout << "Application was made for Designing Effective Alghorithms project" << endl;
	cout << "The project takes place at the Wroclaw University of Technology and is led by dr inz. Jaroslaw Mierzwa" << endl;
	system("pause");
}

//Metoda isNumber(string s) s³u¿y do sprawdzenia, czy dany ³añcuch znaków jest liczb¹.
bool Menu::isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

