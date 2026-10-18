#include <stdio.h>

int ricerca_massimo (int somma[20], int nr);

int main(void)
{
    FILE *input_file;

    int i = 0, j = 0, campionato[20][20], nr = 0, nc = 0, k = 0, max = 0;

    if ((input_file = fopen ("../mat.txt", "r")) == NULL)
    {
        printf ("Errore nella lettura del file\n");
        return 1;
    }

    fscanf(input_file, "%d %d", &nr, &nc);

    int somma [nr];

    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            fscanf (input_file, "%d", &campionato[i][j]);
            printf (" %d ", campionato[i][j]);
        }
        printf ("\n");
        somma[i] = 0;
    }

    for (j = 0; j < nc; j++)
    {
        for (i = 0; i < nr; i++)
        {
            somma[i] = somma[i] + campionato[i][j];
        }
        max = ricerca_massimo(somma, nr);
        printf ("%d\n", max);

    }

    return 0;
}

int ricerca_massimo (int somma[20], int nr)
{
    int i, max = somma[0], indice = 0;

    for (i = 0; i < nr; i++)
    {
        if (somma [i] > max)
        {
            max = somma[i];
            indice = i;
        }
    }

    return indice;
}