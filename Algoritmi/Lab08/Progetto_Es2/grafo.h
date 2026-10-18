#ifndef GRAFO_H
#define GRAFO_H

typedef struct grafo_s *Graph;

void GFree (Graph G); //Libera la memoria occupata da tutto il grafo
Graph read_file (char filename[]);  //Legge il file inizalizzando contemporaneamente il grafo
void print_order (Graph G); //Printa tutti i vertici e i suoi relativi archi in ordine alfabetico
void genera_lista(Graph G); //genera la lista d adiacenza a partire dalla matrice di adiacenza
void search_sotto_grafo_lista (Graph G, char label1[], char label2[], char label3[]); //vede se 3 vertici formano un sottografo usando la lista di adiacenza
void search_sotto_grafo_mat (Graph G, char label1[], char label2[], char label3[]); //vede se 3 vertici formano un sottografo usando la matrice di adiacenza

#endif