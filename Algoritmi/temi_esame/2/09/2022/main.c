#include<stdio.h>
#include<stdlib.h>
#include "ST.h"
#define MAXC 15
#define FILENAME "griglia.txt"

typedef struct grid_s *GRID;
typedef struct elenco_s *WORDS;
typedef struct sol_s *SOL;

struct grid_s {
    char **mat;
    int NR;
    int NC;
};

struct elenco_s{
    ST st;
    int *parole;
    int N;
};

struct sol_s{
    int **covered;
    int N;
};

void read_griglia (GRID griglia){

    FILE *f = fopen (FILENAME, "r");

    fscanf (f, "%d %d", &griglia->NR, &griglia->NC);

    for (int i = 0; i < griglia->NR; i++){
        for (int j = 0; j < griglia->NC; j++){
            fscanf (f, "%c", &griglia->mat[i][j]);
        }
    }

    fclose (f);
}

void read_parole (WORDS parole){
    FILE *f = fopen ("parole.txt", "r");

    char nome[MAXC];
    int val, i = 0;

    while (fscanf (f, "%s %d", nome, &val) == 2){
        parole->parole[i] = val;
        STinsert (parole->st, nome, i);
        i++;
    }
    parole->N = i;
    fclose (f);
    return;
}

//Formato di proposta.txt:
//parola da cercare

int checkR (char* parola, int r, int c, int dr, int dc, GRID griglia, int result){
    if (*parola == '\0'){
        return 1;
    }

    if (parola[0] != griglia->mat[r][c] || r > griglia->NR-1 || c > griglia->NC-1){
        return 0;
    }

    int result = checkR (parola+1, r+dr, c+dc, dr, dc, griglia, result);
    if (result != -1){
        return result;
    }
}

int check (WORDS parole, GRID griglia, SOL sol){
    FILE *f = fopen ("proposta.txt", "r");
    int dr[3] = {1, 0, 1};
    int dc[3] = {0, 1, 1};

    char nome[MAXC], primo;
    int trovato, i, j, n_parole = 1;

    while (fscanf (f, "%s", nome)){
        int *sovr = calloc (parole->N, sizeof (int));
        int index;
        if (index = STsearch (parole->st, nome) == -1){
            return 0;
        }
        for (int i = 0; i < griglia->NR && !trovato; i++){
            for (int j = 0; j < griglia->NC && !trovato; j++){
                for (int k = 0; k < 3 && !trovato; k++){
                    int trovato = checkR (nome, i, j, dr[k], dr[k], griglia, -1);
                }
            }
        }
        if (!trovato){
            return 0;
        }

    }
}

int main(int argc, char* argv[]){
    
    printf("\n");
    return 0;
}