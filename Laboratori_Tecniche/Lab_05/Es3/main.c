#include <stdio.h>
#include <string.h>

# define c_riga 1
# define c_colonna 2
# define c_fine 0

# define d_destra 3
# define d_sinistra 4
# define d_su 5
# define d_giu 6

void carica_matrice (int mat[30][30], int nr, int nc, FILE *input_file);

int leggi_selettore (char selettore[8]);

int leggi_direzione (char direzione[9]);

void gira_riga (int mat[30][30], int nr, int nc, int d, int indice, int posizione);

void gira_colonna (int mat[30][30], int nr, int nc, int d, int indice, int posizione);

int main(void)
{
    FILE *input_file;

    char nome_file[20], stringa_controllo[100], selettore[8], direzione[9];

    int mat [30][30], nr = 0, nc = 0, flag = 1, indice = 0, posizione = 0, s = 0, d = 0, i= 0, j = 0;

    //printf ("Dammi il nome del file: ");
    //scanf ("%s", nome_file);


    if ((input_file = fopen ("../matrice.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file\n");
        return 1;
    }

    fscanf (input_file,"%d %d", &nr, &nc);

    carica_matrice(mat, nr, nc, input_file);

    while (flag)
    {
        printf ("Dammi il selettore, l'indice, la direzione e le posizioni\n");
        fgets (stringa_controllo, sizeof (stringa_controllo), stdin);
        stringa_controllo[strcspn(stringa_controllo, "\n")] = '\0';
        sscanf (stringa_controllo,"%s %d %s %d", selettore, &indice, direzione, &posizione);
        s = leggi_selettore(selettore);
        d = leggi_direzione(direzione);

        switch (s)
        {
            case c_riga:
                gira_riga(mat, nr, nc, d, indice, posizione);
                break;
            case c_colonna:
                gira_colonna(mat, nr, nc, d, indice, posizione);
                break;
            case c_fine:
                flag = 0;
                break;
            default:
                printf ("Errore\n");
                break;
        }
        for (i = 0; i < nr; i++)
        {
            for (j = 0; j < nc; j++)
            {
                printf (" %d ", mat[i][j]);
            }
            printf ("\n");
        }
    }

    return 0;
}

void carica_matrice (int mat[30][30], int nr, int nc, FILE *input_file)
{
    int i = 0, j = 0;

    for (i = 0; i < nr; i++)
    {
        for (j = 0; j < nc; j++)
        {
            fscanf (input_file, "%d", &mat[i][j]);
            printf (" %d ", mat[i][j]);
        }
        printf ("\n");
    }
}

int leggi_selettore (char selettore[8])
{
    int s = 0;

    char tabella[3][9] = {"fine", "riga", "colonna"};

    while (strcmp(selettore, tabella[s])!=0 && s < c_colonna)
    {
        s++;
    }

    return s;
}

int leggi_direzione (char direzione[9])
{
    int d = 3;

    char tabella[4][9] = {"destra", "snistra", "su", "giu"};

    while (strcmp(direzione, tabella[d-3])!=0 && d < d_giu)
    {
        d++;
    }

    return d;
}

void gira_riga (int mat[30][30], int nr, int nc, int d, int indice, int posizione)
{
    int i = 0, index = 0, post = 0, daModificare = 0;

    indice--;

    daModificare = mat [indice][0];

    for (i = 0; i < nc; i++)
    {
        if (d == 3)
        {
            index = (index+posizione);
            while (index >= nc)
            {
                index = index - nc;
            }
            post = mat[indice][index];
            mat[indice][index] = daModificare;
        }
        else
        {
            index = index-posizione;
            while (index < 0)
            {
                index = index + nc;
            }
            post = mat[indice][index];
            mat[indice][index] = daModificare;
        }
        daModificare = post;
    }
}

void gira_colonna (int mat[30][30], int nr, int nc, int d, int indice, int posizione)
{
    int i = 0, index = 0, post = 0, daModificare = 0;

    indice--;

    daModificare = mat [0][indice];

    for (i = 0; i < nr; i++)
    {
        if (d == 6)
        {
            index = index + posizione;
            while (index >= nr)
            {
                index = index - nr;
            }
            post = mat[index][indice];
            mat[index][indice] = daModificare;
        }
        else
        {
            index = index-posizione;
            while (index < 0)
            {
                index = nr + index;
            }
            post = mat[index][indice];
            mat[index][indice] = daModificare;
        }
        daModificare = post;
    }
}