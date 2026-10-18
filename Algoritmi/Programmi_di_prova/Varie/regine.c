#include<stdio.h>
#include <stdlib.h>

#define N 8

int controls (int posr, int posc, int **sol){
    int flag = 1;
    int i, j;
    for (i = posr-1, j = posc-1; i >= 0 && j >= 0; i--, j--){
        if (sol[i][j] == 1){
            return !flag;
        }
    }
    
    for (i = posr-1, j = posc; i >= 0; i--){
        if (sol[i][j] == 1){
            return !flag;
        }
    }

    for (i = posr-1, j = posc+1; i >= 0 && j < N; i--, j++){
        if (sol[i][j] == 1){
            return !flag;
        }
    }
    
    return flag;
}

void queens_r (int posr, int **sol, int **best_sol, int *found){
    int i, j;

    if (*found){
        return;
    }

    if (posr >= N){
        printf("Beatrice\n");
        for (i = 0; i < N; i++){
            for (j = 0; j < N; j++){
                best_sol[i][j] = sol[i][j];
            }
        }
        *found = 1;
        return;
    }
        for (j = 0; j < N; j++){
            sol[posr][j] = 1;
            int flag = controls (posr, j, sol);
            if (flag){
                queens_r (posr+1, sol, best_sol, found);
            }
            sol[posr][j] = 0;
        }
        
    return;
}

void put_queens_wrapper (){
    int **sol = malloc (N*sizeof (int*)), found = 0;
    int **best_sol = malloc (N*sizeof (int*));
    for (int i = 0; i < N; i++){
        sol[i] = (int *) calloc (N, sizeof(int));
        best_sol[i] = (int *) calloc (N, sizeof(int));
    }

    queens_r (0, sol, best_sol, &found);

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            printf (" %d ", best_sol[i][j]);
        }
        printf ("\n");
    }

    for (int i = 0; i < N; i++){
        free (sol[i]);
        free (best_sol[i]);
    }
    free (sol);
    free (best_sol);
    return;
}

int main(int argc, char* argv[]){

    put_queens_wrapper();
    printf("\n");
    return 0;
}