//Plik: Tests.cpp
//Autor: Bartosz Szymczak, 252734
//Projekt 1 PEA
//Listopad 2021r.

#include "Tests.h"

long long int Tests::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return ((long long int)count.QuadPart);
}

void Tests::doTests()
{
	ofstream File("test.txt");
	int n = 10;
	vector<int> townsBF, townsDP;
	Towns t;
	long long int freq, start, end;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);

	townsBF.insert(townsBF.end(), { 2,4,6,8,10,12,14 });
	townsDP.insert(townsDP.end(), { 6,9,12,15,18,21,24 });

	File << endl << "Brute Force" << endl << "Ilosc miast;;Czas;" << endl;
	for (int i = 0; i < townsBF.size(); ++i)
	{
		File << townsBF[i] << ";;;" << endl;
		for (int j = 0; j < n; ++j)
		{
			t.randomTowns(townsBF[i]);
			BruteForce bf(t.getMatrix());
			start = read_QPC();
			bf.doBruteForce();
			end = read_QPC() - start;
			cout << "BF, size = " << townsBF[i] << ", n = " << j << ", time [us] = " << setprecision(10) << (1000000.0 * end) / freq << endl;
			File << ";;" << setprecision(10) << (1000000.0 * end) / freq << ";;" << endl;
		}
	}

	File << endl << "Dynamic Programming" << endl << "Ilosc miast;;Czas;" << endl;
	for (int i = 0; i < townsDP.size(); ++i)
	{
		File << townsDP[i] << ";;;" << endl;
		for (int j = 0; j < n; ++j)
		{
			t.randomTowns(townsDP[i]);
			BruteForce bf(t.getMatrix());
			start = read_QPC();
			bf.doBruteForce();
			end = read_QPC() - start;
			cout << "DP, size = " << townsDP[i] << ", n = " << j << ", time [us] = " << setprecision(10) << (1000000.0 * end) / freq << endl;
			File << ";;" << setprecision(10) << (1000000.0 * end) / freq << ";;" << endl;
		}
	}
}