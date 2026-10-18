#include <stdio.h>

int main(void)
{
    int vet [10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, n = 10, i = 0, j = 0, min = i, temp = 0;

    for (i = 0; i < n-1; i++)
    {
        min = i;
        for (j = i+1; j < n; j++)
        {
            if (vet[j] <= vet[i])
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = vet[i];
            vet[i] = vet[min];
            vet[min] = vet[i];
        }
    }

    return 0;
}