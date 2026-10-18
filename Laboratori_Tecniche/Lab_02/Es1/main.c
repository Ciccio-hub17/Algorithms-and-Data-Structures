#include <stdio.h>

int main(void) {
    int op1, op2, rest, mcd = 0;

    printf ("Dammi due numeri interi\n");

    scanf ( "%d", &op1);
    scanf ( "%d", &op2);

    rest = op1 % op2;
    op1 = op2;
    op2 = rest;
    while (rest != 0) {
        rest = op1 % op2;
        op1 = op2;
        if (rest == 0) {
            mcd = op2;
        }
        else {
            op2 = rest;
        }
    }

    printf ("MCD = %d", mcd);

    return 0;
}