#include <stdio.h>
#include "ACT.h"
#include "ST.h"
#define MAXC 20

typedef struct node *link;

typedef struct activity_s {
    int inizio;
    int fine;
    int costo;
}activity;

struct node{
    activity att;
    int index;
    link next;
};

struct activities {
    activity *vet;
    link *ladj;
    ST st;
    int N;
};

void quicksort (ACT a);

int dfs (ACT a, int v, int result, int *visited){
    link t;
    visited[v] = 1;

    for (t = a->ladj[v]; t != NULL; t = t->next){
        if (a->vet[v].inizio < a->vet[t->index].fine){
            return 0;
        }
        int result = dfs (a, t->index, result, visited);
        if (result == 0){
            return result;
        }
    }
    
    return 1;
}

int ACTcheckDep (ACT a){
    int *visited; //Calloc

    visited [0] = 1;

    int result = dfs (a, 0, 1, visited);
    int i = 1;
    for (i = 1; i < a->N; i++){
        if (visited[i] == 0){
            result = dfs (a, i, 1, visited);
        }
        if (!result){
            break;
        }
    }
    if (!result){
        return 0;
    }
    return 1;
}

int dfsDAG (ACT a, int v, int result, int *pre, int *post, int *time){
    link t;
    if (pre[v] == -1){
        (*time)++;
        pre[v] = *time;
    }
    for (t = a->ladj[v]; t != NULL; t = t->next){
        if (pre[v] > pre[t->index] && post[v]  == -1){
            return 0;
        }
        int result = dfsDAG (a, t->index, result, pre, post, time);
        if (result == 0){
            return 0;
        }
    }

    (*time)++;
    post[v] = *time;
}

void ACTprintSrcsnk (ACT a){
    int *pre;
    int *post, time = -1;
    int sorgente;

    int result = dfsDAG (a, 0, 1, pre, post, &time);

    int i = 1;
    for (i = 1; i < a->N; i++){
        if (pre[i] == 0){
            result = dfsDAG (a, i, 1, pre, post, &time);
        }
        if (!result){
            break;
        }
    }

    int i, *entranti;

    if (result){
        printf ("Il grafo è un DAG\n");
    }
    else{
        printf ("Il grafo è un albero o una foresta di alberi\n");
    }
    printf ("Nodi pozzo:\n");
    for (i = 0; i < a->N; i++){
        if (a->ladj[i] == NULL){
            printf ("%s\n", STsearchByIndex (a->st, i));
        }
        for (link t = a->ladj[i]; t != NULL; t = t->next){
            entranti[t->index] = 1;
        }
    }
    printf ("Sorgenti:\n");
    for (i = 0; i < a->N; i++){
        if (entranti[i] == 0){
            printf ("%s\n", STsearchByIndex (a->st, i));
        }
    }

    return;
}

int calculate (ACT a, int *assegnazioni, int *costi, int *min, int m){
    int somma = 0;
    for (int i = 0; i < m; i++){
        somma += costi[i];
    }
    float media = somma/m;
    int sommai;
    float minimo;
    float sbilanciamento = 0;

    for (int i = 0; i < m; i++){
        // costi[i] contiene GIÀ la somma dei costi per la persona i
        sbilanciamento += fabs(costi[i] - media); // Usa fabs per i float o abs per int
    }
    if (minimo > *min){
        return 0;
    }
    return minimo;
}

int ACTminPers (ACT a){
    int sovr = 0;
    quicksort (a);
    for (int i = 0; i < a->N; i++){
        int j = 0, flag = 0;
        while (j < i && !flag){
            if (a->vet[j].inizio < a->vet[j].fine){
                flag = 1;
            }
        }
        if (flag){
            sovr++;
        }
    }
    return sovr;
}

void ACTbestPlanR (ACT a, int *assegnazioni, int *costi, int pos, int *min, int m, int *best_assegnazioni){

    if (pos >= a->N){
        int minimo;
        if (minimo = calculate (a, assegnazioni, costi, min, m)){
            for (int i = 0; i < a->N; i++){
                best_assegnazioni[i] = assegnazioni[i];
            }
            *min = minimo;
        }
        return;
    }
    int i;

    for (i = 0; i < m; i++){
        assegnazioni[pos] = i;
        costi[i] += a->vet[pos].costo;

        ACTbestPlanR (a, assegnazioni, costi, pos+1, min, m, best_assegnazioni);

        costi[i] -= a->vet[pos].costo;
    }
    return;
}

int ACTminPers (ACT a){
    //DFS che calcola il numero di sovrapposizioni\n
    int m;
    return m;
}

void ACTbestPlan (ACT a){
    int *costi, *assegnazioni, min = 0, *best_assegnazioni;

    int m = ACTminPers (a);
    ACTbestPlanR (a, assegnazioni, costi, 0, min, m, best_assegnazioni);
}