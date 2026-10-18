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
    float op1, op2, result, fileOp1, fileOp2;
    char operation, fileOperation;

    FILE *fp_read, *fp_write;

    if ((fp_read = fopen("operazioni.txt", "r")) == NULL) {
        printf ("Errore nell'apertura del file\n");
        return 2;
    }
    if ((fp_write = fopen("Results.txt", "w")) == NULL) {
        printf ("Errore nell'apertura del file\n");
        return 3;
    }

    while (fscanf (fp_read, " %c %f %f", &fileOperation, &fileOp1, &fileOp2) != EOF) {
        switch (fileOperation) {
            case '+':
                result = addiction (fileOp1, fileOp2);
                break;
            case '-':
                result = difference (fileOp1, fileOp2);
                break;
            case '*':
                result = multiplication (fileOp1, fileOp2);
                break;
            case '/':
                if (fileOp2 != 0) {
                    result = division (fileOp1, fileOp2);
                    break;
                }
                else {
                    printf ("Il divisore è uguale a 0, non si può fare la divisione");
                    return 4;
                }

            default:
                printf ("Scelta errata");
                return 5;
        }
        fprintf (fp_write, " %c %.3f\n", fileOperation, result);

    }


    return 0;
}