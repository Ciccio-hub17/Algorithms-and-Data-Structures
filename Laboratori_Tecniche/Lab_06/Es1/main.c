#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define r_date 0
#define r_partenza 1
#define r_capolinea 2
#define r_ritardo 3
#define r_ritardo_tot 4
#define r_fine 5

void leggi_file (FILE *input_file, char riga [1000], int nr, char struttura[][6][30], int ritardi[]);
int leggi_comando(char comando [15]);
void menu_parola(int nr, char struttura[][6][30], int ritardi[]);
void date (int nr, char struttura[nr][6][30], char data1[], char data2[]);
void partenza (int nr, char struttura[nr][6][30], char fermata[30]);
void capolinea(int nr, char struttura[nr][6][30], char fermata[30]);
void corsa_ritardo (int nr, char struttura[nr][6][30], char data1[], char data2[], int ritardi[nr]);
void ritardo_complessivo (int nr, char struttura[nr][6][30], int ritardi[nr], char tratta[30]);

int main(void)
{
    FILE *input_file;
    char riga [1000];

    int nr = 0;

    if ((input_file = fopen ("../log.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file \n");
        return 1;
    }

    fscanf (input_file, " %d ", &nr);

    char struttura[nr][6][30];
    int ritardi[nr];

    leggi_file(input_file, riga, nr, struttura, ritardi);

    menu_parola(nr, struttura, ritardi);

    return 0;
}

void leggi_file (FILE *input_file, char riga [1000], int nr, char struttura[nr][6][30], int ritardi[nr])
{
    int i = 0;

    while (fgets (riga, 1000, input_file) != NULL)
    {
        sscanf (riga, " %s %s %s %s %s %s %d ", struttura[i][0], struttura[i][1], struttura[i][2], struttura[i][3], struttura[i][4], struttura[i][5], &ritardi[i]);
        i++;
    }

}

void menu_parola(int nr, char struttura[nr][6][30], int ritardi[nr])
{
    char richiesta [100], comando [15];

    int comando_int = 0, flag = 1;

    while (flag)
    {
        printf ("Cosa vuoi fare?\n");
        fgets (richiesta, 100, stdin);
        sscanf (richiesta, " %s", comando);
        comando_int = leggi_comando(comando);
        switch (comando_int)
        {
            case r_date:
                char data1[11], data2[11];
                sscanf (richiesta, " %*s %s %s ", data1, data2);
                date(nr, struttura, data1, data2);
                break;
            case r_partenza:
                char fermataP [30];
                sscanf (richiesta, " %*s %s", fermataP);
                partenza(nr, struttura, fermataP);
                break;
            case r_capolinea:
                char fermataA [30];
                sscanf (richiesta, " %*s %s", fermataA);
                capolinea(nr, struttura, fermataA);
                break;
            case r_ritardo:
                char data_1[11], data_2[11];
                sscanf (richiesta, " %*s %s %s ", data_1, data_2);
                corsa_ritardo(nr, struttura, data_1, data_2, ritardi);
                break;
            case r_ritardo_tot:
                char tratta[30];
                sscanf(richiesta, "%*s %s", tratta);
                ritardo_complessivo(nr, struttura, ritardi, tratta);
                break;
            case r_fine:
                flag = 0;
                break;
            default:
                printf ("Scelta errata\n");
                break;
        }
    }
}

int leggi_comando(char comando [15])
{
    int c=0;

    char tabella[6][15] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};

    while (strcmp(comando, tabella[c]) != 0 && c < r_fine)
    {
        c++;
    }
    return c;
}

void date (int nr, char struttura[nr][6][30], char data1[11], char data2[11])
{
    char dataMax[11], dataMin [11];
    int i = 0;

    if (strcmp (data1, data2) > 0)
    {
        for (i = 0; i < 11; i++)
        {
            dataMax[i] = data1[i];
            dataMin[i] = data2[i];
        }
    }
    else
    {
        for (i = 0; i < 11; i++)
        {
            dataMax[i] = data2[i];
            dataMin[i] = data1[i];
        }
    }

    for (i = 0; i < nr; i++)
    {
        if (strcmp (struttura[i][3], dataMin) >= 0 && strcmp (struttura[i][3], dataMax) <= 0)
        {
            printf ("%s\n", struttura[i][0]);
        }
    }
}

void partenza (int nr, char struttura[nr][6][30], char fermata[30])
{
    int i = 0;

    for (i = 0; i < nr; i++)
    {
        if (strcmp (fermata, struttura[i][1]) == 0)
        {
            printf ("%s\n", struttura[i][0]);
        }
    }
}

void capolinea (int nr, char struttura[nr][6][30], char fermata[30])
{
    int i = 0;

    for (i = 0; i < nr; i++)
    {
        if (strcmp (fermata, struttura[i][2]) == 0)
        {
            printf ("%s\n", struttura[i][0]);
        }
    }
}

void corsa_ritardo (int nr, char struttura[nr][6][30], char data1[], char data2[], int ritardi[nr])
{
    char dataMax[11], dataMin [11];
    int i = 0;

    if (strcmp (data1, data2) > 0)
    {
        for (i = 0; i < 11; i++)
        {
            dataMax[i] = data1[i];
            dataMin[i] = data2[i];
        }
    }
    else
    {
        for (i = 0; i < 11; i++)
        {
            dataMax[i] = data2[i];
            dataMin[i] = data1[i];
        }
    }

    for (i = 0; i< nr; i++)
    {
        if (strcmp (struttura[i][3], dataMin) >= 0 && strcmp (struttura[i][3], dataMax) <= 0 && ritardi [i] > 0)
        {
            printf ("%s\n", struttura[i][0]);
        }
    }
}

void ritardo_complessivo (int nr, char struttura[nr][6][30], int ritardi[nr], char tratta[30])
{
    int somma = 0, i = 0;

    for (i = 0; i < nr; i++)
    {
        if (strcmp (struttura[i][0], tratta) == 0)
        {
            somma = somma + ritardi[i];
        }
    }

    printf ("Ritardo complessivo della tratta %s: %d minuti\n", tratta, somma);
}