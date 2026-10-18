#ifndef QUOTAZIONE_H
#define QUOTAZIONE_H
#include "info_tempo.h"

typedef struct quotazione_s {
    data_t data;
    float quotazione;
}quotazione_t;  //Nodo del BST

typedef struct BSTWrapper *BST; //Puntatore ad un wrapper che mi gestisce un BST (ADT I classe)

BST BSTinit (); //Inizializza il wrapper del BST
void InsertInBST (BST bst, quotazione_t val);   //Crea un nodo e lo inserisce in folgia
void BSTPrint (BST bst);    //stampa il BST (tecnica in order)
void BSTFree (BST bst); //Libera la memoria occupata dal BST
void SearchData (BST bst, data_t data_da_cercare);  //funzione di ricerca in BST
void SearchQuot_max_min_date (BST bst, data_t data1, data_t data2); //Cerca l'item minimo e massimo in uun intervallo di chiavi
data_t searchMin (BST bst); //Cerca la chiave minima
data_t searchMax (BST bst);//Cerca la chiave massima
int prof_min (BST bst); //Calcola la profondità minima
int prof_max (BST bst); //calcola la profondità massima
void BSTbalance(BST bst);   //Bilancia a richiesta

#endif