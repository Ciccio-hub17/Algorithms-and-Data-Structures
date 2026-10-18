#ifndef GRAPH_H
#define GRAPH_H

#include "Item.h"

typedef struct graph *Graph;

// Gestione Grafo
Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
void GRAPHinsertNode(Graph G, Item content);
void GRAPHinsertEdge(Graph G, int id1, int id2);

// Funzione di Verifica
int relationshipK(Graph G, char *name1, Date d1, char *name2, Date d2, int k);

//Funzione di ricerca e ottimizzazione
void largestLineageK(Graph G, int k);

#endif