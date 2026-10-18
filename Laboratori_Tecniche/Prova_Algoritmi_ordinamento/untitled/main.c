#include<stdio.h>
#include<string.h>
#include<string.h>

int main(void)
{
    char parola[] = "1234", carattere;
    int i=0, num, dim = 'A'-'a';
    char *p = parola;
    while (sscanf (p, "%c%n", &carattere, &i) > 0)
    {
        printf ("%c ", *p);
        p+= i;
        printf ("%d\n", carattere);
    }

    return 0;
}
