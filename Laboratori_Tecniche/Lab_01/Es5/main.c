#include <stdio.h>

float addiction (float op1, float op2) {
    return op1 + op2;
}

float difference (float op1, float op2) {
    return op1 - op2;
}

float multiplication (float op1, float op2) {
    return op1 * op2;
}

float division (float op1, float op2) {
    return op1 / op2;
}

int main(void) {
    float op1, op2, result;
    char operation;

    printf ("Dammi l'operazione:");
    operation = getchar ();
    getchar ();
    printf ("Dammi i due valori:");
    scanf ("%f", &op1);
    getchar ();
    scanf ("%f", &op2);
    if (operation == '+') {
        result = addiction (op1, op2);
        printf ("%c %.3f", operation, result);
    }
    else if (operation == '-') {
        result = difference (op1, op2);
        printf ("%c %.3f", operation, result);
    }
    else if (operation == '*') {
        result = multiplication (op1, op2);
        printf ("%c %.3f", operation, result);
    }
    else if (operation == '/') {
        while (op2 == 0) {
            printf ("IL divisore è uguale a 0, cambialo\n");
            scanf ("%f", &op2);
        }
        result = division (op1, op2);
        printf ("%c %.3f", operation, result);
    }
    else {
        return 2;
    }

    return 0;
}