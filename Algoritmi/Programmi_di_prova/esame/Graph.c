#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"
#include "ST.h"
#include "Queue.h"

typedef struct node *link;
struct node { int v; link next; };

struct graph {
    int V;
    int E;
    link *ladj;
    ST st;
};

link NEW(int v, link next) {
    link x = malloc(sizeof(*x));
    x->v = v; x->next = next;
    return x;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof(*G));
    G->V = V;
    G->E = 0;
    G->ladj = calloc(V, sizeof(link));
    G->st = STinit(V);
    return G;
}

void GRAPHfree(Graph G) {
    for (int i = 0; i < G->V; i++) {
        link t = G->ladj[i], next;
        while (t) { next = t->next; free(t); t = next; }
    }
    free(G->ladj);
    STfree(G->st);
    free(G);
}

void GRAPHinsertNode(Graph G, Item content) {
    STinsert(G->st, content);
}

void GRAPHinsertEdge(Graph G, int id1, int id2) {
    G->ladj[id1] = NEW(id2, G->ladj[id1]);
    G->E++;
}

// Ritorna un array 'dist' di dimensione V.
// dist[i] = distanza minima da 'start' a 'i'.
// dist[i] = -1 se non raggiungibile.
int* bfs(Graph G, int start) {
    int *dist = malloc(G->V * sizeof(int));
    for (int i = 0; i < G->V; i++) dist[i] = -1;

    Q q = Qinit();
    Qput(q, start);
    dist[start] = 0; // Distanza da se stesso è 0

    while (!Qempty(q)) {
        int u = Qget(q);
        // Esplora adiacenti
        for (link t = G->ladj[u]; t != NULL; t = t->next) {
            int v = t->v;
            if (dist[v] == -1) { // Se non ancora visitato
                dist[v] = dist[u] + 1; // La distanza è padre + 1
                Qput(q, v);
            }
        }
    }
    Qfree(q);
    return dist;
}


int relationshipK(Graph G, char *name1, Date d1, char *name2, Date d2, int k) {
    // Creo item temporanei solo cercare 
    Item tmp1 = {name1, d1, {0,0,0}};
    Item tmp2 = {name2, d2, {0,0,0}};
    
    int id1 = STsearch(G->st, tmp1);
    int id2 = STsearch(G->st, tmp2);

    if (id1 == -1 || id2 == -1) return 0; // Uno dei due non esiste

    //Se Uno discende dall'altro
    int *distFrom1 = bfs(G, id1);
    if (distFrom1[id2] != -1 && distFrom1[id2] <= k) {
        free(distFrom1);
        return 1; // Trovato id2 discendente di id1
    }

    int *distFrom2 = bfs(G, id2);
    if (distFrom2[id1] != -1 && distFrom2[id1] <= k) {
        free(distFrom1);
        free(distFrom2);
        return 1; // Trovato id1 discendente di id2
    }

    // Caso Antenato Comune
    // Cerco un nodo 'a' che possa raggiungere entrambi con somma distanze <= k
    int found = 0;
    int maxV = STcount(G->st);
    
    for (int a = 0; a < maxV; a++) {
        
        // BFS dall'antenato 'a'
        int *distFromA = bfs(G, a);
        
        int d1_val = distFromA[id1];
        int d2_val = distFromA[id2];

        // Se 'a' è antenato di entrambi
        if (d1_val != -1 && d2_val != -1) {
            if ((d1_val + d2_val) <= k) {
                found = 1;
            }
        }
        free(distFromA);
        if (found) break;
    }

    free(distFrom1);
    free(distFrom2);
    return found;
}

void largestLineageK(Graph G, int k) {
    int maxNodes = -1;
    int bestId = -1;
    int maxV = STcount(G->st);

    // Itero su ogni possibile antenato
    for (int i = 0; i < maxV; i++) {
        int *dists = bfs(G, i);
        int count = 0;

        // Conto quanti nodi hanno 0 < dist <= k
        for (int j = 0; j < maxV; j++) {
            if (dists[j] > 0 && dists[j] <= k) {
                count++;
            }
        }

        if (count > maxNodes) {
            maxNodes = count;
            bestId = i;
        }
        free(dists);
    }

    if (bestId != -1) {
        Item best = STItem(G->st, bestId);
        printf("Persona con piu' discendenti (grado <= %d): %s -> %d discendenti\n", 
               k, best.nome, maxNodes);
    } else {
        printf("Nessuna discendenza trovata.\n");
    }
}