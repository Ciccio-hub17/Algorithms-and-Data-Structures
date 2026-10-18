#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//mi serve per capire che tipo di istruzione devo prendere
#define r_date 0
#define r_partenza 1
#define r_capolinea 2
#define r_ritardo 3
#define r_ritardo_tot 4
#define r_fine 5

void leggi_file (FILE *input_file, char riga [200], int nr, char struttura[][6][30], int ritardi[]);
int leggi_comando(char comando [15]);
void menu_parola(int nr, char struttura[][6][30], int ritardi[]);
void date (int nr, char struttura[nr][6][30], char data1[], char data2[]);
void partenza (int nr, char struttura[nr][6][30], char fermata[30]);
void capolinea(int nr, char struttura[nr][6][30], char fermata[30]);
void corsa_ritardo (int nr, char struttura[nr][6][30], char data1[], char data2[], int ritardi[nr]);
void ritardo_complessivo (int nr, char struttura[nr][6][30], int ritardi[nr], char tratta[30]);

int main(void)
{
    //leggo il file
    FILE *input_file;
    char riga [1000];

    int nr = 0;

    if ((input_file = fopen ("../log.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file \n");
        return 1;
    }

    //leggo la prima riga e mi faccio dare il numero di righe
    fscanf (input_file, " %d ", &nr);

    //matrice di caratteri così composta: per ogni riga, salva i dati che leggi da file
    //<codice_tratta><partenza><destinazione><data><ora_partenza><ora_arrivo>
    //che sono composte al massimo da 30 caratteri

    char struttura[nr][6][30];
    // qui mi salvo il ritardo perchè posso trattarlo come intero
    int ritardi[nr];

    //leggo il file nella sua interezza salvando i dati nella matriciona
    leggi_file(input_file, riga, nr, struttura, ritardi);

    menu_parola(nr, struttura, ritardi);

    fclose(input_file);

    return 0;
}


void leggi_file (FILE *input_file, char riga [200], int nr, char struttura[nr][6][30], int ritardi[nr])
{
    int i = 0;

    //salvo le info che mi servono dentro la matrice
    while (fgets (riga, 200, input_file) != NULL)
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
        //richiesta contiene il comando e poi altre informazioni utili
        fgets (richiesta, 100, stdin);
        //prendo la prima parola disponibile e la mando ad una funzione che la switcha in intero
        sscanf (richiesta, " %s", comando);
        comando_int = leggi_comando(comando);
        char data1[11], data2[11];
        char fermataP [30];
        char fermataA [30];
        char data_1[11], data_2[11];
        char tratta[30];
        //capisco che comando è stato usato
        switch (comando_int)
        {
            //controlla tutte le corse partite tra due date
            case r_date:
                sscanf (richiesta, " %*s %s %s ", data1, data2);
                date(nr, struttura, data1, data2);
                break;
            //controlla tutte le corse che sono partite da una certa fermata
            case r_partenza:
                sscanf (richiesta, " %*s %s", fermataP);
                partenza(nr, struttura, fermataP);
                break;
            //controlla tutte le corse che fanno capolinea in una certa fermata
            case r_capolinea:
                sscanf (richiesta, " %*s %s", fermataA);
                capolinea(nr, struttura, fermataA);
                break;
            //tutte le corse che hanno fatto ritardo in un certo intervallo di date
            case r_ritardo:
                sscanf (richiesta, " %*s %s %s ", data_1, data_2);
                corsa_ritardo(nr, struttura, data_1, data_2, ritardi);
                break;
            //calcola il ritardo complessivo di una determinata tratta
            case r_ritardo_tot:
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

//Permette di leggere qual è il tipo di comando che è stato richiesto

int leggi_comando(char comando [15])
{
    //mi serve per capire quale richiesta è stata fatta
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
    
    //controllo qual è la data più piccola (fortunatamente è scritta in americano)
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

    //ciclo su tutta la matrice
    for (i = 0; i < nr; i++)
    {
        //controllo se la data della riga i-esima è compresa tra le mie due
        if (strcmp (struttura[i][3], dataMin) >= 0 && strcmp (struttura[i][3], dataMax) <= 0)
        {
            printf ("%s\n", struttura[i][0]);
        }
    }
}

void partenza (int nr, char struttura[nr][6][30], char fermata[30])
{
    int i = 0;

    //sempre ciclo sulla matrice
    for (i = 0; i < nr; i++)
    {
        //controllo se la fermata di partenza della tratta è uguale a quella data in input
        if (strcmp (fermata, struttura[i][1]) == 0)
        {
            printf ("%s\n", struttura[i][0]);
        }
    }
}

void capolinea (int nr, char struttura[nr][6][30], char fermata[30])
{
    int i = 0;

    //sempre ciclo sulla matrice
    for (i = 0; i < nr; i++)
    {
        //controllo se la fermata di arrivo della tratta è uguale a quella data in input
        if (strcmp (fermata, struttura[i][2]) == 0)
        {
            printf ("%s\n", struttura[i][0]);
        }
    }
}

void corsa_ritardo (int nr, char struttura[nr][6][30], char data1[], char data2[], int ritardi[nr])
{
    //solito algoritmo per segnarmi qual è la data più piccola e quella più grande
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

    //solito ciclo
    for (i = 0; i< nr; i++)
    {
        //controllo se la data è compresa e se il ritardo è maggiore di 0
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
        //controllo se il codice tratta è quello dato in input oppure no
        if (strcmp (struttura[i][0], tratta) == 0)
        {
            //se lo è somma i ritardi
            somma = somma + ritardi[i];
        }
    }

    //printa il ritardo complessivo
    printf ("Ritardo complessivo della tratta %s: %d minuti\n", tratta, somma);
}