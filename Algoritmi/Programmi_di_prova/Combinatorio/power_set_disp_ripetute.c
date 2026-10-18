#include<stdio.h>

int power_set_disp_rip (int *val, int *sol, int n, int cnt, int pos){
    if (pos >= n){
        printf ("{ ");
        for (int i = 0; i < n; i++){
            if (sol[i] != 0){
                printf (" %d ", sol[i]);
            }
        }
        printf ("}");
        printf ("\n\n");
        return cnt+1;
    }

    sol[pos] = 0;
    cnt = power_set_disp_rip (val, sol, n, cnt, pos+1);
    sol[pos] = 1;
    cnt = power_set_disp_rip (val, sol, n, cnt, pos+1);
    return cnt;
}