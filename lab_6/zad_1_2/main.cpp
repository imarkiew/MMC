#include <iostream>
#include <fstream>
#include "model_isinga.h"
#include "canonical_ensemble .h"

using namespace std;

int main() {

    // zad 1
    int steps = 1200;
    int size = 10;
    ofstream file_1("zad_1_1.txt");
    for (int E = -184; E <= -24; E += 8)
    {
        auto *model_1 = new model_isinga(size, E);
        model_1 -> doprowadzenie_do_stanu_rownowagi(steps);
        model_1 -> zliczanie_srednich(steps);
        file_1 << E << " " << model_1 -> podaj_temperature() << " " << model_1 -> podaj_srednia_magnetyzacje() << " " << model_1 -> podaj_srednia_energie_ukladu()
             << " " << model_1 -> podaj_srednia_energie_duszka() << endl;
        delete model_1;
    }
    file_1.close();

    // zad 2
    ofstream file_2("zad_2_1.txt");
    for (double T = 1; T <= 5; T += 0.1)
    {
        auto *model_2 = new canonical_ensemble(size, T);
        model_2 -> doprowadzenie_do_stanu_rownowagi(steps);
        model_2 -> zliczanie_srednich(steps);
        file_2 << T << " " << model_2 -> podaj_srednia_magnetyzacje() << " " << model_2 -> podaj_srednia_energie_ukladu() <<  endl;
        delete model_2;
    }
    file_2.close();

    return 0;
}