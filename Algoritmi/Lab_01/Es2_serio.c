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

//struttura che permette di prendere i dati
typedef struct struttura{
    char codice[30];
    char partenza[30];
    char destinazione[30];
    char data[30];
    char ora_partenza[30];
    char ora_arrivo[30];
    int ritardo;
}struttura;

void leggi_file (FILE *input_file, int nr, struttura vet[]);
int leggi_comando(char comando [15]);
void menu_parola(int nr, struttura vet[]);
void date (int nr, struttura vet[], char data1[], char data2[]);
void partenza (int nr, struttura vet[], char fermata[30]);
void capolinea(int nr, struttura vet[], char fermata[30]);
void corsa_ritardo (int nr, struttura vet[], char data1[], char data2[]);
void ritardo_complessivo (int nr, struttura vet[], char tratta[30]);

int main(void)
{
    //leggo il file
    FILE *input_file;

    int nr = 0;

    //controllo se il file non è vuoto
    if ((input_file = fopen ("C:\\Users\\franc\\Desktop\\Uni\\Secondo_Anno\\Algoritmi\\Lab_01\\log.txt", "r")) == NULL)
    {
        printf ("Errore nell'apertura del file \n");
        return 1;
    }

    //leggo la prima riga e mi faccio dare il numero di righe
    fscanf (input_file, " %d ", &nr);

    //vettore di strutture
    struttura vet[nr];

    //leggo il file nella sua interezza salvando i dati nella struttura
    leggi_file(input_file, nr, vet);

    //il menu che mi permette di gestire i dati
    menu_parola(nr, vet);

    //chiudo il file
    fclose(input_file);

    return 0;
}


void leggi_file (FILE *input_file, int nr, struttura vet[])
{
    int i = 0;

    //salvo le info che mi servono dentro la struttura
    while (fscanf (input_file, " %s %s %s %s %s %s %d ", vet[i].codice, vet[i].partenza, vet[i].destinazione, vet[i].data, vet[i].ora_partenza, vet[i].ora_arrivo, &vet[i].ritardo) == 7)
    {
        i++;
    }

}

void menu_parola(int nr, struttura vet[])
{
    char richiesta [100], comando [15];

    int comando_int = 0, flag = 1;

    char data1[11], data2[11];
    char fermataP[30];
    char fermataA [30];
    char tratta[30];

    while (flag)
    {
        printf ("Cosa vuoi fare?\n");
        //richiesta contiene il comando e poi altre informazioni utili
        fgets (richiesta, 100, stdin);
        //prendo la prima parola disponibile e la mando ad una funzione che la switcha in intero
        sscanf (richiesta, " %s", comando);
        comando_int = leggi_comando(comando);
        //capisco che comando è stato usato
        switch (comando_int)
        {
            //controlla tutte le corse partite tra due date
            case r_date:
                sscanf (richiesta, " %*s %s %s ", data1, data2);
                date(nr, vet, data1, data2);
                break;
            //controlla tutte le corse che sono partite da una certa fermata
            case r_partenza:
                sscanf (richiesta, " %*s %s", fermataP);
                partenza(nr, vet, fermataP);
                break;
            //controlla tutte le corse che fanno capolinea in una certa fermata
            case r_capolinea:
                sscanf (richiesta, " %*s %s", fermataA);
                capolinea(nr, vet, fermataA);
                break;
            //tutte le corse che hanno fatto ritardo in un certo intervallo di date
            case r_ritardo:
                sscanf (richiesta, " %*s %s %s ", data1, data2);
                corsa_ritardo(nr, vet, data1, data2);
                break;
            //calcola il ritardo complessivo di una determinata tratta
            case r_ritardo_tot:
                sscanf(richiesta, "%*s %s", tratta);
                ritardo_complessivo(nr, vet, tratta);
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

void date (int nr, struttura vet[], char data1[11], char data2[11])
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
        if (strcmp (vet[i].data, dataMin) >= 0 && strcmp (vet[i].data, dataMax) <= 0)
        {
            printf ("%s\n", vet[i].codice);
        }
    }
}

void partenza (int nr, struttura vet[], char fermata[30])
{
    int i = 0;

    //sempre ciclo sulla matrice
    for (i = 0; i < nr; i++)
    {
        //controllo se la fermata di partenza della tratta è uguale a quella data in input
        if (strcmp (fermata, vet[i].partenza) == 0)
        {
            printf ("%s\n", vet[i].codice);
        }
    }
}

void capolinea (int nr, struttura vet[], char fermata[30])
{
    int i = 0;

    //sempre ciclo sulla matrice
    for (i = 0; i < nr; i++)
    {
        //controllo se la fermata di arrivo della tratta è uguale a quella data in input
        if (strcmp (fermata, vet[i].destinazione) == 0)
        {
            printf ("%s\n", vet[i].codice);
        }
    }
}

void corsa_ritardo (int nr, struttura vet[], char data1[], char data2[])
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
        if (strcmp (vet[i].data, dataMin) >= 0 && strcmp (vet[i].data, dataMax) <= 0 && vet[i].ritardo > 0)
        {
            printf ("%s\n", vet[i].codice);
        }
    }
}

void ritardo_complessivo (int nr, struttura vet[], char tratta[30])
{
    int somma = 0, i = 0;

    for (i = 0; i < nr; i++)
    {
        //controllo se il codice tratta è quello dato in input oppure no
        if (strcmp (vet[i].codice, tratta) == 0)
        {
            //se lo è somma i ritardi
            somma = somma + vet[i].ritardo;
        }
    }

    //printa il ritardo complessivo
    printf ("Ritardo complessivo della tratta %s: %d minuti\n", tratta, somma);
}