#include <stdio.h>

#define fileName "C:/Users/franc/Desktop/Uni/Secondo_Semestre/Tecniche_di_programmazione/Laboratori/Lab_03/Es3/numeri.txt"

int massimo (int numbers[100], int k);

int minimo (int numbers[100], int k);



int main(void)
{
    FILE *input_file;

    int first_number = 0, second_number = 0, max = 0 , min = 0 , scarted = 0, i = 0, length = 0, flag = 0, to_do = 0, numbers [20], k = 0, result = 0, j, dimension, number;

    if ((input_file = fopen (fileName, "r")) == NULL)
    {
        printf ("Errore nell'apertura del file\n");
        return 1;
    }

    while ((fscanf (input_file, "%d", &number)) == 1)
    {
        numbers [k] = number;
        k++;
    }

    max = massimo (numbers, k);
    min = minimo (numbers, k);

    printf ("Vengono scartati:\n");

    for (i = 2; i < k; i++)
    {
        first_number = numbers [i-2];
        second_number = numbers [i-1];

        if (first_number + second_number != numbers[i])
        {
            if (first_number - second_number != numbers [i])
            {
                if (first_number * second_number != numbers[i])
                {
                    if (second_number != 0)
                    {
                        if (first_number / second_number != numbers[i])
                        {
                            scarted++;
                            printf ("%d perche' non e' il risultato di alcuna operazione su %d e %d\n", numbers[i], first_number, second_number);
                            i = i + 2;
                        }
                    }
                }
            }
        }
    }

    printf ("Numero massimo: %d\n", max);
    printf ("Numero minimo: %d\n", min);
    printf ("Numeri scartati: %d\n", scarted);

    return 0;

}

int massimo (int numbers[100], int k)
{
    int max = numbers[0], i = 0;

    for (i = 0; i < k; i++)
    {
        if (numbers[i] >= max)
        {
            max = numbers[i];
        }
    }

    return max;
}

int minimo (int numbers[100], int k)
{
    int min = numbers[0], i = 0;

    for (i = 0; i < k; i++)
    {
        if (numbers[i] <= min)
        {
            min = numbers[i];
        }
    }

    return min;
}