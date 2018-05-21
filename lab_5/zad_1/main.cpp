#include <iostream>
#include "perkolacja.h"
#include <fstream>

using namespace std;

int main() {

    int horizontal = 1;
    int result_10 = 0, result_30 = 0, result_50 = 0, result_70 = 0, result_90 = 0;
    double counter_10 = 0, counter_30 = 0, counter_50 = 0, counter_70 = 0, counter_90 = 0;
    auto *perc_10 = new perkolacja(10);
    auto *perc_30 = new perkolacja(30);
    auto *perc_50 = new perkolacja(50);
    auto *perc_70 = new perkolacja(70);
    auto *perc_90 = new perkolacja(90);
    int counter = 2000;

    ofstream file("zad_1.txt");
    if (file.fail()) {
        cout << "Błąd podczas otwierania pliku !" << endl;
        return 0;
    }

    for (float prob = 0.1; prob < 0.9; prob += 0.01)
    {
        for (int i = 0; i < counter; i++)
        {
            perc_10->wypelnij_siatke_perkolacji(prob);
            perc_10->znajdz_agregaty();
            perc_30->wypelnij_siatke_perkolacji(prob);
            perc_30->znajdz_agregaty();
            perc_50->wypelnij_siatke_perkolacji(prob);
            perc_50->znajdz_agregaty();
            perc_70->wypelnij_siatke_perkolacji(prob);
            perc_70->znajdz_agregaty();
            perc_90->wypelnij_siatke_perkolacji(prob);
            perc_90->znajdz_agregaty();
            result_10 = perc_10->znajdz_agregat_perkolujacy(horizontal);
            result_30 = perc_30->znajdz_agregat_perkolujacy(horizontal);
            result_50 = perc_50->znajdz_agregat_perkolujacy(horizontal);
            result_70 = perc_70->znajdz_agregat_perkolujacy(horizontal);
            result_90 = perc_90->znajdz_agregat_perkolujacy(horizontal);

            if (result_10 > 0)
                counter_10++;
            if (result_30 > 0)
                counter_30++;
            if (result_50 > 0)
                counter_50++;
            if (result_70 > 0)
                counter_70++;
            if (result_90 > 0)
                counter_90++;
        }
        file << "prob: "<< prob << ":\t" << 1.0*counter_10/counter << "\t" << 1.0*counter_30/counter << "\t" <<
             1.0*counter_50/counter << "\t" << 1.0*counter_70/counter << "\t" << 1.0*counter_90/counter <<"   "<<endl;
        counter_10 = 0, counter_30 = 0, counter_50 = 0, counter_70 = 0, counter_90 = 0;
        cout << prob << endl;
    }
    file.close();
    delete perc_10, perc_30, perc_50, perc_70, perc_90;

    return 0;
}  
