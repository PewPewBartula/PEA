//Plik: Towns.h
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//PaŸdziernik 2021r.
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include "BruteForce.h"
#include "DynamicProgramming.h"

using std::string;
using namespace std;
#pragma once

//Klasa Towns odpowiedzialna jest za przechowywanie danych na temat miast i tras pomiêdzy nimi oraz 
//komunikacjê pomiêdzy programem a u¿ytkownikiem w zakresie wykonywania odpowiednich dzia³añ nad aktualnymi danymi
class Towns
{
private:
	//Dwuwymiarowy wektor przechowuje macierz, której indeksy odpowiadaj¹ poszczególnym miastom,
	//a wartoœci pod odpowiednimi indeksami oznaczaj¹ wartoœæ trasy pomiêdzy nimi
	vector<vector<int>> matrix;
	//Zmienna przechowuj¹ca iloœæ miast
	int amountOfTowns;

public:
	//Konstruktor definiuje wartoœci argumentów 
	Towns();
	//Metoda uploadTowns() s³u¿y do wczytywania danych z pliku
	void uploadTowns();
	//Metoda randomTowns() s³u¿y do generowania losowych danych 
	void randomTowns();
	void randomTowns(int n);
	//Metoda showTownsMenu() odpowiedzialna jest za interakcjê z u¿ytkownikiem, gdzie u¿ytkownik mo¿e zdecydowaæ 
	//które dzia³anie wykonaæ nad aktualnymi danymi
	void showTownsMenu();
	//Metoda showTowns() pokazuje aktualne dane
	void showTowns();
	//Metoda isNumber(string s) s³u¿y do sprawdzenia, czy dany ³añcuch znaków jest liczb¹.
	bool isNumber(string);
	vector<vector<int>> getMatrix();
};

