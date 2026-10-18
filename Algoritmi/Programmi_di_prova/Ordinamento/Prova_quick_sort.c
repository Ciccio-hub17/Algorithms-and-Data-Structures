#include <stdio.h>

typedef int item;

void quick_sort (item vet[], int l, int r);
int partition (item vet[], int l, int r);

int main (){

    item vet[] = {12, 4, 6, 4, 7, 9, 5};
    int N = 7; 

    quick_sort (vet, 0, N-1);
    for (int i = 0; i < N; i++){
        printf (" %d ", vet[i]);
    }
    printf ("\n");
    return 0;
}

void quick_sort (item vet[], int l, int r){
    if (l >= r){
        return;
    }
    int q = partition (vet, l, r);
    quick_sort (vet, l, q-1);
    quick_sort (vet, q+1, r);
    return;
}

int partition (item vet[], int l, int r){
    int i = l-1, j = r;
    item x = vet[r], tmp;
    for ( ; ; ){
        while (vet[++i] < x);
        while (vet[--j] > x);
        if (i >= j){
            break;
        }
        tmp = vet[i];
        vet[i] = vet[j];
        vet[j] = tmp;
    }
    tmp = vet[r];
    vet[r] = vet[i];
    vet[i] = tmp;
    return i;
}