#include <stdio.h>

int main(void) {
    int n, i, xi;
    unsigned int x0 = 1, x1 = 2;

    printf ("Quanti numeri della serie vuoi stampare?\n");

    scanf (" %d", &n);

    printf ("%d\n", x0);
    printf ("%d\n", x1);

    for (i = 2; i < n; i++) {
        xi = x0 * x1;
        printf ("%d\n", xi);
        x0 = x1;
        x1 = xi;
    }

    return 0;
}