#include<stdio.h>
#include<stdlib.h>

#define FILENAME "griglia.txt"

typedef struct matrice_s *MAT;

struct matrice_s {
    int NR;
    int NC;
    int **mat;
};

int dr[4] = {1, -1, 0, 0};
int dc[4] = {0, 0, 1, -1};

void read_file (MAT mat){

    FILE *f;
    if ((f = fopen(FILENAME, "r")) == NULL){
        printf("Errore nell'apertura del file: \"%s\"", FILENAME);
        exit(-1);
    }
    fscanf (f, "%d %d", &mat->NR, &mat->NC);

    for (int i = 0; i < mat->NR; i++){
        for (int j = 0; j < mat->NC; j++){
            fscanf (f, "%d", &mat->mat[i][j]);
        }
    }
    fclose(f);

    return;
}

/*File proposta.txt organizzato come segue
Non si sa a priori il numero di mosse
Ogni riga comprende 2 interi che definiscono la direzione in cui mi sto muovendo
Il primo intero (1 o -1) indica la riga (e il segno indica se a destra o a sinistra)
e il secondo fa lo stesso (Si assume il file corretto, cioe entrambi i numeri non possono essere diversi da 0)*/
//La matrice covered è una copia di quella standard
int check (MAT griglia, MAT covered, FILE *f){

    int n_cambi = 0;
    int r, c;
    int i = 0, j = 0;
    int prevR = -2, prevC = -2;
    while (fscanf (f, "%d %d", &r, &c) == 2){
        i+= r; j += c;
        if (i >= 0 && i < griglia->NR && j >= 0 && j < griglia->NC){
            if (covered->mat[i][j] != 0){
                return 0;
            }
            covered->mat[i][j] = -1;
            if (prevR != -2){
                if (r != prevR || c != prevC){
                    (n_cambi)++;
                }
            }
            prevR = r;
            prevC = c;
        }
        else{
            return 0;
        }
    }

    for (int m = 0; m < griglia->NR; m++){
        for (int n = 0; n < griglia->NC; n++){
            if (covered->mat[m][n] == 0 && m != 0 && n != 0){
                return 0;
            }
        }
    }

    return n_cambi;
}

int checkR (MAT covered){
    for (int m = 0; m < covered->NR; m++){
        for (int n = 0; n < covered->NC; n++){
            if (covered->mat[m][n] == 0 && m != 0 && n != 0){
                return 0;
            }
        }
    }
    return 1;
}

//I vettori dr e dc sono le direzioni possibili: sono costruiti cosi:
//dr[4] = {1, -1, 0, 0}; dc[4] = {0, 0, 1, -1};
void funR (int *n_min, int cur_cambi, MAT covered, MAT griglia, int r, int c, int posR, int posC, int *dr, int *dc){

    if (cur_cambi > *n_min){
        return;
    }

    if (checkR (covered)){
        if (cur_cambi < *n_min){
            *n_min = cur_cambi;
        }
        return;
    }

    int k, r_new, c_new;
    for (k = 0; k < 4; k++){
        r_new = posR + dr[k]; c_new = posC + dc[k];
        if (r_new >= 0 && r_new < griglia->NR && c_new >= 0 && c_new < griglia->NC){
            if (covered->mat[r_new][c_new] == 0){
                covered->mat[r_new][c_new] = -1;

                if (dr[k] != r || dc[k] != c){
                    funR (n_min, cur_cambi+1, covered, griglia, dr[k], dc[k], r_new, c_new, dr, dc);
                }
                else{
                    funR (n_min, cur_cambi, covered, griglia, dr[k], dc[k], r_new, c_new, dr, dc);
                }

                covered->mat[r_new][c_new] = 0;
            }
        }
    }

    return;
    
}



int main(int argc, char* argv[]){
    
    printf("\n");
    return 0;
}