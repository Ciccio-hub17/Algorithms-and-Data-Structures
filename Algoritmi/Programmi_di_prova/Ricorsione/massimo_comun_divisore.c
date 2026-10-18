#include<stdio.h>

int maxcomdiv(int n1, int n2){
    if ((n1 % n2) == 0){
        return n2;
    }
    int r = n1%n2;
    return maxcomdiv(n2, r);
}

int main (){
    int n1 = 120, n2 = 30, result;
    result = maxcomdiv(n1, n2);
    printf ("%d", result);
    return 0;
}