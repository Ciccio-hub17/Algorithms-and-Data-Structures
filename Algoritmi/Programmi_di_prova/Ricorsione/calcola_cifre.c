#include <stdio.h>

int conta (int n){
    if (n < 10){
        return 1;
    }
    return 1 + conta (n/10);
}

int main (){

    int n, result;
    scanf ("%d", &n);
    result = conta (n);
    printf ("%d", result);
    return 0;
}