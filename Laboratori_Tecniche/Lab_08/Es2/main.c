#include <stdio.h>

void stampaCodifica (void *p, int size, int bigEndian);

void endianness (int test, int *endian);

void converti (unsigned char vet[8], int v[], int size);

int main(void)
{
    float af = -10.354;
    double ad = 11.3465;

    int test = 1;

    void *p = &af;
    void *p1 = &ad;

    int bigEndian = 0, dimaf, dimad;

    dimaf = sizeof (af);
    dimad = sizeof (ad);

    printf ("%d %d sono le dimensioni in byte (rispettivamente float e double)\n", dimaf, dimad);
    printf ("%d %d sono le dimensioni in bit (rispettivamente float e double)\n", dimaf*8, dimad*8);

    endianness(test, &bigEndian);

    stampaCodifica(p, dimaf, bigEndian);
    stampaCodifica(p1, dimad, bigEndian);

    return 0;
}

void endianness (int test, int *endian)
{
    char *p;

    p = (char *)&test;
    if (*p == 1)
    {
        printf ("Il computer usa la codifica littleEndian\n");
        *endian = 0;
    }
    else
    {
        printf ("Il computer usa la codifica bigEndian\n");
        *endian = 1;
    }
}

void stampaCodifica (void *p, int size, int bigEndian)
{
    unsigned char vet[8];

    unsigned char *p1;

    p1 = (unsigned char *)p;


    int i = 0, v[size*8];

    for (i = 0; i < size; i++)
    {
         vet[i] = *p1;
         p1++;
    }

    for (i = 0; i < size; i++)
    {
        vet[i] = (int) vet[i];
    }

    converti(vet, v, size);

    if (size == 4)
    {
        for (i = size*8-1; i > size*8-10; i--)
        {
            if (i == size*8-1)
            {
                printf ("Bit segno: \n%d \nBit esponente\n", v[i]);
            }
            else
            {
                printf (" %d ", v[i]);
            }
        }
        printf ("\n Bit mantissa \n");
        for (i = size*8-10; i >= 0; i--)
        {
            printf (" %d ", v[i]);
        }
        printf ("\n");
    }
    else
    {
        for (i = size*8-1; i > size*8-13; i--)
        {
            if (i == size*8-1)
            {
                printf ("Bit segno: \n%d \nBit esponente\n", v[i]);
            }
            else
            {
                printf (" %d ", v[i]);
            }
        }
        printf ("\n Bit mantissa \n");
        for (i = size*8-13; i >= 0; i--)
        {
            printf (" %d ", v[i]);
        }
        printf ("\n");
    }
}

void converti (unsigned char vet[8], int v[], int size)
{
    int i = 0, num = 0, codifica[8], j = 0, k = 0;

    for (i = 0; i < size; i++)
    {
        num = (int) vet[i];
        for (j = 0; j < 8; j++)
        {
            codifica[j] = num % 2;
            num = num / 2;
        }
        for (j = 0; j < 8; j++)
        {
            v[k] = codifica[j];
            k++;
        }
    }
}