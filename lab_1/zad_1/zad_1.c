#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    int n = 2500;
    int m = (int)pow(2,13)-1;
    int a_1 = 17;
    int c = 0;
    int x_0 = 19;
    int x_1 = 0;

    FILE *file = fopen("zad_1_a=17.txt", "w");
    if (file == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }

    for(int i = 0; i < n; i++)
    {
        x_1 = (a_1*x_0 + c) % m;
        fprintf(file, "%d %d \n", x_1, x_0);
        x_0 = x_1;
    }
    fclose(file);

    //////////////////////////////////////////////////

    a_1 = 85;
    x_0 = 19;
    int values[n];
    values[0] = x_0;

    for(int i = 1; i < n; i++)
    {
        values[i] = (a_1* values[i - 1] + c) % m;
    }

    FILE *file_2 = fopen("zad_1_b.txt", "w");
    if (file_2 == NULL)
    {
        printf("Error while opening file! \n");
        exit(-1);
    }
    for(int i = 0; i < n - 1; i++)
    {
        fprintf(file_2, "%d %d\n", values[i], values[i + 2]);
    }
    fclose(file_2);

    return 0;
}