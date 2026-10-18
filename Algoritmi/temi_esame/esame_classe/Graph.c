#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"
#include "CC.h"
#include "UF.h"

#define MAXC 11
#define maxWT INT_MAX

typedef struct node *link;
struct node { int v; int wt; int enabled; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

struct comp {
    int N;
    int *vet;
    //La riga è la componente connessa e le colonne sono i vertici di appartenenza
};

static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static void  insertE(Graph G, Edge e);
static void  sort(Edge *a, int l, int r );
static int   mstE(Graph G, Edge *mst, Edge *a);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static link NEW(int v, int wt, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->v = v;
  x->wt = wt;
  x->next = next;
  return x;
}

Graph GRAPHinit(int V) {
  int v;
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;

  G->V = V;
  G->E = 0;
  G->z = NEW(-1, 0, NULL);
  if (G->z == NULL)
    return NULL;
  G->ladj = malloc(G->V*sizeof(link));
  if (G->ladj == NULL)
    return NULL;
  for (v = 0; v < G->V; v++)
    G->ladj[v] = G->z;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int v;
  link t, next;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = next) {
      next = t->next;
      free(t);
    }
  STfree(G->tab);
  free(G->ladj);
  free(G->z);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2, wt;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2, wt);
  }
  return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

void  GRAPHshowList(Graph G) {
  int v;
  link t, next;

  for (v=0; v < G->V; v++) {
    printf("%d ", v);
    for (t=G->ladj[v]; t != G->z; t = next) {
      next = t->next;
      printf("-> %d/%d ", t->v, t->wt);
    }
    printf("\n");
  }
}

void GRAPHstore(Graph G, FILE *fout) {
  int i;
  Edge *a;

  a = malloc(G->E * sizeof(Edge));
  if (a == NULL)
    return;

  GRAPHedges(G, a);

  fprintf(fout, "%d\n", G->V);
  for (i = 0; i < G->V; i++)
    fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  G->ladj[v] = NEW(w, wt, G->ladj[v]);
  G->ladj[w] = NEW(v, wt, G->ladj[w]);
  G->E++;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, E = 0;
  link t;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = t->next)
      if (v < t->v)
        a[E++] = EDGEcreate(v, t->v, t->wt);
}

static void sort(Edge *a, int l, int r ) {
  int i, j, min, temp;
  for(i = l; i < r; i++) {
    min = i;
    for (j = i+1; j <= r; j++)
	  if (a[j].wt < a[min].wt)
        min = j;

    temp = a[i].v;
    a[i].v = a[min].v;
    a[min].v = temp;

    temp = a[i].w;
    a[i].w = a[min].w;
    a[min].w = temp;

    temp = a[i].wt;
    a[i].wt = a[min].wt;
    a[min].wt = temp;
  }
  return;
}

static int mstE(Graph G, Edge *mst, Edge *a) {
  int i, k;

  GRAPHedges(G, a);

  sort(a, 0, G->E-1);

  UFinit(G->V);

  for ( i=0, k=0; i < G->E && k < G->V-1; i++ )
    if (!UFfind(a[i].v, a[i].w)) {
      UFunion(a[i].v, a[i].w);
      mst[k++] = a[i];
    }
  UFfree();
  return k;
}

void GRAPHmstK(Graph G) {
  int i, k, weight = 0;
  Edge *mst, *a;

  mst = malloc((G->V-1) * sizeof(Edge));
  a = malloc(G->E * sizeof(Edge));
  if ((a == NULL) || (mst == NULL))
    return;

  k = mstE(G, mst, a);

  printf("\nEdges in the MST: \n");

  for (i=0; i < k; i++) {
    printf("(%s - %s) \n", STsearchByIndex(G->tab, mst[i].v), STsearchByIndex(G->tab, mst[i].w));
    weight += mst[i].wt;
  }
  printf("minimum weight: %d\n", weight);
}


void GRAPHedgeDisable (Graph g, Edge e){
  link t;
  for (t = e.v; t->v != e.w; t = t->next);
  if (t == g->z) return;
  t->enabled = 0;
}

void GRAPHedgeEnable (Graph g, Edge e){
  link t;
  for (t = e.v; t->v != e.w; t = t->next);
  if (t == g->z) return;
  t->enabled = 1;
}

void dfsCC (Graph g, CC comp, int index, Edge arco){
    link t;
    for (t = g->ladj[arco.w]; t != g->z; t = t->next){
      if (arco.enabled == 1){
        comp->vet[t->v] = index;
        dfsCC (g, comp, index, EDGEcreate(arco.w, t->v, t->wt));
      }
    }

    return;
}

CC CCgen (Graph g){
    CC componenti;
    //CCinit;
    dfsCC (g, componenti, 0, EDGEcreate (0, 0, 0));

    int i = 1;
    int pos = 1;
    while (pos < g->V){
      if (componenti->vet[pos] == 0){
        dfsCC (g, componenti, i++, EDGEcreate (pos, pos, 0));
      }
      pos++;
    }

    return componenti;
}

int GraphcheckTreeEdges (Graph g, CC comp, Edge *ev, int en){
  link t;

  for (int i = 0; i < en; i++){
    for (t = g->ladj[ev[i].v]; t != g->z; t = t->next){
      if (t->v == ev[i].w){
        ev[i].enabled = 1;
      }
    }
  }

  CC comp_nuove = CCgen (g);
  if (comp_nuove->N == comp->N){
    return 1;
  }
  return 0;
}

//Si usano le combinazioni semplici
void funR (Graph g, int pos, Edge *sol, int *mark, int indice, CC comp, int start, Edge *a, int *archi, float *cmin, float *cmax, float min, float max, float *c_sum){

  if (pos >= g->V-comp->N){
    if (min < *cmin){
          *cmin = min;
        }
        if (max > *cmax){
          *cmax = max;
        }
    
    return;
  }

  for (int i = start; i < g->E; i++){
    if (mark[i] == 0){
      if (!UFfind (a[i].v, a[i].w)){
        UFunion (a[i].v, a[i].w);
        sol[pos] = a[i];
        archi[i] = indice;
        mark[i] = 1;
        *c_sum += a[i].wt;
        float c_min = min;
        float c_max = max;
        if (a[i].wt < c_min) {
          c_min = a[i].wt;
        }
        if (a[i].wt > c_max) {
          c_max = a[i].wt;
        }

        funR (g, pos+1, sol, mark, indice, comp, i+1, a, archi, cmin, cmax, c_min, c_max, c_sum);

        UFbacktrack ();
        archi[i] = -1;
        mark[i] = 0;
        *c_sum -= a[i].wt;
      }
    }
  }
}

Edge *GraphgenOptTrees (Graph g, CC comp){
  float cmax = 0, cmin = INT_MAX, cavg = 0;
  int *mark, *archi;
  Edge *sol, *a;
  GRAPHedges(g, a);
  //Chiamo l funzione per ogni componente connessa
  for (int i = 0; i < comp->N; i++){
    funR (g, 0, sol, mark, i, comp, 0, a, archi, &cmin, &cmax, 0, 0, &cavg);
  }
}