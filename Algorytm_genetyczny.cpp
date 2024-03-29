// Algorytm_genetyczny.cpp: definiuje punkt wejścia dla aplikacji konsolowej.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

bool pokazywanie = false;

string losowanie_chromosomu()
{
	string x = "aaaaa";
	int losowana_liczba = 0;
	for (int i = 0; i < 5; i++)
	{
		//srand(time(NULL));
		losowana_liczba = rand() % 2;
		if (losowana_liczba == 0)
			x[i] = '0';
		else if (losowana_liczba == 1)
			x[i] = '1';
	}

	return x;
}

int obliczanie_fenotypu(string x)
{
	int fenotyp = 0, zastepcza = 0;
	double potega_dwojki = 0;
	for (int i = 4; i >= 0; i--, potega_dwojki++)
	{
		if (x[i] == '0')
			zastepcza = 0;
		else if (x[i] == '1')
			zastepcza = 1;
		fenotyp = fenotyp + (zastepcza*pow(2, potega_dwojki));

	}
	//cout << " " << fenotyp;
	return fenotyp;
}

int obliczanie_funkcji_przystosowania(int x, int a, int b, int c, int d)
{
	return (a*pow(x, 3)) + (b*pow(x, 2)) + (c*x) + d;
}

int nowy_chromosom(float kolo_ruletki[])
{
	int i = 0, z = 0;
	float losowana_liczba = 0;
	//srand(time(NULL));
	z = (rand() % 101);
	losowana_liczba = (float)z / 100;
	if (pokazywanie)
		cout << "wylosowana liczba to: " << losowana_liczba;
	for (i; i<8; i++)
	{
		losowana_liczba = losowana_liczba - kolo_ruletki[i];
		if (losowana_liczba <= 0)
		{
			if (pokazywanie)
				cout << " co daje nam " << i + 1 << " chromosom z kola ruletki";
			return i;
		}
		else
			continue;

	}

	return i - 1;
}

string mutacja(string x, float Pm)
{
	int z = 0;
	float y = 0;
	//srand(time(NULL));
	z = (rand() % 100 + 1);
	y = (float)z / 100;
	if (pokazywanie)
		cout << "wylosowana liczba to: " << y << endl;
	if (y < Pm)
	{
		//srand(time(NULL));
		z = rand() % 5;
		if (pokazywanie)
			cout << "liczba jest mniejsza niz Pm wiec zmutowany zostaje " << z+1 << " gen danego chromosomu" << endl;
		if (x[z] == '0')
			x[z] = '1';
		else if (x[z] == '1')
			x[z] = '0';
	}
	return x;
}

int maksimum_funkcji(int a, int b, int c, int d)
{
	int wynik = obliczanie_funkcji_przystosowania(0, a, b, c, d);
	int wynik_funkcji = wynik;
	for (int i = 0; i <= 31; i++)
	{
		wynik_funkcji = obliczanie_funkcji_przystosowania(i, a, b, c, d);
		if (wynik < wynik_funkcji)
		{
			wynik = wynik_funkcji;
		}
	}
	return wynik;

	
}

int mnimum_funkcji(int a, int b, int c, int d)
{
	int wynik = obliczanie_funkcji_przystosowania(0, a, b, c, d);
	int wynik_funkcji = wynik;
	for (int i = 0; i <= 31; i++)
	{
		wynik_funkcji = obliczanie_funkcji_przystosowania(i, a, b, c, d);
		if (wynik > wynik_funkcji)
		{
			wynik = wynik_funkcji;
		}
	}

	if (wynik > 0)
		return 0;
	else
	return wynik;
}

int main()
{
	srand(time(NULL));
	int x = 0, p = 0;
	string chromosom[8];
	string chromosom_selekcja[8];
	string pula_poczatkowa[8];
	string pula_najlepsza[8];
	int fenotyp_poczatkowy[8];
	int fenotyp[8];
	int fenotyp_najlepszy[8];
	float losowanie_krzyzowania = 0;
	float funkcja_przystosowania[8];
	float funkcja_przystosowania_max = 0;
	float kolo_ruletki[8];
	int max_fenotyp = 0;
	int max_suma = 0;
	float suma_przystosowania = 0;
	int a = 0, b = 0, c = 0, d = 0;			//deklaracja wspolczynnikow
	float Pk = 0, Pm = 0;					//deklaracja wspolczynnikow krzyzowania i mutacji
	cout << "Podaj wspolczynniki a, b, c oraz d: ";
	cin >> a >> b >> c >> d;
	cout << "Podaj kolejno wspolczynnik krzyżowania a nastepnie wspolczynnik mutacji: ";
	cin >> Pk >> Pm;
	int i = 0;								//ilosc iteracji algorytmu
	char wybor = 'n';
	cout << "Czy chcialbys widziec informacje co kazda iteracje? (y/n) ";
	cin >> wybor;
	if (wybor == 'y' || wybor == 'Y')
		pokazywanie = true;
	int max_funkcji = maksimum_funkcji(a, b, c, d);
	int anty_minus = mnimum_funkcji(a, b, c, d) * (-1);
	int ilosc_iteracji = 0;
	cout << "Podaj ilosc iteracji: ";
	cin >> ilosc_iteracji;
	for (i; i <= ilosc_iteracji; i++)
	{
		
		if (i < 1)
		{
			if (pokazywanie)
			{
				system("cls");
				cout << "Dla " << i + 1 << " iteracji mamy nastepujace informacje: " << endl << endl;
			}
			for (int j = 0; j < 8; j++)
			{
				{
					chromosom[j] = losowanie_chromosomu();
					pula_poczatkowa[j] = chromosom[j];
				}
				fenotyp[j] = obliczanie_fenotypu(chromosom[j]);
				fenotyp_poczatkowy[j] = fenotyp[j];
				funkcja_przystosowania[j] = obliczanie_funkcji_przystosowania(fenotyp[j], a, b, c, d) + anty_minus;
				suma_przystosowania = suma_przystosowania + funkcja_przystosowania[j];
				if (pokazywanie)
					cout << j + 1 << " chromosom to: " << chromosom[j] << ", jego fenotyp to: " << fenotyp[j] << ", a jego funkcja przystosowania wynosi: "
					<< funkcja_przystosowania[j] << endl;
			}
		}
		if (pokazywanie)
			cout <<"aktualna suma przystosowania to: "<<suma_przystosowania<< endl << "kolo ruletki: " << endl;
		for (int j = 0; j < 8; j++)												//zliczenie sumy przystosowania
		{
			kolo_ruletki[j] = funkcja_przystosowania[j] / suma_przystosowania;
			if (pokazywanie)
				cout << "dla " << j + 1 << "ego chromosomu procent ruletki to: " << kolo_ruletki[j] * 100 <<"%"<< endl;
		}
		for (int j = 0; j < 8; j++)												//selekcja + ruletka
		{
			if (pokazywanie)
				cout << "Dla " << j+1 << "ego nowego chromosomu ";
			chromosom_selekcja[j] = chromosom[nowy_chromosom(kolo_ruletki)];
			if (pokazywanie)
				cout << ",\na zatem od teraz chromosom " << j+1 << " to " << chromosom_selekcja[j] << endl;
		}
		for (int j = 0; j < 8; j = j + 2)											//krzyzowanie
		{
			//srand(time(NULL));
			p = rand() % 100 + 1;
			losowanie_krzyzowania = (float)p / 100;
			if (pokazywanie)
				cout << "wylosowana liczba to: " << losowanie_krzyzowania;
			if (losowanie_krzyzowania < Pk)
			{
				//srand(time(NULL));
				p = rand() % 4 + 1;
				if (pokazywanie)
					cout << " wiec krzyzowanie zachodzi (jest mniejsze niz Pk) od " << p + 1 << " genu chromosomu" << endl;
				for (int k = p; k <= 4; k++)
					swap(chromosom_selekcja[j][k], chromosom_selekcja[j + 1][k]);
			}
			else
			{
				if (pokazywanie)
					cout << " wiec krzyzowanie nie zachodzi (jest wieksze niz Pk)" << endl;
				continue;
			}
		}
		if (pokazywanie)
			cout << "Mutacja:" << endl;
		for (int j = 0; j < 8; j++)												//mutacja
		{
			if (pokazywanie)
				cout << "dla " << j + 1 << "ego chromosomu ";
			chromosom_selekcja[j] = mutacja(chromosom_selekcja[j], Pm);
		}

		suma_przystosowania = 0;
		for (int j = 0; j < 8; j++)
		{
			chromosom[j] = chromosom_selekcja[j];
			fenotyp[j] = obliczanie_fenotypu(chromosom[j]);
			funkcja_przystosowania[j] = obliczanie_funkcji_przystosowania(fenotyp[j], a, b, c, d) + anty_minus;
			suma_przystosowania = suma_przystosowania + funkcja_przystosowania[j];

			/*if (funkcja_przystosowania_max<=funkcja_przystosowania[j])
			{	
				funkcja_przystosowania_max = funkcja_przystosowania[j];
				max_fenotyp = fenotyp[j];
				x = j;
			}*/
			if (pokazywanie)
				cout << "dla nowego " << j + 1 << " chromosomu, fenotyp wynosi: " << fenotyp[j] << ", a funkcja przystosowania: " << funkcja_przystosowania[j] << endl;
		}

		funkcja_przystosowania_max = funkcja_przystosowania[0];
		if (max_suma <= suma_przystosowania)
		{
			max_suma = suma_przystosowania;
			for (int j = 0; j < 8; j++)
			{
				pula_najlepsza[j] = chromosom[j];
				fenotyp_najlepszy[j] = fenotyp[j];

				if (funkcja_przystosowania_max <= funkcja_przystosowania[j])
				{
					funkcja_przystosowania_max = funkcja_przystosowania[j];
					max_fenotyp = fenotyp[j];
					x = j;
				}
			}
		}
		if (pokazywanie)
		{
			cout << "nowa suma przystosowania: " << suma_przystosowania << endl;
			system("pause");
		}
		
		//if (obliczanie_funkcji_przystosowania(max_fenotyp,a,b,c,d)==max_funkcji)
		//	break;

	}

	cout << endl << "			Wyniki:" << endl << "\nPula poczatkowa: " << endl;
	for (int j = 0; j < 8; j++)
		cout << "Chromosom " << j + 1 << ": " << pula_poczatkowa[j] << " jego fenotyp: " << fenotyp_poczatkowy[j] << endl;
	cout << "Pula \"wybrana\": " << endl;
	for (int j = 0; j < 8; j++)
		cout << "Chromosom " << j + 1 << ": " <<pula_najlepsza[j] << " jego fenotyp: " << fenotyp_najlepszy[j] << endl;
	cout << "Maksymalna wartosc funkcji w przedziale: " << max_funkcji << endl;
	cout << "Wartosc 'x' dla maksymalnej wartosci: " << obliczanie_funkcji_przystosowania(max_fenotyp, a, b, c, d) << endl;
	cout << "Liczba iteracji: " << i << endl;
	cout << "Wybrany zostal chromosom o numerze: "<< x << " " << pula_najlepsza[x] << " " << fenotyp_najlepszy[x] << endl;

	return 0;
}