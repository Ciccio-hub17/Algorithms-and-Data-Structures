#include <stdio.h>

unsigned long fibonacci (int n);

int main (){
    int n = 5, result;
    printf ("Dammi il numero della sequenza da raggiungere: ");
    scanf ("%d", &n);
    result = fibonacci (n);
    printf ("%d", result);

    return 0;
}

unsigned long fibonacci (int n){
    if (n == 0 || n == 1){
        return n;
    }
    return fibonacci(n-1) + fibonacci (n-2);
}