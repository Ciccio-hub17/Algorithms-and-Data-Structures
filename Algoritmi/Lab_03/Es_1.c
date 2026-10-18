#include<stdio.h>

int majority (int *a, int N);
int majority_ric (int *a, int l, int r);

int main (){

    int N = 3, result;
    int vet[] = {3, 1, 2};
    //int vet[] = {0, 1, 0, 2, 3, 4, 0, 5};

    result = majority (vet, N);
    if (result == -1){
        printf ("Non esiste elemento maggioritario\n");
    }
    else{
        printf ("L'elemento maggioritario e' %d\n", result);
    }

    printf ("\n");
    return 0;
}

int majority (int *a, int N){
    int result;
    return result = majority_ric (a, 0, N-1);
}

int majority_ric (int *a, int l, int r){
    if (l >= r){
        return a[l];
    }

    int c = (l+r)/2, rsx, rdx;
    rsx = majority_ric (a, l, c);
    rdx = majority_ric (a, c+1, r);

    if (rsx == rdx) {
        return rsx;
    }

    int countsx = 1, countdx = 1;
    for (int i = l+1, j = c+2; i <= c && j <= r; i++, j++){
        if (a[i] == rsx){
            countsx++;
        }
        if (a[i] == rdx){
            countdx++;
        }
    }
    if (countsx > countdx && countsx > (r+1)/2){
        return rsx;
    }
    else if (countdx > countsx && countdx > (r+1)/2){
        return rdx;
    }

    return -1;
}
