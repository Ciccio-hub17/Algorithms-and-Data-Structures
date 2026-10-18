#include<stdio.h>

int comb_rip (int *val, int *sol, int pos, int start, int n, int k, int cnt){
    if (pos >= k){
        for (int i = 0; i < k; i++){
            printf (" %d ", sol[i]);
        }
        printf ("\n");
        return cnt+1;
    }
    for (int i = start; i < n; i++){
        sol[pos] = val[i];
        cnt = comb_semp (val, sol, pos+1, i, n, k, cnt);
    }
    return cnt;
}