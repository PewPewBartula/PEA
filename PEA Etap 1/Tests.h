//Plik: Tests.h
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//Listopad 2021r.

#pragma once
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Towns.h"
#include "BruteForce.h"
#include "DynamicProgramming.h"

using namespace std;

//Klasa Tests s³u¿y do wykonywania testów czasowych nad ró¿nymi algorytmami, bêd¹cymi czêœci¹ projektu
class Tests
{
public:
	long long int read_QPC();
	void doTests();
};

