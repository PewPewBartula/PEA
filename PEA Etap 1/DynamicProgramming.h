//Plik: DynamicProgramming.h
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//PaŸdziernik 2021r.

#pragma once
#include <vector>
#include <climits>
#include <iostream>
using namespace std;

//Klasa DynamicProgramming odpowiedzialna jest za przeprowadzaniu algorytmu programowania dynamicznego dla asymetrycznego problemu komiwoja¿era na podanych danych
class DynamicProgramming
{
private:
	//Macierz przechowuj¹ca tymczasowo przekazan¹ macierz po³¹czeñ miêdzy miastami
	vector<vector<int>> temp;
	//Wektor przechowuj¹cy miasta wchodz¹ce w sk³ad najkrótszej œcie¿ki 
	vector<int> path;
	//Zmienna przechowuj¹ca iloœæ miast
	int size;
	//Zmienna przechowuj¹ca koszt najkrótszej œcie¿ki
	int cost;
	//Zmienna przechowuj¹ca bity odpowiadaj¹ce iloœci miast (2 ^ size)
	int bits;
	//Macierz przechowuj¹ca d³ugoœci fragmentów œcie¿ki
	vector<vector<int>> subProblems;
	//Macierz track zawiera œcie¿ki, jakimi nale¿y poruszaæ siê przez fragmenty œcie¿ki
	vector<vector<int>> track;
public:
	//Konstruktor przypisuje wartoœci do zmiennych, przekazywany argument to macierz miast i tras pomiêdzy nimi, nad któr¹ bêd¹ przeprowadzane obliczenia
	DynamicProgramming(vector<vector<int>> matrix);
	//Metoda doDynamicProgramming() s³u¿y do wykonania algorytmu algorytmu programowania dynamicznego na danych przekazanych w konstruktorze
	void doDynamicProgramming();
	//Metoda countPath(int firstTown, int towns) s³u¿y do okreœlenia najkrótszej œcie¿ki od firstTownIndex, przez townsBits
	void countPath(int firstTownIndex, int townsBits);
	//Metoda dpAlghoritm zwraca wartoœæ rekurencyjnie obliczonej najkrótszej œcie¿kê od firstTownIndex przez townsBits
	int dpAlghoritm(int firstTownIndex, int townsBits);
	//Metoda showPath() s³u¿y do wyœwietlenia wyników algorytmu
	void showPath();
};

