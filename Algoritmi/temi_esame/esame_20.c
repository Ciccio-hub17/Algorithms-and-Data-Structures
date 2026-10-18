#include<stdio.h>
#include <string.h>
//#include <UF.h>

typedef struct edge_s{
    int v;
    int w;
    int wt;
}edge;

typedef struct grafo_s{
    int V;
    int E;
    int **madj;
}grafo_t;

grafo_t* init (int V){
    grafo_t* G;
    G->V = V;
    G->E = 0;
    G->madj = malloc (V*sizeof(int*));
    for (int i = 0; i < V; i++){
        G->madj[i] = malloc (V*sizeof (int));
        for (int j = 0; j < V; j++){
            G->madj[i][j] = -1;
        }
    }
    return G;
}

grafo_t* read_file (edge* edges){
    FILE *input;
    if ((input = fopen("grafo.txt", "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", "grafo.txt");
        exit(-1);
    }
    
    int V;
    fscanf (input, "%d", &V);
    grafo_t* G = init (V);

    int u, v, wt;
    while (fscanf (input, "%d %d %d", &u, &v, &wt) == 3){
        G->madj[u][v] = wt;
        G->madj[v][u] = wt;
        edges[G->E].v = u; edges[G->E].w = v; edges[G->E].wt = wt;
        G->E++;
    }
    fclose(input);
    return G;
}

/*suppongo che la soluzione contenga archi esistenti*/

/*I contenuti del file della proposta della soluzione sono i seguenti:
Prima riga: il k che mi da il problema
E righe successive : archi della forma (u, v) con accanto un intero che dice a quale partizione appartiene quell'arco (le partizioni vanno da 0 a E-1)*/

int check (grafo_t* G, int k, edge *edges, int *sol, int n){

    int *count = calloc (k, sizeof (int));
    int *vertex_found = calloc (G->V*sizeof(int));

    for (int i = 0; i < G->E; i++){
        if (vertex_found[edges[sol[i]].v] == 1 && vertex_found[edges[sol[i]].w] == 1){
            free (count);
            free (vertex_found);
            return 0;
        }
        else{
            vertex_found[edges[sol[i]].v] = 1;
            vertex_found[edges[sol[i]].w] = 1;
        }
        count[sol[i]]++;
    }
    
    for (int i = 0; i < G->E; i++){
        //UF uf = UFinit (numero di vertici partizione i);
        for (int j = 0; j < sol[i]; j++){
            //UFunion (uf, sol[i].v, sol[i].w)
        }
        for (int j = 1; j < /*numero di vertici partizione i*/n; j++){
            //if (uf[0] != uf[i]){  free (count) free (vertex_found) return 0;}
        }
    }

    for (int i = 0; i < G->E; i++){
        if (count[i] < k || vertex_found[i] == 0){
            free (count);
            free (vertex_found);
            return 0;
        }
    }

    
    free (count);
    free (vertex_found);
    return 1;
}

void rec_fun (int *sol, int pos, int k, int *best_sol, edge *edges, grafo_t* G, int curr_val, int *min, int n){
    int i;

    if (curr_val >= *min){
        return;
    }

    if (pos >= G->E){
        if (curr_val < *min){
            if (check (G, k, edges, sol, n)){
                for (i = 0; i < G->E; i++){
                    best_sol[i] = sol[i];
                }
                *min = curr_val;
            }
        }
        return;
    }

    for (i = 0; i < n; i++){
        sol[pos] = i;
        curr_val += edges[sol[pos]].wt;

        rec_fun (sol, pos+1, k, best_sol, edges, G, curr_val, min, n);

        curr_val -= edges[sol[pos]].wt;
    }
    return;
}