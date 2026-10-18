#include<stdio.h>
#include<stdlib.h>
#include "titolo.h"
#include "info_tempo.h"

#define MAX_S 21
#define DATA_DIM 11

typedef enum {acquisizione_da_file, 
    ricerca_titolo, 
    ricerca_quotazione_titolo_data, 
    ricerca_quot_min_max, 
    ricerca_quot_min_max_tot, 
    bilanciamento, fine
}possibili_scelte;

//Menu per scegliere l'opzione desiderata
void menu (){
    int flag = 1;
    int scelta;
    int soglia;
    char filename [MAX_S], codice[MAX_S];
    data_t data_utente, data1, data2;

    Lista_titoli titoli = titoli_init ();

    while (flag){
        printf ("MENU TITOLI AZIONARI\nScegliere una di queste opzioni\n\n");
        printf ("0: Acquisire le info da un file di log dato in input\n");
        printf ("1: Ricercare un titolo\n");
        printf ("2: Ricerca di una quotazione di determinato titolo in una determinata data\n");
        printf ("3: Ricerca quotazione massima e minima in un periodo di tempo\n");
        printf ("4: Ricerca quotazione massima e minima in tutto il periodo considerato\n");
        printf ("5: Bilanciamento del BST delle quotazioni\n");
        printf ("6: Termina l'esecuzione\n");
        scanf ("%d", &scelta);
        switch (scelta){
            case acquisizione_da_file:
                printf ("Dammi il nome del file \n");
                scanf ("%s", filename);
                getchar ();
                leggi_file (titoli, filename);
                break;
            case ricerca_titolo:
                printf ("Dammi il titolo azionario da cercare\n");
                scanf ("%s", codice);
                getchar ();
            
                SearchTitolo (titoli, codice);
                break;
            case ricerca_quotazione_titolo_data:
                printf ("Dammi il titolo azionario da cercare\n");
                scanf ("%s", codice);
                
                getchar ();
                printf ("Inserisci la data: Giorno (GG), Mese (MM), ANNO(AAAA), separati da spazi\n");
                scanf ("%d %d %d", &data_utente.giorno, &data_utente.mese, &data_utente.anno);
                while (!valid_date (data_utente)){
                    printf ("Errato, riprovare\n");
                    scanf ("%d %d %d", &data_utente.giorno, &data_utente.mese, &data_utente.anno);
                }
                getchar ();
                SearchTitoloData (titoli, data_utente, codice);
                break;
            case ricerca_quot_min_max:
                printf ("Dammi il titolo azionario da cercare\n");
                scanf ("%s", codice);
                getchar ();
                printf ("Inserisci la prima data: Giorno (GG), Mese (MM), ANNO(AAAA), separati da spazi\n");
                scanf ("%d %d %d", &data1.giorno, &data1.mese, &data1.anno);
                while (!valid_date (data1)){
                    printf ("Errato, riprovare\n");
                    scanf ("%d %d %d", &data1.giorno, &data1.mese, &data1.anno);
                }
                printf ("Inserisci la seconda data: Giorno (GG), Mese (MM), ANNO(AAAA), separati da spazi\n");
                scanf ("%d %d %d", &data2.giorno, &data2.mese, &data2.anno);
                while (!valid_date (data2)){
                    printf ("Errato, riprovare\n");
                    scanf ("%d %d %d", &data2.giorno, &data2.mese, &data2.anno);
                }
                if (cmpData (data1, data2) < 0){
                    swapData (&data1, &data2);
                }
                SearchTitoloData1Data2 (titoli, data1, data2, codice);
                break;
            case ricerca_quot_min_max_tot:
                printf ("Dammi il titolo azionario da cercare\n");
                scanf ("%s", codice);
                
                SearchTitoloMaxMin (titoli, codice);
                break;
            case bilanciamento:
                printf ("Dammi la soglia\n");
                scanf ("%d", &soglia);
                printf ("Dammi il titolo azionario da cercare\n");
                scanf ("%s", codice);
                
                bilanciamentoTitolo (titoli, codice, soglia);
                break;
            case fine:
                flag = 0;
                break;
            default:
                printf ("Opzione errata\n");
                break;
        }

    }
    freeTitoli (titoli);
}

//Interfaaccia
int main(int argc, char* argv[]){

    menu ();
    
    printf("\n");
    return 0;
}