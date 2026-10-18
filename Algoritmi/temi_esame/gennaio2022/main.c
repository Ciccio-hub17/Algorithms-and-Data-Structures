#include<stdio.h>
#include<stdlib.h>
#include <limits.h>

typedef struct matrice *mat;
typedef struct soluzione *SOL;

struct matrice{
    int NR;
    int NC;
    int **mat;
};

struct soluzione {
    int len;
    //questo viene allocato di min (NR, NC) e si inizializza a NULL
    int regioni[][4];
};

void read_file (mat matrice, FILE *f){

    fscanf (f, "%d %d", &matrice->NR, &matrice->NC);
    for (int i = 0; i < matrice->NR; i++){
        for (int j = 0; j < matrice->NC; j++){
            fscanf (f, "%d", &matrice->mat[i][j]);
        }
    }
}

//File della proposta:
//Per ogni sottoregione 4 interi
//indice di riga e colonna in cui inizia la sottoregione, indice di riga e colonna in cui finisce la sottoregione
int verifica (SOL sol, mat matrice){
    mat prov_mat = matrice;
    int i, m, n;
    int rigaIn, colIn, rigaF, colF;
    for (i = 0; sol->regioni[i] != NULL; i++){
        rigaIn = sol->regioni[i][0];
        colIn = sol->regioni[i][1];
        rigaF = sol->regioni[i][2];
        colF = sol->regioni[i][3];
        if (rigaF - rigaIn != colF - colIn){
            return 0;
        }
        for (m = rigaIn; m < rigaF; m++){
            for (n = colIn; n < colF; n++){
                if (prov_mat->mat[m][n] != 0){
                    printf ("sovrapposizione\n");
                    return 0;
                }
                prov_mat->mat[m][n] = 1;
            }
        }
        sol->len++;
    }

    for (m = 0; m < prov_mat->NR; m++){
        for (n = 0; n < prov_mat->NC; n++){
            if (prov_mat->mat[m][n] == 0){
                return 0;
            }
        }
    }
    return 1;
}

/*Cerca la regione piu grande, se la trovi continua a cercarne un'altra,
altrimenti diminuisci la grandezza di quanto ti devi spostare*/
int check_matrix (mat prov_mat){
    for (int m = 0; m < prov_mat->NR; m++){
        for (int n = 0; n < prov_mat->NC; n++){
            if (prov_mat->mat[m][n] == 0){
                return 0;
            }
        }
    }
    return 1;
}

void funR(int *min, mat prova, int k, int cur_reg){

    if (cur_reg > *min){
        return;
    }

    int i, j, m, n;
    if (check_matrix (prova)){
        if (cur_reg < *min){
            *min = cur_reg;
        }
        return;
    }

    int flag, tot_flag = 0;
    for (i = 0; i < prova->NR && !tot_flag; i++){
        for (j = 0; j < prova->NC && !tot_flag; j++){
            flag = 1;
            if (i + k < prova->NR && j + k < prova->NC){
                for (m = i; m < k && flag; m++){
                    for (n = j; n <  k && flag; n++){
                        if (prova->mat[m][n] != 0){
                            flag = 0;
                        }
                    }
                }
                if (flag){
                    tot_flag = 1;
                }
            }
        }
    }

    if (tot_flag){
        int riga = i-1;
        int col = j-1;
        for (m = riga; m < k; m++){
            for (n = col; n < k; n++){
                if (prova->mat[m][n] != 1){
                    prova->mat[m][n] = -1;
                }
            }
        }

        funR (min, prova, k, cur_reg+1);

        for (m = riga; m < k; m++){
            for (n = col; n < k; n++){
                if (prova->mat[m][n] != 1){
                    prova->mat[m][n] = 0;
                }
            }
        }
    }
    else{
        funR (min, prova, k-1, cur_reg);
    }
}

void wrapper (mat matrice){
    int min = INT_MAX;
    int minDim;
    if (matrice->NR < matrice->NC){
        minDim = matrice->NR;
    }
    else {
        minDim = matrice->NC;
    }

    funR (&min, matrice, minDim, 0);
}

int main(int argc, char* argv[]){
    
    printf("\n");
    return 0;
}

void funRR (int k, mat matrice, mat covered, int *min){
    int i, j, flag = 0, r, c;
    for (i = 0; i < matrice->NR && !flag; i++){
        for (j = 0; j < matrice->NC && !flag; j++){
            if (matrice->mat[i][j] == 0 && covered->mat[i][j] == 0){
                flag = 1;
                r = i;
                c = j;
            }
        }
    }
    if (!flag){
        if (k < *min){
            *min = k;
        }
        return;
    }

    int maxR = r + matrice->NR, maxC = c + matrice->NC, minDim;

    if (maxR < maxC){
        minDim = maxR;
    }
    else{
        minDim = maxC;
    }

    int colorabile = 1;

    for (; minDim >= 1; minDim--){
        colorabile = 1;
        for (int m = r; m < r + i && colorabile; m++){
            for (int n = c; n < c + i && colorabile; n++){
                if (matrice->mat[m][n] == 1 || covered->mat[m][n] == 1){
                    colorabile = 0;
                }
            }
        }
    }

    for (int m = r; m < r + i && colorabile; m++){
        for (int n = c; n < c + i && colorabile; n++){
            covered->mat[m][n] = 1;
        }
    }

    funRR (k+1, matrice, covered, min);

    for (int m = r; m < r + i && colorabile; m++){
        for (int n = c; n < c + i && colorabile; n++){
            covered->mat[m][n] = 0;
        }
    }
    return;
}