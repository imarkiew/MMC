#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n = 500;
    double X_0 = 1;
    double Y_0 = 1;
    double Z_0 = 1;
    double K_n[n];

    for(int i = 0; i < n; i++)
    {
        K_n[i] = fmod(X_0/30269 + Y_0/30307 + Z_0/30323, 1);
        X_0 = fmod(171*X_0, 30269);
        Y_0 = fmod(171*Y_0, 30307);
        Z_0 = fmod(171*Z_0, 30323);
    }

    FILE *file = fopen("zad_2_a.txt", "w");
    if (file == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }

    for(int i = 0; i < n; i ++)
    {
        fprintf(file, "%.3g %.3g\n", K_n[i], K_n[i + 1]);
    }
    fclose(file);

    FILE *file_2 = fopen("zad_2_b.txt", "w");
    if (file_2 == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }

    for(int i = 0; i < n - 1; i++)
    {
        fprintf(file_2, "%.3g %.3g\n", K_n[i], K_n[i + 2]);
    }
    fclose(file_2);

    return 0;
}