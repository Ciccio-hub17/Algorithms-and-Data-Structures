#include <stdio.h>

int max (int vet[4], int l, int r);

int main(){
    int vet[4], i, n = 4, result;
    for (i = 0; i < n; i++){
        printf ("vet[%d] = ", i);
        scanf ("%d", &vet[i]);
    }
    result = max (vet, 0, n-1);
    printf ("Massimo: %d", result);
}

int max (int vet[4], int l, int r){
    if (l == r){
        return vet[l];
    }
    int m = (l+r)/2;
    int maxs = max (vet, l, m);
    int maxd = max (vet, m+1, r);
    if (maxs > maxd){
        return maxs;
    }
    return maxd;
}