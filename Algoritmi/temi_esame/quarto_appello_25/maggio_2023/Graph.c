#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "Graph.h"

#define MAXC 11
#define maxWT INT_MAX

typedef struct sol_s *SOL;

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; int **madj; ST tab; link z; } ;

struct triangle {
  int u;
  int v;
  int w;
};

struct triangle_packing{
  struct triangle *vet;
  int N;
  int K;
};

struct sol_s{
  int N;
  int *vet;
  int *best_sol;
  int best_k;
};

TRIANGLE TRIANGLEInit (int V, int K);
void copy_sol (SOL sol);

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

Graph graphRead (){
  FILE *f = fopen ("grafo.txt", "r");
  int V;
  fscanf (f, "%d", &V);
  Graph g = GRAPHinit (V);
  int u, v;
  while (fscanf (f, "%d %d", &u, &v) == 2){
    g->madj[u][v] = 1;
    g->madj[v][u] = 1;
  }

  fclose (f);
  return g;
}

/*il file della proposta contiene k righe
Ogni riga è del tipo
3 vertici di appartenenza (le componenti sono ordinate)
Sulla prima riga è presente il numero di sottoinsiemi di vertici (k)
Devo quindi controllare che i sottoinsiemi siano disgiunti per vertici*/

int check (Graph g){
  FILE *f = fopen ("proposta.txt", "r");
  int K;
  fscanf (f, "%d", &K);

  TRIANGLE tri = TRIANGLEInit (g->V, K);
  int *visited;

  int u, v, w, k;
  for (int i = 0; i < K; i++){
    fscanf (f, "%d %d %d", &u, &v, &w);
    if (visited[u] == 1 || visited[v] == 1 || visited[w] == 1){
      return 0;
    }
    visited[u] = 1; visited[v] = 1; visited[w] = 1;
    tri->vet[i].u = u;
    tri->vet[i].v = v;
    tri->vet[i].w = w;
  }

  for (int i = 0; i < tri->K; i++){
    if (g->madj[tri->vet[i].u][tri->vet[i].v] == 0 || g->madj[tri->vet[i].u][tri->vet[i].w] == 0 || g->madj[tri->vet[i].v][tri->vet[i].w] == 0){
      return 0;
    }
  }

  fclose (f);
  return 1;
}

int pruning (SOL sol, int **madj, int i, int pos){
  for (int k = 0; k < sol->N; k++){
    if (sol->vet[k] == i){
      if (madj[pos][k] == 0){
        return 0;
      }
    }
  }

  return 1;
}

int checkR (int *count, int k, int pos, Graph g){
  for (int i = 0; i < k; i++){
    if (count[i] != 3){
      return 0;
    }
  }
  return 1;
}

void funR (int pos, SOL sol, int k, int *flag, Graph g, int *count){

  if (*flag){
    return;
  }

  if (checkR (count, k, pos, g)){
    copy_sol (sol);
    sol->best_k = k;
    *flag = 1;
    return;
  }

  if (pos >= g->V){
    return;
  }

  for (int i = 0; i < k; i++){
    sol->vet[pos] = i;

    if (count[i] + 1 <= 3){
      count[i]++;
      if (pruning (sol, g->madj, i, pos)){
        funR (pos+1, sol, k, flag, g, count);
      }
      count[i]--;
    }
  }


  sol->vet[pos] = -1;
  funR (pos+1, sol, k, flag, g, count)
}

void wrapper (Graph g){
  int flag = 0;
  int *mark;
  SOL sol;
  //SOL init

  int k_max = g->V/3;

  for (int i = k_max; i >= 1; i--){
    if (flag){
      break;
    }
  }

  return;
}
