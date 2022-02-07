//Plik: menu.h
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//Pa�dziernik 2021r.

#include <iostream>
#include <string>
#include "Towns.h"
#include "Tests.h"
using std::string;
#pragma once

//Klasa odpowiedzialna za interakcj� z u�ytkownikiem
class Menu
{
private:
	//Obiekt typu Towns przechowuje aktualne dane wszystkich miast i po��cze�
	Towns towns;
public:
	//Metoda showMainMenu() odpowiedzialna jest za interakcj� z u�ytkownikiem, gdzie u�ytkownik mo�e zdecydowa� 
	//w jaki spos�b stworzy� dane
	void showMainMenu();
	//Metoda about() s�u�y do wy�wietlenia informacji o autorze i podstawowych informacji o programie.
	void about();
	//Metoda isNumber(string s) s�u�y do sprawdzenia, czy dany �a�cuch znak�w jest liczb�.
	bool isNumber(string s);
};

