#include <stdio.h>
#include "ACT.h"
#include "ST.h"

typedef struct node *link;

struct node{
    int index;
    link next;
};

typedef struct activity_s {
    int start;
    int stop;
    int costo;
}act_sing;

struct attivita{
    act_sing *vet;
    ST st;
    int N;
    link *ladj;
};

struct sol_s{
    int *sol;
    int *best_sol;
    float min;
    int M;
};

void quick_sort (ACT a);

int dfs1 (ACT act, int prev, int result, int *visited){

    visited[prev] = 1;

    for (link t = act->ladj[prev]; t != NULL; t = t->next){
        if (act->vet[prev].start < act->vet[t->index].stop){
            return 0;
        }
        int result = dfs1 (act, t->index, result, visited);
        if (result == 0){
            return result;
        }
    }

    return 1;
}

int ACTCheckDep (ACT a){
    int *visited;

    for (int i = 0; i < a->N; i++){
        if (visited[i] == 0){
            if (!dfs1 (a, i, 1, visited)){
                return 0;
            }
        } 
    }

    return 1;

}

int checkDAG (ACT act, int *pre, int *post, int prev, int *time, int *in){
    if (pre[prev] == -1){
        (*time)++;
        pre[prev] = *time;
    }

    for (link t = act->ladj[prev]; t != NULL; t = t->next){
        if (pre[t->index] < pre[prev] && post[t->index] == -1){
            return 0;
        }
        int result = checkDAG (act, pre, post, t->index, time, in);
        if (result == 0){
            return 0;
        }
    }

    (*time)++;
    post[prev] = *time;

    return 1;
}

int ACTPrintSrcSnk (ACT a){
    int *pre;
    int *post;
    int *in;
    int time = -1;

    for (int i = 0; i < a->N; i++){
        if (pre[i] == -1){
            if (!checkDAG (a, pre, post, i, &time, in)){
                printf ("Il grafo non è nè un dag nè un albero/foresta di alberi\n");
                return 0;
            }
        }
    }

    for (int i = 0; i < a->N; i++){
        for (link t = a->ladj[i]; t != NULL; t++){
            in[t->index]++;
        }
    }

    int flag = 1;
    for (int i = 0; i < a->N && flag; i++){
        if (in[i] > 1){
            flag = 0;
        }
    }

    if (flag){
        printf ("Il grafo è un albero o una foresta di alberi\n");
    }
    else{
        printf ("Il grafo è un DAG\n");
    }

    printf ("Sorgenti:\n");
    for (int i = 0; i < a->N; i++){
        if (in[i] == 0){
            printf ("%s\n", STsearchByIndex (a->st, i));
        }
    }
    printf ("Foglie/Pozzi:\n");
    for (int i = 0; i < a->N; i++){
        if (a->ladj[i] == NULL){
            printf ("%s\n", STsearchByIndex (a->st, i));
        }
    }

}

int ACTminPers (ACT a){
    int sovr = 1;
    int max = 0;

    quick_sort (a);
    //Ordino per tempo di inizio

    for (int i = 1; i < a->N; i++){
        sovr = 1;
        for (int j = 0; j < i; j++){
            if (a->vet[i].start < a->vet[j].stop){
                sovr++;
            }
        }
        if (sovr > max){
            max = sovr;
        }
    }

    return max;
}

int is_possible (int pos, int part, ACT a, SOL sol){
    for (int k = 0; k < a->N; k++){
        if (sol->sol[k] == part){
            if (a->vet[pos].start < a->vet[k].stop && a->vet[pos].stop  > a->vet[k].start){
                return 0;
            }
        }
    }
    return 1;
}

void insert_backtrack (ACT a, int *costi, int parametro, int pos, int part){
    if (parametro == 0){
        costi[part] += a->vet[pos].costo;
    }
    else{
        costi[part] -= a->vet[pos].costo;
    }
    return;
}

int calculate (ACT a, SOL sol, int *costi){
    int somma = 0;
    for (int i = 0; i < sol->M; i++){
        somma += costi[i];
    }

    float media = somma /sol->M;

    float da_minimizzare = 0;

    for (int k = 0; k < sol->M; k++){
        da_minimizzare += abs (costi[k]-media);
    }

    if (da_minimizzare < sol->min){
        return da_minimizzare;
    }
    return 0;
}

void funR (int pos, SOL sol, int *costi, ACT a){

    if (pos >= a->N){
        int minimo;
        if (minimo = calculate (a, sol, costi) != 0){
            copy_sol ();
            sol->min = minimo;
        }
        return;
    }

    for (int i = 0; i < sol->M; i++){
        sol->sol[pos] = i;

        if (is_possible (pos, i, a, sol)){
            insert_backtrack (a, costi, 0, pos, i);

            funR (pos+1, sol, costi, a);

            insert_backtrack (a, costi, 1, pos, i);
        }

        sol->sol[pos] = -1;
    }

}

void ACTBestPlan (ACT a){
    int *costi;

    SOL sol;
    sol->M = ACTminPers (a);

    funR (0, sol, costi, a);

}