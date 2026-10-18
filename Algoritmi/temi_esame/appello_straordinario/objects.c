#include "ST.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "objects.h"
#include <limits.h>

typedef struct node *link;

typedef struct object_s{
    char nome[30];
    float costo;
    float peso;
    float volume;
}object;

struct node {
    object val;
    link *next;
};

CONSTRAINTS vincoli;

struct objects{
    object *vet;
    ST st;
    int len;
};

int check (OBJECTS oggetti, CONSTRAINTS vincoli, float peso_max, float cap_max){

    link t;
    int i;
    float peso = 0, cap = 0;
    for (i = 0; i < oggetti->len; i++){
        for (t = vincoli[i]; t != NULL; t = t->next){
            if (STsearch (oggetti->st, t->val.nome) < 0){
                return 0;
            }
        }
        peso += oggetti->vet[i].peso;
        cap += oggetti->vet[i].volume;
        if (peso > peso_max || cap >= cap_max){
            return 0;
        }
    }

    return 1;
}

int check_R (OBJECTS oggetti, CONSTRAINTS vincoli, float *pesi, float *val, float peso_max, float cap_max, SOL sol){
    for (int i = 0; i < oggetti->len; i++){
        for (link t = vincoli[i]; t != NULL; t = t->next){
            if (STsearch (oggetti->st, t->val.nome) < 0){
                return 0;
            }
        }
    }
    return 1;
}

//Partizioni? (Algoritmo di Er)
//Sol è un vettore di interi parallelo a quello degli oggetti
//L'idea è quella di mettere in sol[pos] la cui pos corrisponde all'oggetto
//Il giorno di riferimento
int calculate_cost (OBJECTS oggetti, SOL sol, SOL best_sol, int m){
    float *costo, *best_costo; //Entrambi allocati (dim m)
    for (int i = 0; i < oggetti->len; i++){
        costo[sol[i]] += oggetti->vet[i].costo;
        best_costo[best_sol[i]] += oggetti->vet[i].costo;
    }

    float min = INT_MAX, max = 0, differenzasol, differenza_best_sol;

    for (int i = 0; i < m; i++){
        if (costo[i] < min){
            min = costo[i];
        }
        if (costo[i] > max){
            max = costo[i];
        }
    }
    differenzasol = max-min;
    min = INT_MAX, max = 0;

    for (int i = 0; i < m; i++){
        if (best_costo[i] < min){
            min = costo[i];
        }
        if (best_costo[i] > max){
            max = costo[i];
        }
    }
    differenza_best_sol = max-min;
    if (differenzasol < differenza_best_sol){
        return 1;
    }
    return 0;
}
void funR (OBJECTS oggetti, CONSTRAINTS vincoli, float *pesi, float *val, float peso_max, float cap_max, int pos, SOL sol, SOL best_sol, int m, int *min_giorni, int *flag){

    if (m != *min_giorni){
        if (*flag) return;
    }

    if (pesi[sol[pos-1]] > peso_max || val[sol[pos-1]] > cap_max){
        return;
    }

    if (pos >= oggetti->len){
        if (check_R (oggetti, vincoli, pesi, val, peso_max, cap_max, sol)){
            if (m == *min_giorni){
                if (calculate_cost(oggetti, sol, best_sol, m)){
                    *flag = 1;
                    for (int k = 0; k < oggetti->len; k++){
                        best_sol[k] = sol[pos];
                    }
                }
            }
            else if (m < *min_giorni){
                *flag = 1;
                for (int k = 0; k < oggetti->len; k++){
                    best_sol[k] = sol[pos];
                }
                *min_giorni = m;
            }
        }
        return;
    }

    int i;
    for (i = 0; i < m-1; i++){
        if (pesi[pos]+ oggetti->vet[pos].peso < peso_max && val[pos]+ oggetti->vet[pos].volume < cap_max){
            sol[pos] = i;
            pesi[i]+= oggetti->vet[pos].peso; val[i] += oggetti->vet[pos].volume;

            funR (oggetti, vincoli, pesi, val, peso_max, cap_max, pos+1, sol, best_sol, m, min_giorni, flag);
            pesi[i]-= oggetti->vet[pos].peso; val[i] -= oggetti->vet[pos].volume;
        }
    }

    sol[pos] = m;
    pesi[i]+= oggetti->vet[pos].peso; val[i] += oggetti->vet[pos].volume;
    funR (oggetti, vincoli, pesi, val, peso_max, cap_max, pos+1, sol, best_sol, m+1, min_giorni, flag);
    pesi[i]-= oggetti->vet[pos].peso; val[i] -= oggetti->vet[pos].volume;
    return;
}
