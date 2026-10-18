#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ACT.h"
#include "ST.h"

#define MAX_S 20

void quick_sort (int l, int r, char **vet);

struct activity {
    int start;
    int end;
    int val;
    int pred1;
    int pred2;
};

struct activities {
    struct activity* vet;
    int NA;
    ST st;
};

ACT activityRead(FILE *f){

    int i, m, n, l;
    int NA, NP;
    fscanf (f, "%d %d", &NA, &NP);

    ACT activities;
    //ACTInit;

    activities->NA = NA;
    struct activity val;
    char nome[MAX_S];
    int dur;

    for (i = 0; i < NA; i++){
        fscanf (f, "%s %d %d %d", nome, &val.start, &dur, &val.val);
        STinsert(activities->st, nome, i);
        activities->vet[i] = val; activities->vet[i].end = activities->vet[i].start + dur;
    }

    char nome1[MAX_S], nome2[MAX_S], nome3[MAX_S];
    int index1, index2, index3;

    for (int j = i; j < NP; j++){
        if (fscanf (f, "%s %s %s", nome1, nome2, nome3) == 3){
            index1 = STsearch (activities->st, nome1);
            index2 = STsearch (activities->st, nome2);
            index3 = STsearch (activities->st, nome3);
            activities->vet[index1].pred1 = index2;
            activities->vet[index1].pred2 = index3;
        }
        else{
            index1 = STsearch (activities->st, nome1);
            index2 = STsearch (activities->st, nome2);
            activities->vet[index1].pred1 = index2;
            activities->vet[index1].pred2 = -1;
        }
    }
    
    fclose(f);
}

int checkSelection(ACT a, char **selected, int nsel){

    int *selected_int = malloc (nsel*sizeof (int));
    int *mark = calloc (a->NA, sizeof (int));
    for (int i = 0; i < nsel; i++){
        selected_int[i] = STsearch(a->st, selected[i]);
    }
    int i, j, count = 1;
    int prev = selected_int[0];
    int new;
    if (a->vet[prev].pred1 != -1 || a->vet[prev].pred2 != -1) return 0;
    for (i = 1; i < nsel; i++){
        if ((a->vet[selected_int[i]].pred1 != -1 && mark[a->vet[selected_int[i]].pred1] != 1) || (a->vet[selected_int[i]].pred2 != -1 && mark[a->vet[selected_int[i]].pred2] != 1)){
            return 0;
        }
        for (j = 0; j < i; j++){
            if (a->vet[selected_int[j]].start < a->vet[selected_int[i]].end || a->vet[selected_int[i]].start < a->vet[selected_int[j]].end){
                return 0;
            }
        }
    }

    return 1;
}

void best_selR (char **sol, int pos, int *max, char **best_sol, int *n_act, int cur_val, ACT a, int *mark){
    
    if (checkSelection (a, sol, pos)){
        if (cur_val > *max){
            for (int i = 0; i < pos; i++){
                strcpy (best_sol[i], sol[i]);
                *max = cur_val;
                *n_act = pos;
            }
        }
    }
    else{
        return;
    }

    if (pos >= a->NA){
        return;
    }

    for (int i = 0; i < a->NA; i++){
        if (mark[i] == 0){
            mark[i] = 1;
            strcpy (sol[pos], STsearchByIndex(a->st, i));
            cur_val += a->vet[i].val;

            best_selR (sol, pos+1, max, best_sol, n_act, cur_val, a, mark);

            mark[i] = 0;
            cur_val -= a->vet[i].val;
        }
    }

    return;
}

int bestSelection (ACT a, char **returned_sol){
    //Allocazioni delle strutture che mi servono

    char **sol;
    int max = 0, n_act = 0, *mark;

    best_selR (sol, 0, &max, returned_sol, &n_act, 0, a, mark);
    
    quick_sort (0, n_act-1, returned_sol);

    //Free delle strutture che mi servono

    return max;
}