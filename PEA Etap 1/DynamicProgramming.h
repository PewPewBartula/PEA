//Plik: DynamicProgramming.h
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//Pa�dziernik 2021r.

#pragma once
#include <vector>
#include <climits>
#include <iostream>
using namespace std;

//Klasa DynamicProgramming odpowiedzialna jest za przeprowadzaniu algorytmu programowania dynamicznego dla asymetrycznego problemu komiwoja�era na podanych danych
class DynamicProgramming
{
private:
	//Macierz przechowuj�ca tymczasowo przekazan� macierz po��cze� mi�dzy miastami
	vector<vector<int>> temp;
	//Wektor przechowuj�cy miasta wchodz�ce w sk�ad najkr�tszej �cie�ki 
	vector<int> path;
	//Zmienna przechowuj�ca ilo�� miast
	int size;
	//Zmienna przechowuj�ca koszt najkr�tszej �cie�ki
	int cost;
	//Zmienna przechowuj�ca bity odpowiadaj�ce ilo�ci miast (2 ^ size)
	int bits;
	//Macierz przechowuj�ca d�ugo�ci fragment�w �cie�ki
	vector<vector<int>> subProblems;
	//Macierz track zawiera �cie�ki, jakimi nale�y porusza� si� przez fragmenty �cie�ki
	vector<vector<int>> track;
public:
	//Konstruktor przypisuje warto�ci do zmiennych, przekazywany argument to macierz miast i tras pomi�dzy nimi, nad kt�r� b�d� przeprowadzane obliczenia
	DynamicProgramming(vector<vector<int>> matrix);
	//Metoda doDynamicProgramming() s�u�y do wykonania algorytmu algorytmu programowania dynamicznego na danych przekazanych w konstruktorze
	void doDynamicProgramming();
	//Metoda countPath(int firstTown, int towns) s�u�y do okre�lenia najkr�tszej �cie�ki od firstTownIndex, przez townsBits
	void countPath(int firstTownIndex, int townsBits);
	//Metoda dpAlghoritm zwraca warto�� rekurencyjnie obliczonej najkr�tszej �cie�k� od firstTownIndex przez townsBits
	int dpAlghoritm(int firstTownIndex, int townsBits);
	//Metoda showPath() s�u�y do wy�wietlenia wynik�w algorytmu
	void showPath();
};

