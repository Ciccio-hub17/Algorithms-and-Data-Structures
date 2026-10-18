#include <stdio.h>

void insertionSort (int vet[100], int len);
void bubbleSort (int vet[100], int len);
void selectionSort (int vet[100], int len);
void copia (int vet[100], int vetCopia [100], int len);

int main(void)
{
    FILE *input;
    int lunghezzaFile = 0, i = 0, lunghezza = 0, vet[100], j = 0, vetCopia[100];
    if ((input = fopen ("../sort.txt", "r")) == NULL )
    {
        printf ("Errore nell'apertura del file \n");
        return 1;
    }

    fscanf (input, "%d", &lunghezzaFile);

    for (i = 0; i < lunghezzaFile; i++)
    {
        fscanf(input, "%d", &lunghezza);
        for (j = 0; j < lunghezza; j++)
        {
            fscanf (input, "%d", &vet[j]);
        }
        copia(vet, vetCopia, lunghezza);
        insertionSort(vetCopia, lunghezza);
        copia(vet, vetCopia, lunghezza);
        bubbleSort(vetCopia, lunghezza);
        copia(vet, vetCopia, lunghezza);
        selectionSort(vetCopia, lunghezza);
    }

    fclose (input);
    return 0;
}

void copia (int vet[100], int vetCopia [100], int len)
{
    int i = 0;

    for (i = 0; i < len; i++)
    {
        vetCopia[i] = vet[i];
    }
}

void insertionSort (int vet[100], int len)
{
    int i = 0, j = 0, x=0, scambi = 0, itInt = 0, itEst = 0, totIt = 0;
    printf ("Insertion sort\n");
    for (i = 1; i < len; i++)
    {
        printf ("Passo %d: ", i);
        j = i-1;
        x = vet[i];
        itInt=0;
        while (j >= 0 && x < vet[j])
        {
            vet[j+1] = vet[j];
            scambi++;
            j--;
            totIt++;
            itInt++;
        }
        printf ("%d iterazioni\n", itInt);
        vet[j+1] = x;
        totIt++;
        itEst++;
    }

    printf ("Numero di scambi: %d\n", scambi);
    printf ("Iterazioni ciclo esterno: %d\n", itEst);
    printf ("iterazioni totali: %d\n", totIt);
}

void bubbleSort (int vet[100], int len)
{
    int i = 0, j = 0, scambi = 0, itInt = 0, itEst = 0, totIt = 0, temp=0, flag = 1;

    printf ("Bubble sort\n");
    for (i = 0; i < len-1 && flag == 1; i++)
    {
        flag = 0;
        itInt=0;
        printf ("Passo %d: ", i);
        for (j = 0; j < len - i - 1; j++)
        {
            if (vet[j] > vet[j+1])
            {
                flag = 1;
                temp = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = temp;
                scambi++;
            }
            itInt++;
            totIt++;
        }
        printf ("%d iterazioni\n", itInt);
        itEst++;
        totIt++;
    }

    printf ("Numero di scambi: %d\n", scambi);
    printf ("Iterazioni ciclo esterno: %d\n", itEst);
    printf ("iterazioni totali: %d\n", totIt);
}

void selectionSort (int vet[100], int len)
{
    int i = 0, j = 0, scambi = 0, itInt = 0, itEst = 0, totIt = 0, temp=0, min=0;

    printf ("Selection sort\n");
    for (i = 0; i < len - 1; i++)
    {
        printf ("Passo %d: ", i);
        min = i;
        itInt=0;
        for (j = i+1; j < len; j++)
        {
            if (vet[j] < vet[min])
            {
                min = j;
            }
            itInt++;
            totIt++;
        }
        if (min != i)
        {
            temp = vet[i];
            vet[i] = vet[min];
            vet[min] = temp;
            scambi++;
        }
        printf ("%d iterazioni\n", itInt);
        itEst++;
        totIt++;
    }

    printf ("Numero di scambi: %d\n", scambi);
    printf ("Iterazioni ciclo esterno: %d\n", itEst);
    printf ("iterazioni totali: %d\n", totIt);
}