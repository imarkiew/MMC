#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

int main() {

    double r = 2;
    double h = 4;
    double V = 4*r*r*h;

    gsl_rng *generator;
    generator = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(generator, 100);

    FILE *file = fopen("zad_2.txt", "w");
    if (file == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }

    double x = 0, y = 0, z = 0;
    int M = 0;
    double proportion = 0;
    for (int N = 1; N <= 2e6; N++)
    {
        x = 2*r*gsl_rng_uniform(generator);
        y = 2*r*gsl_rng_uniform(generator);
        z = h*gsl_rng_uniform(generator);

        if (pow(x, 2) + pow(y, 2) <= pow((z*r/h), 2))
        {
            if (z >= 0.2*x + 0.4*y + 1.2)
            {
                M++;
            }
        }
        proportion = (double)M/N;
        if(N % 1000 ==0)
        fprintf(file, "%d \t %lf \t %lf  \n", N, proportion*V, 2*V*sqrt(proportion *(1/(double)N) * (1 - proportion)));
    }

    fclose(file);
    gsl_rng_free(generator);

    return 0;
}