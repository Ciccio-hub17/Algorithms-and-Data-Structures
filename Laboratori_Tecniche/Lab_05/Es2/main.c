#include <stdio.h>
#include <string.h>

int carica_dizionario (char codifica[50][50], char parola[50][50], FILE *dizionario);

int main(void)
{
    FILE *sorgente, *dizionario, *output;

    int righe = 0, lunghezza = 0, i = 0, k = 0, n = 0, m = 0, s = 0, r = 0, flag = 0, indice = 0;

    char line_sorgente [200], codifica[50][50], parola[50][50], stringa[200], appoggio [200];

    if ((sorgente = fopen ("../sorgente.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file sorgente\n");
        return 1;
    }

    if ((dizionario = fopen ("../dizionario.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file dizionario\n");
        return 2;
    }

    if ((output = fopen ("../output.txt", "w")) == NULL)
    {
        printf ("Errore nell'apertura del file di output\n");
        return 3;
    }

    righe = carica_dizionario(codifica, parola, dizionario);

    while (fgets (line_sorgente, sizeof (line_sorgente), sorgente))
    {
        lunghezza = (int) strlen (line_sorgente);
        i = 0;
        while (i < lunghezza)
        {
            n = 0;
            if (line_sorgente[i] != ' ' && line_sorgente[i] != '\n')
            {
                k = 0;
                while (line_sorgente[i] != ' ' && line_sorgente[i] != '\n')
                {
                    stringa[k] = line_sorgente[i];
                    k++;
                    i++;
                }
                stringa[k+1] = '\0';
                while (n < k)
                {
                    s = 0;
                    for (m = n; m < k; m++)
                    {
                        appoggio [s] = stringa[m];
                        s++;
                    }
                    appoggio[s] = '\0';
                    flag = 0;
                    for (r = 0; r < righe && (!flag); r++)
                    {
                        if (strcmp (appoggio, parola[r]) == 0)
                        {
                            flag = 1;
                            indice = r;
                        }
                    }
                    if (flag)
                    {
                        fprintf (output, "%s", codifica[indice]);
                        n = n + (int) strlen (parola[indice]);
                    }
                    else
                    {
                        fprintf (output, "%c", stringa[n]);
                        n++;
                    }
                }
            }
            else
            {
                fprintf (output, "%c", line_sorgente[i]);
                i++;
            }

        }

    }
    return 0;
}

int carica_dizionario (char codifica[50][50], char parola[50][50], FILE *dizionario)
{
    int righe, i = 0, j = 0;

    fscanf (dizionario, "%d", &righe);

    for (i = 0; i < righe; i++)
    {
        fscanf(dizionario, "%s", &codifica[j]);
        fscanf(dizionario, "%s", &parola[j]);
        j++;
    }

    return righe;
}