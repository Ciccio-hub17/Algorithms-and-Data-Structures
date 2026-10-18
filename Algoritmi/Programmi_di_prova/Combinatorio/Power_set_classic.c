#include<stdio.h>

int power_set_classic (int *val, int *sol, int n, int start, int pos, int cnt){
    if (start >= n){
        printf ("{ ");
        for (int i = 0; i < pos; i++){
            printf (" %d ", sol[i]);
        }
        printf ("}");
        printf ("\n\n");
        return cnt+1;
    }
    for (int i = start; i < n; i++){
        sol[pos] = val[i];
        cnt = power_set_classic (val, sol, n, i+1, pos+1, cnt);
    }
    cnt = power_set_classic (val, sol, n, n, pos, cnt);
    return cnt;
}