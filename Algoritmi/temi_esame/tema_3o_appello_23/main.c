#include<stdio.h>
#include<stdlib.h>
#define FILENAME "grid.txt"

#define vuoto -1
#define normal 1
#define source 0

typedef struct cella_s {
    int vet[4];
    int tipo;
    int visited;
}cella;

int read_file (FILE *f){

    int N, T, val[4], count = -1;
    cella **mat;

    fscanf (f, "%d %d", &N, &T);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            count = -1;
            for (int m = 0; m < 4; m++){
                fscanf (f, "%d", &mat[i][j].vet[m]);
                if (mat[i][j].vet[m] != 0){
                    count++;
                }
            }
            mat[i][j].tipo = count;

        }
    }

    return N;
    
    fclose(f);
}

//Il file di lettura contiene un intero n_moves;
//Seguono n_moves righe di questa forma:
// "Spostamento sulla riga" "Spostamento sulla colonna"
//ES: 0 1 (Vuol dire che devo spostare le celle a est) oppure -1 0 significa che sto spostando le celle a nord
//Assumo che il file sia corretto (Non posso avere entrambi i numeri != 0)

void direzione (int d, int *vet){
    int vet[3];
    if (d == 0){
        vet[0] = -1;
        vet[1] = 0;
        vet[2] = 1;
        return;
    }
    if (d == 1){
        vet[0] = 1;
        vet[1] = 0;
        vet[2] = 0;
        return;
    }
    if (d == 2){
        vet[0] = 0;
        vet[1] = 1;
        vet[2] = 3;
        return;
    }
    
    vet[0] = 0;
    vet[1] = -1;
    vet[2] = 2;
    return;

}

int connected (cella **mat, int r_s, int c_s, int r, int c, int control, int result, int **visited){

    visited[r][c] = 1;

    if (result == 1){
        return result;
    }

    if (mat[r][c].vet[control] != 1){
        return 0;
    }

    if (mat[r][c].tipo == source && r != r_s && c != c_s){
        return 1;
    }

    int vet[3];
    for (int i = 0 ; i < 4 && !result; i++){
        if (mat[r][c].vet[i] != 0){
            direzione (mat[r][c].vet[i], vet);
            result = connected (mat, r_s, c_s, r + vet[0], c + vet[1], vet[2], result, visited);
        }
    }

    return result;
}

int check (int **moves, int n_moves, cella **mat, int N){

    int i, j, k, r_new, c_new, flag, r_s, c_s, d;
    for (k = 0; k < n_moves; k++){
        flag = 0;
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){
                r_new = i + moves[k][0]; c_new = j + moves[k][1];
                if (r_new >= 0 && r_new < N && c_new >= 0 && c_new < N){
                    if (mat[i][j].tipo != vuoto){
                        if (mat[r_new][c_new].tipo == vuoto && mat[i][j].visited == 0 && mat[r_new][c_new].visited == 0){
                            flag = 1;
                            mat[r_new][c_new] = mat[i][j];
                            mat[i][j].tipo = vuoto;
                            mat[i][j].visited = 1;
                            mat[r_new][c_new].visited = 1; 
                            for (int m = 0; m < 4; m++){
                                mat[i][j].vet[m] = 0;
                            }
                            if (mat[r_new][c_new].tipo == source){
                                //salvo le coordinate di una delle due sorgenti
                                r_s = r_new; c_s = c_new;
                            }
                        }
                    }
                }
            }
        }
        if (!flag){
            return 0;
        }
    }
    printf ("Le mosse sono tutte valide\n");
    for (int g = 0; g < 4; g++){
        if (mat[r_s][c_s].vet[g] == 1){
            d = g;
        }
    }
    int *vet = malloc (3*sizeof (int)), **visited;
    direzione (d, vet);

    if (connected (mat, r_s, c_s, vet[0], vet[1], vet[2], 0, visited)){
        printf ("Le sorgenti sono connesse\n");
    }
    else{
        printf ("Le sorgenti non sono connesse\n");
    }
    return 1;

}

int check_move (cella **mat, int dr, int dc, int N){

    int r_new, c_new, flag = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            r_new = i + dr; c_new = j + dc;
            if (r_new >= 0 && r_new < N && c_new >= 0 && c_new < N){
                if (mat[i][j].tipo != vuoto){
                    if (mat[r_new][c_new].tipo == vuoto && mat[i][j].visited == 0 && mat[r_new][c_new].visited == 0){
                        flag = 1;
                        mat[r_new][c_new] = mat[i][j];
                        mat[i][j].tipo = vuoto;
                        mat[i][j].visited = 1;
                        mat[r_new][c_new].visited = 1; 
                        for (int m = 0; m < 4; m++){
                            mat[i][j].vet[m] = 0;
                        }
                    }
                }
            }
        }
    }
    if (!flag) return 0;
    return 1;
}

void search_start (cella **mat, int *start, int N){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (mat[i][j].tipo == source){
                start[0] = i; start[1] = j;
                int vet[3];
                for (int k = 0; k < N; k++){
                    if (mat[i][j].vet[k] == 1){
                        direzione(k, vet);
                    }
                }
                start[2] = vet[2];
                return;
            }
        }
    }
}

int funR (int **moves, int pos, cella **mat, int N, int k, int *dr, int *dc){
    if (pos >= k){
        int start [3];
        int **visited; //Ovviamente allocata
        search_start (mat, start, N);
        if (connected(mat, start[0], start[1], start[0], start[1], start[2], 0, visited)){
            return 1;
        }
    }

    cella **backup;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            backup[i][j] = mat[i][j];
        }
    }

    for (int i = 0; i < 4; i++){
        if (check_move (backup, dr[i], dc[i], N)){
            moves[pos] = {dr[i], dc[i]};

            if (funR (moves, pos+1, mat, N, k, dr, dc)){
                //free backup
                return 1;
            }
        }
    }

    return 0;
}

int third_wrapper (cella **mat, int N, int M){
    int dr[4] = {1, -1, 0, 0};
    int dc[4] = {0, 0, 1, -1};

    int k;
    int **moves; //Ovviamente allocato
    for (k = 1; k < M && !funR (moves, 0, mat, N, k, dr, dc); k++);
}

int main(int argc, char* argv[]){
    
    printf("\n");
    return 0;
}