#include <stdio.h>

void insertion_sort (int vet[7], int n);
int main(void)
{
    int vet[7] = {4, 7, 1, -1, 0, 10, 3}, n = 7;

    insertion_sort(vet, n);
    return 0;
}

void insertion_sort (int vet[7], int n)
{
    int i = 0, j = 0, inf = 0, max = n, x = 0;

    for (i = inf + 1; i < max; i++)
    {
        x = vet[i];
        j = i-1;
        while (j >= inf && x < vet[j])
        {
            vet[j+1] = vet[j];
            j--;
        }
        vet[j+1] = x;
    }

    for (i = inf; i < max; i++)
    {
        printf (" %d ", vet[i]);
    }

}