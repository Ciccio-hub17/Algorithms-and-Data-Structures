#ifndef DIPENDENTE_H
#define DIPENDENTE_H

#define MAX_S 20

typedef struct dipendente_s {
    int matricola;
    char nome[MAX_S];
    char cognome[MAX_S];
    int competenze[4];
}dipendente_t;

dipendente_t ricerca_dipendente (dipendente_t* dip, int N, int matricola);


#endif