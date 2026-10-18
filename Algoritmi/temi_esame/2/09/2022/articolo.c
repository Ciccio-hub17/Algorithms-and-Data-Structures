#include "articolo.h"
#include <stdio.h>
#include "ST.h"

typedef struct sol* SOL;

struct articoli {
    ARTICOLO *vet;
    int N;
    ST st;
};

typedef struct programma {
    int **mat;
    int R;
    int S;
    int N_rel;
    int N_arg;
    ST tab_rel;
    ST tab_arg;
};

struct sol {
    int NA;
    int NV;
    int **temi;
    int *ultimo_slot;
};

//Programma conferenza
//R S
//Matrice della conferenza RxS interi
//Dove si occupano n_slot celle e si occupa la matrice con l'indice del vettore in cui è messo
//L'articolo
PROGRAMMA read_prop (char *filename, ARTICOLI art){
    FILE *f = fopen (filename, "r");
    PROGRAMMA p; //Init
    fscanf (f, "%d %d", &p->R, &p->S);

    for (int i = 0; i < p->R; i++){
        for (int j = 0; j < p->S; j++){
            fscanf (f, "%d", &p->mat[i][j]);
        }
    }
    fclose (f);
    return p;
}

int check (PROGRAMMA p, ARTICOLI art){
    for (int i = 0; i < p->R; i++){
        for (int j = 0; j < p->S; j++){
            if (p->mat[i][j] >= art->N){
                return 0;
            }
        }
    }

    for (int i = 0; i < p->S; i++){
        int *sovr = calloc (p->N_rel, sizeof (int));
        for (int j = 0; j < p->R; j++){
            sovr[art->vet[p->mat[j][i]].rel]++;
        }
        for (int m = 0; m < p->N_rel; m++){
                if (sovr[m] > 1){
                    return 0;
                }
            }
        free (sovr);
    }

    int used = 0;
    for (int i = 0; i < p->R; i++){
        int j = 0;
        while (j < p->S){
            int index = p->mat[i][j];
            int k;
            if (p->mat[i][j] != -1){
                used++;
                if (art->vet[index].slot + j >= p->S){
                    return 0;
                }
                for (k = j; k < j+art->vet[index].slot; k++){
                    if (p->mat[i][k] != index){
                        return 0;
                    }
                }
                j += art->vet[index].slot;
            }
            else{
                j++;
            }
        }
    }

    if (used != art->N){
        return 0;
    }

    return 1;
}

int possibile (int r, int c, ARTICOLO art, PROGRAMMA p, ARTICOLI arti){

    if (c + art.slot >= p->S){
        return 0;
    }

    for (int k = c; k < c+art.slot; k++){
        if (p->mat[r][k] != -1){
            return 0;
        }
    }
    for (int m = c; m < c + art.slot; m++){
        for (int k = 0; k < p->R; k++){
            if (k != r){
                if (p->mat[k][m] != -1 && arti->vet[p->mat[k][m]].rel == art.rel){
                    return 0;
                }
            }
        }
    }
    return 1;
}

void inserimento (PROGRAMMA p, SOL sol, int c, int r, int pos, ARTICOLI art){
    int j;
    for (j = c; j < c + art->vet[pos].slot; j++){
        p->mat[r][j] = pos;
    }

    if (sol->temi[r][art->vet[pos].tema] == 0){
        sol->NA++;
    }
    sol->temi[r][art->vet[pos].tema]++;

    if (c > sol->ultimo_slot[r]+1){
        sol->NV += c - (sol->ultimo_slot[r]+1);
    }

    if (j-1 > sol->ultimo_slot[r]){
        sol->ultimo_slot[r] = j-1;
    }
    
}

void backtrack (PROGRAMMA p, SOL sol, int c, int r, int pos, ARTICOLI art, int vecchio_slot, int vecchioNV){
    int j;
    for (j = c; j < c + art->vet[pos].slot; j++){
        p->mat[r][j] = -1;
    }

    sol->NV =vecchioNV;
    sol->temi[r][art->vet[pos].tema]--;
    if (sol->temi[r][art->vet[pos].tema] == 0){
        sol->NA--;
    }
    
    sol->ultimo_slot[r] = vecchio_slot;

}

void funR (ARTICOLI art, PROGRAMMA p, int *min, int pos, SOL sol){
    if (sol->NA+sol->NV > *min){
        return;
    }

    if (pos >= art->N){
        if (sol->NA+sol->NV < *min){
            *min = sol->NA+sol->NV;
        }
        return;
    }

    for (int i = 0; i < p->R; i++){
        for (int j = 0; j < p->S; j++){
            if (possibile (i, j, art->vet[pos], p, art)){

                int vecchioNV = sol->NV;
                int vecchio_slot = sol->ultimo_slot[i];
                inserimento (p, sol, j, i, pos, art);
                funR (art, p, min, pos+1, sol);
                backtrack (p, sol, j, i, pos, art, vecchio_slot, vecchioNV);

            }
        }
    }
}

