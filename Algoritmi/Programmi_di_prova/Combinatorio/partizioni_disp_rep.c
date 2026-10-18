#include<stdio.h>
#include<stdlib.h>

void partizioni_disp_rep (int *val, int *sol, int n, int k, int pos){
    int *occ, i, j, ok = 1;
    if (pos >= n){
        occ = calloc (k, sizeof(int));
        for (j = 0; j < n; j++){
            occ[sol[j]]++;
        }

        i = 0;
        while (i < k && occ[i] != 0){
            if (!occ[i]){
                ok = 0;
            }
            i++;
        }
        free (occ);
        if (ok){
            //stampa soluzione
        }
        else{
            return;
        }
    }

    for (i = 0; i < k; i++){
        sol[pos] = i; 
        partizioni_disp_rep (val, sol, n, k, pos+1);

    }
}