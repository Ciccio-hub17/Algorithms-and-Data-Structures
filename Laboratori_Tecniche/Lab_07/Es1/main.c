#include <stdio.h>

typedef struct
{
    int x;
    int y;
    int altezza;
    int larghezza;
    int area;
}rettangoli;
void leggiFile (FILE *input_file, int nr, int nc, int matrice [50][50]);
void controllo (int matrice [50][50], int nr, int nc);

int main(void)
{
    FILE *input_file;
    int nr = 0, nc = 0, matrice[50][50];

    if ((input_file = fopen ("../matrice.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file\n");
        return 1;
    }

    fscanf (input_file, "%d %d", &nr, &nc);

    leggiFile(input_file, nr, nc, matrice);

    controllo (matrice, nr, nc);


    fclose (input_file);
    return 0;
}

void leggiFile (FILE *input_file, int nr, int nc, int matrice [50][50])
{
    int i = 0, j = 0;

    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            fscanf (input_file, "%d", &matrice[i][j]);
            printf (" %d ", matrice[i][j]);
        }
        printf ("\n");
    }
}

void controllo (int matrice [50][50], int nr, int nc)
{
    int i = 0, j = 0, altezzaMax = 0, larghezzaMax = 0, areaMax = 0, k = 0, n = 0, flag = 0, iAlt = 0, iLar = 0, iArea = 0, trovato = 0;
    rettangoli ret[25];

    while (i < nr && k == 0)
    {
        while (j < nc && k == 0)
        {
            if (matrice[i][j] == 1 && j < nc)
            {
                ret[k].x = i; ret[k].y = j; ret[k].altezza = 1; ret[k].larghezza = 1; ret[k].area = 1;
                trovato = 1;
                j++;
            }
            while (matrice[i][j] == 1 && j < nc)
            {
                ret[k].larghezza++; ret[k].area++;
                j++;
                k++;
            }
            if (trovato && k == 0)
            {
                k++;
            }
            j++;
        }
        i++;
    }

    while (i < nr)
    {
        j = 0;
        while (j < nc)
        {
            flag = 0;
            if (matrice[i][j] == 1)
            {
                for (n = 0; n < k && flag == 0; n++)
                {
                    if (j == ret[n].y && matrice[i-1][j] == 1)
                    {
                        flag = 1;
                    }
                }
                if (flag)
                {
                    n--;
                    ret[n].altezza++; ret[n].area++;
                    j++;
                    while (matrice[i][j] == 1 && j < nc)
                    {
                        ret[n].area++;
                        j++;
                    }
                }
                else
                {
                    ret[k].x = i; ret[k].y = j; ret[k].altezza = 1; ret[k].area = 1; ret[k].larghezza = 1;
                    j++;
                    while (matrice[i][j] == 1 && j < nc)
                    {
                        ret[k].area++;
                        ret[k].larghezza++;
                        j++;
                    }
                    k++;
                }
            }
            j++;
        }
        i++;
    }

    for (n = 0; n < k; n++)
    {
        if (ret[n].altezza > altezzaMax)
        {
            altezzaMax = ret[n].altezza;
            iAlt = n;
        }
        if (ret[n].larghezza > larghezzaMax)
        {
            larghezzaMax = ret[n].larghezza;
            iLar = n;
        }
        if (ret[n].area > areaMax)
        {
            areaMax = ret[n].area;
            iArea = n;
        }
    }

    printf ("Max altezza: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d \n", ret[iAlt].x, ret[iAlt].y, ret[iAlt].altezza, ret[iAlt].larghezza, ret[iAlt].area);
    printf ("Max larghezza: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d \n", ret[iLar].x, ret[iLar].y, ret[iLar].altezza, ret[iLar].larghezza, ret[iLar].area);
    printf ("Max area: estremo=(%d,%d), altezza=%d, larghezza=%d, area=%d \n", ret[iArea].x, ret[iArea].y, ret[iArea].altezza, ret[iArea].larghezza, ret[iArea].area);

}