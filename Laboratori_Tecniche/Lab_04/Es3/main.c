#include <stdio.h>
#include <ctype.h>

void trova_sotto_matrice (int mat[20][20], int nr, int nc, int dim);

int main(void)
{
    int mat[20][20], nr, nc, i = 0, j = 0, dim = 0, flag = 0, min;

    FILE *input_file;

    if ((input_file = fopen ("C:\\Users\\franc\\Desktop\\Uni\\Secondo_Semestre\\Tecniche_di_programmazione\\Laboratori\\Lab_04\\Es3\\input.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file\n");
        return 1;
    }

    fscanf(input_file, "%d %d", &nr, &nc);

    printf ("\n");

    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            fscanf(input_file, "%d", &mat[i][j]);
            printf (" %d ", mat[i][j]);
        }
        printf ("\n");
    }

    if (nc > nr)
    {
        min = nr;
    }
    else
    {
        min = nc;
    }

    while (flag == 0)
    {
        printf ("\nDammi la dimensione di cui vuoi estrarre le sottomatrici (Compresa fra 1 e %d)\n", min);
        scanf ("%d", &dim);

        if (dim < 1 || dim > min)
        {
            return 2;
        }
        else
        {
            trova_sotto_matrice(mat, nr, nc, dim);
        }
    }

    return 0;
}

void trova_sotto_matrice (int mat[20][20], int nr, int nc, int dim)
{
    int somma = 0, i = 0, j = 0, n = 0, m = 0, max = 0, sum[dim][dim], s = 0, r = 0, previous = 0;

    while (i <= nr - dim)
    {
        j = 0;
        while (j <= nc - dim)
        {
            if (somma > previous)
            {
                previous = somma;
            }
            somma = 0;
            for (n = i; n < i+dim; n++)
            {
                for (m = j; m < j + dim; m++)
                {
                    printf (" %d ", mat[n][m]);
                    somma = somma + mat[n][m];
                }
                printf ("\n");
            }
            printf ("\n");

            if (somma > previous)
            {
                s = 0;
                r = 0;
                for (n = i; n < i+dim; n++)
                {
                    r = 0;
                    for (m = j; m < j + dim; m++)
                    {
                        sum [s][r] = mat[n][m];
                        r++;
                    }
                    s++;
                }
            }

            j++;
        }

        i++;
    }

    printf ("La sottomatrice con somma degli elementi massima (%d) e':\n", previous);
    for (i = 0; i < dim; i++)
    {
        for (j = 0; j < dim; j++)
        {
            printf (" %d ", sum [i][j]);
        }
        printf ("\n");
    }

}