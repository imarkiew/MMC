#include <stdio.h>
#include <sys/time.h>
#include <math.h>
#include <gsl/gsl_rng.h>

long time_diff_millis(struct timeval *tstart, struct timeval *tstop)
{
    return (long)((1000 * tstop->tv_sec - 1000 * tstart->tv_sec) + (tstop->tv_usec - tstart->tv_usec) / 1000); //ms
}

int main()
{
    int n = (int)pow(10, 9);
    unsigned int seed = 123;

    struct timeval tstart, tstop;
    gettimeofday(&tstart, 0);
    gsl_rng * generator = gsl_rng_alloc(gsl_rng_default);
    gsl_rng_set (generator, seed);
    gettimeofday(&tstart, 0);
    for (int i = 0; i < n; i++)
        gsl_rng_uniform(generator);
    gsl_rng_free(generator);
    gettimeofday(&tstop, 0);
    long default_time = time_diff_millis(&tstart, &tstop);

    const gsl_rng_type * generators[] = {gsl_rng_coveyou, gsl_rng_mt19937_1999, gsl_rng_ranlux};
    int length = sizeof(generators)/sizeof(generators[0]);
    long times[length];
    for(int i = 0; i < length; i++)
    {
        struct timeval tstart, tstop;
        gettimeofday(&tstart, 0);
        generator = gsl_rng_alloc(generators[i]);
        gsl_rng_set (generator, seed);
        gettimeofday(&tstart, 0);
        for (int j = 0; j < n; j++)
            gsl_rng_uniform(generator);
        gsl_rng_free(generator);
        gettimeofday(&tstop, 0);
        times[i] = time_diff_millis(&tstart, &tstop);
    }

    FILE *file = fopen("zad_4.txt", "w");
    if (file == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }

    for(int i = 0; i < length; i++)
    {
        fprintf(file, "%i %.3g # %s\n", i + 1, 1.0*times[i]/default_time, generators[i]->name);
    }

    fclose(file);

    return 0;
}

