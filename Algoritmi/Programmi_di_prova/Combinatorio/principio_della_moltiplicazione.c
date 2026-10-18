#include<stdio.h>
#include<stdlib.h>

typedef struct { int *scelte; int n_scelte; } Livello;

int princ_molt (Livello *val, int n, int pos, int *sol, int cnt){
    if (pos >= n){
        for (int i = 0; i < n; i++){
            printf (" %d ", sol[i]);
        }
        printf ("\n");
        return cnt+1;
    }
    for (int i = 0; i < val[pos].n_scelte; i++){
        sol[pos] = val[pos].scelte[i];
        cnt = princ_molt (val, n, pos+1, sol, cnt);
    }
    return cnt;
}

int main (){

    int n = 3, sol[n];
    Livello *val = malloc (n*sizeof (Livello));

    val[0].n_scelte = 2;
    val[1].n_scelte = 3;
    val[2].n_scelte = 3;

    for (int i = 0; i < n; i++){
        val[i].scelte = malloc (val[i].n_scelte*sizeof (int));
    }

    printf ("\n");
    return 0;
}