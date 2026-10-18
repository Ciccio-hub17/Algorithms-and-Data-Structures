#include<stdio.h>
#include<string.h>

void stampa(char s[], int l, int r){

    if (l == r){
        printf ("%c", s[r]);
        return;
    }
    int c = (l+r)/2;
    stampa (s, c+1, r);
    stampa (s, l, c);
    return;
}

int main (){
    char stringa [] = "balordo";

    stampa (stringa, 0, strlen(stringa));

    return 0;
}