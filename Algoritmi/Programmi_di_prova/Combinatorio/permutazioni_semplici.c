#include<stdio.h>

int perm_semp (int *val, int *sol, int pos, int n, int cnt, int *mark){
    if (pos >= n){
        for (int i = 0; i < n; i++){
            printf (" %d ", sol[i]);
        }
        printf ("\n");
        return cnt+1;
    }
    for (int i = 0; i < n; i++){
        if (mark[i] == 0){
            sol[pos] = val[i];
            mark[i] = 1;
            cnt = perm_semp (val, sol, pos+1, n, cnt, mark);
            mark[i] = 0;
        }
    }
}