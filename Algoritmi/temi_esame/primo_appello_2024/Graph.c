#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <string.h>
#include "Graph.h"

#define MAXC 11
#define maxWT INT_MAX

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; int *pesi; } ;

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

//Nuove funzioni
//L'adt graph ha un vettore pesi che mi associa ad ogni vertice il suo peso
//Il valore wt nella lista di adicenza non viene mai usato perche gli archi sono non pesati

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2, wt, E, index, val;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d %d", &V, &E);
  G = GRAPHinit(V);
  G->E = E;

  //Leggo il file per come viene richiesto e aggiungo i pesi ai vari vertici e metto tutto nella symbol tabel
  //Che tanto è una matrice (quindi anche se i nomi si ripetono in più indici funziona)
  for (i=0; i<V; i++) {
    fscanf(fin, "%d %s %d", &index, label1, &val);
    G->pesi[index] = val;
    STinsert(G->tab, label1, i);
  }

  //Leggo direttamente i valori (che sono già interi, non serve passare per la st)
  while(fscanf(fin, "%d %d", &id1, &id2) == 2) {
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2, 0);
  }
  return G;
}

int check_StringR (Graph g, char *str, int prev){

  if (*str == '\0'){
    return 1;
  }

  int i;
  char nome[MAXC];
  link t;
  for (t = g->ladj[prev]; t != g->z; t = t->next){
    strcpy (nome, STsearchByIndex (g->tab,t->v));
    if (strstr (str, nome) == &str[0]){
      int result = check_StringR (g, str+strlen(nome), t->v);
      if (result){
        return result;
      }
    }
  }
  return 0;
}

void checkString (Graph g, char *str){
  int result = 0;
  for (int i = 0; i < g->V && !result; i++){
    if (strstr (str, STsearchByIndex (g->tab, i)) == &str[0]){
      result = check_StringR (g, str+strlen (STsearchByIndex(g->tab, i)), i);
    }
  }
}

int checkR (Graph g, int prev, int new, int *max_parole, int M, ST st){
  char nome_prev[MAXC], nome_new[MAXC];
  strcpy (nome_prev, STsearchByIndex (g->tab, prev));
  strcpy (nome_new, STsearchByIndex (g->tab, new));

  if (max_parole[STsearch (st, nome_new)] + 1 > M){
    return 0;
  }

  char vocali [5] = {'a', 'e', 'i', 'o', 'u'};
  int id1 = 0, id2 = 0;
  for (int i = 0; i < 5; i++){
    if (nome_prev[strlen(nome_prev)-1] == vocali[i]){
      id1 = 1;
    }
    if (nome_new[0] == vocali[i]){
      id2 = 1;
    }
  }
  if (id1 == id2){
    return 0;
  }
  return 1;
}

void funR (Graph g, int pos, int *sol, int *best_sol, int *max, int cur, int prev, int *max_parole, int M, ST st){

  if (cur > *max){
    int k;
    for (k = 0; k < pos; k++){
      best_sol[k] = sol[k];
    }
    for (int j = k; j < g->V; j++){
      best_sol[k] = -1;
    }
    *max = cur;
  }

  if (pos >= g->V){
    return;
  }

  link t;
  for (t = g->ladj[prev]; t != g->z; t = t->next){
    if (checkR (g, prev, t->v, max_parole, M, st)){
      max_parole[STsearch(st, STsearchByIndex(g->tab, t->v))]++;
      sol[pos] = t->v;
      cur += g->pesi[t->v];

      funR (g, pos+1, sol, best_sol, max, cur, t->v, max_parole, M, st);

      max_parole[STsearch(st, STsearchByIndex(g->tab, t->v))]--;
      cur -= g->pesi[t->v];
    }
  }

}

void bestPath (Graph g, int M){
  //Faccio un set dei nomi e alloco un vettore con calloc e ovviamente faccio un'altra symbol table
  int *max_parole;
  ST st;
  int *sol, *best_sol;
  int max = 0;

  for (int i = 0; i < g->V; i++){
    sol[0] = i;
    max_parole[STsearch(st, STsearchByIndex(g->tab, i))]++;

    funR (g, 1, sol, best_sol, &max, g->pesi[i], i, max_parole, M, st);
  }

  int j = 0;

  while (best_sol[j] != -1){
    printf ("%s", STsearchByIndex(g->tab, best_sol[j]));
  }
  return;
}