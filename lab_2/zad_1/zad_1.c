#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <time.h>
#include <math.h>

#define k 100
#define n 10e6

int main()
{
    // Mersenne Twister 19937
    double mt_values[k] = {0};
    // randu
    double randu_values[k] = {0};
    // default
    double def_values[k] = {0};

    time_t ttt = time(NULL);
    struct tm *date = localtime(&ttt);
    int r = (*date).tm_year + 1900;
    int m = (*date).tm_mon;
    int d = (*date).tm_mday;
    int g = (*date).tm_hour;
    int min = (*date).tm_min;
    int s = (*date).tm_sec;
    int X_0 = r + 100*(m - 1 + 12*(d - 1 + 31*(g + 24*(min + 60*s))));

    gsl_rng * generator_1 = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng * generator_2 = gsl_rng_alloc(gsl_rng_randu);

    gsl_rng_set(generator_1, X_0);
    gsl_rng_set(generator_2, X_0);
    srand(X_0);

    for(int i = 0; i < n; i++)
    {
        mt_values[(int)floor(k*gsl_rng_uniform(generator_1))]++;
        randu_values[(int)floor(k*gsl_rng_uniform(generator_2))]++;
        def_values[(int)floor(k*(rand()/(double)RAND_MAX))]++;
    }

    gsl_rng_free(generator_1);
    gsl_rng_free(generator_2);

    for(int i = 0; i < k; i++)
    {
        mt_values[i] = 100*((double)mt_values[i]) / n;
        randu_values[i] = 100*((double)randu_values[i]) / n;
        def_values[i] = 100*((double)def_values[i]) / n;
    }

    FILE *file_1 = fopen("zad_1_mt_k=100.txt", "w");
    FILE *file_2 = fopen("zad_1_randu_k=100.txt", "w");
    FILE *file_3 = fopen("zad_1_default__k=100.txt", "w");
    if (file_1 == NULL || file_2 == NULL|| file_3 == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }

    for(int i = 0; i < k - 1; i++)
    {
        fprintf(file_1, "%d %lf \n", i + 1, 0.5*(mt_values[i] - mt_values[i + 1]));
        fprintf(file_2, "%d %lf \n", i + 1, 0.5*(randu_values[i] - randu_values[i + 1]));
        fprintf(file_3, "%d %lf \n", i + 1, 0.5*(def_values[i] - def_values[i + 1]));
    }

    fclose(file_1);
    fclose(file_2);
    fclose(file_3);

    return 0;
}