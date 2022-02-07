//Plik: Towns.h
//Autor: Bartosz Szymczak, 252734
//Projekt 2 PEA
//Grudzień 2021r.

#include<vector>
#include<string>
#include<iostream>
#include<fstream>


using std::string;
using namespace std;
#pragma once

//Klasa Towns odpowiedzialna jest za przechowywanie danych na temat miast i tras pomiędzy nimi oraz 
//komunikację pomiędzy programem a użytkownikiem w zakresie wykonywania odpowiednich działań nad aktualnymi danymi
class Towns
{
private:
	//Dwuwymiarowy wektor przechowuje macierz, której indeksy odpowiadają poszczególnym miastom,
	//a wartości pod odpowiednimi indeksami oznaczają wartość trasy pomiędzy nimi
	vector<vector<int>> matrix;
	//Zmienna przechowująca ilość miast
	int amountOfTowns;
	//Zmienna przechowująca kryterium stopua
	float stopCriterion;
public:
	//Konstruktor definiuje wartości argumentów 
	Towns();
	//Metoda uploadTowns() służy do wczytywania danych z pliku
	void uploadTowns();
	//Metoda randomTowns() służy do generowania losowych danych 
	void randomTowns();
	void randomTowns(int n);
	//Metoda showTownsMenu() odpowiedzialna jest za interakcję z użytkownikiem, gdzie użytkownik może zdecydować 
	//które działanie wykonać nad aktualnymi danymi
	void showTownsMenu();
	//Metoda showTowns() pokazuje aktualne dane
	void showTowns();
	//Metoda isNumber(string s) służy do sprawdzenia, czy dany łańcuch znaków jest liczbą.
	bool isNumber(string);
	//Metoda searchInFile(ifstream& fileName, string toFind) wyszukuje podany łańcuch znaków w podanym pliku,
	//jednocześnie ustawia wskaźnik na miejsce w pliku po znalezionym łańcuchu 
	bool searchInFile(ifstream& fileName, string toFind);
	//Metoda usatwia kryterium stopu
	void setStopCriterion(float stopCriterion);
};

