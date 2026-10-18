#include <stdio.h>
#include <stdlib.h>
#include "p_soccorso.h"
#include "Graph.h"
#include "ST.h"

struct citta {
    int N;
    ST st;
};

struct sedi_s {
    int* vet;
    int M;
};

struct matrice {
    int **mat;
    int N
};

struct servizi_s{
    int N;
    int* vet;
};

void caricaDati (FILE *f, ELENCO el, DISTMATR mat){
    //el_citta init

    fscanf (f, "%d", &(el->N));
    mat->N = el->N;

    char nome[20];

    for (int i = 0; i < el->N; i++){
        STinsert (el->st, fscanf(f, "%s", nome), i);
    }

    for (int i = 0; i < el->N; i++){
        for (int j = 0; j < el->N; j++){
            fscanf (f, "%d", mat->mat[i][j]);
        }
    }
}

int checkSedi (int MAXD, DISTMATR mat, int MINS, SEDI sol){
    int *citta_coperte; //vettore di 0 di dimensione N
    for (int i = 0; i < sol->M; i++){
        citta_coperte[sol->vet[i]] = 1;
    }

    int flag = 0, i, j;

    for (i = 0; i < mat->N; i++){
        if (citta_coperte[i] == 0){
            flag = 0;
            for (j = 0; j < sol->M; j++){
                if (mat->mat[i][j] <= MAXD){
                    flag = 1;
                    citta_coperte[sol->vet[j]]++;
                }
            }
            if (!flag) return 0;
        }
    }

    for (i = 0; i < mat->N; i++){
        if (citta_coperte[i] != 0 && citta_coperte[i] <= MINS+1){
            return 0;
        }
    }
    return 1;
}

//Si puo fare pruning sulla distanza media (se in mezzo a una soluzione è gai maggiore ella minima)
//

int prunePart (SEDI sedi, float *min, SERVIZI sol, int index, DISTMATR mat, int curr_val, int MAXD){
    float media = (float) curr_val/ (float) sedi->M;
    if (media > *min) return 0;

    if (mat->mat[sol->vet[index]][index] > MAXD){
        return 0;
    }

    return 1;
}

int checkPart (SERVIZI sol, float *min, int curr_val, DISTMATR mat, int MINS, SEDI sedi){
    int *assegnate; //calloc (M)
    for (int i = 0; i < sol->N; i++){
        assegnate[sol->vet[i]]++;
    }
    for (int i = 0; i < sedi->M; i++){
        if (assegnate[i] < MINS){
            return 0;
        }
    }

    float media = (float) curr_val/ (float) sedi->M;
    if (media > *min) return 0;

    return 1;

}

void bestPart (ELENCO cit, SEDI sedi, int MINS, int MAXD, float *min, SERVIZI sol, SERVIZI best_sol, int pos, DISTMATR mat, int curr_val){
    int i, j;
    if (prunePart (sedi, min, sol, pos-1, mat, curr_val, MAXD)){
        return ;
    }

    if (pos >= sedi->M){

        if (checkPart (sol, min, curr_val, mat, MINS, sedi)){
            for (i = 0; i < sol->N; i++){
                best_sol[i] = sol[i];
            }
            *min = (float) curr_val / (float) sedi->M;
        }
        return;
    }

    for (i = 0; i < sedi->M; i++){
        sol->vet[pos] = sedi->vet[i];
        sol->N++;
        curr_val += mat->mat[pos][i];

        bestPart (cit, sedi, MINS, MAXD, min, sol, best_sol, pos+1, mat, curr_val);

        curr_val -= mat->mat[pos][i];
        sol->N--;
    }

    return;
}