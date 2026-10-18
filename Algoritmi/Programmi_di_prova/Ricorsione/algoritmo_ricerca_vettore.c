#include<stdio.h>

int ricerca (int vet[], int l, int r, int n){
    if (l == r){
        if (n == vet[l]){
            return 1;
        }
        return 0;
    }
    int c = (l + r)/2;
    int essx = ricerca (vet, l, c, n);
    int esdx = ricerca (vet, c+1, r, n);
    if (essx || esdx){
        return 1;
    }
    return 0;

}

int main (){
    int n, result, vet[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf ("Dammi la dimensione\n");
    scanf ("%d", &n);
    result = ricerca (vet, 0, 9, n);
    printf ("%d", result);



    return 0;
}