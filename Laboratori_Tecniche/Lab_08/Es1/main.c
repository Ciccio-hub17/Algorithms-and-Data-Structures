#include <stdio.h>

void leggiMatrice (FILE *input_file, int *nr, int *nc, int matrice [50][50]);
int riconosciRegione(int mat[50][50],int nr,int nc,int r,int c,int *b,int *h);

int main(void)
{
    FILE *input_file;
    int matrice[50][50], i = 0, j = 0, b, h;

    int nr, nc;

    if ((input_file = fopen ("../matrice.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file\n");
        return 1;
    }

    leggiMatrice(input_file, &nr, &nc, matrice);

    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            if (riconosciRegione (matrice, nr, nc, i, j, &b, &h))
            {
                printf ("Rettangolo in vertice (%d, %d) di base %d e di altezzza %d\n", i+1, j+1, b, h);
            }
        }
    }

    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            printf (" %d ", matrice[i][j]);
        }
        printf ("\n");
    }

    fclose (input_file);
    return 0;
}

void leggiMatrice (FILE *input_file, int *nr, int *nc, int matrice [50][50])
{
    int i = 0, j = 0;

    fscanf (input_file, "%d %d", nr, nc);

    for (i = 0; i < *nr; i++)
    {
        for (j = 0; j < *nc; j++)
        {
            fscanf (input_file, "%d", &matrice[i][j]);
            printf (" %d ", matrice[i][j]);
        }
        printf ("\n");
    }
}

int riconosciRegione(int mat[50][50],int nr,int nc,int r,int c,int *b,int *h)
{
    int bool = 0, i = r, j = c, i1 = 0, j1 = 0;

    if (mat[r][c] == 1)
    {
        bool = 1;
        *b = 1;
        *h = 1;
        j++;
        while (mat[r][j] == 1 && j < nc)
        {
            *b=*b+1;
            j++;
        }
        i++;
        while (mat[i][c] == 1 && i < nr)
        {
            *h=*h+1;
            i++;
        }
        for (i1 = r; i1 <= i-1; i1++)
        {
            for (j1 = c; j1 <= j-1; j1++)
            {
                mat[i1][j1] = -1;
            }
        }
        return bool;
    }

    return bool;
}

