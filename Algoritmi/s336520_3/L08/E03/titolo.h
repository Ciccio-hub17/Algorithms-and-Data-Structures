#ifndef TITOLO_H
#define TITOLO_H
#include "titolo.h"
#include "quotazione.h"
#include "info_tempo.h"

typedef struct titolo_s *Info_titolo;   //ADT I classe per il singolo titolo
typedef struct wrapperLista_s *Lista_titoli;    //ADT I classe per la collezione di titoli

Lista_titoli titoli_init ();    //Inizializza la lista di titoli
void leggi_file (Lista_titoli titoli, char filename[]); //Legge da file i titoli azionari e inizializza anche tutti i BST
void freeTitoli (Lista_titoli titoli);  //Libera la lista e anche i BST interni ad ogni titolo
void SearchTitolo (Lista_titoli titoli, char codice[]); //Cerca nella lista un titolo
void SearchTitoloData (Lista_titoli titoli, data_t data, char nome[]);  //Cerca la quotazione giornaliera di un titolo azionario
void SearchTitoloData1Data2 (Lista_titoli titoli, data_t data1, data_t data2, char nome[]); //Cerca tutte le quotazioni giornaliere di un titolo tra due date distinte date in input
void SearchTitoloMaxMin (Lista_titoli titoli, char nome[]); //Cerca tutte le quotazioni giornaliere in tutto il periodo considerato
void bilanciamentoTitolo (Lista_titoli titoli, char codice[], int soglia);  //Bilancia l'albero se il rapporto tra max e min supera la soglia

#endif