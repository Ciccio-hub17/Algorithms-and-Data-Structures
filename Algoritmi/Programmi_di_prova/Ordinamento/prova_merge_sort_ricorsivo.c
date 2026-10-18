#include<stdio.h>

void merge_sort(int vet[], int tmp[], int l, int r);
void merge (int vet[], int tmp[], int l, int r, int m);

int main (){
    int vet[] = {10, 3, 5, 7, 1, 11, 19, 1};
    int n = 8;
    int tmp[8];
    merge_sort(vet, tmp, 0, n-1);
    for (int i = 0; i < n; i++){
        printf (" %d ", vet[i]);
    }
}

void merge_sort(int vet[], int tmp [], int l, int r){
    if (l >= r){
        return;
    }
    int m = (l+r)/2;
    merge_sort(vet, tmp, l, m);
    merge_sort(vet, tmp, m+1, r);
    merge (vet, tmp, l, r, m);
}

void merge (int vet[], int tmp[], int l, int r, int m){
    int i = l, j = m+1, k = l;

    while (i <= m && j <= r){
        if (vet[i] <= vet[j]){
            tmp[k++] = vet[i++];
        }
        else{
            tmp[k++] = vet[j++];
        }
    }

    while (i <= m){
        tmp[k++] = vet[i++];
    }
    while (j <= r){
        tmp[k++] = vet[j++];
    }
    for (i = l; i <= r; i++){
        vet[i] = tmp[i];
    }
}