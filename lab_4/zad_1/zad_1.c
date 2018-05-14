#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

int main() {

    gsl_rng *generator;
    generator = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(generator, 100);

    FILE *file = fopen("zad_1.txt", "w");
    if (file == NULL) {
        printf("Error while opening file! \n");
        exit(-1);
    }

    double a = -4, b = 4;
    double x = 0, y = 0;
    double f_x = 0;
    double sum_f_x = 0;
    double sum_f_x_square = 0;
    double integral = 0;
    for (int i = 1; i <= 2e6; i++)
    {
        x = (b - a)*gsl_rng_uniform(generator) + a;
        f_x = exp(-pow(x, 2));
        sum_f_x += f_x;
        sum_f_x_square += pow(f_x, 2);
        integral = (b - a)*sum_f_x/(1.0*i);
        if(i % 1000 == 0)
        fprintf(file, "%d \t %lf \t %lf  \n", i, integral, 2*integral*sqrt(1/((double)i*(i - 1)))*sqrt(sum_f_x_square - (1.0/i)*pow(sum_f_x, 2)));
    }

    fclose(file);
    gsl_rng_free(generator);

    return 0;
}