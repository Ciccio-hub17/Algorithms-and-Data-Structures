#include<stdio.h>
#include<stdlib.h>

#define N 9

int controls(int posr, int posc, int **sol){
    int flag = 1;
    int i, j;
    for (i = posr, j = posc-1; j >= 0; j--){
        if (sol[i][j] == sol[posr][posc]){
            return !flag;
        }
    }
    for (i = posr-1, j = posc; i >= 0; i--){
        if (sol[i][j] == sol[posr][posc]){
            return !flag;
        }
    }
    for (i = (posr/3)*3, j = (posc/3)*3; i <= (posr/3)*3 + 2; i++){
        for (j = (posc/3)*3; j <= (posc/3)*3 + 2; j++){
            if (!(i == posr && j == posc)){
                if (sol[i][j] == sol[posr][posc]){
                    return !flag;
                }
            }
        }
    }

    return flag;
}

void sudoku (int **sol, int posr, int posc, int **best_sol, int *found){
    int i, j;

    if (*found){
        return;
    }

    if (posr >= N){
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){
                best_sol[i][j] = sol[i][j];
            }
        }
        *found = 1;
    }

    for (i = 0; i < N && posr < N; i++){
        sol[posr][posc] = i+1;
        int flag = controls (posr, posc, sol);
        if (flag){
            if (posc == N-1){
                sudoku (sol, posr+1, 0, best_sol, found);
            }
            else{
                sudoku (sol, posr, posc+1, best_sol, found);
            }
        }
        sol[posr][posc] = 0;
    }
    
}

int main(int argc, char* argv[]){
    
    int i, found = 0, j;
    int **sol = malloc (N* sizeof (int*));
    int **best_sol = malloc (N* sizeof (int*));
    for (i = 0; i < N; i++){
        sol[i] = (int *) calloc (N, sizeof (int));
        best_sol[i] = (int *) calloc (N, sizeof (int));
    }

    sudoku (sol, 0, 0, best_sol, &found);

    for (i = 0; i < N; i++){
        for (j = 0; j < N; j++){
            printf (" %d ", best_sol[i][j]);
        }
        printf ("\n");
    }
    for (i = 0; i < N; i++){
        free (sol[i]);
        free (best_sol[i]);
    }
    free (sol);
    free (best_sol);
    printf("\n");
    return 0;
}