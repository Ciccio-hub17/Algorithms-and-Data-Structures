#include<stdio.h>

int perm_rip (int *val, int *sol, int *mark, int n, int pos, int cnt, int n_dist){
    if (pos >= n){
        for (int i = 0; i < n; i++){
            printf (" %d ", sol[i]);
        }
        printf ("\n");
        return cnt+1;
    }
    for (int i = 0; i < n_dist; i++){
        if (mark[i] > 0){
            mark[i]--;
            sol[pos] = val[i];
            cnt = perm_rip (val, sol, mark, n, pos+1, cnt, n_dist);
            mark[i]++;
        }
    }
    return cnt;
}