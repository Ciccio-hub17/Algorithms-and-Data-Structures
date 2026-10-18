#include<stdio.h>

int partition (int *vet, int l, int r){
    int x = vet [r], i = l, j = r-1, temp;
    for ( ; ; ){
        while (vet[i] < x){
            i++;
        }
        while (vet[j] > x){
            j--;
        }
        if (i >= j){
            break;
        }
        temp = vet[i];
        vet[i] = vet[j];
        vet[j] = temp;
    }
    temp = x;
    vet[r] = vet[i];
    vet[i] = temp;
    return i;
}

void quicksort (int *vet, int l, int r){
    if (l >= r){
        return ;
    }
    int q = partition (vet, l, r);
    quicksort (vet, l, q-1);
    quicksort (vet, q+1, r);
}

int main (){

    int n = 8, vet[8];
    for (int i = n-1; i >= 0; i--){
        vet[i] = n-i;
    }
    quicksort (vet, 0, n-1);

    for (int i = 0; i < n; i++){
        printf (" %d ", vet[i]);
    }

    printf ("\n");
    return 0;
}