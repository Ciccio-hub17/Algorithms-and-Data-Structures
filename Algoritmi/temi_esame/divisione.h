#ifndef DIVISIONE_H
#define DIVISIONE_H
#include "dipendente.h"

typedef struct divisione_s* divisione;

int ricerca_divisione (divisione* div, int D, char *sigla);
int ricerca_indice_libero (divisione div, int N);
void ins_dip (divisione div, int mansione, int indice_libero, dipendente_t dip);
int check_divisione (divisione div, int N);

#endif