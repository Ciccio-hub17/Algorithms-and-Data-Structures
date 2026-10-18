#include <ctype.h>
#include <stdio.h>
#include <string.h>

int leggiSequenze (char sequenze [30][5], FILE *input_file);
void controllo (char sequenze [30][5], int nS, FILE *testo);

int main(void)
{
    int nS = 0;
    char sequenze [30][5];
    FILE *input_file, *testo;

    if ((input_file = fopen("../sequenze.txt", "r")) == NULL )
    {
        printf ("Errore nell'apertura del file\n");
        return 1;
    }

    nS = leggiSequenze(sequenze, input_file);

    if ((testo = fopen ("../testo.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file \n");
        return 2;
    }

    controllo (sequenze, nS, testo);

    fclose (testo);
    fclose(input_file);
    return 0;
}

int leggiSequenze (char sequenze [30][5], FILE *input_file)
{
    int dim = 0, i = 0, j = 0;

    fscanf (input_file, "%d", &dim);

    for (i = 0; i < dim; i++)
    {
        fscanf (input_file, "%s", sequenze[i]);
        for (j = 0; j < strlen (sequenze[i]); j++)
        {
            sequenze[i][j] = (char) tolower(sequenze[i][j]);
        }
    }

    return dim;
}

void controllo (char sequenze [30][5], int nS, FILE *testo)
{
    char riga [200], parola [25];

    int i = 0, j = 0, flag = 0, lenSeq, pos = 0, lenCod = 0, k = 0, contatore = 1, occorrenze = 1, len = 0;

    for (i = 0; i < nS; i++)
    {
        printf ("le occorrenze della sequenza %s sono:\n", sequenze[i]);
        contatore = 1;
        occorrenze = 0;
        rewind (testo);
        lenCod = (int) strlen (sequenze[i]);
        char sottoParola[lenCod];
        while (fgets (riga, 200, testo))
        {
            pos = 0;
            while ((sscanf (riga + pos, "%s", parola)) && (occorrenze < 10) && (pos < strlen (riga) - strlen(parola)))
            {
                j = 0;
                flag = 0;
                len = strlen(parola);
                while ((j <= len - lenCod) && (flag == 0))
                {
                    for (k = j; k < lenCod+j; k++)
                    {
                        sottoParola[k-j] = tolower (parola[k]);
                    }
                    sottoParola[k] = '\0';
                    if (strcmp (sottoParola, sequenze[i]) == 0)
                    {
                        flag = 1;
                    }
                    j++;
                }

                if (flag)
                {
                    printf ("%s (posizione %d)\n", parola, contatore);
                    occorrenze++;
                }

                contatore++;
                pos = pos + strlen (parola)+1;
            }
        }
        if (occorrenze == 0)
        {
            printf ("Nessuna\n");
        }
        printf ("\n");
    }
}