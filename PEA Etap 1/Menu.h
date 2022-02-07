//Plik: menu.h
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//PaŸdziernik 2021r.

#include <iostream>
#include <string>
#include "Towns.h"
#include "Tests.h"
using std::string;
#pragma once

//Klasa odpowiedzialna za interakcjê z u¿ytkownikiem
class Menu
{
private:
	//Obiekt typu Towns przechowuje aktualne dane wszystkich miast i po³¹czeñ
	Towns towns;
public:
	//Metoda showMainMenu() odpowiedzialna jest za interakcjê z u¿ytkownikiem, gdzie u¿ytkownik mo¿e zdecydowaæ 
	//w jaki sposób stworzyæ dane
	void showMainMenu();
	//Metoda about() s³u¿y do wyœwietlenia informacji o autorze i podstawowych informacji o programie.
	void about();
	//Metoda isNumber(string s) s³u¿y do sprawdzenia, czy dany ³añcuch znaków jest liczb¹.
	bool isNumber(string s);
};

