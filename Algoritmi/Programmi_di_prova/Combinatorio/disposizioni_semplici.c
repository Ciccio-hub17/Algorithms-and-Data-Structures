#include<stdio.h>
#include<stdlib.h>

int disp_semp (int *val, int *sol, int pos, int cnt, int *mark, int n, int k){
    if (pos >= k){
        for (int i = 0; i < k; i++){
            printf (" %d ", sol[i]);
        }
        printf ("\n");
        return cnt+1;
    }
    for (int i = 0; i < n; i++){
        if (mark[i] == 0){
            sol[pos] = val[i];
            mark[i] = 1;
            cnt = disp_semp (val, sol, pos+1, cnt, mark, n, k);
            mark[i] = 0;
        }
    }
    return cnt;
}