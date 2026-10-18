#include <stdio.h>

void bubble_sort (int vet[7], int n);

int main(void)
{
    int vet[7] = {4, 7, 1, -1, 0, 10, 3}, n = 7;

    bubble_sort(vet, n);

    return 0;
}

void bubble_sort (int vet[7], int n)
{
    int i = 0, j = 0, inf = 0, max = n, flag = 1, temp = 0;

    for (i = inf; i < max - 1 && flag == 1; i++)
    {
        flag = 0;
        for (j = inf; j < max - 1 - i + inf; j++)
        {
            if (vet[j] > vet[j+1])
            {
                flag = 1;
                temp = vet[j+1];
                vet[j+1] = vet[j];
                vet[j] = temp;
            }
        }
    }

    for (i = inf; i < max; i++)
    {
        printf (" %d ", vet[i]);
    }

}