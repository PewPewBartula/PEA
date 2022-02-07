//Plik: Towns.h
//Autor: Bartosz Szymczak, 252734
//Projekt 3 PEA
//Stycze� 2022r. 

#include<vector>
#include<string>
#include<iostream>
#include<fstream>


using std::string;
using namespace std;
#pragma once

//Klasa Towns odpowiedzialna jest za przechowywanie danych na temat miast i tras pomi�dzy nimi oraz 
//komunikacj� pomi�dzy programem a u�ytkownikiem w zakresie wykonywania odpowiednich dzia�a� nad aktualnymi danymi
class Towns
{
private:
	//Dwuwymiarowy wektor przechowuje macierz, kt�rej indeksy odpowiadaj� poszczeg�lnym miastom,
	//a warto�ci pod odpowiednimi indeksami oznaczaj� warto�� trasy pomi�dzy nimi
	vector<vector<int>> matrix;
	//Zmienna przechowuj�ca ilo�� miast
	int amountOfTowns;
	//Zmienna przechowuj�ca wielko�� populacji
	int populationSize;
	//Zmienna przechowuj�ca kryterium stopua
	float stopCriterion;
	//Zmienna przechowuj�ca wsp�czynnik krzy�owania
	float crossover;
	//Zmienna przechowuj�ca wsp�czynnik mutacji
	float mutation;
	//Zmienna przechowujaca wartosc metody mutacji
	int mutMethod;
public:
	//Konstruktor definiuje warto�ci argument�w 
	Towns();
	//Metoda uploadTowns() s�u�y do wczytywania danych z pliku
	void uploadTowns();
	//Metoda randomTowns() s�u�y do generowania losowych danych 
	void randomTowns();
	void randomTowns(int n);
	//Metoda showTownsMenu() odpowiedzialna jest za interakcj� z u�ytkownikiem, gdzie u�ytkownik mo�e zdecydowa� 
	//kt�re dzia�anie wykona� nad aktualnymi danymi
	void showTownsMenu();
	//Metoda showTowns() pokazuje aktualne dane
	void showTowns();
	//Metoda isNumber(string s) s�u�y do sprawdzenia, czy dany �a�cuch znak�w jest liczb�.
	bool isNumber(string);
	//Metoda searchInFile(ifstream& fileName, string toFind) wyszukuje podany �a�cuch znak�w w podanym pliku,
	//jednocze�nie ustawia wska�nik na miejsce w pliku po znalezionym �a�cuchu 
	bool searchInFile(ifstream& fileName, string toFind);
};

