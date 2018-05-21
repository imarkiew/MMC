#include <gsl/gsl_rng.h>

class perkolacja {

private:
	int   liczba_agregatow;
	int   L;//wymiar
	int **siatka_perkolacji;
	int **siatka_perkolacji_numery_agregatow;
	int  *tablica_pomocnicza, *tablica_pomocnicza_2;
	gsl_rng *generatorek;

	// Funcje pomocnicze
	void porzadkowanie(int index);
	void wyswietl_tablica_pomocnicza();
	void nowy_agregat(int i, int j);
	void sasiedztwo(int i, int j);
	void zamiana_etykiet(int zly_numer, int dobry_numer);
	void wybor(int i, int j, int lewy, int dolny);
	int max(int v1, int v2);
	int min(int v1, int v2);

public:
	perkolacja(int wymiar);
	~perkolacja();
	void wypelnij_siatke_perkolacji(float p);
	void wyswietl_siatka_perkolacji();
	void wyswietl_siatka_perkolacji_numery_agregatow();
	void znajdz_agregaty();
	int  znajdz_agregat_perkolujacy(int kierunek);
	void ustaw_wartosc_komorki(int i, int j, int wartosc);
	int  masa_agregatu(int numer_agregatu);
};
