#include "persone.h"
#include <stdio.h>
#include "ST.h"

void copy_sol (SOL solu);

typedef struct node *link;

struct node {
    int index;
    link next;
};

typedef struct persona_s{
    char *indirizzo;
    int n_valigie;
    int distanza;
}persona;

struct persone{
    int N;
    persona *vet;
    int **m_ind;
};

struct vincoli {
    int N;
    link *ladj;
};

struct sol{
    int *sol;
    int *best_sol;
    int m_best;
};

/*Bisogna controllare attraverso una lista di adiacenza con una dfs se i vincoli delle persone
sono rispettati
Inoltre bisognaa controllare che la somma delle persone non superi MP
e la somma del numero di valigie non superi MV*/

int dfs (int v, link *ladj, PERSONS persone, int MP, int MV, int *peso, int *n_pers, int *visited, int result){

    visited[v] = 1;
    (*peso) += persone->vet[v].n_valigie;
    (*n_pers)++;

    if (*peso > MV || *n_pers > MP){
        return 0;
    }

    for (link t = ladj[v]; t != NULL; t = t->next){

        int result = dfs (t->index, ladj, persone, MP, MV, peso, n_pers, visited, result);
        if (result != -1){
            return result;
        }
    }

    return 1;
}

int check (CONSTRAINTS vincoli, PERSONS pers, int MP, int MV){
    int *visited = calloc (pers->N, sizeof (int));
    int peso = 0, n_pers = 0;

    for (int i = 0; i < pers->N; i++){
        if (visited[i] == 0){
            peso = 0; n_pers = 0;
            int result = dfs (i, vincoli->ladj, pers, MP, MV, &peso, &n_pers, visited, -1);
            if (result == 0){
                return 0;
            }
        }
    }
    return 1;
}


/*Devo trovare la distribuzione ottima dei minibus
Non sapendo quanti minibus mi servono, devo usare l'algoritmo di Er per le partizioni
(Anche perche devo partire dal piu piccolo)
Creo un vettore soluzione di dimensione N a cui ad ogni persona associo un minibus 
Che va da 0 a N (stoppo la ricorsione con un flag perche appena trovo una partizione più grande)
Ma ho gia una soluzione valida con una partizione piu piccola mi posso fermare*/

int is_possible (SOL solu, PERSONS pers, int MP, int MV, int *pesi, int *n_pers, int pos, int i){
    if (pesi[i] + pers->vet[pos].n_valigie > MV || n_pers[i] + 1 > MV){
        return 0;
    }
    return 1;
}

void insert (PERSONS pers, int pos, int i, int *pesi, int *n_pers){
    pesi[i] += pers->vet[pos].n_valigie;
    n_pers[i]++;
    return;
}

void backtrack (PERSONS pers, int pos, int i, int *pesi, int *n_pers){
    pesi[i] -= pers->vet[pos].n_valigie;
    n_pers[i]--;
    return;
}

int dfsR (int *visited, int v, SOL solu, int result, link *ladj){
    if (result != -1){
        return result;
    }

    visited[v] = 1;

    for (link t = ladj[v]; t != NULL; t = t->next){
        if (solu->sol[t->index] != solu->sol[v]){
            return 0;
        }
        int result = dfsR (visited, t->index, solu, result, ladj);
        if (result != -1){
            return result;
        }
    }
    return 1;
}

int check_valid (SOL solu, PERSONS pers, CONSTRAINTS vincoli, int *visited){

    for (int i = 0; i < pers->N; i++){
        if (visited [i] == 0){
            int result = dfsR (visited, i, solu, result, vincoli->ladj);
            if (result == 0){
                return 0;
            }
        }
    }
    return 1;
}

int calculate_best_m (SOL solu, int *distanze, PERSONS pers, int *best_distanze){
    for (int i = 0; i < pers->N; i++){
        distanze[solu->sol[i]] += pers->vet[i].distanza;
        best_distanze[solu->sol[i]] += pers->vet[i].distanza;
    }

    for (int i = 0; i < pers->N; i++){
        for (int j = 0; j < pers->N; j++){
            if (solu->sol[i] == solu->sol[j]){
                distanze[solu->sol[i]] -= pers->m_ind[i][j];
            }
            if (solu->best_sol[i] == solu->best_sol[j]){
                best_distanze[solu->best_sol[i]] -= pers->m_ind[i][j];
            }
        }
    }

    int somma = 0, best_somma = 0;
    for (int i = 0; i < solu->m_best; i++){
        somma += distanze[i]; best_somma += best_distanze[i];
    }

    if (somma < best_somma){
        return 1;
    }
    return 0;
}

void funR (SOL solu, PERSONS pers, CONSTRAINTS vincoli, int MP, int MV, int *pesi, int *n_pers, int pos, int *flag, int m){

    if (*flag){
        return;
    }

    if (solu->m_best != -1 && m > solu->m_best){
        *flag = 1;
        return;
    }

    if (pos >= pers->N){
        int *visited = calloc (pers->N, sizeof (int));
        if (check_valid (solu, pers, vincoli, visited)){
            if (m < solu->m_best){
                solu->m_best = m;
                copy_sol (solu);
            }
            else if (m == solu->m_best){
                int *distanze, *best_distanze;
                if (calculate_best_m (solu, distanze, pers, best_distanze)){
                    copy_sol (solu);
                }
            }
        }
        free (visited);
        return;
    }

    int i;
    for (i = 0; i < m; i++){
        if (is_possible (solu, pers, MP, MV, pesi, n_pers, pos, i)){
            solu->sol[pos] = i;
            insert (pers, pos, i, pesi, n_pers);

            funR (solu, pers, vincoli, MP, MV, pesi, n_pers, pos+1, flag, m);

            backtrack (pers, pos, i, pesi, n_pers);
        }
    }

    solu->sol[pos] = m;
    if (is_possible (solu, pers, MP, MV, pesi, n_pers, pos, m)){
        insert (pers, pos, i, pesi, n_pers);
        funR (solu, pers, vincoli, MP, MV, pesi, n_pers, pos+1, flag, m+1);
        backtrack (pers, pos, i, pesi, n_pers);
    }
}
void wrapper (PERSONS pers, CONSTRAINTS vincoli, int MP, int MV){
    int *pesi = calloc (pers->N, sizeof (int));
    int *n_pers = calloc (pers->N, sizeof (int));
    int flag = 0;

    SOL solu; //SOL init

    funR (solu, pers, vincoli, MP, MV, pesi, n_pers, 0, &flag, 0);

}