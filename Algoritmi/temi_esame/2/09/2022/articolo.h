#ifndef ART_H
#define ART_H

typedef struct articolo {
    int rel;
    int slot;
    int tema;
}ARTICOLO;

typedef struct articoli *ARTICOLI;
//Programma è un adt di prima classe come la collezione di articoli
typedef struct programma *PROGRAMMA;

#endif