#include <stdio.h>
#define P 3.14

int main(void) {
    float areaSquare, diagonal, lato, diameter, areaCircle, rate;
    char choiceArea, choiceMeasure;

    printf ("Vuoi calcolare l'area di un cerchio (C) o di un quadrato (Q)?");
    scanf ("%c", &choiceArea);
    if (choiceArea == 'Q') {
        printf("Vuoi darmi la misura del lato (L) o della diagonale(D)?");
        getchar ();
        scanf (" %c", &choiceMeasure);
        if (choiceMeasure == 'L') {
            printf ("Dammi la misura del lato:");
            getchar ();
            scanf("%f", &lato);
            areaSquare = lato * lato;
            printf("Area quadrato = %.3f", areaSquare);
        }
        else {
            printf ("Dammi la misura della diagonale:");
            getchar ();
            scanf("%f", &diagonal);
            areaSquare = diagonal * diagonal / 2;
            printf("Area quadrato = %.3f", areaSquare);
        }
    }
    else {
        printf("Vuoi darmi la miura del diametro (D) o del raggio(R)?");
        getchar ();
        scanf (" %c", &choiceMeasure);
        if (choiceMeasure == 'D') {
            printf ("Dammi la misura del diametro:");
            getchar ();
            scanf("%f", &diameter);
            areaCircle = P * diameter * diameter / 4;
            printf("Area cerchio = %.3f", areaCircle);
        }
        else {
            printf ("Dammi la misura del raggio:");
            getchar ();
            scanf("%f", &rate);
            areaCircle = P * rate * rate;
            printf("Area cerchio = %.3f", areaCircle);
        }
    }

    return 0;
}