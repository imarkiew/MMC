#include <stdio.h>
#include <gsl/gsl_rng.h>

int main(void)
{
    const gsl_rng_type **t, **t0;
    t0 = gsl_rng_types_setup ();
    printf("Dostępne typy generatorów:\n");
    for (t = t0; *t != 0; t++) printf ("%s\n", (*t) -> name);

    gsl_rng * generatorek = gsl_rng_alloc(gsl_rng_mt19937);
    gsl_rng_set (generatorek, 123);

    printf("\n");
    for (int i = 0; i < 100; i++)
        printf("%g \n", gsl_rng_uniform(generatorek));

    gsl_rng_free(generatorek);

    return 0;
}