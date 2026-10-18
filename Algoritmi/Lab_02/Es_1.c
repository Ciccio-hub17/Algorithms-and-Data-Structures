#include<stdio.h>

int gcd (int a, int b);

int main (){
    //mi faccio dare i numeri in input
    int a, b, tmp;
    printf ("Dammi il primo e il secondo numero\n");
    scanf ("%d", &a);
    scanf ("%d", &b);
    
    //li scambio se b > a
    if (b > a){
        tmp = b;
        b = a;
        a = tmp;
    }

    //chiamo la funzione ricorsiva
    int result = gcd (a,b);

    //stampo il risultato
    printf ("Il massimo comune divisore tra %d e %d e' %d", a, b, result);
    return 0;
}

int gcd (int a, int b){
    int tmp;
    //li scambio se b > a
    if (b > a){
        tmp = b;
        b = a;
        a = tmp;
    }

    //se a è divisibile per b allora ho finito e torno b che tanto p sempre il più piccolo
    if ((a % b) == 0){
        return b;
    }

    //una serie di if per capire cosa passare alla funzione ricorsiva
    if ((a % 2) == 0 && (b % 2) == 0){
        return 2* gcd (a/2, b/2);
    }
    else if ((a%2)!= 0 && (b%2) == 0){
        return gcd (a, b/2);
    }
    else if ((a%2)== 0 && (b%2) != 0){
        return gcd (a/2, b);
    }
    else{
        gcd ((a-b)/2, b);
    }
}  