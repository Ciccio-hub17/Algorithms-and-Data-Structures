#include<stdio.h>
#include<stdlib.h>

#include "UF.h"
#include "ST.h"

typedef struct graph *Graph;
typedef struct sol_s *SOL;

struct graph { int V; int E; ST tab; int **madj;};

struct sol_s {
    int *vet;
    int n;
};

void graphLoad (Graph g){
    //graph init
    FILE *f;
    if ((f = fopen("g.txt", "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", "g.txt");
        exit(-1);
    }
    fscanf (f, "%d", &g->V);

    int v, w;
    while (fscanf (f, "%d %d", &v, &w) == 2){
        g->madj[v][w] = 1;
    }

    fclose(f);
}

//Ogni riga del file proposta.txt contiene 2 interi separati da spazio:
//Numero del vertice numero/ della partizione di riferimento

int check (SOL sol, Graph g){

    //Sol init (vet tutto a -1)

    FILE *f;
    if ((f = fopen("proposta.txt", "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", "proposta.txt");
        exit(-1);
    }
    int v, part, max = -1;
    while (fscanf (f, "%d %d", &v, &part) == 2){
        if (sol->vet[v] != -1){
            return 0;
        }
        sol->vet[v] = part;
    }
    for (int i = 0; i < g->V; i++){
        if (sol->vet[i] > max){
            max = sol->vet[i];
        }
    }
    sol->n = max+1;

    int v, flag;
    int *vet_part, len = 0;
    for (int k = 0; k < sol->n; k++){
        len = 0;
        for (int i = 0; i < g->V; i++){
            if (sol->vet[i] == k){
                vet_part[len++] = i;
            }
        }
        int *visited = calloc(sol->n, sizeof(int)); visited[k] = 1;
        for (v = 0; v < g->V; v++){
            if (sol->vet[v] != k && visited[sol->vet[v]] == 0){
                visited[sol->vet[v]] = 1;
                flag = 0;
                for (int j = 0; j < len && !flag; j++){
                    if (g->madj[v][vet_part[j]] == 1){
                        flag = 1;
                    }
                }
                if (!flag){
                    return 0;
                }
            }
        }
        free (visited);
    }
    fclose(f);

    return 1;
}

int checkR (Graph g, SOL sol, int n_part, int *max){
    if (n_part < *max){
        return 0;
    }

    int v, flag;
    int *vet_part, len = 0;
    for (int k = 0; k < n_part; k++){
        len = 0;
        for (int i = 0; i < g->V; i++){
            if (sol->vet[i] == k){
                vet_part[len++] = i;
            }
        }
        for (v = 0; v < g->V; v++){
            if (sol->vet[v] != k){
                flag = 0;
                for (int j = 0; j < len && !flag; j++){
                    if (g->madj[v][vet_part[j]] == 1){
                        flag = 1;
                    }
                }
                if (!flag){
                    return 0;
                }
            }
        }
    }

    return 1;
}

void funR (SOL sol, int pos, Graph g, int m, int *max){

    if (pos >= g->V){
        if (checkR(g, sol, m, max)){
            *max = m;
        }
        return;
    }

    int i;
    for (i = 0; i < m-1; i++){

        sol->vet[pos] = i;

        funR (sol, pos+1, g, m, max);
    }

    sol->vet[pos] = m;
    funR (sol, pos+1, g, m+1, max);
}

int main(int argc, char* argv[]){

    printf("\n");
    return 0;
}