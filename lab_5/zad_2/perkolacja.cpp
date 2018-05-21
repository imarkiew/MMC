/**
@ IMiO EiTI PW
*/
#include <iostream>
#include "perkolacja.h"

using namespace std;

perkolacja::perkolacja(int wymiar) {

	L=wymiar;
	siatka_perkolacji = new int *[L];
	siatka_perkolacji_numery_agregatow = new int *[L];
	tablica_pomocnicza   = new int[L*L];
	tablica_pomocnicza_2 = new int[L*L];
	for (int i = 0; i<L; i++) {
		siatka_perkolacji[i] = new int[L];
		siatka_perkolacji_numery_agregatow[i] = new int[L];
	}
	generatorek = gsl_rng_alloc(gsl_rng_default);
	gsl_rng_set(generatorek, 123);
}


perkolacja::~perkolacja() {

	for (int i = 0; i < L; i++) {
		delete [] siatka_perkolacji[i];
		delete [] siatka_perkolacji_numery_agregatow[i];
	}
	delete [] siatka_perkolacji;
	delete [] siatka_perkolacji_numery_agregatow;
	delete [] tablica_pomocnicza;
	delete [] tablica_pomocnicza_2;
	gsl_rng_free(generatorek);
}


void perkolacja::wypelnij_siatke_perkolacji(float p) {

	for (int k = 0; k < L; k++) 
		for(int l = 0; l < L; l++)
			siatka_perkolacji[k][l] = (gsl_rng_uniform(generatorek) <= p) ? 1 : 0;
}


void perkolacja::wyswietl_siatka_perkolacji() {

	cout << "SIATKA PERKOLACJI" << endl;
	for (int k = 0; k < L; k++) {
		for(int l = 0; l < L; l++) {
			cout << ((siatka_perkolacji[k][l] > 0) ? "# " : "  ");
			if (l == L-1)
				cout << endl;
		}
	}
}


void perkolacja::wyswietl_siatka_perkolacji_numery_agregatow() {

	cout << "NUMERY AGREGATOW" << endl;
	for (int k = 0; k < L; k++) {
		for(int l = 0; l < L; l++) {
			if (siatka_perkolacji_numery_agregatow[k][l] < 10)
				cout << siatka_perkolacji_numery_agregatow[k][l] << ' ';
			else 
				cout << siatka_perkolacji_numery_agregatow[k][l] << ' ';
			if (l == L-1) 
				cout << endl;
		}
	}
}


void  perkolacja::wyswietl_tablica_pomocnicza() {

	cout << "TABLICA POMOCNICZA" << endl;
	for (int k = 0; k < L*L; k++) {
		if (k % L == 0)
			cout << endl;
		cout << tablica_pomocnicza[k] << " ";
	}
	cout << endl; 
}

void perkolacja::znajdz_agregaty() {

	int lewy, dolny;
	for (int k = 0; k < L; k++) 
		for(int l = 0; l < L; l++) 
			siatka_perkolacji_numery_agregatow[k][l] = 0;

	for (int k = 0; k < L*L; k++)
		tablica_pomocnicza[k] = 0;

	liczba_agregatow = 0;
	
	if (siatka_perkolacji[0][0] == 1)
		nowy_agregat(0, 0);

	for (int i = 1; i < L; i++) {
		if (siatka_perkolacji[i][0] == 1) {
			lewy = i-1;
			if (siatka_perkolacji[lewy][0] == 1) 
				siatka_perkolacji_numery_agregatow[i][0] = siatka_perkolacji_numery_agregatow[lewy][0];
			else 
				nowy_agregat(i, 0);
		}
	}

	for (int j = 1; j < L; j++) {
		if (siatka_perkolacji[0][j] == 1) {
			dolny = j-1;
			if (siatka_perkolacji[0][dolny] == 1) 
				siatka_perkolacji_numery_agregatow[0][j] = siatka_perkolacji_numery_agregatow[0][dolny];
			else 
				nowy_agregat(0, j);	
		}
	
		for (int i = 1; i < L; i++) {
			if (siatka_perkolacji[i][j] == 1) {
				dolny = j-1;
				lewy  = i-1;
				if (siatka_perkolacji_numery_agregatow[i][dolny]+siatka_perkolacji_numery_agregatow[lewy][j]==0)
					nowy_agregat(i, j);
				else 
					sasiedztwo(i, j);
			}
		}	
	}
	
	// Koncowe porzadkowanie etykiet
	int index, i, j;

	for (index = L*L-1; index > 0; index--) {
		if (tablica_pomocnicza[index] > 0) {
			for (i = 0; i < L; i++)
				for (j = 0; j < L; j++) 
					if (siatka_perkolacji_numery_agregatow[i][j] == index) 
						siatka_perkolacji_numery_agregatow[i][j] = tablica_pomocnicza[index];	
		}
	}	
}


void perkolacja::nowy_agregat(int i, int j) {

	liczba_agregatow++;
	siatka_perkolacji_numery_agregatow[i][j] = liczba_agregatow;
	tablica_pomocnicza[liczba_agregatow] = 0;
}


void perkolacja::sasiedztwo(int i, int j) {

	int lewy, dolny;

	dolny = j-1;
	lewy  = i-1;
	if (siatka_perkolacji[i][dolny] * siatka_perkolacji[lewy][j] == 1) {
		wybor(i, j, lewy, dolny);
		return;
	}
	
	if (siatka_perkolacji_numery_agregatow[i][dolny] > 0) {
		siatka_perkolacji_numery_agregatow[i][j] = siatka_perkolacji_numery_agregatow[i][dolny];
		return;
	}
	siatka_perkolacji_numery_agregatow[i][j] = siatka_perkolacji_numery_agregatow[lewy][j];
}


void perkolacja::wybor(int i, int j, int lewy, int dolny) {

	int N_L, N_D, kmax, kmin;
	
	if (siatka_perkolacji_numery_agregatow[lewy][j] == siatka_perkolacji_numery_agregatow[i][dolny])
		siatka_perkolacji_numery_agregatow[i][j] = siatka_perkolacji_numery_agregatow[lewy][j];
	else {
		N_L = siatka_perkolacji_numery_agregatow[lewy][j];
		N_D = siatka_perkolacji_numery_agregatow[i][dolny];
 		porzadkowanie(N_L);
		porzadkowanie(N_D);
		kmax = max(N_L, N_D);
		kmin = min(N_L, N_D);
		siatka_perkolacji_numery_agregatow[i][j] = kmin;
		if (kmax != kmin) {
			tablica_pomocnicza[kmax] = kmin;
		}
	}
}


void perkolacja::porzadkowanie(int index) {

	int i = index;
	
	while (tablica_pomocnicza[i] > 0) 
		i = tablica_pomocnicza[i];
	if (index != i)
		zamiana_etykiet(index, i);
}


int perkolacja::znajdz_agregat_perkolujacy(int kierunek) {

	int iarg, jarg, n1, n2;
	
	for (int i1 = 0; i1 < L; i1++) {
		if (kierunek == 1) {
			iarg = i1;
			jarg = 0;
		}
		else {
			iarg = 0;
			jarg = i1;
		}
		if (siatka_perkolacji_numery_agregatow[iarg][jarg] > 0) {
			n1 = siatka_perkolacji_numery_agregatow[iarg][jarg];
			porzadkowanie(n1);
			for (int i2 = 0; i2 < L; i2++) {
				if (kierunek == 1) {
					iarg = i2;
					jarg = L-1;
				}
				else {
					iarg = L-1;
					jarg = i2;
				}
				if (siatka_perkolacji_numery_agregatow[iarg][jarg] > 0) {
					n2 = siatka_perkolacji_numery_agregatow[iarg][jarg];
					porzadkowanie(n2);
					if (n1==n2) 
						return n1;
				}
			}
		}
	}
	return 0;
}


int perkolacja::max(int v1, int v2) {
	return (v1 >= v2) ? v1 : v2; 
}


int perkolacja::min(int v1,int v2) {
	return (v1 <= v2) ? v1 : v2; 
}


void perkolacja::ustaw_wartosc_komorki(int i, int j, int wartosc) {
	  siatka_perkolacji[i][j] = wartosc;
}

void  perkolacja::zamiana_etykiet(int zly_numer, int dobry_numer) {

	for (int i = 0; i < L; i++) 
		for (int j = 0; j < L; j++) 
			if (siatka_perkolacji_numery_agregatow[i][j] == zly_numer) 
				siatka_perkolacji_numery_agregatow[i][j] = dobry_numer;
}

/**
@ Igor Markiewicz
*/
int perkolacja::masa_agregatu(int numer_agregatu) {
	int sum = 0;
	for(int i = 0; i < L; i++)
		for(int j = 0; j < L; j++)
		{
			if (numer_agregatu == siatka_perkolacji_numery_agregatow[i][j]) {
				sum += 1;
			}
		}
	return sum;
	}



