#include<stdlib.h>
#include<stdio.h>

int disp_rip (int *val, int *sol, int pos, int n, int k, int cnt){
    if (pos >= k){
        for (int i = 0; i < n; i++){
            printf (" %d ", sol[i]);
        }
        printf ("\n");
        return cnt+1;
    }

    for (int i = 0; i < n; i++){
        sol[pos] = val[i];
        cnt = disp_rip (val, sol, pos+1, n, k, cnt);
    }
    return cnt;
}