#include <iostream>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>
#include <fstream>

using namespace std;

int main() {

    auto M = (int)1e6;
    double p = 0.95;
    int histogram_length = 100;
    double range = 10;
    double width = range / (double)histogram_length;
    int min = 0;
    gsl_rng *generator = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(generator, 3987);

    vector<double> y;
    int histogram_x_1[histogram_length] = {0}, histogram_x_2[histogram_length] = {0}, histogram_y[histogram_length] = {0};

    double x_1 = 0;
    double x_2 = 0;

    for (int i = 0; i < M; i++) {
        x_1 = 4*gsl_rng_uniform(generator);
        x_2 = gsl_rng_uniform(generator) + 5;
        y.push_back(x_1 + x_2);
        (histogram_x_1[(int)(((x_1 - min) / range)*histogram_length)])++;
        (histogram_x_2[(int)(((x_2 - min) / range)*histogram_length)])++;
        (histogram_y[(int)(((y.back() - min) / range)*histogram_length)])++;
    }

    ofstream file_1("zad_2-x_1.txt");
    ofstream file_2("zad_2-x_2.txt");
    ofstream file_3("zad_2-y.txt");

    if(!(file_1.is_open() || file_2.is_open() || file_3.is_open()))
        cout << "Error while opening file " << endl;

    double step = 0;
    for (int i = 0; i < histogram_length; i++) {
        step = min + width/2 + i*width;
        file_1 << step << " " << 1.0*histogram_x_1[i]/M << endl;
        file_2 << step << " " << 1.0*histogram_x_2[i]/M << endl;
        file_3 << step << " " << 1.0*histogram_y[i]/(M) << endl;
    }

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

    return 0;
}