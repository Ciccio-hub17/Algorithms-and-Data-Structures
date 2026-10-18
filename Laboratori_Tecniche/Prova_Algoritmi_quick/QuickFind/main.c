#include <stdio.h>

int main(void)
{
    int vet[10] = {0,1,2,3,4,5,6,7,8,9}, i = 0, p = 0, q = 0;

    for (i = 0; i < 10; i++)
    {
        vet[i] = i;
    }
    while (scanf ("%d %d", &p, &q) == 2)
    {
        if (vet[p] == vet[q])
        {
            printf ("Coppia già connessa\n");
        }
        else
        {
            for (i = 0; i < 10; i++)
            {
                if (vet[i] == vet[p])
                {
                    vet[i] = vet[q];
                }
            }
        }
    }
    return 0;
}