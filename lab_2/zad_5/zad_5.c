#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <time.h>
#include <math.h>

#define k 1000

int main()
{
    double rad = 1;
    int success_mt = 0;
    int success_default = 0;
    int n = (int)1e7;

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
    gsl_rng_set(generator_1, X_0);
    srand(X_0);

    double x_1_mt = 0;
    double x_2_mt = 0;
    double x_3_mt = 0;

    double x_1 = 0;
    double x_2 = 0;
    double x_3 = 0;

    int save_step = n/k;

    FILE *file1 = fopen("zad_5_n=1e7_mt.txt", "w");
    FILE *file2 = fopen("zad_5_n=1e7_default.txt", "w");

    if (file1 == NULL || file2 == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }

    double v = pow(2*rad , 3);
    for (int i = 0; i < n; i++)
    {
        x_1_mt = gsl_rng_uniform(generator_1)*2*rad - rad;
        x_2_mt = gsl_rng_uniform(generator_1)*2*rad - rad;
        x_3_mt = gsl_rng_uniform(generator_1)*2*rad - rad;

        if(pow(x_1_mt, 2) + pow(x_2_mt, 2) + pow(x_3_mt, 2) <= pow(rad, 2)){success_mt++;}

        x_1 = (rand()/(double)RAND_MAX)*2*rad - rad;
        x_2 = (rand()/(double)RAND_MAX)*2*rad - rad;
        x_3 = (rand()/(double)RAND_MAX)*2*rad - rad;

        if(pow(x_1, 2) + pow(x_2, 2) + pow(x_3, 2) <= pow(rad, 2)){success_default++;}

        if((i + 1) % save_step == 0)
        {
            fprintf(file1, "%d %lf %lf \n", i + 1, v*((double)success_mt/i), 2*v*sqrt(((double)success_mt/pow(i, 2))*(1 - (double)success_mt/i)));
            fprintf(file2, "%d %lf %lf \n", i + 1, v*((double)success_default/i), 2*v*sqrt(((double)success_default/pow(i, 2))*(1 - (double)success_default/i)));
        }

    }

    fclose(file1);
    fclose(file2);

    return 0;
}