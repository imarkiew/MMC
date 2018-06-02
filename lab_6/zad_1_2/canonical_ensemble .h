#ifndef ZAD_1_2_CANONICAL_ENSEMBLE_H
#define ZAD_1_2_CANONICAL_ENSEMBLE_H

#include "model_isinga.h"

/**
 * @author Igor Markiewicz, based on ising model of Ph.D Marek Niewiński
 */
class canonical_ensemble : public model_isinga {

    public:
        canonical_ensemble();
        canonical_ensemble(int size, double temperature);
        ~canonical_ensemble();
        void  doprowadzenie_do_stanu_rownowagi(int liczba_krokow);
        void zliczanie_srednich(int liczba_krokow);

    protected:
        double k_B;
        double T;
};

#endif //ZAD_1_2_CANONICAL_ENSEMBLE_H
