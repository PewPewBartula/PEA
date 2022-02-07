//Plik: Towns.h
//Autor: Bartosz Szymczak, 252734
//Projekt 3 PEA
//Styczeñ 2022r. 

#include<vector>
#include<string>
#include<iostream>
#include<fstream>


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
	//Zmienna przechowuj¹ca wielkoœæ populacji
	int populationSize;
	//Zmienna przechowuj¹ca kryterium stopua
	float stopCriterion;
	//Zmienna przechowuj¹ca wspó³czynnik krzy¿owania
	float crossover;
	//Zmienna przechowuj¹ca wspó³czynnik mutacji
	float mutation;
	//Zmienna przechowujaca wartosc metody mutacji
	int mutMethod;
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
	//Metoda searchInFile(ifstream& fileName, string toFind) wyszukuje podany ³añcuch znaków w podanym pliku,
	//jednoczeœnie ustawia wskaŸnik na miejsce w pliku po znalezionym ³añcuchu 
	bool searchInFile(ifstream& fileName, string toFind);
};

