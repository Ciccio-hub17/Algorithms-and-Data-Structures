#ifndef GRAPH_H
#define GRAPH_H

#include "UF.h"
#include "ST.h"
#include "CC.h"

typedef struct edge { int v; int w; int wt; int enabled;} Edge;

typedef struct graph *Graph;

typedef struct comp* CC;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
void  GRAPHshowList(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHstore(Graph G, FILE *fout);
void  GRAPHedges(Graph G, Edge *a);
void  GRAPHmstK(Graph G);

void GRAPHedgeDisable (Graph g, Edge e);
void GRAPHedgeEnable (Graph g, Edge e);
void dfsCC (Graph g, CC comp);

#endif
