#include "model_isinga.h"
#include "canonical_ensemble .h"
#include <iostream>

using namespace std;

/**
 * @author Igor Markiewicz, based on ising model of Ph.D Marek Niewiński
 */


canonical_ensemble::canonical_ensemble() {
    L =  10;
    k_B = 1;
    siatka = new int* [L];
    for (int i = 0; i < L; i++)
        siatka[i] = new int[L];
}

canonical_ensemble::canonical_ensemble(int rozmiar, double temperatura) {
    L = rozmiar;
    k_B = 1;
    T = temperatura;
    siatka = new int* [L];
    for (int i = 0; i < L; i++)
        siatka[i] = new int[L];

    generatorek = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set(generatorek, 3987);
}

canonical_ensemble::~canonical_ensemble() {}

void canonical_ensemble::doprowadzenie_do_stanu_rownowagi(int liczba_krokow) {
    int i, j, dE;
    double W, prob;
    magnetyzacja = L * L;
    E_Start  = -2 * L * L;
    ustaw_same_jedynki();

    for (int k = 0; k < liczba_krokow; k++) {
        i = (int)floor(gsl_rng_uniform(generatorek)*L);
        j = (int)floor(gsl_rng_uniform(generatorek)*L);
        dE = Delta_E(i, j);

        if (dE <= 0) {
            E_Start  += dE;
            siatka[i][j] = -siatka[i][j];
            magnetyzacja += 2*siatka[i][j];
        }else
        {
            W = exp(-dE / (k_B * T));
            prob = gsl_rng_uniform(generatorek);
            if (prob < W)
            {
                E_Start  += dE;
                siatka[i][j] = -siatka[i][j];
                magnetyzacja += 2*siatka[i][j];
            }
        }
    }
}

void canonical_ensemble::zliczanie_srednich(int liczba_krokow) {
    int E_Duszka_Do_Sredniej = 0, i, j ,dE;
    long magnetyzacja_tot = 0;
    int E_tot = 0;
    int przed, po;
    double W, prob;
    // Petla liczby_krokow
    for (int l = 0; l < liczba_krokow; l++) {
        // Petla statystycznie po kazdym spinie
        for (int k = 0; k < L*L; k++) {
            i  = (int)floor(gsl_rng_uniform(generatorek)*L);
            j  = (int)floor(gsl_rng_uniform(generatorek)*L);
            dE = Delta_E(i,j);
            if (dE <= 0) {
                //E_Duszka -= dE;
                E_Start  += dE;
                siatka[i][j] = -siatka[i][j];
                magnetyzacja += 2*siatka[i][j];
            }else
                {
                    W = exp(-dE / (k_B * T));
                    prob = gsl_rng_uniform(generatorek);
                if (prob < W)
                {
                    E_Start  += dE;
                    siatka[i][j] = -siatka[i][j];
                    magnetyzacja += 2*siatka[i][j];
                }
            }
        }
        E_tot += E_Start;
        magnetyzacja_tot += abs(magnetyzacja);
    }
    // Obliczanie srednich
    Srednia_Energia_Ukladu = E_tot / (float)liczba_krokow;
    Srednia_Magnetyzacja = magnetyzacja_tot / (float)liczba_krokow / ((float)L*(float)L);
}
