#include <iostream>
#include "perkolacja.h"
#include <fstream>

using namespace std;

int main() {

    int horizontal = 1;
    int result_10 = 0, result_30 = 0, result_50 = 0, result_70 = 0, result_90 = 0;
    double counter_10 = 0, counter_30 = 0, counter_50 = 0, counter_70 = 0, counter_90 = 0;
    double mass_10 = 0, mass_30 = 0, mass_50 = 0, mass_70 = 0, mass_90 = 0;
    auto *perc_10 = new perkolacja(10);
    auto *perc_30 = new perkolacja(30);
    auto *perc_50 = new perkolacja(50);
    auto *perc_70 = new perkolacja(70);
    auto *perc_90 = new perkolacja(90);
    int counter = 2000;
    float p_c = 0.61;

    ofstream file("zad_2.txt");
    if (file.fail()) {
        cout << "Błąd podczas otwierania pliku !" << endl;
        return 0;
    }

    for (int i = 0; i < counter; i++)
    {
        perc_10->wypelnij_siatke_perkolacji(p_c);
        perc_10->znajdz_agregaty();
        perc_30->wypelnij_siatke_perkolacji(p_c);
        perc_30->znajdz_agregaty();
        perc_50->wypelnij_siatke_perkolacji(p_c);
        perc_50->znajdz_agregaty();
        perc_70->wypelnij_siatke_perkolacji(p_c);
        perc_70->znajdz_agregaty();
        perc_90->wypelnij_siatke_perkolacji(p_c);
        perc_90->znajdz_agregaty();
        result_10 = perc_10->znajdz_agregat_perkolujacy(horizontal);
        result_30 = perc_30->znajdz_agregat_perkolujacy(horizontal);
        result_50 = perc_50->znajdz_agregat_perkolujacy(horizontal);
        result_70 = perc_70->znajdz_agregat_perkolujacy(horizontal);
        result_90 = perc_90->znajdz_agregat_perkolujacy(horizontal);

        if (result_10 > 0){
            counter_10++;
            mass_10 += perc_10->masa_agregatu(result_10);
        }
        if (result_30 > 0) {
            counter_30++;
            mass_30 += perc_30->masa_agregatu(result_30);
        }
        if (result_50 > 0) {
            counter_50++;
            mass_50 += perc_50->masa_agregatu(result_50);
        }
        if (result_70 > 0) {
            counter_70++;
            mass_70 += perc_70->masa_agregatu(result_70);
        }
        if (result_90 > 0) {
            counter_90++;
            mass_90 += perc_90->masa_agregatu(result_90);
        }
    }
    file  << mass_10/counter_10 << "\t" << mass_30/counter_30 << "\t" <<
          mass_50/counter_50 << "\t" << mass_70/counter_70 << "\t" << mass_90/counter_90 << "   " << endl;

    file.close();
    delete perc_10, perc_30, perc_50, perc_70, perc_90;

    return 0;
}