#ifndef MODEL_ISINGA_H
#define MODEL_ISINGA_H

#include <gsl/gsl_rng.h>
#include <math.h>
/**
	@author Marek Niewinski <niewinski@linuxHP6715b>
 	changed by Igor Markiewicz
*/

class model_isinga {
	
	public:
	  	model_isinga();
		model_isinga(int rozmiar,int energia);		
    	virtual ~model_isinga();
		virtual void  doprowadzenie_do_stanu_rownowagi(int liczba_krokow);
		virtual void  zliczanie_srednich(int liczba_krokow);
		virtual float podaj_srednia_energie_duszka();
		virtual float podaj_srednia_energie_ukladu();
		virtual float podaj_srednia_magnetyzacje();
		virtual float podaj_temperature();

	protected:
		gsl_rng  *generatorek;
		int     **siatka;
		int L; // Rozmiar siatki
		int E; // Energia wewnetrzna ukladu
		int E_Start;
		int E_Duszka;
		int magnetyzacja;
		float Srednia_Energia_Ukladu, Srednia_E_Duszka, Srednia_Magnetyzacja, Temperatura;
		virtual void ustaw_same_jedynki();
		virtual int  Delta_E(int i, int j);
};

#endif
