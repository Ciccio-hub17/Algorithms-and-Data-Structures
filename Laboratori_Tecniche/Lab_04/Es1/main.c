#include <stdio.h>

void sottoSequenze (int v[], int n);

int main(void)
{
    int vet[30], n, i = 0;

    printf ("Quanti valori vuoi aggiungere?\n");
    scanf ("%d", &n);

    for (i = 0; i<n; i++)
    {
        printf ("Dammi il numero da inserire nel vettore\n");
        scanf ("%d", &vet[i]);
    }

    sottoSequenze(vet, n);
    return 0;
}

void sottoSequenze (int v[30],const int n)
{
    int inizio[30], fine[30], i = 0, flag = 0, k = 0, length = 0, j = 0, trovato = 0;

    for (i = 0; i < n; i++)
    {
        if (flag == 0 && v[i] != 0)
        {
            inizio[k] = i;
            k++;
            flag = 1;
        }

        if (flag == 1 && v[i] == 0)
        {
            fine[k-1] = i-1;
            flag = 0;
            trovato = 1;
        }
    }
    if (trovato == 0)
    {
        length = n-1;
        fine[k-1] = n-1;
    }
    else
    {
        for (i = 0; i < k; i++)
        {
            if (fine[i] - inizio[i] >= length)
            {
                length = fine[i] - inizio[i];
            }
        }
    }

    printf ("Dimensione massima %d\n", length);

    for (i = 0; i < k; i++)
    {
        if (fine[i] - inizio[i] == length)
        {
            printf ("[ ");
            for (j = inizio[i]; j <= fine[i]; j++)
            {
                printf ("%d ", v[j]);
            }
            printf ("]\n");
        }
    }
}