#include<stdio.h>

int power_set_comb_semp_r (int *val, int *sol, int n, int start, int j, int pos){
    int cnt = 0;
    if (start >= j){
        printf ("{ ");
        for (int i = 0; i < n; i++){
            printf (" %d ", sol[i]);
        }
        printf ("}");
        printf ("\n\n");
        return cnt+1;
    }
    for (int i = start; i < n; i++){
        sol[pos] = val [i];
        cnt += power_set_comb_semp_r (val, sol, n, i+1, pos+1, cnt);
    }
    return cnt;

}

int power_set (int *val, int *sol, int n){
    int cnt = 1;
    printf ("{ }\n");
    for (int i = 1; i <= n; i++){
        cnt += power_set_comb_semp_r (val, sol, n, i, 0, 0);
    }
    return cnt;

}