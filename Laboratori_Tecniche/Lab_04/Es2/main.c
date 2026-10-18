#include <stdio.h>
#include <math.h>

void ruota (int vet[30], int N, int P, int dir);

int main(void)
{
    int vet[30], n = 0, P = -1, dir, i = 0;

    printf ("Dammi la dimensione massima del vettore \n");
    scanf ("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf ("Dammi il numero da inserire nel vettore \n");
        scanf ("%d", &vet[i]);
    }

    while (P != 0)
    {
        printf ("Dammi il numero di quante posizioni vuoi ruotare il numero del vettore\n");
        scanf ("%d", &P);
        if (P != 0)
        {
            printf ("dammi la direzione (1 a sinistra, -1 a destra)\n");
            scanf ("%d", &dir);
            ruota(vet, n, P, dir);
        }
    }


    return 0;
}

void ruota (int vet[30], int N, int P, int dir)
{
    int i, post = 0, indice;

    for (i = 0; i < P; i++)
    {
        if (dir == -1)
        {
            indice = (i+P) % N;
            post = vet[((i+P) % N)];
            vet[((i+P) % N)] = vet[i];
            vet[i] = post;
        }
        else
        {
            indice = i-P;
            if (indice < 0)
            {
                indice = N + indice;
            }
            post = vet[indice];
            vet[indice] = vet[i];
            vet[i] = post;
        }
    }

    for (i = 0; i < N; i++)
    {
        printf (" %d ", vet[i]);
    }
    printf ("\n");
}