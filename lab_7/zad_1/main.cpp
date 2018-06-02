#include <iostream>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {

    auto M = (int)1e6;
    double p = 0.9545;
    gsl_rng *generator = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(generator, 3987);

    vector<double> y;

    for (int i = 0; i < M; i++)
        y.push_back(gsl_ran_gaussian(generator, 1) + gsl_ran_gaussian(generator, 2));

    auto y_estimator = accumulate(y.begin(), y.end(), 0.0)/M;
    vector<double> y_tmp = y;
    for_each(y_tmp.begin(), y_tmp.end(), [y_estimator](double &yy) {yy = pow(yy - y_estimator, 2.0);});
    auto sigma = sqrt((1.0/(M - 1))*accumulate(y_tmp.begin(), y_tmp.end(), 0.0));

    auto q = (int)floor(p*M);
    auto r = (int)floor((M - q)/2);
    sort(y.begin(), y.end());

    double y_min = y[r];
    double y_max = y[r + q];
    cout << "estymator wartosci oczekiwanej: " << y_estimator << endl;
    cout << "estymator odchylenia stadardowego " << sigma << endl;
    cout << "przedzial rozszerzenia: [" << y_min << ", " << y_max << "]" << endl;

    double sigma_c = sqrt(1*pow(1, 2) + 1*pow(2, 2));
    double mu = 0;
    cout << "przedział rozszerzenia GUM = [" << mu - 2*sigma_c << ", " << mu + 2*sigma_c << "]" << endl;

    return 0;
}