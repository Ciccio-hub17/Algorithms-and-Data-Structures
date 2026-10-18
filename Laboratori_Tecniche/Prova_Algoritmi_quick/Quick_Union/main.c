#include <stdio.h>

int main(void)
{
    int i = 0, p = 0, q = 0, vet[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, j = 0, size[10];

    for (i = 0; i < 10; i++)
    {
        vet[i] = i;
        size[i] = 1;
    }

    while (scanf ("%d %d", &p, &q) == 2)
    {
        for (i = p; i != vet[i]; i = vet[i]);
        for (j = q; j != vet[i]; j = vet[i]);
        if (i == j)
        {
            printf ("Coppia già connessa\n");
        }
        else
        {
            if (size[i] <= size[j])
            {
                vet[i] = j;
                size[j] = size[j] + size[i];
            }
            else
            {
                vet[j] = i;
                size[i] = size[i] + size[j];
            }
        }
    }
    return 0;
}