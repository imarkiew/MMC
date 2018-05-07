#include <stdio.h>
#include <gsl/gsl_rng.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define pi 3.14
#define support_range 12

long time_diff_millis(struct timeval *tstart, struct timeval *tstop)
{
    return (long)((1000 * tstop->tv_sec - 1000 * tstart->tv_sec) + (tstop->tv_usec - tstart->tv_usec) / 1000); //ms
}

int main()
{
    time_t ttt = time(NULL);
    struct tm *date = localtime(&ttt);
    int r = (*date).tm_year + 1900;
    int m = (*date).tm_mon;
    int d = (*date).tm_mday;
    int g = (*date).tm_hour;
    int min = (*date).tm_min;
    int s = (*date).tm_sec;
    int X_0 = r + 100*(m - 1 + 12*(d - 1 + 31*(g + 24*(min + 60*s))));
    int X_1 = r + 120*(m - 1 + 10*(d - 1 + 25*(g + 13*(min - 70*s))));

    gsl_rng * generator_1 = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng * generator_2 = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set(generator_1, X_0);
    gsl_rng_set(generator_2, X_1);

    int histogram_BM[support_range][support_range] = {0};
    double x = 0;
    double y = 0;
    struct timeval tstart_BM, tstop_BM;
    double iterations = 1e7;
    gettimeofday(&tstart_BM, 0);
    for (int i = 0; i < (int)iterations; i++)
    {
        double arg_1 = sqrt(-2*log(gsl_rng_uniform(generator_1)));
        double arg_2 = 2*pi*gsl_rng_uniform(generator_2);
        x = arg_1*cos(arg_2);
        y = arg_1*sin(arg_2);
        histogram_BM[(int)floor(x) + 6][(int)floor(y) + 6]++;
    }
    gettimeofday(&tstop_BM, 0);
    printf("Metoda Boxa - Mullera : %lu milisekund \n", time_diff_millis(&tstart_BM, &tstop_BM));

    FILE *file_1 = fopen("zad_2_BM.txt", "w");
    if (file_1 == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }

    for(int i = 0; i < support_range; i++)
    {
        for(int j = 0; j < support_range; j++)
        {
            fprintf(file_1, "%lf \t %lf \t %lf \n", i - 5.5, j - 5.5, histogram_BM[i][j]/iterations);
        }
    }

    fclose(file_1);

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int histogram_MB[support_range][support_range] = {0};
    struct timeval tstart_MB, tstop_MB;
    gettimeofday(&tstart_MB, 0);
    for (int i = 0; i < (int)iterations; i++)
    {
        double A_1 = gsl_rng_uniform(generator_1);
        double A_2 = gsl_rng_uniform(generator_2);
        double X_1 = 2*A_1 - 1;
        double X_2 = 2*A_2 - 1;
        double B = (X_1*X_1)+(X_2*X_2);
        if (B < 1)
        {
            double z = sqrt(-2*log(B)/B);
            double x = X_1*z;
            double y = X_2*z;
            histogram_MB[(int)floor(x)+6][(int)floor(y)+6]++;
        }
    }
    gettimeofday(&tstop_MB, 0);
    printf("Metoda Marsaglii - Braya : %lu milisekund \n", time_diff_millis(&tstart_MB, &tstop_MB));
    gsl_rng_free(generator_1);
    gsl_rng_free(generator_2);

    FILE *file_2 = fopen("zad_2_MB.txt", "w");
    if (file_2 == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }

    for(int i = 0; i < support_range; i++)
    {
        for(int j = 0; j < support_range; j++)
        {
            fprintf(file_2, "%lf \t %lf \t %lf \n", i - 5.5, j - 5.5, histogram_MB[i][j]/iterations);
        }
    }

    fclose(file_2);

    return 0;
}